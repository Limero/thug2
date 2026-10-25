// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D8E4-0x8023D990 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* The 6-byte payload the byte-fill/fill-rect helpers write and the callers
   read back as a word at +0 and a halfword at +4.  File-local: the corpus
   class for the CALLER'S object (Unk_D329255D) and the byte class the two
   promoted callees use (Unk_F96D0DC8) are both wrong views of this slot. */
typedef struct {
    s32 unk0;
    u16 unk4;
} Rect_t;

void fn_8023D8D0(Unk_D329255D *);
void fn_8023DA64(Unk_71EAD930 *, Unk_F96D0DC8 *);
void *fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
s32 fn_80237454(s32, Rect_t *, s32, s32, s32);
void fn_802403A0(s32);
extern char lbl_802B0EC0[];

s32 fn_8023D8E4(Unk_D329255D *arg0) {
    volatile Rect_t sp8;
    Rect_t sp10;
    s32 tmp;
    s32 res;

    res = 0;
    if (arg0->unk0x4C != 0) {
        fn_80240B0C((Unk_F96D0DC8 *)&sp8, 0, 0, 0, 0, 0, 0);
        fn_8023DA64(arg0, (Unk_F96D0DC8 *)&sp8);
        sp10.unk0 = sp8.unk0;
        sp10.unk4 = sp8.unk4;
        tmp = fn_80237454(arg0->unk0x0, &sp10, 1, 1, 0);
        fn_802403A0((s32)lbl_802B0EC0);
        fn_8023D8D0(arg0);
        res = tmp;
    }
    return res;
}
