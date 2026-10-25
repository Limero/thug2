// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CCA50-0x800CCA98 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
typedef struct CcaSource {
    char pad0x0[0x58];
    __ps_t v58;
    __ps_t v60;
} CcaSource;
typedef struct CcaObject {
    char pad0x0[0x0C];
    CcaSource *src;
    char pad0x10[0x90];
    __ps_t a0;
    __ps_t a8;
    __ps_t b0;
    __ps_t b8;
} CcaObject;
void fn_800CD150(CcaObject *);
void fn_800CCA50(CcaObject *arg0) {
    CcaSource *src;
    arg0->b0 = arg0->a0;
    src = arg0->src;
    arg0->b8 = arg0->a8;
    arg0->a0 = src->v58;
    arg0->a8 = src->v60;
    fn_800CD150(arg0);
}
