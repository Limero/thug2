// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007D354-0x8007D3B8 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// Per-object record reached through self->unk0x18. unk0x68 is an s16
// byte-offset to a derived sub-object; unk0x6C is its virtual method.
typedef struct {
    char pad0x68[0x68];
    s16 unk0x68;
    s32 unk0x6C;
} ScriptRec_8007D354;

void *fn_800592F8(s32);

void *fn_8007D354(char *arg0, s32 arg1) {
    register s32 self __asm__("r30");
    ScriptRec_8007D354 *rec;

    self = (s32)arg0;
    rec = *(ScriptRec_8007D354 **)(arg0 + 0x18);
    if (((s32 (*)(void *))rec->unk0x6C)(arg0 + rec->unk0x68) != 0) {
        return (char *)self + ((arg1 * 0x10) + 0xA0);
    }
    return fn_800592F8(arg1);
}
