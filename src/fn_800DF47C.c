// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DF47C-0x800DF4E0 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F53C(void);
void fn_800AA0BC(Unk_CFB386B2 *);
extern char lbl_8029A500[];
void *fn_800DF47C(Unk_264DC741 *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_8029A500;
    fn_800AA0BC((char *)arg0 + 0x24);
    fn_800AA0BC((char *)arg0 + 0x2A0);
    arg0->unk0x51C = 0;
    arg0->unk0x4 = QB_INPUT;
    arg0->unk0x530 = 0;
    return arg0;
}
