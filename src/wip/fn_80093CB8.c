// WIP DRAFT (non-matching) — hand rewrite 2026-10-10.
// FLAG: -fno-strength-reduce
// family=m2c range=0x80093CB8-0x80093E14 size=348B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Want shape (87 words): frame 0xB60, saves r26-r31+LR.
//   out = 0xB40 bytes at sp+8 (addi r5, r1, 8).
//   r26 = save (lbl_803016B0 word).
//   r27 = 0x80300000 hi-home (ONLY the two loop-2 COUNT reads use it:
//         `lwz r0, 0x1824(r27)`; every other 0x8030xxxx symbol uses a
//         fresh lis). Born at 0xCDC (right after COUNT=0, before G1-test)
//         via the cbase mechanism below.
//   Loop 1 (collect): n=0 (r11); t = tbl home (r8); node = HEAD (r10);
//     NULL pre-check + do-while. Body: boolize (u16 flag != 0) via setcc
//     (li/cmpwi/bne/li) + beq-latch; h2 = node->0x54, beq-latch on h2->8;
//     `slwi r0, r11, 2; stwx r10, r8, r0` (explicit-shift temp into
//     register-base home — resists strength reduction); n++; latch
//     node = node->0x6C, bne-top. COUNT = n via PLAIN symbol (fresh lis,
//     as want has it — NOT via cbase).
//   sort call guarded by COUNT>0 / COUNT>1 (both sides re-read COUNT via
//     PLAIN symbol; want uses fresh lis there too).
//   Loop 2: i (r29), off bytes (r31), prev (r6), e (r3, unpinned so the
//     call needs no `mr`). e-load via `(char *)SYMBOL + off` (hi shared
//     in r28 at link, `addi r30, r28, lo; lwzx r3, r30, r31`).
//   Entry cmpw(off,COUNT) + `b test` sharing the latch `bge done`:
//     written as off-guard + do-while(i). PARKED residual (loop-2 entry
//     + rotation). Tried 2026-10-10, all worse (reverted): pure-goto
//     call-first layout 55.2% (loses entry COUNT-load/cmpw/lis = 3 words
//     short, cascade); guard + goto-test 64.8% (extra `b test` word
//     misaligns); guard-fallthrough-into-top 65.6% (guard-pass calls
//     with unset e -> spurious `mr r3,r31` + reschedule). The want entry
//     (branchless feeder cmpw) is not expressible in C; guard+do-while
//     at 75.9% is the best measured. Loop-1 fully clean (boolize,
//     slwi+stwx via -fno-strength-reduce, latch, COUNT store).
//   2026-10-10: 56.3% -> 69.0% (prologue source-order: G1 read-early /
//     test-late via `g` tmp + store-g + HEAD-load-after-store; cbase init
//     as ABSOLUTE (s32 *)0x80300000 so it folds to one `lis r27` — the
//     symbol-arithmetic form emitted 3 words) -> 75.9% (FLAG
//     -fno-strength-reduce fixes loop-1 reduction split).
#include "types.h"

typedef struct CBSub CBSub;
struct CBSub {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    char pad0xC[0x60];
    s32 unk0x6C;
};

typedef struct CBNode CBNode;
struct CBNode {
    char pad0x0[0x48];
    s32 unk0x48;
    char pad0x4C[0x4];
    u16 unk0x50;
    char pad0x52[0x2];
    CBSub *unk0x54;
    char pad0x58[0x14];
    struct CBNode *unk0x6C;
};

extern bool lbl_80305E78;
extern s32 lbl_8030181C;
extern CBNode *lbl_80301820;
extern s32 lbl_80301824;
extern s32 lbl_803016B0;
extern CBNode *lbl_803795DC[];
s32 fn_80092F30(void **, void **);
void fn_8026A07C(void *, u32, u32, s32 (*)(void **, void **));
void fn_800931C8(void *, s32, void *, s32);

void fn_80093CB8(void) {
    char out[0xB40];
    CBNode *node;
    CBNode *e;
    CBNode **t;
    CBSub *h2;
    s32 n;
    register s32 save __asm__("r26");
    register s32 *cbase __asm__("r27");
    register s32 i __asm__("r29");
    register s32 off __asm__("r31");
    s32 prev;
    s32 f;
    s32 g;

    g = lbl_80305E78;
    lbl_80301824 = 0;
    cbase = (s32 *)0x80300000;
    if (g != 0) {
        return;
    }
    lbl_8030181C = g;
    node = lbl_80301820;
    if (node != NULL) {
        n = 0;
        t = lbl_803795DC;
        do {
            f = (node->unk0x50 != 0);
            if (f == 0) {
                goto latch1;
            }
            h2 = node->unk0x54;
            if (h2->unk0x8 == 0) {
                goto latch1;
            }
            *(CBNode **)((char *)t + (n << 2)) = node;
            n++;
        latch1:
            node = node->unk0x6C;
        } while (node != NULL);
        lbl_80301824 = n;
    }
    save = lbl_803016B0;
    if (lbl_80301824 > 0) {
        if (lbl_80301824 > 1) {
            fn_8026A07C(lbl_803795DC, lbl_80301824, 4, fn_80092F30);
        }
        i = 0;
        off = 0;
        prev = 0;
        if (off >= cbase[0x609]) {
            goto done;
        }
        do {
        top:
            e = *(CBNode **)((char *)lbl_803795DC + off);
            if (e->unk0x48 == 0) {
                goto done;
            }
            if (e->unk0x54->unk0x6C > 0) {
                goto done;
            }
            fn_800931C8(e, 3, out, prev);
            i++;
            off += 4;
            prev = (*(CBNode **)((char *)lbl_803795DC + off))->unk0x48;
        } while (i < cbase[0x609]);
    }
done:
    lbl_803016B0 = save;
}
