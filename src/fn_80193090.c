// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80193090-0x801930EC (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80193678(Unk_72E9CBBF *);
extern s32 fn_8018C080(Unk_672A1C0D *);
s32 fn_80193090(Unk_C8FEE62D *arg0) {
    Unk_89391A04 *temp_r9;

    temp_r9 = *((void * *)&arg0->unk0x14);
    return ((s32 (*)(void *))(*((void * *)&temp_r9->unk0x24)))((char *)arg0 + temp_r9->unk0x20) != 0
               ? 0
               : fn_8018C080((fn_80193678(arg0), arg0));
}
