// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D990-0x8023DA18 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
// Guarded twin of fn_8023D848: same region setup but only when
// arg0->unk0x4C != 0, ends with fn_8023D8D0(arg0) / fn_80238314.
// Suggested rename: fn_8023D990_setup_region_guarded.
#include "types.h"
#include "structs.h"
typedef struct { s32 w; u16 h; } unk_t;
s32 fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_8023DA64(Unk_71EAD930 *, Unk_F96D0DC8 *);
s32 fn_80238314(Unk_673C6403 *, Unk_8C3FE072 *);
void fn_8023D8D0(Unk_D329255D *);
void fn_8023D990(Unk_D329255D *arg0) {
    unk_t sp8;
    unk_t sp10;

    if ((s32)arg0->unk0x4C != 0) {
        fn_80240B0C(&sp8, 0, 0, 0, 0, 0, 0);
        fn_8023DA64(arg0, &sp8);
        sp10.w = sp8.w;
        ((Unk_638CF717 *)&sp10)->unk0x4 = ((Unk_638CF717 *)&sp8)->unk0x4;
        fn_80238314(*((void * *)&arg0->unk0x0), &sp10);
        fn_8023D8D0(arg0);
    }
}
