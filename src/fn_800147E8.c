// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800147E8-0x80014898 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Obj_800147E8 {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[0x14];
    char unk0x20[0x64];
    char unk0x84[0x18];
} Obj_800147E8;
s32 fn_8000DE40(void);
void *fn_8000DEBC(void *, void *, s32);
s32 fn_8000DE5C(void);
void *fn_80014638(void);
char *strcpy(char *, const char *);
s32 fn_8001B658(void *, void *);
s32 fn_8001B6A8(void *);
void fn_800146A4(void *);
void *fn_800147E8(Unk_C8FEE62D *arg0, void *arg1) {
    Obj_800147E8 *temp_r3;
    void *temp_r30;
    void *temp_r31;

    if (fn_8000DE40() != 0) {
        temp_r31 = fn_8000DEBC(arg0, arg1, 0);
        if (fn_8000DE5C() != 0) {
            return temp_r31;
        }
    }
    temp_r3 = (Obj_800147E8 *) fn_80014638();
    if (temp_r3 != NULL) {
        strcpy(temp_r3->unk0x20, (const char *) arg0);
        temp_r30 = temp_r3->unk0x84;
        if (fn_8001B658(temp_r30, arg0) != 0) {
            temp_r3->unk0x8 = fn_8001B6A8(temp_r30);
            return temp_r3;
        }
        fn_800146A4(temp_r3);
    }
    return NULL;
}
