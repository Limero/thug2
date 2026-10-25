// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121A78-0x80121AD4 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8024994C(Unk_31DE137E *);
int OSPanic();
extern char lbl_8029DEB4[];
extern char lbl_8029E06C[];
extern char lbl_8039BA58[];

void fn_80121A78(void) {
    char *mgr;

    mgr = lbl_8039BA58;
    if (*(s32 *)(mgr + 0x398) == 0) {
        OSPanic(lbl_8029DEB4, 0x16E, lbl_8029E06C);
    }
    fn_8024994C(*(Unk_31DE137E **)(mgr + 0x398));
}
