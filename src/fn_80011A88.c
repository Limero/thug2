// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011A88-0x80011BB8 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80290628[];
extern s32 lbl_802FFEE8;
void fn_80010768(void *);
Unk_9994C3F5 *fn_80010B38(void *);
void fn_80010764(void *);
void *fn_80011E00(void *, s32);

typedef struct { u32 hi : 24; u32 lo : 8; } NodeFlags;

s32 fn_80011A88(Unk_C7387A53 *arg0, s32 arg1,void * arg2) {
    u32 temp_r0;
    u32 temp_r30;
    u32 temp_r4;
    u32 temp_r9_2;
    u32 temp_r10;
    Unk_9994C3F5 *temp_r3;
    Unk_9994C3F5 *temp_r3_2;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9_3;
    char *temp_base;

    lbl_802FFEE8 = 1;
    temp_r3 = fn_80010B38(arg2);
    temp_r4 = (arg1 + 3) & QB_UNKNOWN_0xFFFFFFFC;
    temp_r0 = (u32) *((u32 *)&temp_r3->unk0x8) >> 8U;
    if (temp_r0 >= temp_r4) {
        lbl_802FFEE8 = 0;
        return arg2;
    }
    temp_r9 = arg0->unk0x80;
    temp_r3_2 = fn_80010B38(((s32 (*)(void *, void *, s32))temp_r9->unk0x24)((char *)arg0 + *(s16 *)&temp_r9->unk0x20, temp_r4 - temp_r0, 1));
    if ((s32) (arg2 + ((u32) *((u32 *)&temp_r3->unk0x8) >> 8U)) != temp_r3_2) {
        temp_r9_3 = arg0->unk0x80;
        temp_base = (char *)arg0 + *(s16 *)&temp_r9_3->unk0x48;
        lbl_802FFEE8 = 0;
        ((s32 (*)(void *, void *))temp_r9_3->unk0x4C)(temp_base, temp_r3_2);
        return 0;
    } else {
        s32 zero = 0;
        fn_80010768(temp_r3);
        fn_80010768(temp_r3_2);
        temp_r30 = (u32) *((u32 *)&temp_r3_2->unk0x8) >> 8U;
        fn_80011E00((char *)arg0 + 4, 1);
        temp_r9_2 = *((u32 *)&temp_r3->unk0x8);
        temp_r10 = *(s32 *)&lbl_80290628;
        temp_r30 = temp_r30 + temp_r10;
        ((NodeFlags *)&temp_r3->unk0x8)->hi = (temp_r9_2 >> 8) + temp_r30;
        fn_80010764(temp_r3);
        lbl_802FFEE8 = zero;
        return arg2;
    }
}
