// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131C48-0x80131C94 (76B). Byte-identical.
// Walks a linked list via fn_8012ED7C starting from NULL, calling
// fn_80130E88 on each node with arg0 until the list ends.
// Suggested rename: fn_ForEachListNode(node, arg).
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8012ED7C(CStruct *);
void fn_80130E88(Unk_C7387A53 *, s32);
void fn_80131C48(s32 arg0) {
    void *t;

    t = fn_8012ED7C(0);
    while (t != 0) {
        fn_80130E88(t, arg0);
        t = fn_8012ED7C(t);
    }
}