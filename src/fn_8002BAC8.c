// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002BAC8-0x8002BB14 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802917B8[];
typedef struct Unk_BAC8 {
    char pad0x0[0x8];
    s32 unk0x8;
    f32 unk0xC;
} Unk_BAC8;
void *fn_8002BAC8(Unk_BAC8 *arg0, f32 farg0) {
    volatile double _dummy;

    fn_8002B900();
    arg0->unk0xC = farg0;
    arg0->unk0x8 = (s32)lbl_802917B8;
    return arg0;
}
