// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032328-0x80032388 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80032F18(s32);
extern char lbl_80291B60[];
extern char lbl_80291B60[];
void fn_80032610();
void fn_8002DD1C(Unk_C8FEE62D *arg0, s32 arg1);
void fn_800320D8(void *);
void fn_80032328(CScript *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_80291B60;
    fn_80032610();
    fn_80032F18(arg0);
    fn_8002DD1C((char *)arg0 + 4, 0);
    if (arg1 & 1) {
        fn_800320D8(arg0);
    }
}