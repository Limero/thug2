// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F3D0-0x8009F464 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8012F8E8(Unk_FFAD6788 *, s32, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void fn_80032088(s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8009F3D0(Unk_C8FEE62D *arg0, s32 arg1, CStruct *arg2) {
    void *temp_r28;
    void *temp_r29;
    void *temp_r3;

    temp_r28 = arg0->unk0x14;
    if (temp_r28 == NULL) {
        fn_80032088(0xF8);
        temp_r3 = fn_8012ED98();
        arg0->unk0x14 = temp_r3;
        temp_r29 = temp_r3 + 0xBC;
        if ( ((Unk_FFAD6788 *)temp_r3)->unk0xBC != NULL) {
            CObject_RemoveRefLink(*(s32 *)((char *)temp_r29), temp_r29);
            ((Unk_FFAD6788 *)temp_r3)->unk0xBC = temp_r28;
        }
        ((Unk_FFAD6788 *)temp_r3)->unk0xBC = arg0;
        if (arg0 != NULL) {
            CObject_AddRefLink(arg0, temp_r29);
        }
    }
    fn_8012F8E8(arg0->unk0x14, arg1, arg2);
}
