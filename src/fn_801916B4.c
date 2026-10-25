// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801916B4-0x801917FC (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void AddChecksum(void *, s32, s32);
void fn_80131BAC(void *, s32);
void CStruct_delete(void *, s32);
void fn_800F28E4(void *, void *);
void CStruct_new(s32);
s32 fn_800A398C(s32);
void *GetChecksum_3(void *, s32);
s32 fn_800F2A48(s32, s32, s32);
s32 CStruct_ctor();
s32 fn_801745B4(s32);
extern char lbl_80301A38[];
extern void *lbl_80301B48;
extern char lbl_80305EAC[];
#include "qb_constants.h"
#include "structs.h"

typedef void (*Vtbl_0x64)(void *, s32, void *, s32);
typedef struct {
    char pad0x0[0x60];
    s16 unk0x60;
    Vtbl_0x64 unk0x64;
} Vtbl;

void fn_801916B4(CStruct *arg0) {
    register void *var_r3 __asm__("r30");
    void *temp_r31;
    s32 temp_r4;

    if (arg0->unk0x8 != 0) {
        temp_r4 = arg0->unk0xC;
        if (temp_r4 != 0) {
            if (temp_r4 == QB_SKATER) {
                var_r3 = (void *)fn_801745B4(*(s32 *)&lbl_80305EAC);
            } else {
                var_r3 = (void *)fn_800A398C(*(s32 *)&lbl_80301A38);
            }
            fn_80131BAC(var_r3, QB_GOAL_PLAY_STREAM);
            CStruct_new(8);
            temp_r31 = (void *)CStruct_ctor();
            AddChecksum(temp_r31, QB_TYPE, QB_PARTIALANIM);
            AddChecksum(temp_r31, QB_ID, QB_JAWROTATION);
            if (var_r3 != 0) {
                CScript *cs = (CScript *)GetChecksum_3(var_r3, QB_ANIMBLENDER);
                Vtbl *v = (Vtbl *)cs->unk0x18;
                v->unk0x64((char *)cs + v->unk0x60, QB_REMOVEANIMCONTROLLER, temp_r31, 0);
            }
            if (temp_r31 != 0) {
                CStruct_delete(temp_r31, 3);
            }
            arg0->unk0xC = 0;
        }
        temp_r31 = lbl_80301B48;
        temp_r4 = fn_800F2A48(temp_r31, arg0->unk0x8, 0);
        if (temp_r4 != 0) {
            fn_800F28E4(temp_r31, temp_r4);
        }
        arg0->unk0x8 = 0;
    }
}
