// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9DE8-0x801A9E88 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800121D8(s32);
extern void *fn_801A9A70(void *);
bool fn_801A9DE8(CStruct *arg0, s32 *arg1, s32 arg2) {
    register s32 *a1 __asm__("r29");
    register s32 a2 __asm__("r28");
    u32 mask;
    s32 key;
    s32 k2;
    char *arr;
    u32 off;
    CStruct *bkt;
    CStruct *nd;

    a1 = arg1;
    mask = 1U << *(s32 *)arg0;
    key = *a1;
    a2 = arg2;
    arr = *((char * *)&arg0->unk0x4);
    off = (key & (mask - 1)) * 12;
    bkt = arr + off;
    if (((Unk_4C649A8C *)bkt)->unk0x4 != 0) {
        nd = fn_801A9A70((void *)fn_800121D8(0));
        k2 = *a1;
        nd->unk0x4 = a2;
        nd->unk0x0 = k2;
        nd->unk0x8 = bkt->unk0x8;
        bkt->unk0x8 = (s32)nd;
    } else {
        *(s32 *)((char *)arr + off) = key;
        bkt->unk0x4 = a2;
    }
    (arg0->unk0x8)++;
    return true;
}
