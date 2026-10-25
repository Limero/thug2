// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2888-0x801A28F8 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009E004(Unk_DB0E2BAB *);
s32 fn_8002439C(Unk_503E8FDE *);
extern char lbl_802AB320[];
extern char lbl_802AB378[];
void *fn_801A2888(Unk_A7137CF0 *arg0) {
    Unk_C8FEE62D *temp_r9;

    fn_8009E004(arg0);
    temp_r9 = (char *)arg0 + 0x58;
    arg0->unk0x8 = (s32)lbl_802AB320;
    temp_r9->unk0x14 = (s32)lbl_802AB378;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x8 = 0;
    fn_8002439C((char *)arg0 + 0x70);
    arg0->unk0x144 = 0;
    return arg0;
}
