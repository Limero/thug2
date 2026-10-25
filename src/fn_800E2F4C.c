// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E2F4C-0x800E2FF0 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { char _pad[0x20]; s32 sub; } Obj;
typedef struct { s8 x, y, z, w; } Packed4;     /* 4 bytes at 0xc(r1)   */
s32 fn_801293FC(s32, s32);                     /* array-element reader   */
void fn_80069D24(void *, s32, s32 *);
void fn_80128E94(void *, s32, s32 *, s32);     /* (ctx, 0, &out, 1)     */
bool fn_800E2F4C(Obj *arg0, void *arg1) {
    s32 sp8;
    Packed4 v;
    fn_80128E94(arg1, 0, &sp8, 1);
    if (arg0->sub != 0) {
        v.x = fn_801293FC(sp8, 0);
        v.y = fn_801293FC(sp8, 1);
        v.z = fn_801293FC(sp8, 2);
        v.w = fn_801293FC(sp8, 3);
        fn_80069D24(arg0->sub, 2, (s32 *)&v);
    }
    return true;
}
