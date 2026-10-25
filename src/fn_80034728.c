// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034728-0x800347B0 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80291CA0[];
void fn_80033538(void);
s32 fn_8005525C(void);
s32 fn_8006FB50(s32, s32);
Unk_6A70655D *fn_800335E0(Unk_DB0E2BAB *);
void *GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800CBDE0(Unk_C7387A53 *);
s32 Mem_NewZero(s32);
s32 fn_8002DCCC(s32);
void *fn_80034728(Unk_DB0E2BAB *arg0) {
    s32 temp;
    fn_80033538();
    arg0->unk0x14 = (s32)lbl_80291CA0;
    temp = fn_8005525C();
    arg0->unk0x1C = temp;
    arg0->unk0x20 = fn_8006FB50(temp, 0);
    arg0->unk0x24 = fn_800CBDE0(GetChecksum_3(fn_800335E0(arg0), QB_ANIMBLENDER));
    arg0->unk0x18 = fn_8002DCCC(Mem_NewZero(0x38));
    arg0->unk0x20 = 0;
    return arg0;
}
