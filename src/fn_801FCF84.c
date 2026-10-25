// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FCF84-0x801FCFE4 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
typedef struct {
    char pad0x0[0x10];
    f32 unk0x10;
} Rec2_801FCF84;
typedef struct {
    char pad0x0[0xA0];
    Rec2_801FCF84 *unk0xA0;
} Rec_801FCF84;
extern f32 lbl_802AE6C8;
extern char lbl_802AE6BC[];
void Mem_NewZero(s32);
Rec2_801FCF84 *fn_80024C48(void);
void fn_80024D00(Rec2_801FCF84 *, s32);
void fn_801FCF84(Rec_801FCF84 *arg0) {
    Rec2_801FCF84 *temp;
    if (arg0->unk0xA0 == 0) {
        Mem_NewZero(0x18);
        temp = fn_80024C48();
        arg0->unk0xA0 = temp;
        temp->unk0x10 = lbl_802AE6C8;
        fn_80024D00(arg0->unk0xA0, (s32) lbl_802AE6BC);
    }
}
