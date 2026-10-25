// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033644-0x800336C4 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80033538(void);
s32 fn_8005525C(void);
s32 fn_8006FB50(s32, s32);
s32 fn_800335E0(CStruct *);
s32 GetChecksum_3(s32, s32);
s32 fn_800CBDE0(void);
extern char lbl_80291DA0[];
void *fn_80033644(Unk_DB0E2BAB *arg0) {
    s32 v;

    fn_80033538();
    arg0->unk0x14 = (s32)lbl_80291DA0;
    v = fn_8005525C();
    arg0->unk0x20 = v;
    arg0->unk0x1C = fn_8006FB50(v, 0);
    GetChecksum_3(fn_800335E0(arg0), QB_ANIMBLENDER);
    arg0->unk0x24 = fn_800CBDE0();
    arg0->unk0x1C = 0;
    arg0->unk0x28 = -1;
    return arg0;
}
