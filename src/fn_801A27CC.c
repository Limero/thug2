// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A27CC-0x801A2888 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80300460;
extern char lbl_80305EAC[];
void fn_801A362C(void *, s32);
u64 fn_8001448C(void);
typedef struct {
    char pad0x0[0x40];
    s16 unk0x40;
    char pad0x42[0x2];
    s32 unk0x44;
    char pad0x48[0x10];
    s16 unk0x58;
    char pad0x5A[0x2];
    s32 unk0x5C;
} Vt27CC;
void fn_801A27CC(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1) {
    Vt27CC *temp_r9;
    Vt27CC *temp_r9_2;
    s32 temp_r4;

    if (arg1 != NULL) {
        temp_r9 = (Vt27CC *)arg1->unk0x14;
        if (((s32 (*)(void *))temp_r9->unk0x44)((char *)arg1 + temp_r9->unk0x40) != 0) {
            temp_r9_2 = (Vt27CC *)arg1->unk0x14;
            if ((((s32 (*)(void *))temp_r9_2->unk0x5C)((char *)arg1 + temp_r9_2->unk0x58) != 0) && (lbl_80300460 == 0) && ((s32) *(s32 *)((char *)(*(void * *)&lbl_80305EAC) + 0x388) != -QB_UNKNOWN_0x16D13502)) {
                fn_801A362C((char *)arg0 + 0x70, arg1->unk0x18);
                temp_r4 = (u32) fn_8001448C() + 1;
                arg0->unk0x140 = temp_r4;
                arg0->unk0x144 = 1;
            }
        }
    }
}
