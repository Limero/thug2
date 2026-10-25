// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D688-0x8023D6FC (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern u16 lbl_802B0EBC;
void strcpy(s32);
s32 fn_80243EF0(void);
void fn_80243924(s32, s32, void *);
void fn_8023D688(Unk_5492E6FA *arg0, u8 *arg1, s32 arg2) {
    if (arg1 != NULL) {
        if ((s32) *arg1 == 0) {
            arg0->unk0x9C = lbl_802B0EBC;
        } else {
            strcpy((char *)arg0 + 0x9C);
        }
    }
    if (arg2 >= 0) {
        arg0->unk0xBC = arg2;
    }
    fn_80243924(fn_80243EF0(), arg0->unk0xC4, (char *)arg0 + 0x78);
}
