// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801875CC-0x801876C8 (252B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void fn_801270B4(CStruct *, s32);
extern void CStruct_dtor(CStruct *);
extern s32 fn_80127358(CStruct *, Unk_C7387A53 *);
extern s32 ContainsFlag(CStruct *, s32);
extern void fn_80127C14(CStruct *, s32, CStruct *);

void fn_801875CC(Unk_526DA6F2 *arg0, s32 arg1) {
    CStruct *cur;
    void *next;

    if (arg1 != 0) {
        fn_801270B4(arg0->unk0x3A8, arg1);
    } else {
        CStruct_dtor(arg0->unk0x3A8);
    }
    cur = (void *)fn_80127358(arg0->unk0x1C, NULL);
    if (cur != NULL) {
        do {
            next = (void *)fn_80127358(arg0->unk0x1C, cur);
            if (arg1 != 0) {
                if (cur->unk0x4 == QB_GOALMANAGER_PARAMS) {
                    goto block_874;
                }
                if (!(cur->unk0x8 != 0 && (ContainsFlag(cur->unk0x8, arg1) != 0))) {
                    goto block_next;
                }
            }
            fn_801270B4(arg0->unk0x1C, cur->unk0x4);
            goto block_next;
block_874:
            CStruct_dtor(cur->unk0x8);
            fn_80127C14(cur->unk0x8, QB_DIFFICULTY_LEVELS, arg0->unk0x3A8);
block_next:
            cur = next;
        } while (cur != NULL);
    }
    arg0->unk0x44 = 0;
    arg0->unk0x48 = 0;
    arg0->unk0x4C = 0;
    arg0->unk0x50 = 0;
}
