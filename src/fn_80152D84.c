// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152D84-0x80152E10 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A7DA8[];
extern void* lbl_80305EAC;
s32 fn_80128A90(CStruct *, void *);
s32 fn_80128C80(CStruct *, void *, void *, void *);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_8009F9AC(Unk_6A70655D *, void *);
bool ScriptPauseSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r31;
    Unk_9994C3F5 *temp_r3;
    Unk_E71E4713 *temp_r9;

    temp_r31 = fn_80128A90(pParams, (void *)(s32)lbl_802A7DA8);
    fn_80128C80(pParams, 0, &sp8, 1);
    temp_r3 = fn_801746A4(lbl_80305EAC, sp8);
    if (temp_r3 != 0) {
        temp_r9 = temp_r3->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x64)((void *)((char *)temp_r3 + temp_r9->unk0x60));
        fn_8009F9AC(temp_r3, temp_r31);
    }
    return true;
}
