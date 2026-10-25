// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800963F8-0x800964EC (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Obj_800963F8 {
    s32 unk0x0;
    u16 flags;
    u16 pad0x6;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
} Obj_800963F8;
extern Unk_9994C3F5 *lbl_802FFE98;
void Mem_Alloc2(s32);
Obj_800963F8 *fn_8009636C(void);
void fn_80010D94(s32, s32);
s32 Mem_Alloc(void *);
void fn_80010E78(s32);
void *fn_800963F8(Obj_800963F8 *arg0, s32 arg1) {
    register u16 flags_r10 __asm__("r10");
    u16 var_r0;
    Obj_800963F8 *temp_r3;
    s32 *temp_r4;

    Mem_Alloc2(0x1C);
    temp_r3 = fn_8009636C();
    *temp_r3 = *arg0;
    flags_r10 = temp_r3->flags & 0xFFCF;
    temp_r3->flags = flags_r10;
    if (arg1 != 0) {
        var_r0 = flags_r10 | 1;
    } else {
        temp_r3->flags = flags_r10 | 4;
        fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
        temp_r3->unk0x14 = Mem_Alloc((void *)(*(s32 *)arg0->unk0x14 + 0x40));
        fn_80010E78(lbl_802FFE98->unk0x11C);
        temp_r4 = (s32 *)arg0->unk0x14;
        memcpy((void *)temp_r3->unk0x14, temp_r4, *(s32 *)temp_r4 + 0x40);
        var_r0 = temp_r3->flags | 0x100;
    }
    temp_r3->flags = var_r0;
    return temp_r3;
}
