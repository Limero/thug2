// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A97C4-0x801A987C (184B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802AB974[];
extern s32 fn_80128610(CStruct *, void *, void *, s32);
extern s32 GetChecksum(CStruct *, s32);
extern void fn_801A9270(s32, s32, s32);
extern s32 CStruct_dtor(CStruct *);

void fn_801A97C4(Unk_C7387A53 *arg0) {
    s32 sp8[8];
    s32 sp40;
    CStruct *p;
    s32 i;
    s32 j;

    j = 0;
    do {
        sprintf(sp8, (s32)lbl_802AB974, j);
        if (fn_80128610(arg0->unk0x38, sp8, &sp40, 0) != 0) {
            i = 0;
            p = sp40;
            while (i < p->unk0x4) {
                fn_801A9270(arg0, GetChecksum(sp40, i++), j);
                p = sp40;
            }
        }
    } while (++j <= 7);
    CStruct_dtor(arg0->unk0x38);
}
