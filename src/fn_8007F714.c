// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F714-0x8007F7F8 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 *fn_8007F714(s32 *arg0, Unk_C7387A53 *arg1) {
    u8 col[4];
    Unk_C7387A53 *temp_r10;
    void *temp_r8;
    void *alt;
    void *entry;
    void *mid;
    void *temp_r9;
    void *dst;
    void *dst2;

    temp_r10 = arg1->unk0x30;
    col[0] = 0;
    col[1] = 0;
    col[2] = 0;
    col[3] = 0;
    if ((temp_r10 != NULL) && (temp_r10->unk0x48 != 0)) {
        temp_r8 = (void *)temp_r10->unk0x54;
        if ((temp_r8 != NULL) && (*(u16 *)((char *)temp_r8 + 0x5E) != 0)) {
            entry = *(void **)(*(void **)((char *)temp_r8 + 0x58));
            mid = *(void **)((char *)entry + 0x14);
            temp_r9 = *(void **)((char *)mid + 4);
            if (temp_r9 != NULL) {
                dst = (void *)(((Unk_C7387A53 *)temp_r8)->unk0x38 + (*(u16 *)((char *)temp_r9 + 0xC) << 5));
                col[0] = *(u8 *)((char *)dst + 0xC);
                col[1] = *(u8 *)((char *)dst + 0xD);
                col[2] = *(u8 *)((char *)dst + 0xE);
                col[3] = *(u8 *)((char *)dst + 0xF);
            }
        }
    } else {
        alt = (void *)arg1->unk0x20;
        if (alt != NULL) {
            dst2 = *(void **)alt;
            col[0] = *(u8 *)((char *)dst2 + 0x18);
            col[1] = *(u8 *)((char *)dst2 + 0x19);
            col[2] = *(u8 *)((char *)dst2 + 0x1A);
            col[3] = *(u8 *)((char *)dst2 + 0x1B);
        }
    }
    *arg0 = *(s32 *)col;
    return arg0;
}
