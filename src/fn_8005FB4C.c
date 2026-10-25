// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005FB4C-0x8005FCB4 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"

typedef struct Node Node;

/* vtable entry read at +0x14 of a node's vtable; the callee arg is its +4. */
typedef struct Vtbl {
    char pad0x0[0x14];
    void *unk0x14;
} Vtbl;

typedef struct Ent {
    char pad0x0[0x4];
    s32 unk0x4;
} Ent;

struct Node {
    Vtbl *vtable; /* +0x0 */
    Node *next;   /* +0x4 */
    Node *prev;   /* +0x8 */
};

/* +0x10/+0x14 form one addressable sub-object: retail materialises
 * `this+0x10` ONCE (addi r31,r30,0x10) and then reaches the head through
 * 0(r31) and the count through 4(r31). */
typedef struct List {
    Node *head; /* +0x10 */
    s32 count;  /* +0x14 */
} List;

typedef struct Obj {
    char pad0x0[0x10];
    List list;
    char pad0x18[0x18];
    void *unk0x30;
    char pad0x34[0x1C];
    void *vtable; /* +0x50 */
} Obj;

/* Frame slots, at the exact retail offsets.  Every member is volatile: the
 * retail body stores to 0x40/0x48/0x50/0x30/0x18 and never reads them back,
 * so only volatile keeps the dead stores alive.  The 4-byte pads give the
 * observed 8-byte stride and there is NO trailing pad (that would make the
 * frame 0x70 instead of 0x68). */
typedef struct FR {
    volatile Node *sp8;
    char pad0x4[4];
    volatile Node *sp10;
    char pad0x14[4];
    volatile Node *sp18;
    char pad0x1C[4];
    volatile Node *sp20;
    char pad0x24[4];
    volatile Node *sp28;
    char pad0x2C[4];
    volatile Node *sp30;
    char pad0x34[4];
    volatile Node *sp38;
    char pad0x3C[4];
    volatile Node *sp40;
    char pad0x44[4];
    volatile Node *sp48;
    char pad0x4C[4];
    volatile Node *sp50;
} FR;

void fn_8005953C(void *);
void fn_80053228(s32);
void fn_800620EC(void *);
extern char lbl_80293F08[];

void fn_8005FB4C(Obj *arg0, s32 arg1) {
    FR fr;
    List *temp_r31;
    Node *temp_r9;
    Node *var_r0;
    Node *temp_r0;
    Node *temp_r9_2;
    Node *temp_r9_3;
    Node *var_r11;
    Node *temp_r0_2;
    Node *temp_r10;
    s32 temp_cr0_eq;

    arg0->vtable = (void *)lbl_80293F08;
    if (arg0->unk0x30 != NULL) {
        fn_8005953C(arg0->unk0x30);
    }
    temp_r9 = arg0->list.head;
    var_r0 = NULL;
    fr.sp8 = temp_r9;
    if (temp_r9 != NULL) {
        var_r0 = temp_r9->next;
    }
    fr.sp10 = var_r0;
    temp_r31 = &arg0->list;
    if (var_r0 != temp_r9) {
        do {
            temp_r9_2 = fr.sp10->vtable->unk0x14;
            if (temp_r9_2 != NULL) {
                fn_80053228(((Ent *)temp_r9_2)->unk0x4);
            }
            temp_r0 = fr.sp10->next;
            fr.sp10 = temp_r0;
        } while (temp_r0 != fr.sp8);
    }
    fn_800620EC(arg0);
    temp_r9_3 = arg0->list.head;
    var_r11 = NULL;
    if (temp_r9_3 != NULL) {
        var_r11 = temp_r9_3->next;
    }
    temp_r0_2 = temp_r31->head;
    fr.sp20 = var_r11;
    fr.sp28 = temp_r0_2;
    if (var_r11 != temp_r0_2) {
        do {
            temp_r10 = fr.sp20;
            fr.sp40 = temp_r10;
            temp_cr0_eq = temp_r10 == temp_r31->head;
            fr.sp20 = temp_r10->next;
            fr.sp38 = temp_r10;
            fr.sp50 = temp_r10;
            fr.sp38 = temp_r10->next;
            fr.sp48 = temp_r10;
            if (temp_cr0_eq == 0) {
                temp_r10->prev->next = temp_r10->next;
                temp_r10->next->prev = temp_r10->prev;
                Mem_Free(temp_r10);
                temp_r31->count = temp_r31->count - 1;
            }
            fr.sp30 = fr.sp38;
        } while (fr.sp20 != fr.sp28);
    }
    fr.sp18 = fr.sp20;
    Mem_Free(temp_r31->head);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
