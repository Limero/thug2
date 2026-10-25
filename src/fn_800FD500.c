// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FD500-0x800FD558 (88B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800FD59C(Unk_16447AB3 * arg);
void fn_800FD500(Unk_64D775D7 *arg0, void *arg1) {
    __ps_t *p2;
    arg0->unk0x20 = ((__ps_t *)arg1)[0];
    arg0->unk0x28 = ((__ps_t *)arg1)[1];
    arg0->unk0x30 = ((__ps_t *)arg1)[2];
    arg0->unk0x38 = ((__ps_t *)arg1)[3];
    p2 = (__ps_t *)((char *)arg0 + 0x20);
    __asm__("" : "+r"(p2));
    p2[4] = ((__ps_t *)arg1)[4];
    p2[5] = ((__ps_t *)arg1)[5];
    fn_800FD59C(arg0);
}