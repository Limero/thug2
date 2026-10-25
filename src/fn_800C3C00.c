// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C3C00-0x800C3CFC (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80299094;
extern f32 lbl_80299098;
void fn_800C2AB0(Unk_C7387A53 *);
void fn_800C3CFC(void);
void fn_800C3E48(Unk_B8EAF2F7 *);
void fn_800C40DC(Unk_B96D32C4 *);
void fn_800C4414(Unk_7CBE46D8 *);
void fn_800C4560(Unk_999439AE *);
void fn_800C4734(Unk_C7387A53 *);
void fn_800C47EC(Unk_C7387A53 *, f32);
void fn_800C48A0(Unk_C7387A53 *);
void fn_800C3C00(Unk_49743DB6 *arg0) {
    int cnt;
    s32 off;
    f32 c;

    fn_800C3CFC();
    fn_800C3E48(arg0);
    fn_800C2AB0(arg0);
    if ((s32) arg0->unk0x330 == 0) {
        fn_800C4560(arg0);
        fn_800C4414(arg0);
        fn_800C4734(arg0);
        goto block_4;
    }
    if ((s32) arg0->unk0x328 != 0) {
        fn_800C4560(arg0);
        fn_800C47EC(arg0, lbl_80299094 - __builtin_fabsf(arg0->unk0x324));
block_4:
        fn_800C40DC(arg0);
        fn_800C48A0(arg0);
        return;
    }
    fn_800C40DC(arg0);
    cnt = arg0->unk0x1AC;
    if (cnt-- == 0) {
        return;
    }
    {
    c = lbl_80299098;
    off = ((cnt * 0x10) - cnt) << 5;
    do {
        *(f32 *)((char *)(off + arg0->unk0x2F0) + (s32)0x8) = c;
        *(f32 *)((char *)(off + arg0->unk0x2F0) + (s32)0xA4) = c;
        off -= 0x1E0;
        cnt--;
    } while (cnt != -1);
    }
}
