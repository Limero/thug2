#!/usr/bin/env python3
"""Pad short SDK data sections up to their splits-claim sizes.

Background: the mwcc available today omits trailing zero padding that the
original toolchain emitted (verified: 15 SDK .data claims exceed their
freshly compiled objects by 1-7 zero bytes each, e.g. OSInterrupt
InterruptPrioTable 0x2C vs claim 0x30). dtk cannot cover the difference
(zero gaps adjacent to claims are skipped, not emitted), so the linked DOL
shifts. This tool extends those sections with zero bytes via objcopy
--update-section (which handles all ELF bookkeeping).

It also STRIPS sections the link must not see: GXLight.o emits an empty
.data (current mwcc puts its jump table nowhere reachable) while dtk
auto-covers the real table with relocations; linking both grows .data.
STRIP entries remove the whole section.
No-op for objects/sections already at size (and errors loudly if an object
is LONGER than its claim, which would overlap the next split). Correctness
is verified the usual way: the linked DOL must stay byte-identical.

Manifest regeneration: compare every linked C data claim against its
object (see M7.2 notes); entries below are (object suffix, section, size).

Usage: wired into the mwcc* ninja rules (see configure.py patch); also
  tools/venv/bin/python tools/pad_sdk_data.py <object>   (single file)
"""
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = os.path.join(ROOT, "build/binutils/powerpc-eabi-objdump")
OBJCOPY = os.path.join(ROOT, "build/binutils/powerpc-eabi-objcopy")

# (object path suffix sans extension, section, target size). Regenerate
# as described above.
PADS = [
    ("os/OS", "data", 0x1F8),
    ("os/OSCache", "data", 0x230),
    ("os/OSContext", "data", 0x1D8),
    ("os/OSInterrupt", "data", 0x30),
    ("ar/ar", "data", 0x48),
    ("ar/arq", "data", 0x48),
    ("ai/ai", "data", 0x48),
    ("ax/AX", "data", 0x48),
    ("ax/AXVPB", "data", 0xD8),
    ("dsp/dsp", "data", 0x80),
    ("dsp/dsp_task", "data", 0x140),
    ("si/SIBios", "data", 0x118),
    ("si/SISamplingRate", "data", 0x98),
    ("gx/GXFrameBuf", "data", 0x748),
]

# (object path suffix sans extension, section): drop the section entirely.
# The range must stay covered by dtk auto-asm. Currently EMPTY: stripping
# is a last resort (it discards bytes; prefer carving ranges back to auto
# or restoring claims). Never fail the build here: warn and skip.
STRIP = [
]


def section_size(obj, section):
    h = subprocess.run([OBJDUMP, "-h", obj], capture_output=True, text=True).stdout
    m = re.search(r"\.%s\s+([0-9a-f]+)" % section, h)
    return int(m.group(1), 16) if m else None


def section_bytes(obj, section):
    r = subprocess.run([OBJDUMP, "-s", "-j", "." + section, obj],
                       capture_output=True, text=True).stdout
    got = bytearray()
    for line in r.splitlines():
        m = re.match(r"^\s*[0-9a-f]+ ([0-9a-f ]+?)(?:\s{2,}.*)?$", line)
        if m:
            got += bytes.fromhex(m.group(1).replace(" ", ""))
    return bytes(got)


def pad_one(path):
    for suffix, section in STRIP:
        if not path.endswith(suffix + ".o"):
            continue
        r = subprocess.run([OBJDUMP, "-t", path], capture_output=True, text=True)
        # refuse if any real symbol lives in the section (only the section
        # symbol itself, named exactly like the section, may remain)
        owned = [l.split()[-1] for l in r.stdout.splitlines()
                 if re.match(r"[0-9a-f]+ \w+\s+\S+ \.%s\s" % section, l)
                 and l.split()[-1] != "." + section]
        if owned:
            print("pad_sdk_data: %s .%s has symbols, skipping strip: %s"
                  % (path, section, owned[:3]), file=sys.stderr)
            return 0
        r = subprocess.run([OBJCOPY, "-R", "." + section, path],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print("pad_sdk_data: objcopy -R failed on %s: %s" % (path, r.stderr),
                  file=sys.stderr)
            return 1
        print("pad_sdk_data: %s stripped .%s" % (path, section))
        return 0
    for suffix, section, size in PADS:
        if not path.endswith(suffix + ".o"):
            continue
        cur = section_size(path, section)
        if cur is None:
            return 0
        if cur == size:
            return 0
        if cur > size:
            print("pad_sdk_data: %s .%s bigger than claim (%#x > %#x)"
                  % (path, section, cur, size), file=sys.stderr)
            return 1
        raw = section_bytes(path, section)
        assert len(raw) == cur, (path, section, len(raw), cur)
        with tempfile.NamedTemporaryFile(delete=False) as f:
            f.write(raw + b"\x00" * (size - cur))
            tmp = f.name
        r = subprocess.run([OBJCOPY, "--update-section", ".%s=%s" % (section, tmp),
                            path], capture_output=True, text=True)
        os.unlink(tmp)
        if r.returncode != 0:
            print("pad_sdk_data: objcopy failed on %s: %s" % (path, r.stderr),
                  file=sys.stderr)
            return 1
        print("pad_sdk_data: %s .%s %d -> %d" % (path, section, cur, size))
        return 0
    return 0


def main():
    rc = 0
    for path in sys.argv[1:]:
        rc |= pad_one(path)
    return rc


if __name__ == "__main__":
    sys.exit(main())
