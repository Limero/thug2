// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80258A38-0x80258B78 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"
#include "structs.h"
extern void *lbl_803CA340;
void *fn_8024EAF4(s32 **heap, s32 size);
void *fn_80257E48(CStruct * arg0, s32 arg1);
void fn_80257CC4(void *dst, s32 size);
void fn_8024EBD8(void *heap, s32 * ptr);

void *Vtable0x8030804C_m18(Unk_31DE137E *arg0, s32 arg1) {
    register s32 a_lim __asm__("r27") = arg0->unk0x1C;
    register s32 a_bs __asm__("r28") = (s32)arg1;
    register s32 a_p __asm__("r31");
    register s32 a_i __asm__("r29");
    register s32 a_q __asm__("r30");
    void *res;
    s32 cnt;
    s32 v;

    a_p = (s32)fn_8024EAF4((s32 **)lbl_803CA340, 0x58);
    /* r13-form via extra_cflags */
    ((Unk_DB0E2BAB *)a_p)->unk0x0 = fn_80257E48((void *)a_bs, 8);
    ((Unk_DB0E2BAB *)a_p)->unk0x4 = fn_80257E48((void *)a_bs, 0x10);
    ((Unk_DB0E2BAB *)a_p)->unk0x8 = fn_80257E48((void *)a_bs, 0x10);
    ((Unk_DB0E2BAB *)a_p)->unk0xC = fn_80257E48((void *)a_bs, 6);
    ((Unk_DB0E2BAB *)a_p)->unk0x10 = fn_80257E48((void *)a_bs, 8);
    v = fn_80257E48((void *)a_bs, 4);
    cnt = v + 1;
    ((Unk_DB0E2BAB *)a_p)->unk0x14 = cnt;
    if (((Unk_DB0E2BAB *)a_p)->unk0x0 <= 0) {
        goto fail;
    }
    if (((Unk_DB0E2BAB *)a_p)->unk0x4 <= 0) {
        goto fail;
    }
    if (((Unk_DB0E2BAB *)a_p)->unk0x8 <= 0) {
        goto fail;
    }
    if (cnt <= 0) {
        goto fail;
    }
    a_i = 0;
    for (;;) {
        if (a_i >= cnt) {
            goto ok;
        }
        a_q = a_p + 0x18;
        for (;;) {
            v = fn_80257E48((void *)a_bs, 8);
            *(s32 *)a_q = v;
            if ((a_q += 4, v) < 0) {
                goto fail;
            }
            if (v >= ((CScript *)a_lim)->unk0x18) {
                goto fail;
            }
            a_i += 1;
            if (a_i >= ((Unk_DB0E2BAB *)a_p)->unk0x14) {
                goto ok;
            }
        }
    }
ok:
    res = (void *)a_p;
    goto done;
fail:
    if (a_p != 0) {
        fn_80257CC4((void *)a_p, 0x58);
        fn_8024EBD8(lbl_803CA340, (void *)a_p);
    }
    res = 0;
done:
    return res;
}
