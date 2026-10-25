// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A53C0-0x801A54DC (284B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct { s32 f0; s32 f1; s32 f2; s32 f3; } Out16;

void fn_801A7EB4(Unk_C7387A53 * arg0);
s32 fn_801A56BC(s32 arg0);
s32 fn_80128E94(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
void fn_80129570(void *arg0, s32 arg1);
s32 fn_80129528(CStruct * arg0, s32 arg1);
s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
s32 fn_80128C80(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

// s_find_trick_in_mapping @ 0x801A53C0
void *s_find_trick_in_mapping(void *arg0, void *arg1, s32 arg2) {
    Out16 st;
    void *sp18;
    s32 sp1C;
    s32 temp_r30;
    s32 temp_r31;

    fn_801A7EB4(&st);
    temp_r31 = fn_801A56BC(arg1);
    fn_80128E94(temp_r31, 0, &sp18, 1);
    if (arg2 >= 0 && arg2 < ((CStruct *)sp18)->unk0x4) {
    } else {
        fn_80129570((char *)arg1 + 0x6C, 0);
        fn_80129570(temp_r31, 0);
    }
    fn_80128E34((temp_r30 = fn_80129528(sp18, arg2)), QB_TRICKNAME, &st.f1, 1);
    fn_80128E34(temp_r30, QB_TRICKSLOT, &st.f2, 1);
    if (fn_80128C80(temp_r30, QB_ISCAT, (sp1C = 0, &sp1C), 0), sp1C != 0) {
        st.f3 = 1;
    }
    *(Out16 *)arg0 = st;
    return arg0;
}
