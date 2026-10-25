// PARKED 2026-10-05: DIFF 8.11%, object 444 B vs want 480 B.
// SEMANTICS: this is a script-iterator "flag propagation" pass over a linked
// list of nodes. It picks the lowest free bit of a 32-bit flag word
// (mask = first clear bit above the mandatory bit 0), ORs it into
// arg0->node.flags18, walks the node list clearing that bit out of every
// node's +0x20 word, then loops: for every node that does not have the bit
// set it sets it and calls fn_8009F8AC(node) (a "dirty, please re-scan"
// callback), restarting the outer scan whenever arg0->node.flags1C picks the
// bit up. It restores the cursor scratch struct and clears flags18 at the end.
//
// STRUCT SHAPE RECOVERED FROM `want` (offsets are exact):
//   struct FlagNode { s32 +0x00; FlagNode *next@+0x04; s32 +0x08;
//                     FlagNode *unk0C@+0x0C; s32 +0x10; s32 +0x14;
//                     u32 flags18@+0x18; u32 flags1C@+0x1C; u32 flags20@+0x20; }
//   struct ScriptCtx { s32 +0x00; FlagNode node@+0x04; }   <- arg0
//   local Cursor (r1+0x08, 20 B): { s32; FlagNode *cur@+4; char *str@+8; }
//     *cur is the walk cursor; str is initialised to, and restored to,
//     lbl_80297BF0 on entry/exit.
//   `next` is compared against the sentinel -1 (cmpwi rX,-1) -> NODE_END.
//
// WHAT CHANGED (all of it kept, all measured):
//  1. Replaced every `*(s32*)((char*)arg0 + 0x1C)` pun with real struct
//     members. The old m2c body declared the cursor local as a bare `s32`,
//     so it stored at &sp8+4 / &sp8+8, i.e. 8 bytes PAST the object's own
//     storage: frame 0x28 with the cursor overlapping the r26-r31 save area.
//     With a real 3-field Cursor the frame becomes 0x38 = want.
//  2. Cursor declared 20 bytes (3 used fields + 2 trailing words) - that is
//     what makes `stwu r1,-0x38` come out right. Measured: 12 B -> frame
//     0x30, 16 B -> 0x30, 20 B -> **0x38**, 24 B -> 0x38. The two trailing
//     words are never stored, so their type does not matter; only the size.
//  3. `Cursor *c = &sp8;` + all member access through `c->`. want keeps
//     `addi r11,r1,8` live in r29 for the whole function and does every
//     cursor store/load as 4(r29)/8(r29); without an escaping address ngccc
//     folds it back to 0xc(r1)/0x10(r1) and the register pressure drops by 2.
//  4. `var_r27 <<= 1` instead of `var_r27 *= 2`: want emits `slwi r27,r27,1`,
//     `*=` emits `add r27,r27,r27`. One word, but it is the loop-carried one.
//  5. `temp_r0 = temp_r10;` inside the `if (f & 1)` guard: want's shift loop
//     tests a COPY (`mr r0,r10` in the preheader) of the flag word, not the
//     register the load landed in. Reproducing that copy is worth 1 word.
//
// STILL BLOCKING (measured, ordered by payoff):
//  * Register allocation, not semantics: want holds the mask in TWO callee-
//    saved registers at once (r27 and `mr r28,r27`) so it saves 7 GPRs
//    (r25-r31, `stmw r25,0x1c`); this body holds 6 (r26-r31) and puts the
//    save area at 0x20. Everything downstream then differs by a register
//    NUMBER (want `mr r30,r3`, got `mr r29,r3`), which is why the raw index-
//    aligned score reads 8% even though the instruction streams are nearly
//    isomorphic. Adding a second named copy of the mask (`var_r28 = var_r27`,
//    used by the inner-loop test) does NOT change it - gcc coalesces it.
//  * want keeps a redundant `li r11,0` + `b` in the four "else p = NULL"
//    arms of the advance idiom (4 x 1 word). Every spelling of that idiom
//    (`if (p == NULL) p = NULL; else p = p->next;`, the inverted test, the
//    ternary, and `p = NULL; if (p) p = p->next;`) compiles byte-identically:
//    ngccc's crossjump folds the constant store and branches straight to the
//    join. The advance looks like an inlined helper
//    (`q = cur->unk0C; if (q->next == NODE_END) q = NULL; cur = q;
//    return q ? q->next : NULL;`) but making it a real `static` function is
//    WORSE - gcc does not inline it and emits a separate object.
//  * The +8 on the save area: with a 20 B local ngccc rounds the save-area
//    start up to 0x20; want starts it at 0x1c. Local-area sizes 12/16/20/24 B
//    give save-area starts 0x18/0x18/0x20/0x20, so no single local size
//    yields 0x1c - the original must have a second live local there.
//
// NOTE ON THE NUMBER: the pre-session body scored 10.91% with a 440 B
// object. That higher number is an artefact of index-alignment on a
// wrong-shaped (16 B short, 0x28 frame) object, not progress: the typed body
// matches want's frame, local offsets, shift idiom and call sequence, and is
// the one worth continuing from.
// family=m2c range=0x800A1C18-0x800A1DF8 size=480B
extern char lbl_80297BF0[];
void fn_8009F8AC(void *);

typedef struct FlagNode FlagNode;
struct FlagNode {
    s32 unk00;
    FlagNode *next;
    s32 unk08;
    FlagNode *unk0C;
    s32 unk10;
    s32 unk14;
    u32 flags18;
    u32 flags1C;
    u32 flags20;
};

typedef struct ScriptCtx {
    s32 unk00;
    FlagNode node;
} ScriptCtx;

typedef struct Cursor {
    s32 unk00;
    FlagNode *cur;
    char *str;
    void *pad0;
    void *pad1;
} Cursor;

#define NODE_END ((FlagNode *)-1)

void fn_800A1C18(ScriptCtx *arg0) {
    Cursor sp8;
    Cursor *c = &sp8;
    u32 temp_r10;
    u32 var_r27;
    u32 temp_r26;
    FlagNode *temp_r11;
    FlagNode *var_r11;
    FlagNode *var_r9;
    FlagNode *var_r9_2;
    FlagNode *var_r9_3;
    FlagNode *var_r9_4;
    FlagNode *var_r11_2;
    FlagNode *var_r11_3;
    FlagNode *var_r31;
    FlagNode *var_r31_2;
    u32 temp_r0;
    s32 var_r9_5;

    c->cur = NULL;
    c->str = lbl_80297BF0;
    var_r27 = 1;
    temp_r10 = arg0->node.flags18;
    if (temp_r10 & 1) {
        temp_r0 = temp_r10;
        do {
            var_r27 <<= 1;
        } while (temp_r0 & var_r27);
    }
    temp_r11 = &arg0->node;
    c->cur = temp_r11;
    arg0->node.flags18 = (arg0->node.flags18 | var_r27);
    var_r9 = temp_r11->unk0C;
    if (var_r9->next == NODE_END) {
        var_r9 = NULL;
    }
    c->cur = var_r9;
    if (var_r9 == NULL) {
        var_r9_2 = NULL;
    } else {
        var_r9_2 = var_r9->next;
    }
    var_r11 = var_r9_2;
    temp_r26 = ~var_r27;
    if (var_r11 != NULL) {
        do {
            var_r11->flags20 = (var_r11->flags20 & temp_r26);
            var_r11_2 = c->cur->unk0C;
            if (var_r11_2->next == NODE_END) {
                var_r11_2 = NULL;
            }
            c->cur = var_r11_2;
            if (var_r11_2 == NULL) {
                var_r11 = NULL;
            } else {
                var_r11 = var_r11_2->next;
            }
        } while (var_r11 != NULL);
    }
    do {
loop_16:
        c->cur = temp_r11;
        arg0->node.flags1C = (arg0->node.flags1C & temp_r26);
        var_r9_3 = temp_r11->unk0C;
        if (var_r9_3->next == NODE_END) {
            var_r9_3 = NULL;
        }
        c->cur = var_r9_3;
        if (var_r9_3 == NULL) {
            var_r9_4 = NULL;
        } else {
            var_r9_4 = var_r9_3->next;
        }
        var_r31 = var_r9_4;
        if (var_r31 != NULL) {
loop_22:
            var_r31_2 = var_r31;
            var_r11_3 = c->cur->unk0C;
            if (var_r11_3->next == NODE_END) {
                var_r11_3 = NULL;
            }
            c->cur = var_r11_3;
            var_r31 = NULL;
            if (var_r11_3 != NULL) {
                var_r31 = var_r11_3->next;
            }
            temp_r0 = var_r31_2->flags20;
            var_r9_5 = 1;
            if (!(temp_r0 & var_r27)) {
                var_r9_5 = 0;
            }
            if ((var_r9_5 != 0) || (var_r31_2->flags20 = (temp_r0 | var_r27),
                                    fn_8009F8AC(var_r31_2),
                                    ((arg0->node.flags1C & var_r27) == 0))) {
                if (var_r31 != NULL) {
                    goto loop_22;
                }
            } else {
                goto loop_16;
            }
        }
    } while (arg0->node.flags1C & var_r27);
    c->str = lbl_80297BF0;
    arg0->node.flags18 = (arg0->node.flags18 & temp_r26);
}