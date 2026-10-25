// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D848-0x8023D8D0 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
// Viewport/region initializer: builds two {w,h} structs via fn_80240B0C +
// fn_8023DA64, copies the first into the second plus extra fields, then
// calls fn_80237708. Suggested rename: fn_8023D848_setup_region.
#include "types.h"
#include "structs.h"
typedef struct { s32 w; u16 h; } unk_t;
s32 fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_8023DA64(Unk_71EAD930 *, Unk_F96D0DC8 *);
void fn_80237708(void *, Unk_F5317C5D *, s32);
void fn_8023D848(Unk_D329255D *arg0) {
    unk_t sp8;
    unk_t sp10;
    u8 zb;
    s32 zw;

    fn_80240B0C(&sp8, 0, 0, 0, 0, 0, 0);
    fn_8023DA64(arg0, &sp8);
    sp10.w = sp8.w;
    ((Unk_638CF717 *)&sp10)->unk0x4 = ((Unk_638CF717 *)&sp8)->unk0x4;
    fn_80237708(*((void * *)&arg0->unk0x0), &sp10, 0);
    __asm__("li %0,0" : "=r"(zb));
    zw = 0;
    arg0->unk0x4C = zb;
    arg0->unk0x5C = zw;
}
