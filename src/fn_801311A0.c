// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801311A0-0x80131234 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1
#include "types.h"
#include "structs.h"
void fn_80032088(s32);
s32 fn_8012ED98(void);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
s32 fn_801309EC(Unk_15EF4A35 *);
void fn_80126F88(Unk_80577C09 *, CStruct *);
void fn_8012EE64(Unk_069CE08E *, s32);
void fn_801311A0(Unk_15EF4A35 *arg0, s32 arg1, Unk_C8FEE62D *arg2, Unk_80577C09 *arg3) {
    CScript *r31;
    CStruct *obj;
    s32 ok;

    fn_80032088(0xF8);
    r31 = (CScript *) fn_8012ED98();
    fn_8012F260((Unk_15EF4A35 *) r31, (s32) arg0, arg1, (CStruct *) arg2);
    fn_801309EC((Unk_15EF4A35 *) r31);
    obj = (CStruct *) r31->unk0x18;
    ok = (obj != 0);
    if (ok != 0)
        fn_80126F88(arg3, obj);
    if (r31 != 0)
        fn_8012EE64((Unk_069CE08E *) r31, 3);
}
