// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BCCC-0x8007BD1C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80295CE0[];
void fn_8005DB04(void);
void fn_8007BD70(void *);
void *fn_8007BCCC(Unk_C8FEE62D *arg0) {
    fn_8005DB04();
    arg0->unk0x14 = (s32)lbl_80295CE0;
    arg0->unk0x18 = (s32)Mem_Alloc2(8);
    fn_8007BD70(arg0);
    return arg0;
}
