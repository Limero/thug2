// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A998-0x8015AACC (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern bool lbl_80305DF4;
extern s32 lbl_803A00D0[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 CStruct_delete(CStruct *, s32);
bool ScriptRemoveFromCutsceneDestroyList(CStruct *pParams, CScript *pScript) {
    volatile s32 sp8[2];
    volatile s32 sp10[2];
    volatile s32 sp18[2];
    volatile s32 sp20[2];
    volatile s32 sp28[2];
    volatile s32 sp30[2];
    s32 sp38[2];
    CStruct *head;
    void *nxt;
    void *advnext;
    CStruct *curscan;
    CStruct *curfresh;
    CStruct *entry;
    void *unext;
    s32 *listp;
    s32 zero;
    void *termchk;

    if (lbl_80305DF4 != 0) {
        return false;
    }
    GetChecksum_2(pParams, QB_NAME, &sp38[0], 1);
    nxt = NULL;
    head = (void *)lbl_803A00D0[0];
    sp8[0] = (s32)head;
    if (head != NULL) {
        nxt = *((void * *)&head->unk0x4);
    }
    sp10[0] = (s32)nxt;
    if (nxt == head) {
        return false;
    }
    zero = 0;
    do {
        curscan = (void *)sp10[0];
        entry = *((void * *)&curscan->unk0x0);
        if (entry->unk0x4 == sp38[0]) {
            if (entry != NULL) {
                if (entry->unk0xC != 0) {
                    CStruct_delete(entry->unk0xC, 3);
                    entry->unk0xC = zero;
                }
                Mem_Free(entry);
            }
            listp = lbl_803A00D0;
            curfresh = (void *)sp10[0];
            sp20[0] = (s32)curfresh;
            sp30[0] = (s32)curfresh;
            unext = *((void * *)&curfresh->unk0x4);
            sp28[0] = (s32)curfresh;
            sp20[0] = (s32)unext;
            if (curfresh != (void *)lbl_803A00D0[0]) {
                *(s32 *)(*((void * *)&curfresh->unk0x8) + 4) = curfresh->unk0x4;
                *(s32 *)(*((void * *)&curfresh->unk0x4) + 8) = curfresh->unk0x8;
                Mem_Free(curfresh);
                listp[1] -= 1;
            }
            sp18[0] = sp20[0];
            return true;
        }
        advnext = *((void * *)&curscan->unk0x4);
        termchk = (void *)sp8[0];
        sp10[0] = (s32)advnext;
    } while (advnext != termchk);
    return false;
}
