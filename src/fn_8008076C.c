// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008076C-0x800808EC (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029628C;
void *fn_8007DF14(s32);
s32 fn_80080538(CScript *, s32 *, s32 *);
void fn_8007E89C(void);

void fn_8008076C(CScript *arg0, void *arg1) {
    s32 buf[5000];
    volatile double _dummy;
    Unk_9994C3F5 *s;
    s32 cnt;
    s32 i;
    s32 off;
    register s32 *src __asm__("r30");
    register void *node __asm__("r10");
    f32 *op;

    s = fn_8007DF14(arg0->unk0x18);
    if (s->unk0x8 != 0
        && (((Unk_897A0ACF *)(node = **((void ** *)&arg0->unk0x20)))->unk0x4 & 0x10)) {
        void *sub;
        f32 wa;

        i = 0;
        sub = *((void * *)&((Unk_897A0ACF *)node)->unk0x14);
        if (i < (s32)*((u16 *)&((Unk_B1B57F13 *)sub)->unk0x28)) {
            wa = lbl_8029628C;
            op = (f32 *)arg1;
            off = 0;
            do {
                i++;
                op[0] = (*((f32 * *)&((Unk_B1B57F13 *)sub)->unk0x34))[off + 0];
                sub = *((void * *)&((Unk_897A0ACF *)node)->unk0x14);
                op[1] = (*((f32 * *)&((Unk_B1B57F13 *)sub)->unk0x34))[off + 1];
                sub = *((void * *)&((Unk_897A0ACF *)node)->unk0x14);
                op[2] = (*((f32 * *)&((Unk_B1B57F13 *)sub)->unk0x34))[off + 2];
                op[3] = wa;
                op += 4;
                off += 3;
                sub = *((void * *)&((Unk_897A0ACF *)node)->unk0x14);
            } while (i < (s32)*((u16 *)&((Unk_B1B57F13 *)sub)->unk0x28));
        }
        fn_8007E89C();
    } else {
        cnt = fn_80080538(arg0, &buf[0], &buf[2500]);
        fn_8007E89C();
        if (cnt > 0) {
            s32 n = cnt;
            f32 wb = lbl_8029628C;
            src = &buf[0];
            do {
                ((f32 *)arg1)[0] = (*(f32 **)((char *)fn_8007DF14(arg0->unk0x18) + 0xC))[src[0] * 3 + 0];
                ((f32 *)arg1)[1] = (*(f32 **)((char *)fn_8007DF14(arg0->unk0x18) + 0xC))[src[0] * 3 + 1];
                ((f32 *)arg1)[2] = (*(f32 **)((char *)fn_8007DF14(arg0->unk0x18) + 0xC))[src[0] * 3 + 2];
                ((f32 *)arg1)[3] = wb;
                src++;
                arg1 = (char *)arg1 + 0x10;
                n--;
            } while (n != 0);
        }
        fn_8007E89C();
    }
}
