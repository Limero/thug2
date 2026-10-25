// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FE204-0x800FE278 (116B). Byte-identical.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_80103BC4(Unk_87891B5F *, void *);

typedef void *(*FP)(void *);
register s32 r31_guard __asm__("r31");

void fn_800FE204(CStruct *arg0, void *arg1) {
    __ps_t sp[2];
    Unk_CC629601 *vt;
    s16 off;
    FP fp;
    void *ret;
    register char *rp __asm__("r9");
    register void *f8 __asm__("r30");
    __ps_t ha;
    __ps_t hr;
    __ps_t lr;
    __ps_t la;

    vt = *((char * *)&arg0->unk0xC);
    off = vt->unk0x40;
    fp = *((FP *)&((Unk_C7387A53 *)vt)->unk0x44);
    f8 = *((void * *)&arg0->unk0x8);
    ret = fp((char *)arg0 + off);
    __asm__("mr %0, %1" : "=r"(rp) : "r"(ret));
    ha = ((__ps_t *)arg1)[1];
    hr = ((__ps_t *)rp)[1];
    lr = ((__ps_t *)rp)[0];
    la = ((__ps_t *)arg1)[0];
    sp[1] = ha - hr;
    sp[0] = la - lr;
    fn_80103BC4(f8, (void *)&sp[0]);
}
