// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C64C4-0x801C6598 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef float PS __attribute__((mode(PS)));

extern f32 lbl_802ACD5C;
extern f32 lbl_802ACD60;
extern char lbl_802ACE88[];
void fn_8009F53C(void);

void *fn_801C64C4(void *arg0) {
    f32 v[4];
    f32 *q;
    f32 a;
    f32 b;
    s32 i;

    fn_8009F53C();
    i = 0x14;
    *(s32 *)((char *)arg0 + 0x18) = (s32)lbl_802ACE88;
    do {
        i -= 1;
    } while (i != 0);
    *(s32 *)((char *)arg0 + 0x2AC) = 0;
    *(s32 *)((char *)arg0 + 0x4) = 0x850EEF66;
    *(s32 *)((char *)arg0 + 0x2B8) = 0;
    *(s32 *)((char *)arg0 + 0x2BC) = 0;
    *(s32 *)((char *)arg0 + 0x2B0) = 0;
    *(s32 *)((char *)arg0 + 0x2B4) = 0;
    *(s32 *)((char *)arg0 + 0x2C0) = 0;
    *(s32 *)((char *)arg0 + 0x2C4) = 0;
    *(s32 *)((char *)arg0 + 0x28) = 0;
    a = lbl_802ACD5C;
    b = lbl_802ACD60;
    q = v;
    v[0] = a;
    q[2] = a;
    q[3] = b;
    q[1] = a;
    *(PS *)((char *)arg0 + 0x38) = *(PS *)&q[2];
    *(s32 *)((char *)arg0 + 0x2A0) = 0;
    *(PS *)((char *)arg0 + 0x30) = *(PS *)&q[0];
    *(s32 *)((char *)arg0 + 0x24) = 0;
    v[0] = a;
    q[3] = b;
    q[1] = a;
    q[2] = a;
    *(PS *)((char *)arg0 + 0x48) = *(PS *)&q[2];
    *(PS *)((char *)arg0 + 0x40) = *(PS *)&q[0];
    return arg0;
}
