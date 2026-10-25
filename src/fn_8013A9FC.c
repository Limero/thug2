// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013A9FC-0x8013AAB8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8013F74C(void *);
s32 fn_8013E2D4(Unk_440CB216 *);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void fn_8013DEE0(Unk_440CB216 *, s32, s32, void *, s32, s32, s32);

s32 fn_8013A9FC(Unk_C8FEE62D *arg0) {
    struct {
        u8 mb;
        char pad1[7];
        s32 unk10;
        s32 unk14;
        char pad18[0x18];
    } msg;
    Unk_89391A04 *temp_r9;

    fn_80137CB4(&msg);
    if (arg0->unk0x14 & 1) {
        if (fn_8013E2D4(arg0->unk0xC) != 0) {
            temp_r9 = arg0->unk0x10;
            fn_8013DEE0(arg0->unk0xC, 4, 0, 0, temp_r9->unk0x4C, *((u16 *)&temp_r9->unk0x50), 0);
            return 1;
        }
        return 4;
    }
    if (fn_8013F74C(arg0->unk0x10) != 0) {
        msg.mb = 4;
        msg.unk10 = 0xFF;
        msg.unk14 = 1;
        fn_8013CC84(arg0->unk0xC, *(s32 *)(arg0->unk0x10 + 0x48), &msg);
        return 1;
    }
    return 4;
}