// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80255F5C-0x80255FF4 (152B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
static void fn_8024EBD8(s32 heap, s32 val);
void fn_80257CC4(void *dst, s32 n);

void fn_80255F5C(Unk_C8FEE62D *arg0) {
    s32 heap;
    s32 v;

    v = arg0->unk0x10;
    if (v != 0) {
        heap = lbl_803CA340;
        fn_8024EBD8(heap, v);
    }
    v = arg0->unk0x14;
    if (v != 0) {
        heap = lbl_803CA340;
        fn_8024EBD8(heap, v);
    }
    v = arg0->unk0x18;
    if (v != 0) {
        heap = lbl_803CA340;
        fn_8024EBD8(heap, v);
    }
    v = arg0->unk0x1C;
    if (v != 0) {
        heap = lbl_803CA340;
        fn_8024EBD8(heap, v);
    }
    v = arg0->unk0x20;
    if (v != 0) {
        heap = lbl_803CA340;
        fn_8024EBD8(heap, v);
    }
    fn_80257CC4(arg0, 0x2C);
}
