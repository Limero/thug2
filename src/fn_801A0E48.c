// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A0E48-0x801A0F54 (268B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *GetChecksum_3(Unk_6A70655D *, s32);
void fn_801A0DA8(Unk_6A70655D *);
void fn_800D8908(Unk_C7387A53 *, CStruct *);
s32 fn_800F0AFC(CStruct *);
void fn_8009E1F0(Unk_C8FEE62D *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_8009F204(Unk_C8FEE62D *, void *, Unk_C8FEE62D *);
void fn_801A0E48(Unk_6A70655D *arg0, CStruct *arg1) {
    s32 temp_r3;
    void *obj;
    Unk_4E705049 *vt;
    s32 sp8;
    s32 spC;

    obj = GetChecksum_3(arg0, QB_MOTION);
    if (obj == NULL) {
        fn_801A0DA8(arg0);
    }
    fn_800D8908(obj, arg1);
    {
        register s32 t __asm__("r3");
        t = fn_800F0AFC(arg1);
        if (t != 0) {
            register s32 tv __asm__("r4");
            tv = t;
            fn_8009E1F0(arg0, tv);
        }
    }
    sp8 = 0;
    if (GetChecksum_2(arg1, QB_TRIGGERSCRIPT, &sp8, 0) != 0) {
        spC = 0;
        GetStructure_2(arg1, QB_PARAMS, &spC, 0);
        fn_8009F204(arg0, sp8, spC);
    }
    vt = *((void * *)&((CScript *)obj)->unk0x18);
    ((void (*)(void *, void *))(vt->unk0x1C))(obj + vt->unk0x18, arg1);
    {
        void *obj2;
        void *vt2;

        obj2 = GetChecksum_3(arg0, QB_SUSPEND);
        vt2 = *((void * *)&((CScript *)obj2)->unk0x18);
        temp_r3 = ((Unk_4E705049 *)vt2)->unk0x18;
        ((void (*)(void *, void *))(((Unk_4E705049 *)vt2)->unk0x1C))(obj2 + temp_r3, arg1);
    }
}
