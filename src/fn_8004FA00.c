// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004FA00-0x8004FA18 (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Initializes two fields of the object at arg0 from data reachable through
// the pointer stored at *arg1: 0x1C0 = 1 and 0x1B0 = *(ptr + 0x18).
// Suggested rename: InitFields_ViaPtr
#include "types.h"
void fn_8004FA00(void *arg0, void *arg1) {
    void *p = *(void **)arg1;
    s32 v = *(s32 *)((char *)p + 0x18);
    *(s32 *)((char *)arg0 + 0x1C0) = 1;
    *(s32 *)((char *)arg0 + 0x1B0) = v;
}