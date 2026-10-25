// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021DA20-0x8021DAD4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305EAC;
extern char lbl_802A83F8[];
s32 fn_8021D454(s32, void *, s32);
s32 fn_8021D4E8(s32, void *, s32);
void fn_8021DAD4(void *, void *, s32);
void fn_80173910(void *, void *);
s32 fn_80229B5C(void *);
typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;
void fn_8021DA20(void *arg0) {
    search_t sp8;
    search_t *p = &sp8;
    register search_t *s __asm__("r27");
    s32 temp_r28;
    s32 temp_r30;
    void *temp_r31;
    void *var_r30;
    temp_r28 = lbl_80305EAC;
    p->name = (char *)lbl_802A83F8;
    p->cursor = 0;
    var_r30 = (void *)fn_8021D454((s32)arg0, (void *)p, 0);
    s = p;
    if (var_r30 != NULL) {
        do {
            temp_r31 = (void *)fn_8021D4E8((s32)arg0, (void *)&sp8, 0);
            if (fn_80229B5C(var_r30) == 0) {
                temp_r30 = *(s32 *)((char *)var_r30 + 0x18);
                fn_8021DAD4(arg0, var_r30, 6);
                fn_80173910((void *)temp_r28, (void *)temp_r30);
            }
            var_r30 = temp_r31;
        } while (var_r30 != NULL);
    }
    s->name = (char *)lbl_802A83F8;
}
