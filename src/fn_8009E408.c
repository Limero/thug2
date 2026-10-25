// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E408-0x8009E440 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x24];
    CStruct *unk0x24;
} Obj9E3D0;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

s32 fn_8009E408(Obj9E3D0 *arg0, s32 arg1, s32 *arg2) {
    if (arg0->unk0x24 != NULL) {
        return GetChecksum_2(arg0->unk0x24, arg1, arg2, 0);
    }
    return 0;
}
