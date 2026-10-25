// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009B4B0-0x8009B5D8 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
#include "structs.h"
extern Unk_9994C3F5 *lbl_802FFE98;
void fn_80010D94(s32, s32);
void fn_80010E78(s32);
void *fn_8009B4B0(Unk_5D1D68CC *arg0, Unk_5D1D68CC *arg1) {
    s32 temp_r29;
    u16 temp_r0;
    s32 t0, t1, t2, t3, t4, t5, t6;
    void *hd;

    t0 = arg1->unk0x0; t1 = arg1->unk0x4; t2 = arg1->unk0x8; t3 = arg1->unk0xC;
    arg0->unk0x0 = t0; arg0->unk0x4 = t1; arg0->unk0x8 = t2; arg0->unk0xC = t3;
    hd = lbl_802FFE98;
    t4 = arg1->unk0x10; t5 = arg1->unk0x14; t6 = arg1->unk0x18;
    arg0->unk0x10 = t4; arg0->unk0x14 = t5; arg0->unk0x18 = t6;
    fn_80010D94(*(s32 *)((char *)hd + (s32)0x11C), 0x20);
    temp_r29 = arg0->unk0xC;
    arg0->unk0x10 = (s32) Mem_Alloc(temp_r29);
    memcpy(arg0->unk0x10, arg1->unk0x10, temp_r29);
    temp_r0 = *(u16 *)((char *)arg0 + (s32)0xA);
    if (temp_r0 & 2) {
        if (temp_r0 & 0x100) {
            if (temp_r0 & 0x200) {
                arg0->unk0x14 = 0;
            } else {
                arg0->unk0x14 = arg0->unk0x10 + (temp_r29 >> 1);
            }
        } else {
            arg0->unk0x14 = (s32) Mem_Alloc(temp_r29);
        }
        if (*(u8 *)((char *)arg0 + (s32)0x9) != 6) {
            if (arg0->unk0x14 != 0) {
                memcpy(arg0->unk0x14, arg1->unk0x14, temp_r29);
            }
        }
        *(u16 *)((char *)arg0 + (s32)0xA) =
            (u16) (*(u16 *)((char *)arg0 + (s32)0xA) | 0x20);
    }
    fn_80010E78(lbl_802FFE98->unk0x11C);
    return arg0;
}
