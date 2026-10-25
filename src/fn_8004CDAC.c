// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004CDAC-0x8004CE30 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
void fn_8009E1F0(void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 Mem_NewZero(s32);
s32 fn_8000F2F8(Unk_9F352E7C *, void *);
extern char lbl_802FFE98[];
extern char lbl_80300434[];
void fn_8000F320(Unk_F12C5E01 *self);
typedef struct { char pad0x0[0x10]; s16 unk0x10; s32 unk0x14; } View4CDAC;
bool ScriptScreenElementSystemInit(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;
    void *temp_r10;
    Unk_89783F6B *temp_r3;
    View4CDAC *temp_r9;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x124);
    Mem_NewZero(0x198);
    temp_r30 = fn_8004DC78();
    fn_8000F320(*(void * *)&lbl_802FFE98);
    fn_8009E1F0(temp_r30, QB_ROOT_WINDOW);
    temp_r10 = *(void * *)&lbl_80300434;
    temp_r9 = (View4CDAC *)((Unk_C7387A53 *)temp_r10)->unk0x2C;
    ((s32 (*)(void *, void *))temp_r9->unk0x14)(temp_r10 + temp_r9->unk0x10, temp_r30);
    return true;
}