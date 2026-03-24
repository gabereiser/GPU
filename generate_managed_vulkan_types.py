from __future__ import annotations

import re
import shutil
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent
VK_XML = ROOT / "dependencies" / "Vulkan-Headers" / "registry" / "vk.xml"
MANAGED = ROOT / "Managed"
GENERATED = MANAGED / "Vulkan" / "Generated"


TYPE_DECL_RE = re.compile(
    r"public\s+(?:(?:readonly|partial|sealed|static|abstract|unsafe)\s+)*(?:struct|enum|class|interface)\s+([A-Za-z_][A-Za-z0-9_]*)"
)
DELEGATE_DECL_RE = re.compile(
    r"public\s+(?:(?:readonly|partial|sealed|static|abstract|unsafe)\s+)*delegate\s+[^(\r\n;]+\s+([A-Za-z_][A-Za-z0-9_]*)\s*\("
)
CS_IDENTIFIER_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")

PRIMITIVE_MAP = {
    "void": "void",
    "char": "byte",
    "float": "float",
    "double": "double",
    "size_t": "nuint",
    "uint8_t": "byte",
    "int8_t": "sbyte",
    "uint16_t": "ushort",
    "int16_t": "short",
    "uint32_t": "uint",
    "int32_t": "int",
    "uint64_t": "ulong",
    "int64_t": "long",
    "uintptr_t": "nuint",
    "intptr_t": "nint",
    "int": "int",
}

CSharp_KEYWORDS = {
    "event",
    "object",
    "string",
    "fixed",
    "base",
    "lock",
    "params",
    "ref",
    "out",
    "in",
}


@dataclass
class Member:
    cs_type: str
    name: str
    is_pointer: bool
    is_array: bool
    array_length: int | None = None
    pointee_type: str | None = None
    length_expr: str | None = None


def pascal_from_constant_suffix(suffix: str) -> str:
    parts = [part for part in suffix.split("_") if part]
    if not parts:
        return "Value0"

    words: list[str] = []
    for part in parts:
        lower = part.lower()
        if part.isdigit():
            words.append(part)
            continue
        if re.fullmatch(r"[0-9]+[a-zA-Z]+", part):
            words.append(part.upper())
            continue
        if re.fullmatch(r"[a-zA-Z]+[0-9]+", part):
            words.append(part[0].upper() + part[1:])
            continue
        words.append(lower.capitalize())

    name = "".join(words)
    if name[0].isdigit():
        name = "Value" + name
    return name.replace("Bit", "Bit").replace("KHR", "KHR").replace("EXT", "EXT")


def map_vk_name(name: str) -> str:
    if name.startswith("PFN_vk"):
        return "PFN_gpu" + name[len("PFN_vk") :]
    if name.startswith("Vk"):
        return name[len("Vk") :]
    return name


def type_name_to_constant_prefix(type_name: str) -> str:
    base = type_name[2:] if type_name.startswith("Vk") else type_name
    snake = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", base).upper()
    return f"VK_{snake}_"


def sanitize_identifier(name: str) -> str:
    if not name:
        return "Value"
    name = name[0].upper() + name[1:]
    if name.startswith("Pp"):
        name = "PP" + name[2:]
    elif name.startswith("p") and len(name) > 1 and name[1].isupper():
        name = "P" + name[1:]
    elif name.startswith("sType"):
        name = "SType"
    elif name.startswith("pNext"):
        name = "PNext"
    if name.lower() in CSharp_KEYWORDS:
        return "@" + name
    return name


def is_valid_type_identifier(name: str) -> bool:
    return bool(CS_IDENTIFIER_RE.fullmatch(name))


def escape_csharp_string(value: str) -> str:
    return value.replace("\\", "\\\\").replace('"', '\\"')


def load_existing_manual_types() -> set[str]:
    types: set[str] = set()
    for path in MANAGED.rglob("*.cs"):
        if GENERATED in path.parents:
            continue
        text = path.read_text(encoding="utf-8")
        for match in TYPE_DECL_RE.finditer(text):
            types.add(match.group(1))
        for match in DELEGATE_DECL_RE.finditer(text):
            types.add(match.group(1))
    return types


def load_known_xml_type_names(root: ET.Element) -> set[str]:
    known: set[str] = set()
    for type_element in root.findall("./types/type"):
        name = type_element.get("name") or (type_element.findtext("name") or "").strip()
        if name:
            known.add(name)

    for enums in root.findall("./enums"):
        name = enums.get("name")
        kind = enums.get("type")
        if name and kind in {"enum", "bitmask"}:
            known.add(name)

    return known


def load_constant_int_values(root: ET.Element) -> dict[str, int]:
    values: dict[str, int] = {}
    for enums in root.findall("./enums"):
        for enum in enums.findall("enum"):
            name = enum.get("name")
            value = enum.get("value")
            if not name or value is None:
                continue
            text = value.strip()
            if text.startswith('"') or text.startswith("'"):
                continue
            text = text.replace("ULL", "").replace("UL", "").replace("U", "")
            try:
                values[name] = int(text, 0)
            except ValueError:
                continue
    return values


def enum_base_type_name(root: ET.Element, enum_name: str) -> str:
    for type_element in root.findall("./types/type"):
        name = type_element.get("name") or (type_element.findtext("name") or "").strip()
        if name != enum_name:
            continue
        if type_element.get("category") == "bitmask":
            underlying = type_element.findtext("type") or "VkFlags"
            if underlying == "VkFlags64":
                return "ulong"
            return "uint"
    return "int"


def parse_numeric_value(value: str, enum_type: str) -> str:
    suffix = "UL" if enum_type == "ulong" else "U" if enum_type == "uint" else ""
    value = value.replace("ULL", "").replace("UL", "").replace("U", "")
    if value.startswith("~"):
        return value
    if value.endswith("F") or value.endswith("f"):
        value = value[:-1]
    return f"{value}{suffix}" if suffix and value.isdigit() else value


def extension_enum_value(enum: ET.Element, enum_type: str) -> str:
    if "bitpos" in enum.attrib:
        shift = int(enum.attrib["bitpos"])
        if enum_type == "ulong":
            return f"(1UL << {shift})"
        return f"(1U << {shift})"

    if "value" in enum.attrib:
        return parse_numeric_value(enum.attrib["value"], enum_type)

    if "alias" in enum.attrib:
        return enum.attrib["alias"]

    if "offset" not in enum.attrib or "extnumber" not in enum.attrib:
        return "0"

    extnumber = int(enum.attrib["extnumber"])
    offset = int(enum.attrib["offset"])
    base = 1_000_000_000 + (extnumber - 1) * 1000 + offset
    if enum.attrib.get("dir") == "-":
        base = -base
    suffix = "UL" if enum_type == "ulong" else "U" if enum_type == "uint" and base >= 0 else ""
    return f"{base}{suffix}"


def gather_enum_members(root: ET.Element) -> dict[str, list[tuple[str, str]]]:
    members: dict[str, list[tuple[str, str]]] = {}
    value_by_source_name: dict[str, str] = {}

    for enums in root.findall("./enums"):
        enum_name = enums.get("name")
        enum_kind = enums.get("type")
        if enum_kind not in {"enum", "bitmask"} or not enum_name:
            continue

        enum_type = enum_base_type_name(root, enum_name)
        prefix = type_name_to_constant_prefix(enum_name)
        rows: list[tuple[str, str]] = []
        used_names: set[str] = set()
        for enum in enums.findall("enum"):
            source_name = enum.get("name")
            if not source_name:
                continue
            if enum.get("alias"):
                alias_target = enum.get("alias") or ""
                alias_value = value_by_source_name.get(alias_target)
                if alias_value is None:
                    continue
                alias_suffix = source_name.removeprefix(prefix).removeprefix("VK_")
                member_name = pascal_from_constant_suffix(alias_suffix)
                if member_name in used_names:
                    member_name += "Alias"
                used_names.add(member_name)
                rows.append((member_name, alias_value))
                value_by_source_name[source_name] = alias_value
                continue

            if "value" not in enum.attrib and "bitpos" not in enum.attrib:
                continue

            suffix = source_name.removeprefix(prefix).removeprefix("VK_")
            member_name = pascal_from_constant_suffix(suffix)
            while member_name in used_names:
                member_name += "Value"
            used_names.add(member_name)
            value = (
                parse_numeric_value(enum.attrib["value"], enum_type)
                if "value" in enum.attrib
                else extension_enum_value(enum, enum_type)
            )
            rows.append((member_name, value))
            value_by_source_name[source_name] = value
        members[enum_name] = rows

    for extension in root.findall("./extensions/extension"):
        for require in extension.findall("require"):
            for enum in require.findall("enum"):
                extends = enum.get("extends")
                if not extends or extends not in members:
                    continue
                enum_type = enum_base_type_name(root, extends)
                source_name = enum.get("name")
                if not source_name:
                    continue
                prefix = type_name_to_constant_prefix(extends)
                suffix = source_name.removeprefix(prefix).removeprefix("VK_")
                member_name = pascal_from_constant_suffix(suffix)

                existing_names = {name for name, _ in members[extends]}
                while member_name in existing_names:
                    member_name += "Ext"

                if enum.get("alias"):
                    alias = enum.get("alias") or ""
                    alias_value = value_by_source_name.get(alias)
                    if alias_value is None:
                        continue
                    members[extends].append((member_name, alias_value))
                    value_by_source_name[source_name] = alias_value
                    continue

                if (
                    "offset" not in enum.attrib
                    and "bitpos" not in enum.attrib
                    and "value" not in enum.attrib
                ):
                    continue
                value = extension_enum_value(enum, enum_type)
                members[extends].append((member_name, value))
                value_by_source_name[source_name] = value

    for key in members:
        deduped: list[tuple[str, str]] = []
        seen: set[str] = set()
        for name, value in members[key]:
            if name in seen:
                continue
            seen.add(name)
            deduped.append((name, value))
        members[key] = deduped

    return members


def map_type(
    type_name: str,
    is_pointer: bool,
    handle_names: set[str],
    known_type_names: set[str],
) -> str:
    if is_pointer:
        return "nint"
    if type_name in PRIMITIVE_MAP:
        return PRIMITIVE_MAP[type_name]
    if type_name in handle_names:
        return "nuint"
    if type_name.startswith("Vk") and type_name in known_type_names:
        return map_vk_name(type_name)
    if type_name.startswith("PFN_vk") and type_name in known_type_names:
        return map_vk_name(type_name)
    if type_name.startswith("PFN_") and type_name in known_type_names:
        return map_vk_name(type_name)
    if type_name in {"ANativeWindow", "AHardwareBuffer", "CAMetalLayer", "IOSurfaceRef"}:
        return map_vk_name(type_name)
    if (
        type_name in known_type_names
        and is_valid_type_identifier(type_name)
        and type_name not in PRIMITIVE_MAP
        and not type_name.startswith("VK_")
        and type_name != "vk_platform"
    ):
        return map_vk_name(type_name)
    return "nint"


def parse_member(
    member: ET.Element,
    handle_names: set[str],
    known_type_names: set[str],
    constant_values: dict[str, int],
) -> Member:
    raw = "".join(member.itertext()).strip()
    type_name = member.findtext("type") or "void"
    name = member.findtext("name") or "Value"
    type_tail = member.find("type").tail if member.find("type") is not None else ""
    name_tail = member.find("name").tail if member.find("name") is not None else ""
    is_pointer = "*" in (type_tail or "") or "*" in (member.text or "")
    is_array = "[" in (name_tail or "") or ":" in raw
    array_length: int | None = None
    cs_type = map_type(type_name, is_pointer, handle_names, known_type_names)
    pointee_type = None
    length_expr = member.get("len")

    if is_pointer:
        pointee_type = map_type(type_name, False, handle_names, known_type_names)

    if "[" in (name_tail or "") or "[" in raw:
        match = re.search(rf"{re.escape(name)}\s*\[([^\]]+)\]", raw)
        if match is None:
            match = re.search(r"\[([^\]]+)\]", raw)
        if match:
            token = match.group(1).strip()
            if token.isdigit():
                array_length = int(token)
            elif token in constant_values:
                array_length = constant_values[token]
        if array_length is None or is_pointer:
            cs_type = "nint"
        elif type_name == "char":
            cs_type = "byte"
    elif ":" in raw:
        cs_type = "nint"

    return Member(
        cs_type=cs_type,
        name=sanitize_identifier(name),
        is_pointer=is_pointer,
        is_array=is_array,
        array_length=array_length,
        pointee_type=pointee_type,
        length_expr=length_expr,
    )


def render_enum_block(name: str, base_type: str, members: list[tuple[str, str]]) -> str:
    lines = [f"public enum {map_vk_name(name)} : {base_type}", "{"]
    if not members:
        lines.append("    None = 0,")
    else:
        for member_name, value in members:
            lines.append(f"    {member_name} = {value},")
    lines.append("}")
    return "\n".join(lines)


def render_stub_enum_block(name: str, base_type: str = "int") -> str:
    return "\n".join(
        [
            f"public enum {map_vk_name(name)} : {base_type}",
            "{",
            "    None = 0,",
            "}",
        ]
    )


def render_flags_block(name: str, base_type: str, members: list[tuple[str, str]]) -> str:
    lines = ["[System.Flags]", f"public enum {map_vk_name(name)} : {base_type}", "{"]
    if all(member_name != "None" for member_name, _ in members):
        lines.append("    None = 0,")
    for member_name, value in members:
        lines.append(f"    {member_name} = {value},")
    lines.append("}")
    return "\n".join(lines)


def render_basetype_block(name: str, underlying: str) -> str:
    mapped = map_vk_name(name)
    return "\n".join(
        [
            f"public readonly struct {mapped}",
            "{",
            f"    public {mapped}({underlying} value) => Value = value;",
            "",
            f"    public {underlying} Value {{ get; }}",
            "}",
        ]
    )


def render_delegate_block(type_element: ET.Element, handle_names: set[str]) -> str:
    name = type_element.findtext("name") or ""
    mapped_name = map_vk_name(name)
    text = "".join(type_element.itertext())
    before_name, after_name = text.split(name, 1)
    return_text = before_name.replace("typedef", "").replace("(VKAPI_PTR *", "").strip()
    return_type = return_text.split()[-1]
    signature = after_name[after_name.find("(") + 1 : after_name.rfind(")")]
    params = []
    if signature.strip() != "void":
        for raw_param in [p.strip() for p in signature.split(",") if p.strip()]:
            tokens = raw_param.split()
            param_name = tokens[-1]
            if param_name.startswith("*"):
                param_name = param_name[1:]
            param_name = sanitize_identifier(param_name)
            param_type_match = re.search(r"(PFN_vk[A-Za-z0-9_]+|Vk[A-Za-z0-9_]+|[A-Za-z_][A-Za-z0-9_]*)", raw_param)
            param_type = param_type_match.group(1) if param_type_match else "void"
            is_pointer = "*" in raw_param or "[" in raw_param
            known_type_names = set()
            cs_type = map_type(param_type, is_pointer and param_type != "char", handle_names, known_type_names)
            if param_type == "char" and "*" in raw_param:
                cs_type = "nint"
            params.append(f"{cs_type} {param_name}")

    cs_return = map_type(return_type, "*" in return_text, handle_names, set())
    if return_type == "void" and "*" in return_text:
        cs_return = "nint"
    if cs_return == "void" and "*" in return_text:
        cs_return = "nint"

    param_list = ",\n    ".join(params)
    if param_list:
        return "\n".join(
            [
                f"public unsafe delegate {cs_return} {mapped_name}(",
                f"    {param_list});",
            ]
        )
    return f"public unsafe delegate {cs_return} {mapped_name}();"


def render_struct_block(name: str, members: list[Member]) -> str:
    lines = ["[StructLayout(LayoutKind.Sequential)]", f"public struct {map_vk_name(name)}", "{"]
    if not members:
        lines.append("    public uint _dummy;")
    else:
        used: set[str] = set()
        for member in members:
            field_name = member.name
            while field_name in used:
                field_name += "_"
            used.add(field_name)
            if member.array_length is not None:
                lines.append(f"    [FixedCount({member.array_length})]")
                lines.append(
                    f"    [MarshalAs(UnmanagedType.ByValArray, SizeConst = {member.array_length})]"
                )
                lines.append(f"    public {member.cs_type}[] {field_name};")
                continue
            if member.is_pointer:
                pointee_expr = (
                    f"typeof({member.pointee_type})"
                    if member.pointee_type and member.pointee_type != "void"
                    else "null"
                )
                if member.length_expr:
                    escaped = escape_csharp_string(member.length_expr)
                    lines.append(
                        f'    [NativePointer({pointee_expr}, LengthExpression = "{escaped}")]'
                    )
                else:
                    lines.append(f"    [NativePointer({pointee_expr})]")
            lines.append(f"    public {member.cs_type} {field_name};")
    lines.append("}")
    return "\n".join(lines)


def render_union_block(name: str, members: list[Member]) -> str:
    lines = ["[StructLayout(LayoutKind.Explicit)]", f"public struct {map_vk_name(name)}", "{"]
    if not members:
        lines.append("    [FieldOffset(0)] public uint _dummy;")
    else:
        used: set[str] = set()
        for member in members:
            field_name = member.name
            while field_name in used:
                field_name += "_"
            used.add(field_name)
            lines.append(f"    [FieldOffset(0)] public {member.cs_type} {field_name};")
    lines.append("}")
    return "\n".join(lines)


def write_file(path: Path, body: str, uses_runtime: bool = False) -> None:
    lines = ["// Generated by generate_managed_vulkan_types.py. Do not edit by hand."]
    if uses_runtime:
        lines.append("using System.Runtime.InteropServices;")
        lines.append("")
    lines.append("namespace GPU;")
    lines.append("")
    lines.append(body.strip() if body.strip() else "// No generated declarations.")
    lines.append("")
    path.write_text("\n".join(lines), encoding="utf-8")


def main() -> int:
    tree = ET.parse(VK_XML)
    root = tree.getroot()
    existing = load_existing_manual_types()
    known_type_names = load_known_xml_type_names(root)
    constant_values = load_constant_int_values(root)

    if GENERATED.exists():
        shutil.rmtree(GENERATED)
    GENERATED.mkdir(parents=True, exist_ok=True)

    handle_names = {
        (t.get("name") or (t.findtext("name") or "").strip())
        for t in root.findall("./types/type")
        if t.get("category") == "handle"
    }
    known_type_names.update(handle_names)

    enum_members = gather_enum_members(root)
    emitted_enum_names: set[str] = set()

    enum_blocks: list[str] = []
    flag_blocks: list[str] = []
    basetype_blocks: list[str] = []
    func_blocks: list[str] = []
    struct_blocks: list[str] = []
    union_blocks: list[str] = []
    emitted_type_names: set[str] = set(existing)

    for enums in root.findall("./enums"):
        name = enums.get("name")
        kind = enums.get("type")
        if not name or kind not in {"enum", "bitmask"}:
            continue
        mapped = map_vk_name(name)
        if mapped in emitted_type_names:
            continue
        base_type = enum_base_type_name(root, name)
        members = enum_members.get(name, [])
        if kind == "enum":
            enum_blocks.append(render_enum_block(name, base_type, members))
            emitted_enum_names.add(mapped)
            emitted_type_names.add(mapped)

    for type_element in root.findall("./types/type"):
        category = type_element.get("category")
        name = type_element.get("name") or (type_element.findtext("name") or "").strip()
        if not name:
            continue
        mapped = map_vk_name(name)
        if mapped in emitted_type_names:
            continue

        if category == "basetype":
            c_type = type_element.findtext("type") or "nint"
            underlying = PRIMITIVE_MAP.get(c_type, map_type(c_type, False, handle_names, known_type_names))
            basetype_blocks.append(render_basetype_block(name, underlying))
            emitted_type_names.add(mapped)
        elif category == "bitmask":
            underlying = type_element.findtext("type") or "VkFlags"
            base_type = "ulong" if underlying == "VkFlags64" else "uint"
            source_bits = type_element.get("bitvalues") or type_element.get("requires") or ""
            members = enum_members.get(source_bits, [])
            flag_blocks.append(render_flags_block(name, base_type, members))
            emitted_type_names.add(mapped)
        elif category == "funcpointer":
            func_blocks.append(render_delegate_block(type_element, handle_names))
            emitted_type_names.add(mapped)
        elif category == "struct":
            members = [
                parse_member(m, handle_names, known_type_names, constant_values)
                for m in type_element.findall("member")
            ]
            struct_blocks.append(render_struct_block(name, members))
            emitted_type_names.add(mapped)
        elif category == "union":
            members = [
                parse_member(m, handle_names, known_type_names, constant_values)
                for m in type_element.findall("member")
            ]
            union_blocks.append(render_union_block(name, members))
            emitted_type_names.add(mapped)

    # Some platform and auxiliary types are not marked with category in vk.xml.
    # Emit named wrappers for them so generated structs keep more semantic shape
    # than a blanket nint field type.
    for type_element in root.findall("./types/type"):
        category = type_element.get("category")
        name = type_element.get("name") or (type_element.findtext("name") or "").strip()
        if not name:
            continue
        if not is_valid_type_identifier(name):
            continue
        if name in PRIMITIVE_MAP:
            continue
        if name.startswith("VK_"):
            continue
        if name in {"vk_platform"}:
            continue
        mapped = map_vk_name(name)
        if mapped in emitted_type_names:
            continue
        if category in {"handle", "struct", "union", "bitmask", "enum", "funcpointer", "basetype"}:
            continue
        basetype_blocks.append(render_basetype_block(name, "nint"))
        emitted_type_names.add(mapped)

    # Some platform basetypes are not declared as <types/type> entries in a way that
    # survives the generic pass above but are still part of the broader API surface.
    extra_basetypes = [
        "AHardwareBuffer",
        "ANativeWindow",
        "CAMetalLayer",
        "IOSurfaceRef",
        "MTLBuffer_id",
        "MTLCommandQueue_id",
        "MTLDevice_id",
        "MTLSharedEvent_id",
        "MTLTexture_id",
        "OHBufferHandle",
        "OHNativeWindow",
        "OH_NativeBuffer",
    ]
    for name in extra_basetypes:
        mapped = map_vk_name(name)
        if mapped in emitted_type_names:
            continue
        basetype_blocks.append(render_basetype_block(name, "nint"))
        emitted_type_names.add(mapped)

    for type_element in root.findall("./types/type"):
        if type_element.get("category") != "enum":
            continue
        name = type_element.get("name") or (type_element.findtext("name") or "").strip()
        if not name:
            continue
        mapped = map_vk_name(name)
        if mapped in emitted_type_names or mapped in emitted_enum_names:
            continue
        enum_blocks.append(render_stub_enum_block(name))
        emitted_enum_names.add(mapped)
        emitted_type_names.add(mapped)

    write_file(GENERATED / "Enums.Generated.cs", "\n\n".join(enum_blocks))
    write_file(GENERATED / "Flags.Generated.cs", "\n\n".join(flag_blocks))
    write_file(GENERATED / "Basetypes.Generated.cs", "\n\n".join(basetype_blocks))
    write_file(GENERATED / "FunctionPointers.Generated.cs", "\n\n".join(func_blocks))
    write_file(GENERATED / "Structs.Generated.cs", "\n\n".join(struct_blocks), uses_runtime=True)
    write_file(GENERATED / "Unions.Generated.cs", "\n\n".join(union_blocks), uses_runtime=True)

    print(f"Wrote generated Vulkan managed types to {GENERATED}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
