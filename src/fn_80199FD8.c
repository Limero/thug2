// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199FD8-0x8019A0C4 (236B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern char lbl_802A83F8[];
extern void *fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern void *fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 fn_801403CC(void *arg0);
extern s32 fn_801813F0(CStruct * arg0);
bool fn_80199FD8(void) {
    struct out_s {
        s32 _0;
        s32 _4;
        s32 _8;
        s32 _c;
    } out;
    register struct out_s *op __asm__("r29");
    register struct out_s *p __asm__("r4");
    register s32 mgr __asm__("r30");
    s32 total;
    register s32 lblv __asm__("r9");
    register char *anch __asm__("r11");
    register s32 a0 __asm__("r3");
    register s32 a3 __asm__("r5");
    CScript *node;

    __asm__ volatile("lis %0,%3@ha\n\tlis %1,%4@ha\n\tlwz %2,%3@l(%0)"
                     : "=r"(anch), "=r"(lblv), "=r"(mgr)
                     : "s"(lbl_80305F9C), "s"(lbl_802A83F8));
    p = &out;
    op = p;
    p->_8 = (s32)(lblv - 0x7C08);
    p->_4 = 0;
    __asm__ volatile("" ::: "memory");
    node = fn_8021D454(({ a0 = mgr; a0; }), p,
                       ({ a3 = 0;
                          __asm__ volatile("li %0,0" : "=r"(total));
                          a3; }));
    if (node != NULL) {
        do {
            node = fn_8021D4E8(mgr, &out,
                               (total += node->unk0x38, 0));
        } while (node != NULL);
    }
    if (total == 0) {
        op->_8 = (s32)lbl_802A83F8;
        return false;
    }
    node = fn_8021D454(mgr, &out, 0);
    if (node != NULL) {
        do {
            if (fn_801813F0(fn_801403CC(*((void * *)&node->unk0x18))) == total) {
                op->_8 = (s32)lbl_802A83F8;
                return true;
            }
            node = fn_8021D4E8(mgr, &out, 0);
        } while (node != NULL);
    }
    op->_8 = (s32)lbl_802A83F8;
    return false;
}
