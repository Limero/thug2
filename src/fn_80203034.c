// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80203034-0x8020309C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802AED58[];
void fn_8009F53C(void);
void *fn_80203034(Unk_C8FEE62D *arg0) {
    void *t;
    fn_8009F53C();
    arg0->unk0x20 = 0;
    arg0->unk0x18 = (s32)lbl_802AED58;
    t = Mem_Alloc2(0xC);
    arg0->unk0x1C = (s32)t;
    arg0->unk0x4 = QB_PAGERMESSAGE;
    ((CStruct *)t)->unk0x8 = (s32)t;
    ((CStruct *)t)->unk0x4 = (s32)t;
    return arg0;
}
