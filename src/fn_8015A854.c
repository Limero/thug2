// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A854-0x8015A998 (324B). Byte-identical.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803A00D0[];
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void *Mem_NewZero(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
bool ScriptAddToCutsceneDestroyList(CStruct *pParams, CScript *pScript) {
    volatile s32 sp8[2];
    volatile s32 sp10[2];
    volatile s32 sp18[2];
    s32 sp20;
    s32 sp24;
    s32 sp28;
    CStruct *head;
    void *nxt;
    void *headcopy;
    Unk_9994C3F5 *head2;
    s32 eacret;
    CStruct *node;
    CStruct *nn;
    s32 *listp;
    s32 cnt_tmp;

    GetChecksum_2(pParams, QB_NAME, &sp20, 1);
    GetChecksum_2(pParams, QB_DESTROY_FUNC, &sp24, 1);
    sp28 = 0;
    GetStructure_2(pParams, QB_DESTROY_PARAMS, &sp28, 0);
    nxt = NULL;
    head = (void *)lbl_803A00D0[0];
    sp8[0] = (s32)head;
    if (head != NULL) {
        nxt = *((void * *)&head->unk0x4);
    }
    sp10[0] = (s32)nxt;
    if (nxt != head) {
        void *term = head;
        __asm__("" : "+r"(term));
        do {
            nxt = *(void **)((char *)(void *)sp10[0] + 4);
            sp10[0] = (s32)nxt;
        } while (nxt != term);
    }
    node = Mem_NewZero(0x10);
    node->unk0x4 = 0;
    node->unk0x8 = 0;
    eacret = CStruct_ctor(CStruct_new(8));
    node->unk0xC = eacret;
    node->unk0x4 = sp20;
    node->unk0x8 = sp24;
    if (sp28 != 0) {
        fn_80126FF4(eacret, sp28);
    }
    head2 = (void *)lbl_803A00D0[0];
    sp18[0] = (s32)head2;
    listp = lbl_803A00D0;
    nn = Mem_Alloc2(0xC);
    cnt_tmp = *(listp + 1);
    nxt = *((void * *)&head2->unk0x8);
    nn->unk0x0 = (s32)node;
    *(listp + 1) = cnt_tmp + 1;
    nn->unk0x8 = (s32)nxt;
    nn->unk0x4 = (s32)head2;
    head2->unk0x8 = (s32)nn;
    *(s32 *)((char *)*((void * *)&nn->unk0x8) + 4) = (s32)nn;
    return true;
}
