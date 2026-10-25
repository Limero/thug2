// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-O1` -> 67.78% to 76.67%.
// PARKED 67.5% (twin of fn_8021B574 — same residual, see that file's park note)
// family=m2c range=0x8021B6C8-0x8021B830 size=360B
// FLAG: -O1
#include "types.h"
#include "structs.h"
extern char lbl_802A8030[];
extern char lbl_802A83F8[];
s32 fn_8022989C(CScript * arg0);
s32 fn_8022AA20(CScript * arg0);
s32 fn_8022986C(CScript * arg0);
s32 fn_80219638(Unk_C7387A53 * arg0);
void *fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
void *fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);

/* search-state frame template: r1+8 .. r1+0x27 (locals 0x20 => frame 0x38 w/ stmw r28) */
struct ss_B6C8 {
    u8 b0;          /* +0x00 -> r1+0x08 */
    u8 _p0[3];
    s32 idx;        /* +0x04 -> r1+0x0C (callee out+4) */
    void *filter;   /* +0x08 -> r1+0x10 (callee out+8) */
    u8 _g[4];       /* +0x0C -> r1+0x14 */
    void *unk10;    /* +0x10 -> r1+0x18 (addi anchor) */
    void *walk;     /* +0x14 -> r1+0x1C */
    s32 mode;       /* +0x18 -> r1+0x20 */
    u8 tail[4];     /* +0x1C -> size 0x20 */
};

s32 fn_8021B6C8(Unk_C7387A53 *arg0) {
    struct ss_B6C8 ss;
    Unk_9994C3F5 *tp;
    register void *t1 __asm__("r4");
    CStruct *anchor;
    void *e;
    s32 var_r9;
    Unk_C7387A53 *w;
    register void *node __asm__("r11");
    register void *val __asm__("r3");
    register void *n2 __asm__("r11");
    register void *nx __asm__("r11");
    void *w2;
    s32 count;

    tp = t1 = &ss;
    __asm__("" : "+r"(t1));
    ss.idx = 0;
    ss.mode = (s32)lbl_802A8030;
    ss.filter = (void *)lbl_802A83F8;
    anchor = &ss.unk10;
    __asm__("" : "+r"(anchor));
    *((void * *)&anchor->unk0x4) = 0;
    count = 0;
    e = fn_8021D454(arg0, t1, 1);
    if (e != NULL) {
        do {
            if ((fn_8022989C(e) != 0) && (fn_8022AA20(e) == 0)) {
                if ((fn_8022986C(e) == 0) || (fn_80219638(arg0) == 0)) {
                    goto block_5;
                }
            } else {
block_5:
                count += 1;
            }
            e = fn_8021D4E8(arg0, &ss, 1);
        } while (e != NULL);
    }
    w = (char *)arg0 + 0x148;
    ss.walk = w;
    __asm__("" ::: "memory");
    node = w->unk0xC;
    if ((s32)((CStruct *)node)->unk0x4 == -1) {
        node = NULL;
    }
    ss.walk = node;
    if (node != NULL) {
        val = ((CStruct *)node)->unk0x4;
    } else {
        val = 0;
    }
    n2 = val;
    if (n2 != NULL) {
        do {
            if ((((Unk_C7387A53 *)n2)->unk0x20 & 0xC) == 4) {
                count += 1;
            }
            w2 = *(void **)&ss.walk;
            nx = ((Unk_E266FB50_2 *)w2)->unk0xC;
            if ((s32)((CStruct *)nx)->unk0x4 == -1) {
                nx = NULL;
            }
            *(void **)&ss.walk = nx;
            if (nx == NULL) goto block_null;
            n2 = *((void * *)&((CStruct *)nx)->unk0x4);
            goto block_test;
block_null:
            n2 = NULL;
block_test:
            ;
        } while (n2 != NULL);
    }
    *((void * *)&tp->unk0x8) = (void *)lbl_802A83F8;
    ss.mode = (s32)lbl_802A8030;
    return count;
}
