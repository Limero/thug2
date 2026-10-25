// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131E50-0x80131EA0 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
void fn_800A42F8(s32);
s32 fn_800A5BF4(s32, s32, s32);
extern s32 lbl_80301A78;

/* file-local layout, not the shared Unk_FFAD6788: only field 0xE0 is touched
   and it is read as s32 (lwz + cmpwi + passed as fn_800A42F8's s32 arg). */
typedef struct {
    s32 pad_00[0x38];
    s32 unk0xE0;
} T_80131E50;

void fn_80131E50(T_80131E50 *arg0, s32 arg1) {
    register s32 a0 __asm__("r30");
    register s32 a1 __asm__("r31");

    a0 = (s32)arg0;
    a1 = arg1;
    if (*(s32 *)((char *)a0 + 0xE0) != 0) {
        fn_800A42F8(*(s32 *)((char *)a0 + 0xE0));
        fn_800A5BF4(lbl_80301A78, a1, a0);
    }
}
