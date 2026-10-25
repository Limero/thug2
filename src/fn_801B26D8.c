// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B26D8-0x801B27F8 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802ABF14[];
extern f64 lbl_802ABF20;
extern f32 lbl_802ABF28;
typedef union { u32 w[2]; f64 d; } cvt_801B26D8_u;
typedef struct {
    u8 _0[0x30];
    f32 t[4];
    f32 out;
    u8 pad[4];
    cvt_801B26D8_u cvt;
} fr_801B26D8;
s32 fn_8012834C(CStruct *, void *, void *, s32);
void fn_800071D4(void *);
register __ps_t *pdr_801B26D8 __asm__("r10");
bool fn_801B26D8(Unk_C7387A53 *arg0, CStruct *arg1) {
    fr_801B26D8 fr;
    CStruct *p;
    f32 temp;
    f64 magic;
    f32 cval;
    f32 v58;
    register f32 m0r __asm__("fr13");
    register f32 cvalr __asm__("fr13");
    register f32 p5cr __asm__("fr11");
    s32 pg;
    u32 bias;
    s32 ret;
    ret = fn_8012834C(arg1, (s32)lbl_802ABF14, &fr.out, 1);
    __asm__ volatile("lis %0,0x4330" : "=r"(bias));
    fr.cvt.w[1] = (u32)ret;
    __asm__ volatile("lis %0,0x802b" : "=r"(pg));
    magic = *(f64 *)((char *)pg - 0x40e0);
    fr.cvt.w[0] = bias;
    fr.out = (f32)(fr.cvt.d - magic);
    fn_800071D4(&fr);
    temp = fr.out;
    p = arg0->unk0xC;
    pdr_801B26D8 = (__ps_t *)&fr._0[0];
    fr.t[1] = fr.out;
    fr.t[2] = fr.out;
    fr.t[0] = fr.out;
    cvalr = lbl_802ABF28;
    __asm__ __volatile__("" : "+f"(cvalr));
    fr.t[3] = cvalr;
    __asm__ __volatile__(
        ".long 0xE1BE00C0\n\t"
        ".long 0xE1410038\n\t"
        ".long 0xE17E00C8\n\t"
        ".long 0xE1010040\n\t"
        ".long 0x11AD5028\n\t"
        ".long 0xE19E00D0\n\t"
        ".long 0x11205090\n\t"
        ".long 0xE01E00D8\n\t"
        ".long 0x116B4028\n\t"
        ".long 0xF1A10008\n\t"
        ".long 0x11404090\n\t"
        ".long 0xF16A0008\n\t"
        ".long 0x118C482A\n\t"
        ".long 0x1000502A\n\t"
        ".long 0xF1810018\n\t"
        ".long 0xF0010020\n\t"
        ".long 0xF1810028\n\t"
        ".long 0xF0010030"
        : : : "fr13", "fr12", "fr11", "fr10", "fr9", "fr8", "fr0", "memory");
    m0r = ((f32 *)fr._0)[0];
    __asm__ __volatile__("" : "+f"(m0r));
    v58 = *((f32 *)&p->unk0x58);
    if (v58 >= m0r) {
    } else {
        goto fail;
    }
    p5cr = *((f32 *)&p->unk0x5C);
    if (p5cr >= ((f32 *)fr._0)[1]) {
    } else {
        goto fail;
    }
    if (*((f32 *)&p->unk0x60) >= ((f32 *)pdr_801B26D8)[2]) {
    } else {
        goto fail;
    }
    __asm__ __volatile__("fcmpu 0, %0, %1" : : "f"(v58), "f"(((f32 *)fr._0)[4]));
fail:
    return false;
}
