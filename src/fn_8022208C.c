// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022208C-0x802221E8 (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_802A83F8[];
extern s32 lbl_80305F9C;
extern s32 lbl_80305EAC;
extern char *strcpy(char *, char *);

s32 fn_8021D454(s32, void *, s32);
s32 fn_8021D4E8(s32, void *, s32);
s32 fn_80219698(s32);
s32 fn_8022989C(void *);
void fn_8021DAD4(void *, void *, s32);
void fn_80173910(void *, void *);
void fn_80137CB4(void *);
s32 fn_8021B55C(void *, s32);
void fn_8013DE78(void *, void *);

typedef struct {
    s32 ctx[4];
    struct {
        s8 b00;
        s8 b01;
        char str[0x16];
    } name;
    struct {
        u8 t00;
        char p01;
        u16 t02;
        void *next;
        char pad08[4];
        s32 v0C;
        u8 v10;
        char pad11[0x17];
    } msg;
} Frame_t;

typedef struct {
    char pad00[0x18];
    s32 f18;
    char pad1C[0x1BC];
    s32 f1D8;
} Node_t;

bool ScriptKickPlayer(void) {
    Frame_t fr;
    s32 *q;
    register s32 *p __asm__("r19");
    s32 mgr;
    s32 cnt;
    s32 flag;
    register s32 t29 __asm__("r29");
    s32 t30;
    s32 t30b;
    Node_t *node;

    mgr = lbl_80305F9C;
    q = &fr.ctx[0];
    __asm__("mr %0,%1" : "=r"(p) : "r"((void *)q));
    q[2] = (s32)lbl_802A83F8;
    q[1] = 0;
    cnt = 0;
    node = (Node_t *)fn_8021D454(mgr, q, 1);
    if (node != NULL) {
        do {
            flag = 1;
            if (!(node->f1D8 & 0x400)) {
                flag = 0;
            }
            if (flag != 0) {
                if (fn_80219698(mgr) != 0) {
                    t29 = node->f18;
                    t30 = fn_8022989C(node);
                    fn_8021DAD4((void *)mgr, node, 4);
                    if (t30 == 0) {
                        fn_80173910((void *)lbl_80305EAC, (void *)t29);
                    }
                } else {
                    fn_80137CB4(&fr.msg);
                    t30b = fn_8021B55C((void *)mgr, 0);
                    fr.name.b00 = 0;
                    fr.name.b01 = cnt;
                    strcpy(&fr.name.str[0], (char *)node + 0x3C);
                    fr.msg.next = &fr.name;
                    fr.msg.t02 = 0x12;
                    fr.msg.t00 = 0x61;
                    fr.msg.v0C = 2;
                    fr.msg.v10 = 8;
                    fn_8013DE78((void *)t30b, &fr.msg);
                }
            } else {
                cnt += 1;
                if ((node = (Node_t *)fn_8021D4E8(mgr, (void *)&fr.ctx[0], 1)) != NULL) {
                    continue;
                }
            }
            break;
        } while (1);
    }
    p[2] = (s32)lbl_802A83F8;
    return true;
}
