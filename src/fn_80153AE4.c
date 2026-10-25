// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153AE4-0x80153BB0 (204B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern char lbl_802A8030[];
s32 NextItem(s32);
s32 fn_8021D578(s32, CStruct *);
s32 fn_8021D5AC(void *, CStruct *);
s32 fn_802195BC(Unk_C7387A53 *);
s32 fn_8022989C(CScript *);

s32 ScriptIsObserving(CStruct *pParams, CScript *pScript) {
    struct search { s32 out; s32 zero; s32 name; } sp8;
    struct search *sp;
    void *spv;
    s32 ctx;
    s32 name;
    Unk_C7387A53 *entry;
    s32 flags;
    s32 var_r3;

    ctx = lbl_80305F9C;
    spv = &sp8;
    ((struct search *)spv)->zero = 0;
    ((struct search *)spv)->name = (s32)lbl_802A8030;
    __asm__("" : "+r"(spv));
    sp = (struct search *)spv;
    entry = NextItem(ctx);
    if (entry != 0) {
        var_r3 = fn_8022989C(entry);
        sp->name = (s32)lbl_802A8030;
        return var_r3;
    }
    entry = fn_8021D578(ctx, sp);
    if (entry != NULL) {
        do {
            flags = entry->unk0x20;
            if ((flags & 1) != 0) {
                if ((flags & 4) != 0) {
                    sp->name = (s32)lbl_802A8030;
                    return 1;
                }
            }
            entry = fn_8021D5AC(ctx, &sp8);
        } while (entry != NULL);
    }
    var_r3 = (fn_802195BC(ctx) ^ 1) == 0;
    sp->name = (s32)lbl_802A8030;
    return var_r3;
}
