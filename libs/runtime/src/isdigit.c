// isdigit — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// ctype bit test: (_ctype_ + 1)[c] & _N(4). Same idiom as the other ctype
// leaves (tolower, isspace); corroborated by newlib strtol.c's own
// digit-test site.
// range 0x8026E57C-0x8026E590 (20B). Byte-identical.
#include "types.h"
extern const unsigned char _ctype_[];
s32 isdigit(s32 arg0) {
    return (_ctype_ + 1)[arg0] & 4;
}
