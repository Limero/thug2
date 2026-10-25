// range 0x8000F268-0x8000F2C8 (96B). Byte-identical.
// Identification: virtual dispatch wrapper, sibling of fn_8000F10C with the
// vtable method at (offsets 0x40/0x44 instead of 0x20/0x24). Optional 4th arg
// `disp` defaults to `this->cc->0`; result converted by fn_80010B1C.
#include "types.h"
#include "structs.h"
char *fn_80010B1C(char *);
char *fn_8000F268(Unk_4897C6F8 *this, s32 a, s32 b, Unk_E15B2970 *disp) {
    char *vt, *res;
    if (disp == 0)
        disp = *(char **)(this->unk0xCC);
    vt = disp->unk0x80;
    res = (*(char *(**)(char *))(vt + 0x44))((char *)disp + ((Unk_CC629601 *)vt)->unk0x40);
    if (res != 0)
        fn_80010B1C(res);
    return res;
}