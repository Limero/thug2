// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F08FC-0x801F0958 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CStruct_ctor(void);
s32 CStruct_dtor(CStruct *);
s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 CStruct_new(s32);
void fn_801F08FC(Unk_C7387A53 *arg0, CStruct *arg1) {
    if ((s32) arg0->unk0x24 == 0) {
        CStruct_new(8);
        arg0->unk0x24 = CStruct_ctor();
    }
    CStruct_dtor(arg0->unk0x24);
    fn_80126FF4(arg0->unk0x24, arg1);
}
