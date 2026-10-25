// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EFC18-0x801EFC8C (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F53C(void);
void fn_801A38A0(Unk_FFAD6788 *);
extern char lbl_802ADE98[];
void *fn_801EFC18(Unk_D4CE523B *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802ADE98;
    fn_801A38A0((char *)arg0 + 0x28);
    fn_801A38A0((char *)arg0 + 0x98);
    fn_801A38A0((char *)arg0 + 0x108);
    fn_801A38A0((char *)arg0 + 0x178);
    arg0->unk0x4 = QB_SKATERBALANCETRICK;
    arg0->unk0x1E8 = 0;
    arg0->unk0x24 = 0;
    return arg0;
}
