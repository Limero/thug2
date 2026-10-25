// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801197FC-0x8011984C (80B). Byte-identical.
#include "types.h"
#include "mem.h"
s32 fn_80119470(void *);
void fn_8011984C(void *);
void fn_801197FC(void *arg0, s32 arg1) {
    if (fn_80119470(arg0) == 0) {
        fn_8011984C(arg0);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
