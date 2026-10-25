// atoff — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Matches newlib's stdlib/atoff.c verbatim: atoff(s) == strtof(s, NULL),
// passing a NULL endptr to fn_8026AA68 (strtof, still parked — callee keeps
// its fn_ name until promotion). The float return rides home in f1 for free,
// so the bytes match the older void-form draft exactly.
// range 0x8026A058-0x8026A07C (36B). Byte-identical.
#include "types.h"
float fn_8026AA68(u8 *, s32);
float atoff(const char *s) {
    return fn_8026AA68((u8 *)s, 0);
}
