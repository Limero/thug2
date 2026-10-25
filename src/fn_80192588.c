// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192588-0x80192688 (256B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801276E8(CStruct *, void *, s32);
void fn_80127848(CStruct *, void *, s32);
void fn_8018F70C(void);
extern char lbl_802A98F0[];
extern char lbl_802A98FC[];
extern char lbl_802A9908[];
extern char lbl_802A98D4[];
extern char lbl_802A9910[];
void fn_80192588(CStruct *arg0, CStruct *arg1) {
    fn_8018F70C();
    if ((s32) arg0->unk0x80 != 0) {
        fn_801276E8(arg1, (s32)lbl_802A98F0, 1);
    } else {
        fn_801276E8(arg1, (s32)lbl_802A98F0, 0);
    }
    if ((s32) arg0->unk0x7C != 0) {
        fn_80127848(arg1, (s32)lbl_802A98FC, 1);
    } else {
        fn_80127848(arg1, (s32)lbl_802A98FC, 0);
    }
    if ((s32) arg0->unk0x78 != 0) {
        fn_80127848(arg1, (s32)lbl_802A9908, 1);
    } else {
        fn_80127848(arg1, (s32)lbl_802A9908, 0);
    }
    fn_801276E8(arg1, (s32)lbl_802A98D4, arg0->unk0x50);
    fn_801276E8(arg1, (s32)lbl_802A9910, arg0->unk0x84);
}
