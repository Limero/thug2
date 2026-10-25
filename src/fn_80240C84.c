// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240C84-0x80240DC0 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void *fn_80240C7C(void *arg0);
void *fn_80240C80(void *arg0);
s32 fn_80240C84(Unk_9994C3F5 *arg0, CStruct *arg1, s32 arg2) {
    struct {
        f32 v[3];
        char _p[4];
        f32 s[3];
    } fr;
    f32 *ps;
    register s32 psr __asm__("r30");
    f32 *pv;
    register s32 pc __asm__("r27");
    s32 m0;
    Unk_F5317C5D *temp_r9;
    CStruct *var_r31;

    if (arg1->unk0x4 & 1) {
        var_r31 = fn_80240C7C(arg1);
    } else {
        var_r31 = *(void **)((char *)fn_80240C80(arg1) + 0x14);
    }
    if (arg2 & 1) {
        temp_r9 = *((void * *)&var_r31->unk0xC);
        ps = &fr.s[0];
        psr = (s32)ps;
        pv = &fr.v[0];
        __asm__("mr %0,%1" : "=r"(pc) : "r"(pv));
        ((s32 (*)(void *, void *))temp_r9->unk0xC)((void *)psr, (char *)var_r31 + temp_r9->unk0x8);
        fr.v[0] = fr.s[2];
        ((s32 (*)(void *, void *))*(s32 *)((char *)(var_r31->unk0xC) + 0xC))((void *)psr, (char *)var_r31 + *(s16 *)((char *)(var_r31->unk0xC) + 8));
        m0 = psr;
        pv[2] = fr.s[0];
    } else {
        temp_r9 = *((void * *)&var_r31->unk0xC);
        ps = &fr.s[0];
        psr = (s32)ps;
        pv = &fr.v[0];
        __asm__("mr %0,%1" : "=r"(pc) : "r"(pv));
        ((s32 (*)(void *, void *))temp_r9->unk0xC)((void *)psr, (char *)var_r31 + temp_r9->unk0x8);
        fr.v[0] = fr.s[0];
        ((s32 (*)(void *, void *))*(s32 *)((char *)(var_r31->unk0xC) + 0xC))((void *)psr, (char *)var_r31 + *(s16 *)((char *)(var_r31->unk0xC) + 8));
        m0 = psr;
        pv[2] = fr.s[2];
    }
    ((s32 (*)(void *, void *))*(s32 *)((char *)(var_r31->unk0xC) + 0xC))((void *)m0, (char *)var_r31 + *(s16 *)((char *)(var_r31->unk0xC) + 8));
    fr.v[1] = fr.s[1];
    *(__ps_t *)arg0 = *(__ps_t *)&fr.v[0];
    *((__ps_t *)((char *)arg0 + 8)) = *(__ps_t *)((char *)pc + 8);
    return (s32)arg0;
}
