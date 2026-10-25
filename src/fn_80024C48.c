// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024C48-0x80024CA4 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802913E4;
extern char lbl_80291448[];
void fn_80024724(void);
typedef struct Node {
    s32 unk0x0;
    s32 unk0x4;
    void *unk0x8;
    s32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
} Node;
Node *fn_80024C48(Node *arg0) {
    f32 temp_f0;

    fn_80024724();
    temp_f0 = lbl_802913E4;
    arg0->unk0x8 = lbl_80291448;
    arg0->unk0x4 = 2;
    arg0->unk0x10 = temp_f0;
    arg0->unk0x14 = temp_f0;
    arg0->unk0xC = 0;
    return arg0;
}
