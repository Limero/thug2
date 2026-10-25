// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004CA68-0x8004CC00 (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void fn_801309EC(void *);
void * fn_80125480(void *arg0);
extern char lbl_80300434[];
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(s32, s32, s32, s32);
s32 fn_80128E34(CStruct *, void *, void *, void *);
s32 Script_SpawnScript(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetElement(CStruct *, Unk_C7387A53 *, CStruct *, void *, void *);

bool ScriptRunScriptOnScreenElement(CStruct *arg0, s32 arg1) {
    struct {
        void *sp10;
        volatile double _dummy;
    } sp10u;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 spC;
    s32 sp8;
    void *temp_r31;
    void *temp_r3;
    void *temp_r3_2;
    void *slot;
    struct { char _0[0x18]; s16 off; s16 _p; void *fn; } *temp_r9;

    GetElement(&sp10u.sp10, *(s32 *)&lbl_80300434, arg0, QB_ID, 1);
    fn_80128E34(arg0, 0, &sp20, 1);
    sp24 = 0;
    GetChecksum_2(arg0, QB_CALLBACK, &sp24, 0);
    sp28 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp28, 0);
    sp2C = 0;
    GetStructure_2(arg0, QB_CALLBACK_PARAMS, &sp2C, 0);
    temp_r3 = fn_80125480(sp20);
    if ((temp_r3 != NULL) && (*(u8 *)((char *)temp_r3 + 2) == 9)) {
        temp_r9 = ((Unk_9994C3F5 *)sp10u.sp10)->unk0x8;
        ((s32 (*)(void *, void *, void *, void *))temp_r9->fn)(sp10u.sp10 + temp_r9->off, sp20, sp28, arg1);
    } else {
        sp8 = 0;
        spC = 0;
        temp_r3_2 = (void *)Script_SpawnScript(sp20, sp28, sp24, sp2C, 0, 0, 0, 0, 0, 0);
        if (temp_r3_2 != NULL) {
            void *t = sp10u.sp10;
            temp_r31 = temp_r3_2 + 0xBC;
            if ( ((Unk_FFAD6788 *)temp_r3_2)->unk0xBC != NULL) {
                CObject_RemoveRefLink(((Unk_FFAD6788 *)temp_r3_2)->unk0xBC, temp_r31);
                ((Unk_FFAD6788 *)temp_r3_2)->unk0xBC = NULL;
            }
            ((Unk_FFAD6788 *)temp_r3_2)->unk0xBC = t;
            if (t != NULL) {
                CObject_AddRefLink(t, temp_r31);
            }
            fn_801309EC(temp_r3_2);
        }
    }
    slot = &sp10u.sp10;
    if (sp10u.sp10 != NULL) {
        CObject_RemoveRefLink(sp10u.sp10, slot);
        sp10u.sp10 = NULL;
    }
    return true;
}
