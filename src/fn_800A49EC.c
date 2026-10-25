// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A49EC-0x800A4AB4 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80301A78[];
void fn_800A5BF4(s32 arg0, void *arg1, s32 arg2);
void CStruct_delete(s32 arg0, s32 arg1);

typedef struct {
    void *unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[4];
} P800A49EC;

typedef struct {
    P800A49EC *unk0x0;
    s32 unk0x4;
} O800A49EC;

void fn_800A49EC(O800A49EC *arg0, s32 arg1, s32 arg2) {
    s32 i;
    P800A49EC *p = arg0->unk0x0;

    for (i = 0; i < arg0->unk0x4; i++) {
        if (p->unk0x8 == arg2 || arg2 == QB_ALL_GROUPS) {
            if (p->unk0x0 != NULL) {
                fn_800A5BF4(*(s32 *)lbl_80301A78, p->unk0x0, arg1);
            }
            p->unk0x4 = QB_NULL_SCRIPT;
            if (p->unk0xC != 0) {
                CStruct_delete(p->unk0xC, 3);
                p->unk0xC = 0;
            }
        }
        p++;
    }
}
