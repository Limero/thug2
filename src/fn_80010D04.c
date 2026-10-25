// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010D04-0x80010D94 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80010A68(s32, s32);
extern char lbl_80290630[];
extern char lbl_80290610[];
typedef struct Wip10D04 { s32 unk0x0; void *unk0x4; char *unk0x8; s32 unk0xC; } Wip10D04;
void fn_80010D04(Unk_C7387A53 *arg0) {
    Wip10D04 sp8; CStruct *var_r9; Unk_C7387A53 *base; Wip10D04 *p; s32 var_r0;
    register s32 rb __asm__("r10");
    register s32 rs __asm__("r11");
    if (arg0->unk0x40 != 0) { fn_80010A68(arg0->unk0x40, 3); }
    rb = (s32)((char *)arg0 + 0x48); base = (Unk_C7387A53 *)(s32)rb;
    rs = (s32)&sp8;
    *(volatile char **)&((Wip10D04 *)(s32)rs)->unk0x8 = lbl_80290630;
    p = (Wip10D04 *)(s32)rs;
    __asm__ __volatile__ ("" : "+r"(p));
    *(volatile void **)&((Wip10D04 *)(s32)rs)->unk0x4 = (void *)base;
    var_r9 = base->unk0xC;
    if (var_r9->unk0x4 == -1) { var_r9 = NULL; }
    *(volatile void **)&p->unk0x4 = (void *)var_r9;
    if (var_r9 == NULL) { var_r0 = 0; } else { var_r0 = var_r9->unk0x4; }
    arg0->unk0x40 = var_r0;
    *(volatile char **)&p->unk0x8 = lbl_80290610 + 0x20;
}
