// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800139D4-0x80013A1C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    void *obj;
    s32 a;
    s32 b;
} Rec;

extern s32 lbl_802FFF18[];
extern s32 lbl_802FFF20;
extern Rec lbl_803C9C78[32];

void fn_800139D4(void *arg0, s32 arg1, s32 arg2) {
    register s32 idx __asm__("r11");
    s32 cnt = lbl_802FFF20;
    Rec *rec;

    idx = lbl_802FFF18[cnt];
    lbl_802FFF18[cnt] = idx + 1;
    rec = (Rec *)((char *)&lbl_803C9C78[0] + cnt * 0xC0 + idx * 0xC);
    rec->obj = arg0;
    rec->b = arg2;
    rec->a = arg1;
}
