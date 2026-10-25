// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ACAB0-0x800ACBB8 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E274(Unk_31DE137E *, s32);
s32 fn_8009F678(Unk_6A70655D *);
s32 Mem_NewZero(s32);
void AddInteger(CStruct *, s32, s32);
void Script_RunScript(void *, void *, void *, void *, void *);
extern char lbl_80301A38[];
extern char lbl_80298590[];
extern char lbl_8029858C[];
void *fn_800ACAB0(void *arg0, s32 arg1) {
    f32 sp8[4];
    f32 *sp8p;
    void *temp_r10;
    void *temp_r30;
    Unk_89391A04 *temp_r9;
    Unk_89391A04 *temp_r9_2;
    f32 temp_f0;
    f32 temp_f13;

    temp_r30 = (void *)fn_8009F678(Mem_NewZero(0x118));
    fn_8009E274(temp_r30, QB_OBJECT_TYPE_COMPOSITE);
    temp_r10 = (void *)*(s32 *)&lbl_80301A38;
    temp_r9 = *(Unk_89391A04 **)((char *)temp_r10 + 0x2C);
    ((s32 (*)(void *, void *))temp_r9->unk0x14)((char *)temp_r10 + temp_r9->unk0x10, temp_r30);
    AddInteger((CStruct *)arg1, QB_ISBLOCKING, *(s32 *)((char *)arg0 + 0x34B8));
    Script_RunScript(QB_CUTSCENEOBJ_ADD_COMPONENTS, (void *)arg1, temp_r30, 0, 0);
    temp_r9_2 = *(Unk_89391A04 **)((char *)temp_r30 + 0x8);
    ((s32 (*)(void *))temp_r9_2->unk0x4C)((char *)temp_r30 + temp_r9_2->unk0x48);
    Script_RunScript(QB_CUTSCENEOBJ_INIT_MODEL, (void *)arg1, temp_r30, 0, 0);
    temp_f0 = *(f32 *)lbl_8029858C;
    temp_f13 = *(f32 *)lbl_80298590;
    sp8p = sp8;
    *(f32 *)sp8p = temp_f0;
    *(f32 *)(sp8p + 3) = temp_f13;
    *(f32 *)(sp8p + 2) = temp_f0;
    *(f32 *)(sp8p + 1) = temp_f0;
    *(__ps_t *)((char *)temp_r30 + 0x58) = *(__ps_t *)sp8p;
    *(__ps_t *)((char *)temp_r30 + 0x60) = *(__ps_t *)(sp8p + 2);
    return temp_r30;
}
