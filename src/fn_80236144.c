// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80236144-0x802361E8 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802B0C5C[];
void fn_802373AC(Unk_673C6403 *, s32);
void fn_8023B364(Unk_673C6403 *);
s32 fn_80235D1C(Unk_673C6403 *, void *);

typedef struct {
    char pad0[0x3530];
    s32 arr[58][58][4];
    char pad1[0x1772C - 0x3530 - 58 * 58 * 16];
    s32 unk0x1772C;
} S36144;

void fn_80236144(S36144 *arg0) {
    s32 i;
    s32 j;

    fn_802373AC((Unk_673C6403 *)arg0, 0);
    for (i = 0; i <= 0x39; i++) {
        for (j = 0; j < 0x3A; j++) {
            arg0->arr[j][i][0] = 0;
            arg0->arr[j][i][1] = 0;
            arg0->arr[j][i][2] = 0;
            arg0->arr[j][i][3] = 0;
        }
    }
    fn_8023B364((Unk_673C6403 *)arg0);
    fn_80235D1C((Unk_673C6403 *)arg0, lbl_802B0C5C);
    arg0->unk0x1772C = (arg0->unk0x1772C & ~8) | 1;
}
