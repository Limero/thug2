// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209A2C-0x80209C1C (496B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_80126EDC(CStruct *, CStruct *);
void fn_8009F190(Unk_C8FEE62D * arg0);
void fn_8012F8E8(Unk_FFAD6788 * arg0, s32 arg1, CStruct * arg2);
s32 fn_80126F40(CStruct *, CStruct *);
s32 CStruct_delete(CStruct *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetStructure(s32, s32);
void fn_801F0E84(CScript *);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_8009F204(Unk_C8FEE62D * arg0, void *arg1, Unk_C8FEE62D * arg2);
void fn_801309EC(Unk_DB0E2BAB * arg0);
void fn_8020C500(Unk_90685748 * arg0);
void fn_80209A2C(Unk_605C573D *arg0, CStruct *arg1) {
    struct {
        s32 f8;
        s32 padC;
        s32 f10;
        s32 f14;
        s32 f18;
        s32 f1C;
        s32 f20;
        s32 f24;
    } fr;
    s32 entry;
    s32 temp_r3;
    Unk_C8FEE62D *temp_ptr;

#define sp8 fr.f8
#define sp10 fr.f10
#define sp14 fr.f14
#define sp18 fr.f18
#define sp1C fr.f1C
#define sp20 fr.f20
#define sp24 fr.f24
    sp10 = 0;
    sp14 = 0;
    GetChecksum_2(arg1, QB_SCRIPTTORUNFIRST, &sp10, 0);
    GetStructure_2(arg1, QB_PARAMS, &sp14, 0);
    arg0->unk0xA68 = 0;
    if ((arg0->unk0x12AC) != 0) {
        arg0->unk0x12AC = 0;
        if (sp10 != 0) {
            fn_80126EDC(&sp8, arg1);
            fn_8009F190((void *)(arg0->unk0xC));
            fn_8012F8E8(*(s32 *)(arg0->unk0xC + 0x14), sp10, sp14);
            fn_80126F40(arg1, &sp8);
            CStruct_delete(&sp8, 2);
        }
        temp_r3 = fn_801259C8(arg0->unk0x12B0, 0);
        if (temp_r3 == 0) {
            return;
        }
        entry = fn_80129528(temp_r3, arg0->unk0x12B4);
        sp18 = 0;
        GetChecksum_2(entry, QB_TRICKSLOT, &sp18, 0);
        if (sp18 != 0) {
            sp1C = 0;
            GetChecksum_2(arg0->unk0xA6C, sp18, &sp1C, 0);
            if (sp1C != 0) {
                temp_r3 = GetStructure(sp1C, 0);
                if (temp_r3 != 0) {
                    entry = temp_r3;
                }
            }
        }
        sp20 = 0;
        GetChecksum_2(entry, QB_SCR, &sp20, 0);
        if (sp20 == 0) {
            return;
        }
        fn_801F0E84((void *)(arg0->unk0x30));
        sp24 = 0;
        arg0->unk0xA68 = arg0->unk0x12C0;
        GetStructure_2(entry, QB_PARAMS, &sp24, 0);
        temp_ptr = arg0->unk0xC;
        if (arg1 != 0) {
            fn_80126FF4(arg1, sp24);
            fn_8009F204((void *)temp_ptr, sp20, arg1);
        } else {
            fn_8009F204((void *)temp_ptr, sp20, sp24);
        }
        fn_801309EC((void *)(temp_ptr->unk0x14));
        *(s32 *)(arg0->unk0x34 + 0x144) = 1;
        fn_8020C500(arg0);
    }
}
