// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019BA98-0x8019BB20 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EC8;
s32 ContainsFlag(void *, s32);

// File-local layout of the receiver: only 0x438 is read (a 32-bit flag/field
// XOR'd against the table entry — want's `lwz r3, 0x438(r28)`), so the true
// member type is `s32`.  Declared locally rather than leaning on the
// mega-merged shared class (AGENTS M6.89d-note: a merged member type can be
// wrong for the one function you are matching).
typedef struct S8019BA98 {
    char pad0x0[0x438];
    s32 unk438;
} S8019BA98;

s32 fn_8019BA98(S8019BA98 *arg0, CStruct *arg1) {
    s32 var_r31;
    s32 temp_r3;
    s32 *table;
    s32 *base;

    table = &lbl_80305EC8;
    __asm__("" : "+r"(table));
    if (table[0] != 0) {
        base = table;
        __asm__("" : "+r"(base));
        var_r31 = 0;
        do {
            if (ContainsFlag(arg1, *(s32 *)((char *)var_r31 + (s32)base)) != 0) {
                s32 tv = *(s32 *)((char *)var_r31 + (s32)base);
                temp_r3 = arg0->unk438 ^ tv;
                return (temp_r3 == 0);
            }
            var_r31 += 4;
        } while (*(s32 *)((char *)var_r31 + (s32)base) != 0);
    }
    return 0;
}
