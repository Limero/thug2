// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077C48-0x80077C9C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8005BF08(void *, void *);
s32 fn_8009B4B0(void *, s32);
extern char lbl_80295990[];
void *fn_80077C48(CStruct *arg0, Unk_C7387A53 *arg1) {
    void *m;
    fn_8005BF08(arg0, arg1);
    arg0->unk0x8 = (s32)lbl_80295990;
    m = Mem_Alloc2(0x1C);
    arg0->unk0xC = fn_8009B4B0(m, arg1->unk0xC);
    return arg0;
}
