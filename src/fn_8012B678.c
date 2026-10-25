// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012B678-0x8012B7B4 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
u8 *fn_8012B2A0(u8 *);
u8 *fn_8012B678(u8 *arg0) {
    s32 sp8;
    register s32 depth __asm__("r30");
    s32 tag;
    s32 min_tag;

    min_tag = 0x16;
    tag = *arg0;
    if (tag == 0x1A) {
        goto skip5;
    }
    if (tag > 0x1A) {
        goto high_tags;
    }
    if (tag == 5) {
        goto group5;
    }
    if (tag > 5) {
        goto low_tags;
    }
    if (tag == 3) {
        goto group3;
    }
    goto done;

low_tags:
    if (tag > 0x18) {
        goto done;
    }
    if (tag < min_tag) {
        goto done;
    }
    goto skip5;

high_tags:
    if (tag == 0x1E) {
        goto skip13;
    }
    if (tag > 0x1E) {
        goto high_tags2;
    }
    if (tag > 0x1C) {
        goto done;
    }
    goto read_length;

high_tags2:
    if (tag == 0x1F) {
        goto skip9;
    }
    goto done;

skip5:
    arg0 += 5;
    goto done;

skip9:
    arg0 += 9;
    goto done;

skip13:
    arg0 += 0xD;
    goto done;

read_length:
    fn_8012CB2C(&sp8, arg0 + 1);
    arg0 += sp8 + 5;
    goto done;

group3:
    depth = 1;
    do {
        arg0 = fn_8012B2A0(arg0);
        tag = *arg0;
        if (tag == 3) {
            depth += 1;
        } else if (tag == 4) {
            depth -= 1;
        }
    } while (depth != 0);
    goto after_group;

group5:
    depth = 1;
    do {
        arg0 = fn_8012B2A0(arg0);
        tag = *arg0;
        if (tag == 5) {
            depth += 1;
        } else if (tag == 6) {
            depth -= 1;
        }
    } while (depth != 0);

after_group:
    arg0 += 1;
done:
    return arg0;
}
