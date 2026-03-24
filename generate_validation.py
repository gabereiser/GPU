from __future__ import annotations

import re
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent
VK_XML = ROOT / "dependencies" / "Vulkan-Headers" / "registry" / "vk.xml"
OUTPUT = ROOT / "VALIDATION.md"
MANAGED = ROOT / "Managed"
GPU_HEADER = ROOT / "include" / "gpu" / "gpu.h"
GPU_VULKAN_HEADER = ROOT / "include" / "gpu" / "gpu_vulkan.h"


SECTION_ORDER = [
    ("Objects", "handle"),
    ("Structs", "struct"),
    ("Unions", "union"),
    ("Enums", "enum"),
    ("Flags", "bitmask"),
    ("Types", "basetype"),
    ("Function Pointer Types", "funcpointer"),
    ("Commands", "command"),
    ("Constants", "constant"),
]


TYPE_DECL_RE = re.compile(
    r"public\s+(?:(?:readonly|partial|sealed|static|abstract|unsafe)\s+)*(?:struct|enum|class|interface)\s+([A-Za-z_][A-Za-z0-9_]*)"
)
DELEGATE_DECL_RE = re.compile(
    r"public\s+(?:(?:readonly|partial|sealed|static|abstract|unsafe)\s+)*delegate\s+[^(\r\n;]+\s+([A-Za-z_][A-Za-z0-9_]*)\s*\("
)


@dataclass(frozen=True)
class ValidationRow:
    source: str
    target: str
    managed_status: str
    native_status: str


def map_name(name: str) -> str:
    if name.startswith("PFN_vk"):
        return "PFN_gpu" + name[len("PFN_vk") :]
    if name.startswith("vk"):
        return "gpu" + name[len("vk") :]
    if name.startswith("Vk"):
        return name[len("Vk") :]
    if name.startswith("VK_"):
        return "GPU_" + name[len("VK_") :]
    return name


def load_managed_types() -> set[str]:
    managed_types: set[str] = set()
    for path in MANAGED.rglob("*.cs"):
        text = path.read_text(encoding="utf-8")
        for match in TYPE_DECL_RE.finditer(text):
            managed_types.add(match.group(1))
        for match in DELEGATE_DECL_RE.finditer(text):
            managed_types.add(match.group(1))
    return managed_types


def load_native_text() -> str:
    parts: list[str] = []
    if GPU_HEADER.exists():
        parts.append(GPU_HEADER.read_text(encoding="utf-8"))
    if GPU_VULKAN_HEADER.exists():
        parts.append(GPU_VULKAN_HEADER.read_text(encoding="utf-8"))
    return "\n".join(parts)


def native_status_for(name: str, mapped: str, native_text: str, category: str) -> str:
    if category == "command":
        return "present" if name in native_text else "missing"

    if category == "constant":
        return "present" if name in native_text else "missing"

    if category == "handle":
        handle_name = f"{mapped}Handle"
        gpu_type_name = f"GPU{mapped}"
        gpu_symbol = f"gpu{mapped}"
        if handle_name in native_text or gpu_type_name in native_text or gpu_symbol in native_text:
            return "present"
        return "missing"

    if name in native_text or mapped in native_text:
        return "present"

    return "missing"


def managed_status_for(mapped: str, managed_types: set[str], category: str) -> str:
    if category == "command":
        return "out_of_scope"

    if category == "constant":
        return "out_of_scope"

    if category == "handle":
        if mapped in managed_types:
            return "present"
        if f"{mapped}Handle" in managed_types:
            return "handle_only"
        return "missing"

    return "present" if mapped in managed_types else "missing"


def collect_type_rows(
    root: ET.Element, managed_types: set[str], native_text: str
) -> dict[str, list[ValidationRow]]:
    buckets: dict[str, list[ValidationRow]] = {
        "handle": [],
        "struct": [],
        "union": [],
        "enum": [],
        "bitmask": [],
        "basetype": [],
        "funcpointer": [],
    }

    for type_element in root.findall("./types/type"):
        category = type_element.get("category")
        if category not in buckets:
            continue

        name = type_element.get("name")
        if not name:
            name_node = type_element.find("name")
            if name_node is not None and name_node.text:
                name = name_node.text.strip()

        if not name:
            continue

        mapped = map_name(name)
        buckets[category].append(
            ValidationRow(
                source=name,
                target=mapped,
                managed_status=managed_status_for(mapped, managed_types, category),
                native_status=native_status_for(name, mapped, native_text, category),
            )
        )

    for key in buckets:
        buckets[key].sort(key=lambda row: row.source)

    return buckets


def collect_command_rows(root: ET.Element, native_text: str) -> list[ValidationRow]:
    rows: list[ValidationRow] = []
    for command in root.findall("./commands/command"):
        name_node = command.find("proto/name")
        if name_node is None or not name_node.text:
            continue
        name = name_node.text.strip()
        mapped = map_name(name)
        rows.append(
            ValidationRow(
                source=name,
                target=mapped,
                managed_status="out_of_scope",
                native_status=native_status_for(name, mapped, native_text, "command"),
            )
        )
    rows.sort(key=lambda row: row.source)
    return rows


def collect_constant_rows(root: ET.Element, native_text: str) -> list[ValidationRow]:
    rows: list[ValidationRow] = []
    seen: set[str] = set()
    for enums in root.findall("./enums"):
        for enum in enums.findall("enum"):
            name = enum.get("name")
            if not name or name in seen:
                continue
            seen.add(name)
            mapped = map_name(name)
            rows.append(
                ValidationRow(
                    source=name,
                    target=mapped,
                    managed_status="out_of_scope",
                    native_status=native_status_for(name, mapped, native_text, "constant"),
                )
            )
    rows.sort(key=lambda row: row.source)
    return rows


def summarize(rows: list[ValidationRow]) -> str:
    managed_counts: dict[str, int] = {}
    native_counts: dict[str, int] = {}

    for row in rows:
        managed_counts[row.managed_status] = managed_counts.get(row.managed_status, 0) + 1
        native_counts[row.native_status] = native_counts.get(row.native_status, 0) + 1

    managed_summary = ", ".join(
        f"{key}={managed_counts[key]}" for key in sorted(managed_counts)
    )
    native_summary = ", ".join(
        f"{key}={native_counts[key]}" for key in sorted(native_counts)
    )
    return f"Managed: {managed_summary or 'none'} | Native: {native_summary or 'none'}"


def render_section(title: str, rows: list[ValidationRow]) -> list[str]:
    lines = [f"## {title}", "", summarize(rows), ""]
    for row in rows:
        lines.append(
            f"- `{row.source}` -> `GPU.{row.target}` | Managed: `{row.managed_status}` | Native: `{row.native_status}`"
        )
    lines.append("")
    return lines


def main() -> int:
    tree = ET.parse(VK_XML)
    root = tree.getroot()

    managed_types = load_managed_types()
    native_text = load_native_text()

    type_buckets = collect_type_rows(root, managed_types, native_text)
    command_rows = collect_command_rows(root, native_text)
    constant_rows = collect_constant_rows(root, native_text)

    lines = [
        "# Validation",
        "",
        "Vulkan-to-GPU validation generated from `vk.xml`.",
        "",
        "This file is the contract check for one `GPU` world view: every Vulkan object, struct, type, enum, flag, function pointer, command, and constant is listed with its expected `GPU` name and whether the current repo actually exposes that shape.",
        "",
        "Status meanings:",
        "- `present`: the expected shape exists in the current repo",
        "- `handle_only`: the managed side only has the handle wrapper, not the full object/type name",
        "- `missing`: the expected shape is not present",
        "- `out_of_scope`: not represented as a managed public type in the current design",
        "",
    ]

    for title, key in SECTION_ORDER:
        if key == "command":
            rows = command_rows
        elif key == "constant":
            rows = constant_rows
        else:
            rows = type_buckets[key]
        lines.extend(render_section(title, rows))

    OUTPUT.write_text("\n".join(lines), encoding="utf-8")
    print(f"Wrote {OUTPUT}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
