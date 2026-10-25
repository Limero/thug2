// PARKED 16%: hand-rebuilt from disasm; semantic body correct. What resisted:
// (1) want's scratch-birth+home-copy pointer pair (addi r11,&sp for entry
//     stores + mr r26,r11 home used ~120 insns later) — GCC merges/coalesces
//     into one reg; register pins on this web are ignored, "+r" barriers send
//     it to r0, two-var forms coalesce.
// (2) register roles r26=&sp-home / r27=cat only land together when cat is
//     pinned r27, but then the scratch/home split still never forms.
// (3) want's loop places the action block OUT-OF-LINE before the loop head
//     (entered by forward ble, fail falls through to exit test); every C shape
//     (while/break/goto-web) gives inline action + inverse bgt-to-exit.
// (4) want keeps found flag in caller-saved r8 (provably never live across a
//     call on any path); GCC allocates it callee-saved, stealing a slot and
//     shifting stmw span/roles.
// Best-match body below (asm-addi pins &sp birth post-call; cat pin r27).
// family=m2c range=0x802183E0-0x80218564 size=388B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8021C1B4(Unk_031F7D04 *, Unk_A1F83658 *);
void fn_8022AABC(Unk_31DE137E *, s32);
s32 fn_8013E034(void *, CStruct *);
void fn_8013F65C(Unk_C7387A53 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_80145008(Unk_FFAD6788 *);
void fn_802204B8(Unk_C7387A53 *);
extern s32 lbl_802FFE98;
extern s32 lbl_80305EAC;
extern char lbl_8029F480[];

void fn_802183E0(Unk_C7387A53 *arg0) {
    struct {
        s32 f0;
        s32 f4;
        s32 f8;
        s32 fC;
    } sp;
    Unk_B0F19D72 *mgr;
    Unk_C7387A53 *obj;
    Unk_C8FEE62D *walker;
    CStruct *next;
    CScript *node;
    Unk_F5317C5D *cb;
    void *varg;
    s32 found;
    s32 *p;
    s32 *wp;
    s32 lblv;
    s32 *ph;
    register s32 cat __asm__("r27");
    s32 count;
    s32 i;
    s32 elem;
    s32 t;

    mgr = (void *)lbl_802FFE98;
    fn_8000F2F8(mgr, mgr->unk0x5F8);
    lblv = (s32)lbl_8029F480;
    obj = *((void * *)&arg0->unk0x20);
    __asm__ __volatile__("addi %0,1,8" : "=r"(p));
    p[2] = lblv;
    p[1] = 0;
    ph = (s32 *)&sp;
    found = 0;
    walker = *((void * *)&obj->unk0x154);
    cat = lbl_80305EAC;
    if (walker->unk0x4 == -1) {
        walker = NULL;
    }
loop:
    if (walker == NULL) {
        goto exit_test;
    }
    next = *((void * *)&walker->unk0xC);
    if (next->unk0x4 == -1) {
        next = NULL;
    }
    node = *((void * *)&walker->unk0x4);
    if ((u32)*((u32 *)&node->unk0x18) > (u32)*(u32 *)(obj->unk0xC + 0x1804)) {
        goto exit_test;
    }
    fn_8021C1B4(obj, node);
    if (node != NULL) {
        fn_8022AABC(node, 3);
    }
    cb = *((void * *)&walker->unk0x14);
    varg = (void *)walker + cb->unk0x8;
    walker = next;
    ((s32 (*)(void *, s32))cb->unk0xC)(varg, 3);
    found = 1;
    goto loop;
exit_test:
    if (found != 0) {
        wp = (s32 *)obj + 3;
        count = 2;
        do {
            elem = *wp;
            wp = wp + 1;
            if (elem != 0) {
                t = fn_8013E034((void *)elem, &sp);
                if (t != 0) {
                    fn_8013F65C(t, 0);
                }
            }
        } while (--count != 0);
        for (i = 0; i <= 7; i++) {
            t = fn_801746A4(cat, i);
            if (t != 0) {
                fn_80145008(t);
            }
        }
        fn_802204B8(obj);
    }
    fn_8000F320(lbl_802FFE98);
    p[2] = (s32)lbl_8029F480;
}
