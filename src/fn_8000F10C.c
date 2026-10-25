// range 0x8000F10C-0x8000F16C (96B). Byte-identical.
// Identification: virtual allocator/dispatch wrapper. `disp` (4th arg) is
// optional — if 0, it is resolved from `this->cc->0`. Dispatches through the
// vtable at `disp->0x80` (half-word method offset at 0x20, fnptr at 0x24) on
// `disp + offset`, then converts the fresh result to an allocator header via
// fn_80010B1C (addr-=0xc; header word 0xCF7FE01FE1). Sibling of F16C (which
// resolves the dispatcher unconditionally and reads offsets 0x28/0x2c) and of
// F1A8/F208/F268 (0x30..0x44).
#include "types.h"
#include "structs.h"
char *fn_80010B1C(char *);
char *fn_8000F10C(Unk_4897C6F8 *this, s32 a, s32 b, Unk_E15B2970 *disp) {
    char *vt, *res;
    if (disp == 0)
        disp = *(char **)(this->unk0xCC);
    vt = disp->unk0x80;
    res = (*(char *(**)(char *))(vt + 0x24))((char *)disp + ((Unk_0FC2D8A9 *)vt)->unk0x20);
    if (res != 0)
        fn_80010B1C(res);
    return res;
}