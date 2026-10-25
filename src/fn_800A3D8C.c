// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3D8C-0x800A3E28 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void CStruct_delete(s32, s32);
void Mem_Free2(void *);
void Mem_Free(void *);

typedef struct {
    s32 unk0;
    s32 unk4;
} Unk_A3D8C;

void fn_800A3D8C(Unk_A3D8C *arg0, s32 arg1) {
    s32 i;
    s32 off;

    if (arg0->unk0 != 0) {
        i = 0;
        if (i < arg0->unk4) {
            off = 0;
            do {
                s32 v = *(s32 *)(off + arg0->unk0 + 0xC);

                if (v != 0) {
                    CStruct_delete(v, 3);
                }
                i++;
                off += 0x14;
            } while (i < arg0->unk4);
        }
        if (arg0->unk0 != 0) {
            Mem_Free2((void *)arg0->unk0);
        }
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
