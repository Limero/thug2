// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AABBC-0x801AAC24 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E1F0(Unk_C8FEE62D *, s32);
void fn_8009F678(void);
void fn_801A0D50(Unk_6A70655D *);
extern char lbl_802ABB10[];
void *fn_801AABBC(Unk_69536BB4 *arg0) {
    fn_8009F678();
    arg0->unk0x8 = (s32)lbl_802ABB10;
    fn_801A0D50(arg0);
    arg0->unk0x1C = QB_UNKNOWN_0xD2156C50;
    fn_8009E1F0(arg0, QB_CROWN_OBJECT);
    arg0->unk0x120 = 0;
    return arg0;
}
