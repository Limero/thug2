// WIP DRAFT (non-matching) — hand-rebuilt from the WANT disassembly.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 30.9963% -> 33.2103% per-object flags: -Os -> -fno-gcse
// family=m2c range=0x80015434-0x80015870 size=1084B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.8% ([11]rev->2.8%).
//
// REBUILT 2026-10-06 from tmp_bundles/80015434.md. Fixes over the m2c body:
//  * the path buffer is `char sp8[0x100]` (m2c had `s32 sp8`) — this alone sets
//    the WANT frame (-0x140 / stmw r18@0x108): 8 header + 0x100 locals + 0x38 saves.
//  * every entry walk uses BYTE offsets: m2c's `var_r29 + 8` (s32*) stepped +0x20
//    and `(s32*)var_r29 + len` stepped len*4 — both were wrong.
//  * `fn_80014904` is a 4-arg call `(newbuf, 1, c, h)`: WANT sets r4/r5/r6 and leaves
//    r3 = the fn_8000F10C return (the new entry buffer). m2c called it 3-arg with r3=1.
//  * the packed-table pre-header is 8 bytes (len = ((strlen(str)+4) & ~3) + 8).
//  * globals are referenced as the registered symbols (lbl_802FFE58 / lbl_802FFF68 /
//    lbl_802FFE98 are lis+lwz displacement loads; lbl_80290B44 / lbl_80290B4C are
//    lis+addi address relocs). Raw address literals emitted lis+ori instead.
//  * real per-record struct types (Entry/Group/Item/Mgr) instead of s32 casts.
// Byte swap uses the same SWAP32 expression as the matched src/fn_80041E54.c.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct Mgr_15434 {
    char pad0x00[0x118];
    s32 unk0x118;
} Mgr_15434;

typedef struct Entry_15434 {
    u32 word0;
    u32 word1;
    /* NUL-terminated name follows at +0x8 */
} Entry_15434;

typedef struct Group_15434 {
    s32 count;      /* +0x0 */
    s32 value;      /* +0x4 */
    void *items;    /* +0x8 */
} Group_15434;

typedef struct Item_15434 {
    s32 a;          /* +0x0 */
    s32 b;          /* +0x4 */
    s32 c;          /* +0x8 */
} Item_15434;

extern bool lbl_802FFE58;
extern bool lbl_802FFF68;
extern Mgr_15434 *lbl_802FFE98;
extern char lbl_80290B44[];
extern char lbl_80290B4C[];

void *fn_8000F10C(Mgr_15434 *, s32, s32, s32);
s32 fn_800147E8(char *, char *);
s32 fn_800146E0(void);
void fn_80014904(void *, s32, s32, s32);
s32 fn_80014898(s32);
void fn_800151F4(char *, s32 *, s32 *);
void *Mem_Alloc(s32);
void Mem_Free(void *);
int strlen(const char *);
// FLAG: -fno-gcse

void *fn_80015434(s32 arg0) {
    char sp8[0x100];
    Entry_15434 *e;
    Entry_15434 *w;
    s32 *a23;
    s32 *a24;
    s32 *a26;
    s32 *a20;
    s32 *a19;
    Group_15434 *table;
    Group_15434 *g;
    char *p;
    s32 n;
    s32 uniq;
    s32 next;
    s32 i;
    s32 j;
    s32 k;
    s32 flag;
    s32 cnt;
    s32 len;
    s32 off;
    s32 h;
    s32 c;
    u32 v0;
    u32 v1;

    if (lbl_802FFE58 == 0) {
        return NULL;
    }
    lbl_802FFF68 = 1;
    n = 0;
    sprintf(sp8, lbl_80290B44, arg0);
    uniq = 0;
    h = fn_800147E8(sp8, lbl_80290B4C);
    c = fn_800146E0();
    e = (Entry_15434 *)fn_8000F10C(lbl_802FFE98, c, 1, lbl_802FFE98->unk0x118);
    fn_80014904(e, 1, c, h);
    fn_80014898(h);

    if (e->word0 != 0xFFFFFFFFu) {
        w = e;
        do {
            v0 = w->word0;
            v1 = w->word1;
            n++;
            w->word0 = (v0 >> 0x18) | ((v0 >> 8) & 0xFF00) | ((v0 << 8) & 0xFF0000) | (v0 << 0x18);
            w->word1 = (v1 >> 0x18) | ((v1 >> 8) & 0xFF00) | ((v1 << 8) & 0xFF0000) | (v1 << 0x18);
            len = ((strlen((char *)w + 8) + 4) & ~3) + 8;
            w = (Entry_15434 *)((char *)w + len);
        } while (w->word0 != 0xFFFFFFFFu);
    }

    a23 = NULL;
    a24 = NULL;
    a26 = NULL;
    a20 = NULL;
    a19 = NULL;
    if (n > 0) {
        a23 = (s32 *)fn_8000F10C(lbl_802FFE98, n * 4, 1, lbl_802FFE98->unk0x118);
        a24 = (s32 *)fn_8000F10C(lbl_802FFE98, n * 4, 1, lbl_802FFE98->unk0x118);
        a26 = (s32 *)fn_8000F10C(lbl_802FFE98, n * 4, 1, lbl_802FFE98->unk0x118);
        a20 = (s32 *)fn_8000F10C(lbl_802FFE98, n * 4, 1, lbl_802FFE98->unk0x118);
        a19 = (s32 *)fn_8000F10C(lbl_802FFE98, n * 4, 1, lbl_802FFE98->unk0x118);
    }

    w = e;
    next = n + 1;
    if (w->word0 != 0xFFFFFFFFu) {
        off = 0;
        do {
            char *str;

            str = (char *)w + 8;
            *(s32 *)((char *)a23 + off) = (s32)w->word0;
            *(s32 *)((char *)a24 + off) = (s32)w->word1;
            fn_800151F4(str, (s32 *)((char *)a26 + off), (s32 *)((char *)a20 + off));
            *(s32 *)((char *)a19 + off) = (s32)str;
            off += 4;
            len = ((strlen(str) + 4) & ~3) + 8;
            w = (Entry_15434 *)((char *)w + len);
        } while (w->word0 != 0xFFFFFFFFu);
    }

    for (i = 0; i < n; i++) {
        flag = 1;
        for (j = 0; j < i; j++) {
            if (a26[i] == a26[j]) {
                flag = 0;
                break;
            }
        }
        if (flag != 0) {
            uniq++;
        }
    }

    table = (Group_15434 *)Mem_Alloc((uniq + next) * 0xC);
    k = 0;
    for (i = 0; i < n; i++) {
        flag = 1;
        for (j = 0; j < k; j++) {
            if (table[j].value == a26[i]) {
                flag = 0;
                break;
            }
        }
        if (flag != 0) {
            table[k].value = a26[i];
            k++;
        }
    }

    p = (char *)table + uniq * 0xC + 0xC;
    for (i = 0; i < uniq; i++) {
        g = (Group_15434 *)((char *)table + i * 0xC);
        g->items = p;
        cnt = 0;
        for (j = 0; j < n; j++) {
            if (a26[j] == g->value) {
                cnt++;
                ((Item_15434 *)p)->a = a23[j];
                ((Item_15434 *)p)->b = a24[j];
                ((Item_15434 *)p)->c = a20[j];
                p += 0xC;
            }
        }
        g->count = cnt;
    }
    ((Group_15434 *)((char *)table + uniq * 0xC))->count = -1;

    Mem_Free(a19);
    Mem_Free(a20);
    Mem_Free(a26);
    Mem_Free(a24);
    Mem_Free(a23);
    Mem_Free(e);
    lbl_802FFF68 = 0;
    return table;
}

// NOTE 2026-10-06: semantic structure confirmed against the WANT:
// open/parse `lbl_80290B44` (a "%s"-style format) into sp8, hash it via
// fn_800147E8(sp8, lbl_80290B4C), allocate a packed entry table with
// fn_8000F10C(mgr, size, 1, mgr->0x118), then walk the 0x8-prefixed records
// (u32 header + u32 payload + NUL name padded to 4, total ((strlen+4)&~3)+8),
// byte-swap both header words, build five parallel n-slot arrays, count the
// distinct fn_800151F4 hashes, and emit a group table [(count,value,items)] with
// a -1 sentinel, then free everything.
// Residuals not measurable here (no compiler in this slice): (a) the exact
// bswap emission for a u32 pair (keeping the matched fn_80041E54.c expression);
// (b) register colouring of the five allocation results and the RLE group
// pointer; (c) whether GCC emits the `mr r3,r21` for the 4-arg fn_80014904 call.
// PARKED 2026-10-06: best body above; not measured this round.
