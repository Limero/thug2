// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DF860-0x800DF924 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029A4A0;

f32 fn_8012772C(void *, s32, f32);
f32 fn_800AA95C(void *, f32, f32, f32);

/* arg0: the pad/player object (0x288 = right stick, 0x290 = left stick). */
typedef struct Df860Pad {
    char pad0x0[0x288];
    f32 right;          /* 0x288 */
    f32 pad0x28C;
    f32 left;           /* 0x290 */
} Df860Pad;

/* The stick sub-object at arg0 + 0x24; its own members sit at 0x244..0x26C. */
typedef struct Df860Stick {
    char pad0x0[0x244];
    f32 rightX;         /* 0x244 */
    f32 rightY;         /* 0x248 */
    f32 leftX;          /* 0x24C */
    f32 leftY;          /* 0x250 */
    char pad0x254[0x10];
    f32 rightZ;         /* 0x264 */
    char pad0x268[4];
    f32 leftZ;          /* 0x26C */
} Df860Stick;

s32 fn_800DF860(Df860Pad *arg0, void *arg1, CScript *arg2) {
    volatile double _dummy;
    Df860Stick *st;
    f32 scale;

    st = (Df860Stick *)((char *)arg0 + 0x24);
    scale = lbl_8029A4A0;
    fn_8012772C((void *)arg2->unk0x18, QB_LEFTSTICKANGLE, arg0->left * scale);
    fn_8012772C((void *)arg2->unk0x18, QB_LEFTSTICKMAGNITUDE,
                fn_800AA95C(st, st->leftX, st->leftY, st->leftZ));
    fn_8012772C((void *)arg2->unk0x18, QB_RIGHTSTICKANGLE, arg0->right * scale);
    fn_8012772C((void *)arg2->unk0x18, QB_RIGHTSTICKMAGNITUDE,
                fn_800AA95C(st, st->rightX, st->rightY, st->rightZ));
    return 1;
}
