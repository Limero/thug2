// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80095518-0x80095574 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Snapshots four fields of a QB object (0x0/0x4/0x8/0xC) into the
// lbl_80301860..74 globals and sets the first to 1.
// Suggested rename: SnapshotObjectToGlobals
#include "types.h"
#include "structs.h"
extern bool lbl_80301860;
extern s32 lbl_80301864;
extern s32 lbl_80301868;
extern s32 lbl_8030186C;
extern s32 lbl_80301870;
extern bool lbl_80301874;
void fn_80095518(CStruct *arg0) {
    lbl_80301860 = 1;
    lbl_80301868 = arg0->unk0x4;
    lbl_80301864 = arg0->unk0x0;
    lbl_80301870 = arg0->unk0xC;
    lbl_8030186C = arg0->unk0x8;
    lbl_80301874 = 0;
}
