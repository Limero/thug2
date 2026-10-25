// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80076F8C-0x80077088 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802FFE98[];
extern bool lbl_803016A8;
extern s32 lbl_80301858;
extern char lbl_80295718[];
extern char lbl_8029571C[];
s32 fn_800768A8(Unk_78674569 *, Unk_9994C3F5 *, s32, s32, s32);
void fn_80014898(s32);
void fn_80014904(void *, s32, s32, s32);
void fn_80010E78(s32);
void fn_80010D94(s32, s32);
s32 fn_800146E0(s32);
s32 fn_800147E8(Unk_C8FEE62D *, void *);
void DCFlushRange(s32, s32);
s32 fn_80076F8C(s32 arg0, Unk_9994C3F5 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    char sp8[0x80];
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;

    sprintf((s32)sp8, (s32)lbl_80295718, arg0);
    temp_r3 = fn_800147E8((s32)sp8, (s32)lbl_8029571C);
    if (temp_r3 == 0) {
        if (lbl_803016A8 != 0) {
            lbl_80301858 = temp_r3;
        }
        return 0;
    }
    temp_r29 = fn_800146E0(temp_r3);
    fn_80010D94(*(s32 *)((char *)(*(void * *)&lbl_802FFE98) + (s32)0x11C), 0x20);
    temp_r30 = Mem_Alloc(temp_r29);
    fn_80010E78(*(s32 *)((char *)(*(void * *)&lbl_802FFE98) + (s32)0x11C));
    fn_80014904(temp_r30, temp_r29, 1, temp_r3);
    fn_80014898(temp_r3);
    DCFlushRange(temp_r30, temp_r29);
    return fn_800768A8(temp_r30, arg1, arg2, arg3, arg4);
}
