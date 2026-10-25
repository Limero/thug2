// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FD03C-0x801FD1FC (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern f32 lbl_802AE6CC;
extern f32 lbl_802AE6D0;
extern f32 lbl_802AE6D4;
void fn_8010794C(Unk_C7387A53 *);
void fn_80107A8C(void *, void *);
void fn_80107AA0(char *, void *);
s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
void fn_801FCF84(Unk_C7387A53 *);
void fn_801FCFE4(Unk_C7387A53 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

typedef struct {
    __ps_t pairA;
    __ps_t pairB;
    char desc[0xA8];
    s32 c0;
    char pad[0x14];
    __ps_t d[14];
} FR;

void fn_801FD03C(Unk_34679126 *arg0) {
    FR fr;
    __ps_t *pp = &fr.pairA;
    void *pd = fr.d;
    void *pd2;
    s32 *c0p;

    fr.pairA = arg0->unk0x40;
    pp[1] = arg0->unk0x48;
    pd2 = pd;
    __asm__("" : "+r"(pd2));
    *(f32 *)((char *)&fr.pairA + 4) += arg0->unk0x8C;
    fn_8010794C(fr.desc);
    fn_80107A8C(fr.desc, pp);

    {
        f32 *fp = (f32 *)&fr.d[2];
        f32 cc = lbl_802AE6CC;
        f32 d0 = lbl_802AE6D0;
        __ps_t tA;
        __ps_t tB;
        __ps_t cp1;
        __ps_t cp2;
        fp[0] = cc;
        fp[2] = cc;
        fp[1] = d0;
        fp[3] = cc;
        tB = pp[1];
        tA = fr.pairA;
        cp1 = *(__ps_t *)&fr.d[2];
        cp2 = *(__ps_t *)&fr.d[3];
        *(__ps_t *)&fr.d[0] = __builtin_ps_add(tA, cp1);
        *(__ps_t *)&fr.d[1] = __builtin_ps_add(tB, cp2);
    }
    {
        void *a0 = fr.desc;
        __asm__("" : "+r"(a0));
        fn_80107AA0(a0, pd);
    }

    if (fn_80107B20(fr.desc, 1, 0) != 0) {
        s32 ctr;
        register char *w5 __asm__("r5");
        c0p = &fr.c0;
        fn_801FCF84(arg0);
        ctr = 4;
        do {
            ctr -= 1;
        } while (ctr != 0);
        w5 = (char *)&fr.d[4];
        __asm__("" : "+r"(w5));
        {
            f32 one = lbl_802AE6D4;
            f32 cc = lbl_802AE6CC;
            *(__ps_t *)&fr.d[0] = *(__ps_t *)((char *)fr.desc + 0x88);
            *(__ps_t *)&fr.d[1] = *(__ps_t *)((char *)fr.desc + 0x90);
            *(__ps_t *)&fr.d[2] = *(__ps_t *)((char *)fr.desc + 0x98);
            *(__ps_t *)&fr.d[3] = *(__ps_t *)((char *)fr.desc + 0xA0);
            *(f32 *)((char *)&fr.d[4] + 0x0) = one;
            *(f32 *)((char *)&fr.d[4] + 0x4) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x8) = cc;
            *(f32 *)((char *)&fr.d[4] + 0xc) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x10) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x14) = one;
            *(f32 *)((char *)&fr.d[4] + 0x18) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x1c) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x20) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x24) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x28) = one;
            *(f32 *)((char *)&fr.d[4] + 0x2c) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x30) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x34) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x38) = cc;
            *(f32 *)((char *)&fr.d[4] + 0x3c) = one;
            *(__ps_t *)&fr.d[12] = *(__ps_t *)((char *)fr.desc + 0x98);
            *(__ps_t *)&fr.d[13] = *(__ps_t *)((char *)fr.desc + 0xA0);
        }
        {
            void *obj = arg0->unk0xA0;
            void *vt = *((void * *)&((Unk_9994C3F5 *)obj)->unk0x8);
            ((void *(*)(void *, void *, void *, void *)) *
             (void **)((char *)vt + 0x1C))(
                (char *)obj + ((Unk_2BAD2BE8 *)vt)->unk0x18, pd2,
                w5, (char *)&fr.d[4] + 0x40);
        }
    } else {
        fn_801FCFE4(arg0);
        __asm__ volatile("");
        c0p = &fr.c0;
    }
    if (fr.c0 != 0) {
        CObject_RemoveRefLink(fr.c0, c0p);
        fr.c0 = 0;
    }
}
