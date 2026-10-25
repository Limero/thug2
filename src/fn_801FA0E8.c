// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA0E8-0x801FA178 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F53C(void);
void fn_801FA1C8(void *);
void fn_801FB15C(Unk_C7387A53 *);
void fn_801FC364(s32, s32);
void fn_801FC3D8(s32, s32);
extern char lbl_802AE5F8[];
extern char lbl_802AE578[];
extern char lbl_802AE58C[];
void *fn_801FA0E8(Unk_DB0E2BAB *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802AE5F8;
    arg0->unk0x4 = QB_RAILEDITOR;
    fn_801FC364(0x190, (s32)lbl_802AE578);
    fn_801FC3D8(0xC8, (s32)lbl_802AE58C);
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x34 = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x24 = 0;
    fn_801FA1C8(arg0);
    fn_801FB15C(arg0);
    return arg0;
}
