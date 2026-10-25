// WIP DRAFT — 2026-10-10: 46.7% -> 73.3% (44/60), size-exact 240B.
// Levers: register pins lst->r6 + i->r8 (+6.6, also restored alignment),
// nested-if split-beq scan + do/for bdnz core (structure now exact: beq/lhz/
// andi/beq/li/addi/bdnz all match), q->r11 + e->r9 pins (+20 total), entry
// reorder (sub-load split, found=0 before i++, c-temp). Neutral/reverted:
// full rewrite from scratch (DIFF — extra `b` words from goto-adv), FLAG drop
// (232B/13.8% — flag is load-bearing), n->r10 pin (DIFF — body reuses r10),
// `found >= c` for the bge (DIFF — layout break).
// REMAINING 16 words: (a) guard+latch store/compare order — want cmpw,stw,beq,
// got stw,cmpw,beq (6 words, twice); (b) slot/head reload scratch regs — want
// r10/r11, got r9/r0 (4 words); (c) skip-test form — want cmpw+bge, got
// cmpwi+ble/beq (u8 range proof folds <=0 to ==0; c-temp did not defeat it),
// sub-load dest r11 vs r10, mtctr r10 vs r0 (6 words).
// 2026-10-15: want's skip-test decoded: `li r7,0`(found) @0x8007E080 then
// `cmpw r7,r10; bge` @0x8007E098 — the skip compares the found-register
// against c (skip iff found>=c with found==0), NOT c-against-0. Spelling it
// `if (found >= c)` DOES emit cmpw+bge but drops to DIFF: c's double use
// (compare + mtctr) pulls c into r0 (want r10), the lhz sinks below the bge,
// and the inner loop gains a cmpwi/beq. Moving q above the test and unpinning
// q (to let sb+q coalesce into r11 and free r10 for c) both stay DIFF.
// Reverted to the 73.3% body. A working shape needs found>=c WITH c single-use
// for mtctr (compare via a coalesced copy?) plus sb+q sharing r11 — untested.
// 2026-10-17: `n = c` hoisted above the skip with `if (found >= n)` (compare
// via the single-use mtctr var so c stays single-use) tried: DIFF (the
// found>=c family breaks the r10/r11 colouring; c pulls into r0). Reverted
// to the 73.3% body.
// typed redraft
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 35.0000% -> 46.6667% per-object flags: -Os -> -fno-schedule-insns
// FLAG: -fno-schedule-insns
// family=m2c range=0x8007E030-0x8007E120 size=240B
// INERT: not registered in splits.txt/configure.py
// 2026-09-22: REDRAFTED 13.3% -> 35.0%. Decode: for each node of the circular
// list at arg0->0x10, deref node->unk0x0 twice to get the object, then
// obj->unk0x30->unk0x54 is a table: it has a u16 count at hdr->unk0x12, a
// 32-byte element array at unk0x30 and a second 32-byte array at unk0x38; for
// each element e, scan e->unk0xC-indexed entries of the second array (e->unk0x4
// of them) and set/clear bit 3 of e->unk0x6 if any entry has (*(u16*)x + 0xA) & 0x80.
// PARK REASON: two mutually exclusive failure modes for the OUTER entry guard
// (want keeps it inline: cmpw/stw/beq at 0x8007E04C):
//   * non-volatile slot208 -> ngccc PROVES slot208 == head (no call in this
//     function) and rotates the guard into the bottom test (`b test`), 35.0%;
//   * volatile slot208     -> guard survives, but the tail then loads
//     cur->unk0x4 before the slot208 reload (+2 words) and the whole inner
//     block shifts, 30.6%.
// Also residual: want runs the inner scan on CTR (mtctr/bdnz) while ngccc emits
// a compare/branch count-up loop, and register roles differ (i r8 vs r5,
// lst r6 vs r7). Tried: for/do-while/no-guard inner loops, pointer vs indexed
// scan, `-Os` (mandatory, already in FLAG), goto-shaped outer list walk.#include "types.h"
#include "structs.h"
typedef struct E030_Hdr {
    char pad0x0[0x12];
    u16 unk0x12;
} E030_Hdr;
typedef struct E030_Ent {
    s32 unk0x0;
    u8 unk0x4;
    char pad0x5[0x1];
    u8 unk0x6;
    char pad0x7[0x5];
    u16 unk0xC;
    char pad0xE[0x12];
} E030_Ent;
typedef struct E030_Sub {
    void *unk0x0;
    char pad0x4[0x1C];
} E030_Sub;
typedef struct E030_Lst E030_Lst;
typedef struct E030_Lve1 {
    char pad0x0[0x54];
    E030_Lst *unk0x54;
} E030_Lve1;
struct E030_Lst {
    char pad0x0[0x8];
    E030_Hdr *unk0x8;
    char pad0xC[0x24];
    E030_Ent *unk0x30;
    char pad0x34[0x4];
    E030_Sub *unk0x38;
};
typedef struct E030_Obj {
    char pad0x0[0x30];
    E030_Lve1 *unk0x30;
} E030_Obj;
s32 fn_8007E030(CStruct *arg0) {
    struct { void * slot208; s32 pad20c; void * volatile slot210; } slots;
    CStruct *head;
    CStruct *cur;
    CStruct *obj;
    register E030_Lst *lst __asm__("r6");
    register E030_Ent *e __asm__("r9");
    E030_Sub *p;
    E030_Sub *sb;
    s32 c;
    register E030_Sub *q __asm__("r11");
    void *node;
    void *temp_r0;
    s32 found;
    s32 j;
    s32 n;
    void *x;
    register u32 i __asm__("r8");

    head = (CStruct *)arg0->unk0x10;
    node = NULL;
    slots.slot208 = head;
    if (head != NULL) node = (void *)head->unk0x4;
    slots.slot210 = node;
    if (node != head) {
        do {
            cur = (CStruct *)slots.slot210;
            i = 0;
            obj = *(CStruct **)(*(s32 **)&cur->unk0x0);
            lst = ((E030_Obj *)(void *)obj)->unk0x30->unk0x54;
            goto test;
        loop:
            e = &lst->unk0x30[i];
            sb = lst->unk0x38;
            found = 0;
            i++;
            c = (s32)e->unk0x4;
            if (c <= 0) {
                goto next;
            }
            q = &sb[e->unk0xC];
            n = c;
            for (; n != 0; n--, q++) {
                x = q->unk0x0;
                if (x != NULL) {
                    if ((*(u16 *)((char *)x + 0xA) & 0x80) != 0) {
                        found = 1;
                    }
                }
            }
        next: ;
            if (found != 0) {
                e->unk0x6 = (u8)(e->unk0x6 | 8);
            } else {
                e->unk0x6 = (u8)(e->unk0x6 & 0xF7);
            }
        test:
            if (i < (u32)lst->unk0x8->unk0x12) {
                goto loop;
            }
            cur = (CStruct *)slots.slot210;
            temp_r0 = (void *)cur->unk0x4;
            slots.slot210 = temp_r0;
        } while (temp_r0 != (void *)slots.slot208);
    }
    return 1;
}
