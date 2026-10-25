// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032698-0x80032778 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[8];
    s16 unk0x8;
    char pad0xA[2];
    s32 (*unk0xC)(void *, s32);
} Vt698;

typedef struct {
    char pad0x0[0x40];
    void *unk0x40[6];
    s32 unk0x58;
} Obj698;

void fn_80032698(Obj698 *arg0, void *arg1) {
    s32 i;
    s32 j;
    s32 off;
    s32 zero;
    void **w;
    void **base;
    Vt698 *vt;
    s32 *src;

    i = 0;
    if (i < arg0->unk0x58) {
        base = (void **)((char *)arg0 + 0x40);
        if (arg1 != 0) {
            zero = 0;
        } else {
            zero = 0;
        }
        zero = 0;
        w = base;
        off = 0;
        do {
            if ((s32)arg1 == *(s32 *)w) {
                if (arg1 != 0) {
                    vt = *(Vt698 **)((char *)arg1 + 0x14);
                    vt->unk0xC((char *)arg1 + vt->unk0x8, 3);
                }
                *(s32 *)w = zero;
                j = i;
                if (j < arg0->unk0x58 - 1) {
                    src = (s32 *)((char *)((s32)off + (s32)base));
                    do {
                        j++;
                        *src = *(s32 *)((char *)src + 4);
                        src++;
                    } while (j < arg0->unk0x58 - 1);
                }
                arg0->unk0x58 = arg0->unk0x58 - 1;
                return;
            }
            i++;
            w = (void **)((char *)w + 4);
            off += 4;
        } while (i < arg0->unk0x58);
    }
}
