// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB604-0x800AB80C (520B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_800AC810(s32);
extern char lbl_80301B48[];
void fn_800AB80C(Unk_DF035CC0 *);
void StopMusic(void);
void Mem_Free(void *);
extern char lbl_80298730[];
extern char lbl_8029854C[];
void fn_800F28E4(Unk_C7387A53 *arg0, CStruct *arg1);
void * fn_800F2A48(Unk_C7387A53 *arg0, s32 arg1, s32 arg2);
s32 sprintf();
void CStruct_delete(CStruct *, s32);
void fn_8012EC50(s32);
unsigned int fn_8000A778(const char *);
void Script_RunScript(s32, s32, s32, s32, s32);

typedef struct {
    char pad0x0[0x8];
    s16 unk0x8;
    char pad0xA[0x2];
    s32 (*unk0xC)(void *, s32);
} Vtbl;
void fn_800AB604(Unk_A03F5E5B *arg0, s32 arg1) {
    char sp8[0x100];
    s32 *var_r31_2;
    s32 temp_r30;
    s32 var_r28;
    s32 z;
    s32 z2;
    register s32 anc __asm__("r26");
    register s32 var_r30 __asm__("r30");
    void *temp_r11;
    void *temp_r11_2;
    void *temp_r11_3;
    void *temp_r11_4;
    Vtbl *temp_r9;
    Vtbl *temp_r9_2;
    Vtbl *temp_r9_3;
    Vtbl *temp_r9_4;
    char *var_r31;
    temp_r11 = arg0->unk0x4;
    arg0->unk0x34D8 = (s32)lbl_80298730;
    if (temp_r11 != NULL) {
        temp_r9 = (Vtbl *)((Unk_F2F24C3E *)temp_r11)->unk0x2354;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        arg0->unk0x4 = NULL;
    }

    temp_r11_2 = arg0->unk0x10;
    if (temp_r11_2 != NULL) {
        temp_r9_2 = (Vtbl *)((CScript *)temp_r11_2)->unk0x214;
        ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(temp_r11_2 + temp_r9_2->unk0x8, 3);
    }
    temp_r11_3 = arg0->unk0x18;
    arg0->unk0x10 = NULL;
    if (temp_r11_3 != NULL) {
        temp_r9_3 = (Vtbl *)((CScript *)temp_r11_3)->unk0x214;
        ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(temp_r11_3 + temp_r9_3->unk0x8, 3);
    }

    arg0->unk0x18 = NULL;
    var_r30 = 0;
    if (var_r30 < (s32) arg0->unk0x2C58) {
        z = 0;
        var_r31 = (char *)arg0 + 0x2058;
        do {
            temp_r11_4 = ((CStruct *)var_r31)->unk0x4;
            if (temp_r11_4 != NULL) {
                temp_r9_4 = (Vtbl *)((CScript *)temp_r11_4)->unk0x214;
                ((s32 (*)(void *, s32))temp_r9_4->unk0xC)(temp_r11_4 + temp_r9_4->unk0x8, 3);
            }
            ((CStruct *)var_r31)->unk0x8 = z;
            var_r30 += 1;
            var_r31 += 0xC;
        } while (var_r30 < (s32) arg0->unk0x2C58);
    }

    var_r28 = 0;
    fn_800AB80C(arg0);
    fn_800AC810(arg0);
    if (var_r28 < (s32) arg0->unk0x345C) {
        __asm__ volatile("lis %0,%1@ha" : "=r"(anc) : "s"(lbl_80301B48));
        z2 = 0;
        var_r31_2 = (s32 *)((char *)arg0 + 0x2C5C);
        do {
            temp_r30 = *(s32 *)((char *)anc + 0x1B48);
            var_r28 += 1;
            fn_800F28E4((Unk_C7387A53 *) temp_r30, fn_800F2A48((Unk_C7387A53 *) temp_r30, *var_r31_2, 1));
            *var_r31_2 = z2;
            var_r31_2 += 1;
        } while (var_r28 < (s32) arg0->unk0x345C);
    }
    if ((s32) arg0->unk0x34B8 != 0) {
        StopMusic();
        if ((s32) arg0->unk0x34B8 != 0) {
            Script_RunScript(QB_CUTSCENEKILLOBJECTS, 0, 0, 0, 0);
            sprintf(sp8, (s32) lbl_8029854C, arg0->unk0x34BC);
            fn_8012EC50(fn_8000A778(sp8));
        }
    }
    if ((s32) arg0->unk0x34D4 != 0) {
        CStruct_delete((CStruct *) arg0->unk0x34D4, 3);
        arg0->unk0x34D4 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
