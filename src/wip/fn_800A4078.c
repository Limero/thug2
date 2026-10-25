// PARKED: NEAR 68.3% (baseline was an m2c DIFF husk). Last gain: the three
// entry-field stores (arr/count/flag) are emitted in the reverse of the source
// order that reads naturally, so list them arr, count, flag (66.5 -> 68.3).
// reproduce: cd <repo> && \
// LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//       tools/test_wip_drafts.py --addr 0x800A4078
// WHAT IS NOW EXACT (all verified against 0x800A4078..0x800A42F4):
//   * prologue/epilogue: 0x48 frame, stmw/lmw r20, mfcr/mtcrf 8 (cr4 save),
//   * both fn_80127358 chains + the fn_800A42F8 call gated on `arg2`
//     (cmpwi cr4,r31,0 hoisted into the loop preheader),
//   * the append loop's shape: `n=0; i=0; ... if (n < cnt) do {...} while (i < cnt)`
//     — TWO counters (r24 = running total, r26 = item index); a `for (i=0;...)`
//     form sinks the init into the preheader and costs ~5 insns,
//   * the append body incl. `mr r31,r27` / `addi r27,r31,0x14` (e = newarr+n),
//   * loop 2: `for (j=0;j<old;j++) { *dst = *src; src++; dst++; n++; }` with NO
//     `if (old > 0)` guard (the guard's `cmpwi/ble` IS the rotated loop's entry
//     test; adding the guard duplicates it) -> mtctr/bdnz + the 5-lwz/5-stw
//     20-byte entry copy, byte-identical,
//   * `*dst = *src` (struct assign) is what batches the copy; 5 separate member
//     assignments give interleaved lwz/stw pairs and do not match.
// REMAINING DIFF (3 items, in order of cost):
//   1. f4 (offset +0x10) update — want 2 insns
//        lwz r9,0x10(r31); rlwimi r9,r3,0x1f,0,0 ; rlwinm r9,r9,0,2,0 ; stw
//      i.e. `t = f4; t = (t & ~1) | (flag & 1); t &= 7;`.  Every plain C form
//      folds to 3 insns (`clrlwi &6 ; slwi ; or`), which shifts every later word
//      of the loop body by one (~20 words = the bulk of the remaining 33%).
//      The rlwimi IS reproducible — `((struct{u32 b:1;u32 r:31;})&e->f4)->b = v`
//      compiles to exactly `rlwimi rX,rY,31,0,0` (verified in isolation) — but
//      then the accompanying `& 7` is folded into it (or, as a separate memory
//      store, leaves two lwz/stw pairs).  Tried and ruled out: (x&7)|(y&1),
//      (x&6)|(y&1), ((x&7)&~1)|(y&1), ((x&~1)|(y&1))&7, (x&7)|((y&2)>>1),
//      3-bit bitfield read-modify-write (=> 5 insns), 1-bit bitfield store
//      before/after the mask.  Also note mb/me of the want's rlwinm are 2/0
//      (= mask 7) while GCC's own encoding for a constant 7 is 0/2 — a hint the
//      mask was not written as a plain `& 7` in the original source.
//   2. early-exit store order: want stw 0xc(flag), 4(count), 0(arr); got emits
//      0, 0xc, 4.  Reordering the three source statements changed nothing
//      (measured), so it is GCC's store scheduler, not the C order.
//   3. callee-saved register NUMBERS (values are all correct, allocation order
//      differs): cnt/const QB_DEFAULT want r23/r22, got r22/r23; item index i
//      and the IV induction pointer want r26/r27, got r27/r26.  Giving the
//      early-exit loop its own counter (instead of reusing i) was worth +6 pts
//      (60.2 -> 66.5) — the same lever may still fix these two swaps.
// NOT load-bearing, do not "clean up": the redundant `if (arg0->arr != NULL)`
// re-test before each Mem_Free2 (removing it drops to 23%: the want re-tests
// the register the destructor loop clobbered), and `& 7` semantics in f4.
// family=m2c range=0x800A4078-0x800A42F8 size=640B
// WIP DRAFT (non-matching) — C body hand-derived from the retail disassembly.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Derived from 0x800A4078..0x800A42F4:
//  * lbl_802FFE98 is a POINTER global (`lis r9,0x8030; lwz r3,-0x168(r9)`) —
//    declaring it `extern s32` and casting its VALUE is wrong (and costs the
//    frame: it forced GCC to keep &sp8 and the constant 1 in r18/r19),
//  * the +0x10 word is a 3-bit mask at bits 0..2: rlwimi(bit0) + rlwinm &7,
//  * the append loop runs off ONE counter (r24) used as the store index in
//    loop 2 (`mulli r0,r24,0x14; mtctr <old count>`),
//  * the append loop copies whole 20-byte entries (5 lwz then 5 stw).

#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* 0x14-byte list element */
typedef struct {
	s32 f0;
	s32 f1;
	s32 f2;
	s32 f3;
	u32 f4;
} A4078_entry;

/* arg0: the array/count/dirty-flag header */
typedef struct {
	A4078_entry *arr;
	s32 count;
	s32 pad8;
	s32 flag;
} A4078_list;

/* the global walker object at lbl_802FFE98, only +0x124 is touched */
typedef struct {
	s32 pad[0x49];
	s32 v124;
} A4078_glob;

/* arg1: the source list; fn_80129528 walks items[index] */
typedef struct {
	s32 pad0;
	s32 count;
	s32 *items;
} A4078_src;

/* the node chain fn_80127358 hands back */
typedef struct {
	s32 pad0;
	s32 f1;
	s32 f2;
	s32 f3;
} A4078_node;

extern void *lbl_802FFE98;

void CStruct_delete(s32, s32);
s32 *fn_80129528(A4078_src *, s32);
A4078_node *fn_80127358(s32 *, A4078_node *);
void fn_800A42F8(A4078_list *, s32);
s32 GetStructure_2(void *, s32, s32 *, s32);
s32 GetChecksum_2(void *, s32, s32 *, s32);
s32 ContainsFlag(void *, s32);
A4078_entry *CStruct_new(s32);
s32 fn_80126EDC(A4078_entry *, s32);
void fn_8000F2F8(A4078_glob *, s32);
void fn_8000F320(A4078_glob *);
A4078_entry *Mem_Alloc(s32);
void Mem_Free2(A4078_entry *);

void fn_800A4078(A4078_list *arg0, A4078_src *arg1, s32 arg2) {
	s32 sp8;
	s32 cnt;
	s32 n;
	s32 i;
	s32 *item;
	A4078_node *node1;
	A4078_node *node2;
	A4078_entry *e;
	A4078_entry *newarr;

	cnt = arg1->count;
	if (arg2 != 0 && cnt == 0) {
		if (arg0->arr != NULL) {
			s32 j = 0;

			if (cnt < arg0->count) {
				do {
					s32 node = arg0->arr[j].f3;

					if (node != 0)
						CStruct_delete(node, 3);
					j++;
				} while (j < arg0->count);
			}
			if (arg0->arr != NULL)
				Mem_Free2(arg0->arr);
			arg0->arr = NULL;
			arg0->count = 0;
			arg0->flag = 1;
		}
		return;
	}
	n = 0;
	i = 0;
	fn_8000F2F8((A4078_glob *)lbl_802FFE98, ((A4078_glob *)lbl_802FFE98)->v124);
	newarr = Mem_Alloc((arg0->count + cnt) * 0x14);
	if (n < cnt) {
		do {
			item = fn_80129528(arg1, i);
			node1 = fn_80127358(item, 0);
			node2 = fn_80127358(item, node1);
			if (arg2 != 0)
				fn_800A42F8(arg0, node1->f2);
			e = newarr + n;
			n += 1;
			if (GetStructure_2(item, QB_PARAMS, &sp8, 0) != 0)
				e->f3 = fn_80126EDC(CStruct_new(8), sp8);
			else
				e->f3 = 0;
			if (GetChecksum_2(item, QB_GROUP, &e->f2, 0) == 0)
				e->f2 = QB_DEFAULT;
			e->f4 = (e->f4 & 7) | (ContainsFlag(item, 0x80367192) & 1);
			e->f0 = node1->f2;
			e->f1 = node2->f2;
			arg0->flag = 1;
			i += 1;
		} while (i < cnt);
	}
	if (arg0->arr != NULL) {
		s32 old = arg0->count;
		A4078_entry *src = arg0->arr;
		A4078_entry *dst = newarr + n;
		s32 j;

		for (j = 0; j < old; j++) {
			*dst = *src;
			src++;
			dst++;
			n++;
		}
		if (arg0->arr != NULL)
			Mem_Free2(arg0->arr);
	}
	arg0->count = n;
	arg0->arr = newarr;
	fn_8000F320((A4078_glob *)lbl_802FFE98);
}
