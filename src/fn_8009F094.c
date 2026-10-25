// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F094-0x8009F134 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CObject_ClearRefLinks(CStruct *);
void fn_8012EFCC(Unk_FFAD6788 *, s32);
void fn_80131AF4(Unk_15EF4A35 *);
void fn_8009F094(Unk_C8FEE62D *arg0) {
    s32 v = arg0->unk0x14;
    if (v != 0) {
        fn_8012EFCC(v, 0);
    }
    fn_80131AF4(arg0);
    arg0->unk0xC = (s32) (arg0->unk0xC & QB_UNKNOWN_0xFFFFFFFD);
    {
        void *temp_r30 = arg0->unk0x10;
        void *temp_r9 = ((Unk_C7387A53 *)temp_r30)->unk0x2C;
        ((Unk_A53985D4 *)temp_r9)->unk0x1C(temp_r30 + ((Unk_A53985D4 *)temp_r9)->unk0x18, arg0);
        temp_r9 = ((Unk_C7387A53 *)temp_r30)->unk0x2C;
        ((Unk_A53985D4 *)temp_r9)->unk0x34(temp_r30 + ((Unk_A53985D4 *)temp_r9)->unk0x30, arg0);
    }
    arg0->unk0xC = (s32) (arg0->unk0xC | 1);
    CObject_ClearRefLinks((char *)arg0 + 0x48);
}
