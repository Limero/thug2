// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8580-0x801A867C (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305EAC;
extern s32 fn_801A8148(s32, s32);
extern s32 fn_801FC0E0(void);
extern s32 fn_801FBEDC(s32, s32, s32);
#include "qb_constants.h"
#include "structs.h"
bool fn_801A8580(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_DB0E2BAB *p;
    Unk_DB0E2BAB *l2;
    u32 n;
    u32 i;
    s32 j;
    s32 tmp;
    void *mgr;

    p = (Unk_DB0E2BAB *)arg0->unk0x54;
    n = 0;
    goto check;
    do {
        p = (Unk_DB0E2BAB *)p->unk0xC;
        n += 1;
    check:;
        if (p->unk0x4 == -1) {
            p = NULL;
        }
    } while (p != NULL);
    for (i = 0; i < n; i++) {
        l2 = (Unk_DB0E2BAB *)((char *)arg0 + 0x48);
        p = (Unk_DB0E2BAB *)l2->unk0xC;
        j = i;
        if (p->unk0x4 == -1) {
            p = NULL;
        }
        for (;;) {
            if (p != NULL) {
                j--;
                if (j + 1 == 0) {
                    goto found;
                }
                p = (Unk_DB0E2BAB *)p->unk0xC;
                if (p->unk0x4 == -1) {
                    p = NULL;
                }
                continue;
            }
            break;
        }
        p = NULL;
    found:
        fn_801A8148(p->unk0x4, arg1);
    }
    mgr = (void *)lbl_80305EAC;
    if (*(s32 *)((char *)mgr + 0x388) == QB_LOAD_SK5ED_GAMEPLAY) {
        tmp = fn_801FC0E0();
        fn_801FBEDC(tmp, arg0->unk0x18, arg1);
    }
    return true;
}
