// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058FF4-0x80059048 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct S_80058FF4 {
    s32 unk0x0;    /* 0x48484880 */
    s32 unk0x4;
    s32 unk0x8;
    f32 x;         /* +0xC = 0.5f; fn_80059380 writes x/y here */
    f32 y;         /* +0x10, left untouched by this ctor */
    f32 *xs;       /* +0x14 */
    f32 *ys;       /* +0x18 */
} S_80058FF4;
extern f32 lbl_8029349C;
void *fn_80058FF4(void *arg0) {
    S_80058FF4 *o = (S_80058FF4 *)arg0;
    s8 sp8[4];
    sp8[0] = 0x48;
    sp8[1] = 0x48;
    sp8[2] = 0x48;
    sp8[3] = -0x80;
    o->x = lbl_8029349C;
    o->unk0x0 = *(s32 *)sp8;
    o->unk0x4 = 0;
    o->unk0x8 = 0;
    o->xs = 0;
    o->ys = 0;
    return arg0;
}
