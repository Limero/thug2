// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B4694-0x800B47E8 (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800B6570(void *);
s32 fn_8009F498(void *);
void *GetChecksum_3(void *, s32);
void fn_800B34E4(void *, void *);
s32 fn_800C9780(void *);
void fn_8005FD68(void *, void *, s32, s32);
void fn_800601CC(void *, s32);
s32 fn_800CC2D4(void *);
void fn_800B4694(Unk_A9B14BE5 *arg0) {
    s32 sp8[16];
    register s32 temp_r30 __asm__("r30");
    s32 temp_r28;
    s32 temp_r29;
    s32 var_ctr;
    s32 t1;
    s32 t2;
    void *t3;
    s32 flag2;
    s32 tmp;
    s32 bit0;

    if (arg0->unk0x23C != 0) {
        temp_r30 = arg0->unk0xC;
        t1 = fn_800B6570(arg0);
        t2 = fn_8009F498(t1);
        t3 = GetChecksum_3(t2, QB_MODEL);
        temp_r28 = *(s32 *)((char *)t3 + 0x210);
        temp_r29 = (s32)GetChecksum_3((void *)temp_r30, QB_SKELETON);
        var_ctr = 4;
        do {
            var_ctr -= 1;
        } while (var_ctr != 0);
        fn_800B34E4(arg0, &sp8);
        __asm__("li %0,1" : "=r"(temp_r30));
        fn_8005FD68((void *)temp_r28, &sp8, temp_r30 ^ 1, fn_800C9780((void *)temp_r29));
        fn_800601CC((void *)temp_r28, fn_800C9780((void *)temp_r29));
        return;
    }
    {
        void *p = (void *)arg0->unk0x210;
        s32 var_r9;

        if (p != NULL) {
            tmp = *(s32 *)((char *)p + 0x48);
            var_r9 = 0;
            if (tmp & QB_UNKNOWN_0x40000000) {
                bit0 = tmp & QB_UNKNOWN_0x20000000;
                var_r9 = (bit0 == 0);
            }
            if (var_r9 != 0) {
                var_ctr = 4;
                do {
                    var_ctr -= 1;
                } while (var_ctr != 0);
                fn_800B34E4(arg0, &sp8);
                temp_r30 = 0;
                if (arg0->unk0x214 != 0) {
                    temp_r30 = fn_800C9780((void *)arg0->unk0x214);
                }
                flag2 = 1;
                if (arg0->unk0x214 == 0) {
                    flag2 = 0;
                }
                if (arg0->unk0x218 != 0) {
                    flag2 = fn_800CC2D4((void *)arg0->unk0x218);
                }
                fn_8005FD68((void *)arg0->unk0x210, &sp8, flag2 ^ 1, temp_r30);
            }
        }
    }
}
