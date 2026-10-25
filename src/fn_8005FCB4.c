// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005FCB4-0x8005FD34 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80036960(CStruct *);
s32 fn_80036968(Unk_C8FEE62D *);
bool fn_8005FCB4(CStruct *arg0,CStruct * arg1) {
    void *temp_r29;
    void *temp_r30;
    CStruct *temp_r30_2;

    if ((s32) arg0->unk0xC == 0) {
        arg0->unk0x8 = fn_80036968(arg1);
        temp_r30 = arg0->unk0x50;
        temp_r30_2 = temp_r30 + 0x10;
        temp_r29 = (char *)arg0 + ((Unk_89391A04 *)temp_r30)->unk0x10;
        ((s32 (*)(void *, void *))temp_r30_2->unk0x4)(temp_r29, fn_80036968(arg1));
        arg0->unk0xC = fn_80036960(arg1);
    }
    return true;
}
