from __future__ import annotations

import sys
import xml.etree.ElementTree as ET
from pathlib import Path


ROOT = Path(__file__).resolve().parent
VK_XML = ROOT / "dependencies" / "Vulkan-Headers" / "registry" / "vk.xml"
OUTPUT = ROOT / "VULKAN_NAMES.txt"


def add_name(names: set[str], value: str | None) -> None:
    if not value:
        return
    value = value.strip()
    if value:
        names.add(value)


def collect_names(root: ET.Element) -> list[str]:
    names: set[str] = set()

    for element in root.iter():
        add_name(names, element.get("name"))

        if element.tag == "name":
            add_name(names, element.text)

        if element.tag == "enum":
            add_name(names, element.get("name"))

        if element.tag == "command":
            add_name(names, element.get("name"))

        if element.tag == "type":
            add_name(names, element.get("name"))

    return sorted(names)


def main() -> int:
    if not VK_XML.exists():
        print(f"vk.xml not found: {VK_XML}", file=sys.stderr)
        return 1

    tree = ET.parse(VK_XML)
    names = collect_names(tree.getroot())
    OUTPUT.write_text("\n".join(names) + "\n", encoding="utf-8")
    print(f"Wrote {len(names)} names to {OUTPUT}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
