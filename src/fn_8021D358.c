// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x8021D358-0x8021D3F8 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802A83F8[];
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;
void *fn_8021D358(s32 arg0, s32 arg1) {
    search_t sp8;
    search_t *p = &sp8;
    register search_t *s __asm__("r30");
    CScript *node;
    CScript *n;

    p->cursor = 0;
    p->name = (char *)lbl_802A83F8;
    node = (CScript *)fn_8021D454(arg0, (CStruct *)p, 0);
    s = p;
    while (node != NULL) {
        n = node->unk0x18;
        if (n != NULL && n->unk0x18 == arg1) {
            s->name = (char *)lbl_802A83F8;
            return node;
        }
        node = (CScript *)fn_8021D4E8(arg0, (CStruct *)&sp8, 0);
    }
    s->name = (char *)lbl_802A83F8;
    return NULL;
}
