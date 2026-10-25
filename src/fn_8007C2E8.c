// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007C2E8-0x8007C340 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8037B5E8[];
extern f32 *lbl_80364C3C;
typedef struct {
    char _pad[0x160];
    f32 m[3][3];
} Mat3_t;
bool fn_8007C2E8(s32 arg0) {
    f32 *s = lbl_80364C3C;
    Mat3_t *d = (Mat3_t *)lbl_8037B5E8;
    d->m[0][arg0] = -s[arg0 * 4];
    d->m[1][arg0] = -s[arg0 * 4 + 1];
    d->m[2][arg0] = -s[arg0 * 4 + 2];
    return true;
}
