// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161420-0x801614BC (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern char lbl_802A83F8[];
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);

typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;

s32 ScriptAtLeastOneObjectPlaced(void) {
    search_t sp8;
    Unk_C7387A53 *w;
    register s32 ctx;
    register search_t *p __asm__("r4");
    register search_t *spv __asm__("r30");

    ctx = *(s32 *)&lbl_80305F9C;
    __asm__("addi %0,1,8" : "=r"(p));
    spv = p;
    p->name = (char *)lbl_802A83F8;
    p->cursor = 0;
    w = (void *)fn_8021D454(ctx, p, 0);
    while (w != NULL) {
        if (w->unk0x38 > 0) {
            spv->name = (char *)lbl_802A83F8;
            return 1;
        }
        w = (void *)fn_8021D4E8(ctx, &sp8, 0);
    }
    spv->name = (char *)lbl_802A83F8;
    w = (void *)0;
    return (s32)w;
}
