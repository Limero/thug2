// GQR2 setter: packs 4 args into a GQR value and writes it via fn_80269EB0.
// range=0x80269EC0-0x80269EF8 size=56B
// Byte-twin of fn_80269EF8 (GQR3). Retail is MWCC-compiled; build with
// mw_version="GC/1.2.5n", -O3 (see configure.py). Byte-identical.
#include "types.h"

void fn_80269EB0(s32);

void fn_80269EC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 lo;
    arg0 = (arg0 << 8) + arg1;
    lo = arg2 << 8;
    arg0 <<= 16;
    lo += arg3;
    fn_80269EB0(arg0 | lo);
}
