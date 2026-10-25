// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80214278-0x80214308 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF6B4[];
extern f32 fn_800144C8(void);
extern s32 GetStructure(s32 hash, s32 flag);
extern s32 GetFloat(CStruct * arg0, s32 hash, f32 * out, s32 flag);

void fn_80214278(Unk_DB0E2BAB *arg0) {
    union { f32 f; u64 pad; } sp8;
    u32 _dummy[2];
    f32 temp_f31;
    f32 temp_f12;
    f32 konst;
    f32 prod;
    register char *page __asm__("r9");
    s32 temp_r0;

    __asm__("" : : "m"(sp8.f), "m"(_dummy[0]));
    temp_r0 = arg0->unk0x1C;
    if ((temp_r0 != 2) && (temp_r0 != 4)) {
        temp_f31 = fn_800144C8();
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_DISPLAY_OFFSET_RESTORE_RATE, &sp8, 1);
        __asm__ volatile("lis %0,%1@ha" : "=r"(page) : "s"(lbl_802AF6B4));
        temp_f12 = *((f32 *)&arg0->unk0xB4);
        __asm__ __volatile__("" ::: "memory");
        prod = sp8.f;
        __asm__ __volatile__("" ::: "memory");
        __asm__ volatile("lfs %0,%1@l(%2)" : "=f"(konst)
                         : "s"(lbl_802AF6B4), "r"(page));
        temp_f31 = temp_f31 * prod;
        konst = konst - temp_f12;
        *((f32 *)&arg0->unk0xB4) =
            konst * temp_f31 + temp_f12;
    }
}
