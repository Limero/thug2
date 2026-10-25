// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800101A0-0x80010258 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_NewZero(s32);
void *fn_8001094C(void *, s32);
void *fn_8000F95C(void *, void *, void *, void *);
extern char lbl_802905E4[];
extern char lbl_802905EC[];

/* Four parallel arrays of 8 node/registry pointers, contiguous at +0x188. */
typedef struct {
    char pad0x0[0x188];
    void *unk0x188[8];
    void *unk0x1A8[8];
    void *unk0x1C8[8];
    void *unk0x1E8[8];
} S_800101A0;

void fn_800101A0(S_800101A0 *arg0, s32 arg1) {
    void *temp_r3;
    s32 var_r4;
    s32 var_r30;
    s32 i;
    void **base;

    var_r4 = arg1;
    if (var_r4 > 8) {
        var_r4 = 8;
    }
    if (var_r4 > 1) {
        var_r30 = var_r4 - 1;
        base = &arg0->unk0x1E8[0];
        i = 0;
        do {
            temp_r3 = fn_8001094C(Mem_NewZero(0x1C), 0x25BA8);
            base[i - 24] = temp_r3;
            base[i - 16] = fn_8000F95C(arg0, temp_r3, 1, lbl_802905E4);
            temp_r3 = fn_8001094C(Mem_NewZero(0x1C), 0x6F158);
            base[i - 8] = temp_r3;
            base[i] = fn_8000F95C(arg0, temp_r3, 1, lbl_802905EC);
            i++;
        } while (--var_r30 != 0);
    }
}
