// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253C60-0x80253D10 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
void *fn_8024EAF4(void *heap, s32 size);

void *fn_80253C60(Unk_C7387A53 *arg0, s32 arg1) {
    s32 aligned;
    CStruct *node;

    aligned = (arg1 + 7) & ~7;
    if ((aligned + arg0->unk0x34) > arg0->unk0x38) {
        if (arg0->unk0x30 != 0) {
            s32 lblv;
            lblv = lbl_803CA340;
            node = fn_8024EAF4(lblv, 8);
            arg0->unk0x3C = arg0->unk0x3C + arg0->unk0x34;
            node->unk0x4 = arg0->unk0x40;
            node->unk0x0 = arg0->unk0x30;
            arg0->unk0x40 = (s32)node;
        }
        {
            register s32 n __asm__("r4");
            s32 lblv;
            arg0->unk0x38 = aligned;
            n = aligned;
            lblv = lbl_803CA340;
            arg0->unk0x30 = (s32)fn_8024EAF4(lblv, n);
        }
        arg0->unk0x34 = 0;
    }
    {
        s32 used = arg0->unk0x34;
        s32 base = arg0->unk0x30;
        arg0->unk0x34 = used + aligned;
        return (void *)(base + used);
    }
}
