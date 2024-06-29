import sys
if len(sys.argv) < 2:
    print(f"usage: cut_tool.py <executable>")
    exit(1)

out = ""
with open(sys.argv[1], "+rb") as exe:
    txt = exe.read()
    out = txt[txt.find(b"tiny\0"):]

with open(sys.argv[1], "+wb") as exe:
    exe.write(out)
