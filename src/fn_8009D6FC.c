// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D6FC-0x8009D838 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u8 unk0x0;
    u8 f_01;
    u8 f_02;
    u8 f_03;
    u8 f_04;
    u8 pad0x05[0x0E];
    u8 f_13;
    u8 f_14;
    u8 f_15;
    u8 f_16;
} Unk_8009D6FC;

void fn_8009D6FC(Unk_8009D6FC *s) {
    s->f_14 = s->f_02;
    s->f_15 = s->f_03;
    s->f_16 = s->f_04;
    s->f_13 = s->f_01;

    if (abs(0x80 - s->f_01) <= 0x32) {
        s->f_01 = 0x80;
    }

    if (abs(0x80 - s->f_02) <= 0x32) {
        s->f_02 = 0x80;
    }

    if (abs(0x80 - s->f_03) <= 0x32) {
        s->f_03 = 0x80;
    }

    if (abs(0x80 - s->f_04) <= 0x32) {
        s->f_04 = 0x80;
    }

    if (abs(0x80 - s->f_13) <= 0x32) {
        if (abs(0x80 - s->f_14) <= 0x32) {
            s->f_13 = 0x80;
            s->f_14 = 0x80;
        }
    }

    if (abs(0x80 - s->f_15) <= 0x32) {
        if (abs(0x80 - s->f_16) <= 0x32) {
            s->f_15 = 0x80;
            s->f_16 = 0x80;
        }
    }
}
