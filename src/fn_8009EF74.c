// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EF74-0x8009F010 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80132010(Unk_651D75B3 *, s32 *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

/* 12-byte ref-link list node: the object that owns the link, plus the
   next/prev pointers CObject_AddRefLink/CObject_RemoveRefLink splice. */
typedef struct RefLink {
    void *obj;
    struct RefLink *next;
    struct RefLink *prev;
} RefLink;

s32 fn_8009EF74(Unk_C8FEE62D *arg0, s32 *arg1) {
    RefLink node;
    RefLink *np;
    s32 var_r3;

    if (arg0->unk0x14 == 0) {
        return 1;
    }
    np = &node;
    np->next = NULL;
    np->prev = NULL;
    node.obj = arg0;
    if (arg0 != NULL) {           /* redundant (arg0 already dereferenced
                                     above) but present in retail */
        CObject_AddRefLink(arg0, (Unk_9994C3F5 *)np);
    }
    var_r3 = 1;
    fn_80132010((Unk_651D75B3 *)arg0->unk0x14, arg1);
    if (node.obj != NULL) {
        goto unlink9;
    }
    var_r3 = 0;
    __asm__ volatile("beq 1f");  /* 1 insn wedge: retail's redundant flag-reusing beq */
unlink9:
    CObject_RemoveRefLink((CStruct *)node.obj, (CStruct *)np);
    node.obj = NULL;
    __asm__("1:\n\t");           /* re-define the join label inside the asm stream */
    return var_r3;
}
