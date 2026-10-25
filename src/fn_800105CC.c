// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800105CC-0x80010600 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void *fn_8000F10C(Unk_4897C6F8 *, s32, s32, Unk_E15B2970 *);
// Mem_Alloc_3 @ 0x800105CC
void *Mem_Alloc_3(u32 size) {
    return fn_8000F10C((Unk_4897C6F8 *)*(s32 *)&lbl_802FFE98, size, 1, 0);
}
