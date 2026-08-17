# -*- coding: utf-8 -*-
import re
import sys
import os

def usage():
    print("Usage: python3 mk2cmake.py <input.mk> <output.cmake>")
    sys.exit(1)

if len(sys.argv) != 3:
    usage()

MK_FILE = sys.argv[1]
CMAKE_FILE = sys.argv[2]

if not os.path.isfile(MK_FILE):
    print(f"Error: input file not found: {MK_FILE}")
    sys.exit(1)

out = []

def conv_value(val):
    # $(FOO) -> ${FOO}
    val = re.sub(r'\$\((\w+)\)', r'${\1}', val)
    return f'"{val.strip()}"'

with open(MK_FILE, encoding="utf-8") as f:
    for raw in f:
        s = raw.strip()

        if not s:
            out.append("")
            continue

        # comment
        if s.startswith("#"):
            out.append(s.replace(".mk", ".cmake"))
            continue

        # ifeq ($(VAR), y)
        m = re.match(r'ifeq\s*\(\$\((\w+)\)\s*,\s*(\w+)\)', s)
        if m:
            var, val = m.groups()
            out.append(f'if({var} STREQUAL "{val}")')
            continue

        if s == "else":
            out.append("else()")
            continue

        if s == "endif":
            out.append("endif()")
            continue

        # ifneq ($(VAR), y)
        m = re.match(r'ifneq\s*\(\$\((\w+)\)\s*,\s*(\w+)\)', s)
        if m:
            var, val = m.groups()
            out.append(f'if(NOT {var} STREQUAL "{val}")')
            continue

        if s == "else":
            out.append("else()")
            continue

        if s == "endif":
            out.append("endif()")
            continue

        # export VAR := value
        # export VAR ?= value
        # export VAR = value
        m = re.match(r'export\s+(\w+)\s*(?:\?=|:=|=)\s*(.*)', s)
        if m:
            var, val = m.groups()
            out.append(f'set({var} {conv_value(val)})')
            out.append(f'set(ENV{{{var}}} {conv_value(val)})')
            continue

        # CFLAGS += ...
        m = re.match(r'CFLAGS\s*\+=\s*(.*)', s)
        if m:
            flags = m.group(1)
            for token in flags.split():
                if token.startswith("-D"):
                    token = token.replace("$(", "${").replace(")", "}")
                    out.append(f'list(APPEND BES_SDK_FLAGS {token})')
            continue

        # unknown lines: ignore safely

with open(CMAKE_FILE, "w", encoding="utf-8") as f:
    f.write("\n".join(out))