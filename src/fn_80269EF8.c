// GQR3 setter: packs 4 args into a GQR value and writes it via fn_80269EB8.
// range=0x80269EF8-0x80269F30 size=56B
// Retail is MWCC-compiled (mflr-first prologue, pop-before-mtlr epilogue);
// build with mw_version="GC/1.2.5n", -O3 (see configure.py). Param
// reassignment keeps hi in r3 so mwcc emits want's weave:
// [hi-add r3][lo-shift r0][hi-shift r3][lo-add r0][or]. Byte-identical.
#include "types.h"

void fn_80269EB8(s32);

void fn_80269EF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 lo;
    arg0 = (arg0 << 8) + arg1;
    lo = arg2 << 8;
    arg0 <<= 16;
    lo += arg3;
    fn_80269EB8(arg0 | lo);
}
