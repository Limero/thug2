// isspace — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// ctype bit test: (_ctype_ + 1)[c] & _S(8). Same idiom as the other ctype
// leaves (tolower, isdigit); corroborated by newlib strtol.c's own
// whitespace-skip site.
// range 0x8026E590-0x8026E5A4 (20B). Byte-identical.
#include "types.h"
extern const unsigned char _ctype_[];
s32 isspace(s32 arg0) {
    return (_ctype_ + 1)[arg0] & 8;
}
