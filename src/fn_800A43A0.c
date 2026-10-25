// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A43A0-0x800A4460 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

// The list header: {entry array, entry count}.  unk0x0 is deliberately s32
// (the game reloads it every iteration), unk0x4 is the count.
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
} A43A0_List;

// One entry, 0x14-byte stride; only +0x4, +0x8 and +0xC are ever touched.
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
} A43A0_Elem;

void CStruct_delete(s32, s32);

void fn_800A43A0(A43A0_List *arg0, s32 arg1) {
    s32 i = 0;
    while (i < (s32) arg0->unk0x4) {
        if (((A43A0_Elem *)((char *)arg0->unk0x0 + i * 0x14))->unk0x8 == arg1
            || arg1 == QB_ALL_GROUPS) {
            ((A43A0_Elem *)((char *)arg0->unk0x0 + i * 0x14))->unk0x4 =
                QB_NULL_SCRIPT;
            if (((A43A0_Elem *)((char *)arg0->unk0x0 + i * 0x14))->unk0xC != 0) {
                CStruct_delete(((A43A0_Elem *)((char *)arg0->unk0x0 + i * 0x14))->unk0xC, 3);
                ((A43A0_Elem *)((char *)arg0->unk0x0 + i * 0x14))->unk0xC = 0;
            }
        }
        i += 1;
    }
}
