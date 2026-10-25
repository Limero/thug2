// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005841C-0x80058550 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct { char _00[0x20]; s16 unk20; s32 unk24; } RecA_t;
typedef struct { char _00[0x68]; s16 unk68; s32 unk6C; } RecB_t;

typedef struct {
    s32 unk0; s32 unk4; s32 unk8; s32 unkC; s32 unk10; s32 unk14;
} New_t;

typedef struct {
    s32 unk0; s32 unk4; s32 unk8; s32 unkC; s32 unk10; s32 unk14;
    s32 unk18; s32 unk1C;
} Arg0_t;

s32 fn_800556B0(void);
s32 fn_8005EF7C(void *arg0, void *arg1, s32 arg2);
void fn_800FB184(void *arg0, s32 arg1);
void fn_8005F408(void *arg0, s32 arg1);

void *fn_8005841C(Arg0_t *arg0, void *arg1, s32 arg2, s32 arg3) {
    RecA_t *rec = *(RecA_t **)((char *)arg0 + 0x18);
    New_t *nw = ((s32 (*)(void *, void *, s32))rec->unk24)((char *)arg0 + rec->unk20, arg1, arg3);
    void *sub;
    void *sub14;

    if (nw != NULL) {
        nw->unk0 = fn_800556B0();
        nw->unk4 = arg0->unk4 | 2;
        nw->unkC = arg0->unkC;
        if (arg0->unk10 != 0) {
            nw->unk10 = fn_8005EF7C(arg0->unk10, arg1, arg3);
        }
        sub14 = arg0->unk14;
        if (sub14 != NULL) {
            RecB_t *rec2 = *(RecB_t **)((char *)sub14 + 0xC);
            sub = ((s32 (*)(void *, void *))rec2->unk6C)((char *)sub14 + rec2->unk68, arg1);
            if (sub != NULL) {
                nw->unk14 = (s32)sub;
                fn_800FB184(sub, nw->unk0);
                nw->unk4 &= QB_UNKNOWN_0xFFFFFFBF;
                if (arg2 != 0) {
                    nw->unk4 |= 4;
                }
                if (nw->unk10 != 0) {
                    fn_8005F408(nw->unk10, *(s32 *)((char *)sub + 8));
                }
            } else {
                nw->unk14 = 0;
                nw->unk4 &= QB_UNKNOWN_0xFFFFFFBF;
                if (nw->unk10 != 0) {
                    fn_8005F408(nw->unk10, 0);
                }
            }
        }
        return nw;
    }
    return NULL;
}
