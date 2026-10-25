// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80066834-0x80066988 (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80062D44(void *);
void fn_80062BBC(void * arg0);
extern char lbl_8029422C[];
#include "structs.h"
s32 Mem_Alloc(s32);
s32 Mem_Alloc2(s32);
extern char lbl_80294230[];
extern char lbl_80294248[];
void *fn_80066834(Unk_DCEB657B *arg0, s32 arg1, s32 arg2) {
    s32 var_r27;
    void *temp_r28;
    void *var_r30;
    f32 temp_f0;
    register char *pgF __asm__("r11");

    fn_80062D44(arg0);
    var_r27 = arg2 - 1;
    arg0->unk0xF8 = arg1;
    arg0->unk0x84 = arg2;
    arg0->unk0x20 = (s32)lbl_80294230;
    arg0->unk0x8 = (s32)lbl_80294248;
    arg0->unk0x94 = 0;
    temp_r28 = Mem_Alloc((arg2 * 0x30) | 8) + 8;
    *(s32 *)((char *)temp_r28 - 0x8) = arg2;
    var_r30 = temp_r28;
    if (arg2 != 0) {
        do {
            fn_80062BBC(var_r30);
            var_r30 += 0x30;
        } while (0 != var_r27--);
    }
    arg0->unk0x100 = temp_r28;
    arg0->unk0x124 = Mem_Alloc(((arg2 << 1) + arg2) << 2);
    arg0->unk0x114 = Mem_Alloc2(4);
    arg0->unk0x118 = Mem_Alloc2(4);
    arg0->unk0x11C = Mem_Alloc2(4);
    pgF = (char *)&lbl_8029422C;
    *(u8 *)(arg0->unk0x114 + 0x0) = 0x80;
    temp_f0 = *(volatile f32 *)((char *)pgF);
    *(u8 *)((*(volatile s32 *)&arg0->unk0x114) + 1) = 0x80;
    *(u8 *)(arg0->unk0x114 + 0x2) = 0x80;
    *(u8 *)(arg0->unk0x114 + 0x3) = 0x80;
    *(u8 *)(arg0->unk0x118 + 0x0) = 0x80;
    *(u8 *)(arg0->unk0x118 + 0x1) = 0x80;
    *(u8 *)(arg0->unk0x118 + 0x2) = 0x80;
    *(u8 *)(arg0->unk0x118 + 0x3) = 0x80;
    *(u8 *)(arg0->unk0x11C + 0x0) = 0x80;
    *(u8 *)(arg0->unk0x11C + 0x1) = 0x80;
    *(u8 *)(arg0->unk0x11C + 0x2) = 0x80;
    *(u8 *)(arg0->unk0x11C + 0x3) = 0x80;
    *(volatile f32 *)&arg0->unk0x110 = temp_f0;
    arg0->unk0x128 = (s32)(*(volatile s32 *)&arg0->unk0x128 | 4);
    return arg0;
}
