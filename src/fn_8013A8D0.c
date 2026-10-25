// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013A8D0-0x8013A93C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);

bool fn_8013A8D0(CStruct *arg0) {
    struct {
        u8 mb;
        u16 mh;
        void *mp;
        char pad[0x20];
    } msg;
    s32 sp30;

    fn_80137CB4(&msg);
    sp30 = **((s32 * *)&arg0->unk0x0);
    msg.mp = &sp30;
    msg.mh = 4;
    msg.mb = 2;
    fn_8013CC84(arg0->unk0xC, *(s32 *)(arg0->unk0x10 + 0x48), &msg);
    return true;
}