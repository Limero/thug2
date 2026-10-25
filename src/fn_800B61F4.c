// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B61F4-0x800B6254 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800B48AC(s32);
s32 fn_80060DE4(s32);
typedef struct {
    char pad0x0[0x10];
    s16 unk0x10;
    char pad0x12[2];
    s32 unk0x14;
} Vt80B61F4;
void fn_800B61F4(CScript *arg0) {
    Vt80B61F4 *temp_r9;

    temp_r9 = (Vt80B61F4 *)arg0->unk0x18;
    ((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10);
    if (((s32) arg0->unk0x210 != 0) && (fn_80060DE4(arg0->unk0x210) != 0)) {
        fn_800B48AC((s32)arg0);
    }
}
