// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x8021CD38-0x8021CDA0 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80137CB4(Unk_C71E6DE1 *);
s32 NextItem(s32);
s32 fn_8022989C(s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

void fn_8021CD38(Unk_C7387A53 *arg0) {
    Unk_C71E6DE1 sp8;

    fn_80137CB4(&sp8);
    if (fn_8022989C(NextItem((s32)arg0)) == 0) {
        sp8.unk0x0 = 0x4A;
        sp8.unk0xC = 2;
        sp8.unk0x10 = 8;
        fn_8013DE78((void *)arg0->unk0xC, &sp8);
    }
}
