// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F5F4-0x8007F714 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8007F5F4(Unk_C7387A53 *arg0) {
    s32 var_r10;
    s32 var_r6;
    s32 var_r8;
    u32 var_r10_3;
    s32 c80;
    s32 cFF;
    void *base;
    Unk_C7387A53 *temp_r9;
    void *temp_r8;
    void *temp_r7;
    void *entry;
    void *mid;
    void *dst;
    void *eb;

    temp_r9 = (Unk_C7387A53 *)arg0->unk0x30;
    if ((temp_r9 != NULL) && (temp_r9->unk0x48 != 0)) {
        temp_r9 = (Unk_C7387A53 *)temp_r9->unk0x54;
        if (temp_r9 != NULL) {
            var_r10 = 0;
            if (var_r10 < *(u16 *)((char *)temp_r9 + 0x5E)) {
                do {
                    temp_r7 = (void *)((Unk_C7387A53 *)arg0->unk0x30)->unk0x54;
                    entry = *(void **)((char *)((var_r10 * 4) + (s32)((Unk_C7387A53 *)temp_r7)->unk0x58));
                    mid = *(void **)((char *)entry + 0x14);
                    temp_r8 = *(void **)((char *)mid + 4);
                    if (temp_r8 != NULL) {
                        var_r6 = 0;
                        dst = (void *)(((Unk_C7387A53 *)temp_r7)->unk0x38 + (*(u16 *)((char *)temp_r8 + 0xC) << 5));
                        if (var_r6 < *(u8 *)((char *)temp_r8 + 4)) {
                            do {
                                *(u8 *)((char *)dst + 0xC) = 0x80;
                                var_r6 += 1;
                                *(u8 *)((char *)dst + 0xD) = 0x80;
                                *(u8 *)((char *)dst + 0xE) = 0x80;
                                dst = (void *)((char *)dst + 0x20);
                                *(u8 *)((char *)temp_r8 + 6) |= 0x10;
                            } while (var_r6 < *(u8 *)((char *)temp_r8 + 4));
                        }
                    }
                    var_r10 += 1;
                } while (var_r10 < *(u16 *)((char *)((Unk_C7387A53 *)((Unk_C7387A53 *)arg0->unk0x30)->unk0x54) + 0x5E));
            }
        }
    } else if (arg0->unk0x20 != 0) {
        var_r10_3 = 0U;
        if (var_r10_3 < (u32)arg0->unk0x24) {
            c80 = 0x80;
            cFF = 0xFF;
            var_r8 = 0;
            do {
                base = (void *)arg0->unk0x20;
                var_r10_3 += 1;
                eb = *(void **)((char *)(var_r8 + (s32)base));
                var_r8 += 4;
                *(u8 *)((char *)eb + 0x18) = c80;
                *(u8 *)((char *)eb + 0x19) = c80;
                *(u8 *)((char *)eb + 0x1A) = c80;
                *(u8 *)((char *)eb + 0x1B) = cFF;
            } while (var_r10_3 < (u32)arg0->unk0x24);
        }
    }
}
