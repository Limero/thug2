// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E758-0x8018E868 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* Unk_C8FEE62D.unk0x20 is typed s32 corpus-wide, so the entry param is s32.
   The s32 spelling is also the byte-exact one (the void* form warns and the
   `lwz`/call-arg order is unchanged either way). */
extern s32 GetInteger(s32, s32, s32 *, s32);
extern void AddInteger(s32, s32, s32);
extern f32 fn_800144C8(void);
extern f32 lbl_802A9648;   /* .rodata2 data:float  = 1000.0f  (ms per second) */
extern f64 lbl_802A9650;   /* .rodata2 data:double = 2147483648.0 (2^31 bias)   */

void fn_8018E758(Unk_C8FEE62D *arg0) {
    u32 sp8;
    u32 ms;
    u32 sec;
    s32 tmp;
    register s32 t0 __asm__("r0");
    register s32 t1 __asm__("r0");
    f32 f;
    Unk_89391A04 *vt;

    vt = (Unk_89391A04 *)arg0->unk0x14;
    if (vt->unk0x9C((char *)arg0 + vt->unk0x98) == 0) {
        GetInteger(arg0->unk0x20, QB_CURRENT_TIME, (s32 *)&sp8, 0);
        ms = sp8;
        f = fn_800144C8() * lbl_802A9648;
        if (f >= lbl_802A9650) goto slow;
        t0 = (s32)f;
        goto join;
    slow:
        t1 = (s32)(f - lbl_802A9650);
        t1 = t1 ^ 0x80000000;
    join:;
        if (f >= lbl_802A9650) tmp = t1; else tmp = t0;
        ms = ms + (u32)tmp;
        AddInteger(arg0->unk0x20, QB_CURRENT_TIME, ms);
        sec = ms / 1000;
        AddInteger(arg0->unk0x20, QB_CURRENT_TIME_SECONDS, sec);
        AddInteger(arg0->unk0x20, QB_CURRENT_TIME_FRACTION, (ms / 10) - (sec * 100));
    }
}
