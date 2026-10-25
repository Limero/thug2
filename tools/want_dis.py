#!/usr/bin/env python3
"""Disassemble the want bytes of a DOL function (no compile)."""
import sys, struct
sys.path.insert(0, "tools")
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

addr = int(sys.argv[1], 0)
end = int(sys.argv[2], 0) if len(sys.argv) > 2 else addr + 0x100
code = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (end - gl.t_addr)]
md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
for ins in md.disasm(code, addr):
    print(f"{ins.address:08X}: {ins.bytes.hex()}  {ins.mnemonic} {ins.op_str}")
