// tolower — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Original SN Systems ProDG newlib source (crashwoc decomp, runtime/libc).
// Compiles byte-exact against the THUG2 DOL (0x80269F30, 0x1C) with the
// game's ngccc (ProDG 3.9.3). The _ctype_ table reference resolves to the
// DOL's newlib ctype table (0x802B1D04 via the _ctype_ symbol alias in
// symbols.txt).
#include "types.h"

extern unsigned char _ctype_[];

int tolower(int c) {
    if ((_ctype_ + 1)[c] & 1)
        c += 0x20;
    return c;
}
