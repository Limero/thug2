// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022AB28-0x8022ACE0 (440B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802B03E0[];
extern s32 lbl_80305FC0;
extern bool lbl_80305FC4;
extern s32 lbl_80305FC8;
extern s32 fn_800145AC(void);
extern void fn_8022B484(s32 arg0, s32 arg1);
extern void fn_8022B000(void *arg0, void *arg1, s32 arg2);
extern void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

struct LS { s32 pad; volatile s32 iter; void *volatile hc; };

void fn_8022AB28(Unk_C7387A53 *arg0) {
    struct LS ls;
    struct LS *p;
    register struct LS *q __asm__("r27");
    register s32 mgr __asm__("r28");
    register void *n __asm__("r11");
    char *itv;
    void *nd;
    CStruct *cur;
    void *tailv;
    void *tn;
    register void *tp __asm__("r11");
    s32 cnt;
    CStruct *w;
    char *h1;
    Unk_42076946 *h2;

    mgr = arg0->unk0x20;
    if ((u32)(fn_800145AC() - lbl_80305FC8) > 0xBB8) {
        lbl_80305FC8 = fn_800145AC();
        return;
    }
    if (lbl_80305FC4 == 0) {
        return;
    }
    if ((u32)(fn_800145AC() - lbl_80305FC0) <= 0x1F4) {
        return;
    }

    p = &ls;
    p->hc = &lbl_802B03E0;
    p->iter = 0;
    fn_8022B484(mgr, 1);
    __asm__ __volatile__("mr %0,%1" : "=r"(q) : "r"(p));
    itv = (char *)mgr + 0x190;
    p->iter = (s32)itv;
    n = ((Unk_E266FB50_2 *)itv)->unk0xC;
    if (((CStruct *)n)->unk0x4 == -1) {
        n = NULL;
    }
    q->iter = (s32)n;
    if (n == NULL) {
        __asm__ __volatile__("li %0,0" : "=r"(n));
    } else {
        __asm__ __volatile__("lwz %0,4(%0)" : "+b"(n));
    }
    cur = n;
    if (cur == NULL) {
        goto exit_body;
    }
    h1 = (char *)mgr + 0x178;
    do {
        itv = (char *)(q->iter);
        n = ((Unk_E266FB50_2 *)itv)->unk0xC;
        if (((CStruct *)n)->unk0x4 == -1) {
            n = NULL;
        }
        q->iter = (s32)n;
        nd = n ? *((void * *)&((CStruct *)n)->unk0x4) : NULL;

        tn = *((void * *)&cur->unk0xC);
        tp = *((void * *)&cur->unk0x10);
        cnt = 0;
        __asm__ __volatile__("addi %0,%1,0x178" : "=r"(h2) : "b"(mgr));
        ((Unk_C7387A53 *)tp)->unk0xC = (s32)tn;
        *(s32 *)(cur->unk0xC + 0x10) = cur->unk0x10;
        *((void * *)&cur->unk0xC) = cur;
        *((void * *)&cur->unk0x10) = cur;

        w = ((Unk_E266FB50_2 *)h1)->unk0xC;
        goto check2;
        do {
            cnt++;
            w = *((void * *)&w->unk0xC);
        check2:
            if (w->unk0x4 == -1) {
                w = NULL;
            }
        } while (w != NULL);

        fn_8022B000((void *)mgr, cur, cnt);

        tailv = *((void * *)&h2->unk0x10);
        *((void * *)&cur->unk0xC) = h2;
        *((void * *)&cur->unk0x10) = tailv;
        *(void **)(*((void * *)&h2->unk0x10) + 0xC) = cur;
        *((void * *)&h2->unk0x10) = cur;

        cur = nd;
    } while (cur != NULL);

exit_body:
    Script_RunScript(QB_UPDATE_LOBBY_SERVER_LIST, 0, 0, 0, 0);
    {
        register char *a9 __asm__("r9");
        char *a11;
        __asm__ __volatile__("lis %0,%1@ha" : "=r"(a9) : "s"(lbl_802B03E0));
        __asm__ __volatile__("lis %0,lbl_80305FC4@ha" : "=b"(a11));
        __asm__ __volatile__(
            "li 0,0\n\t"
            "addi %0,%0,0x3e0\n\t"
            "stw 0,0x5fc4(%1)\n\t"
            "stw %0,8(%2)"
            : "+r"(a9)
            : "b"(a11), "b"(q)
            : "memory", "r0");
    }
}
