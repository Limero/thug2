// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D7F0-0x8021D888 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802A83F8[];
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_80229884(CScript *);
typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;
s32 fn_8021D7F0(s32 arg0) {
    search_t sp8;
    search_t *p = &sp8;
    register search_t *s __asm__("r29");
    s32 node;

    p->cursor = 0;
    p->name = (char *)lbl_802A83F8;
    node = fn_8021D454(arg0, (CStruct *)p, 1);
    s = p;
    while (node != 0) {
        if (fn_80229884((CScript *)node) != 0) {
            s->name = (char *)lbl_802A83F8;
            return node;
        }
        node = fn_8021D4E8(arg0, (CStruct *)&sp8, 1);
    }
    s->name = (char *)lbl_802A83F8;
    return 0;
}
