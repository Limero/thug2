// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013A744-0x8013A7D4 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);

s32 fn_8013A744(CStruct *arg0) {
    struct {
        u8 mb;
        u16 mh;
        void *mp;
        char pad[0x20];
    } msg;
    volatile s32 sp30;
    register s32 var_r11 __asm__("r11");
    register void *temp_r9 __asm__("r9");
    Unk_FFAD6788 *temp_r9_2;

    fn_80137CB4(&msg);
    temp_r9 = arg0->unk0x10;
    var_r11 = 1;
    sp30 = 8;
    if (!(((CStruct *)temp_r9)->unk0x68 & 8)) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        return 4;
    }
    msg.mb = 0xC;
    fn_8013CC84(arg0->unk0xC, ((CStruct *)temp_r9)->unk0x48, &msg);
    temp_r9_2 = arg0->unk0x10;
    sp30 = 8;
    temp_r9_2->unk0x68 = temp_r9_2->unk0x68 | 8;
    return 1;
}