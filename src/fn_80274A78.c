// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80274A78-0x80274AC4 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
register unsigned int save_base __asm__("r11");
register unsigned int save_r14 __asm__("r14");
register unsigned int save_r15 __asm__("r15");
register unsigned int save_r16 __asm__("r16");
register unsigned int save_r17 __asm__("r17");
register unsigned int save_r18 __asm__("r18");
register unsigned int save_r19 __asm__("r19");
register unsigned int save_r20 __asm__("r20");
register unsigned int save_r21 __asm__("r21");
register unsigned int save_r22 __asm__("r22");
register unsigned int save_r23 __asm__("r23");
register unsigned int save_r24 __asm__("r24");
register unsigned int save_r25 __asm__("r25");
register unsigned int save_r26 __asm__("r26");
register unsigned int save_r27 __asm__("r27");
register unsigned int save_r28 __asm__("r28");
register unsigned int save_r29 __asm__("r29");
register unsigned int save_r30 __asm__("r30");
register unsigned int save_r31 __asm__("r31");

void __save_gpr(void) {
    __asm__(".globl _savegpr_14\n_savegpr_14:");
    *(unsigned int *)(save_base - 0x48) = save_r14;
    __asm__(".globl _savegpr_15\n_savegpr_15:");
    *(unsigned int *)(save_base - 0x44) = save_r15;
    __asm__(".globl _savegpr_16\n_savegpr_16:");
    *(unsigned int *)(save_base - 0x40) = save_r16;
    __asm__(".globl _savegpr_17\n_savegpr_17:");
    *(unsigned int *)(save_base - 0x3C) = save_r17;
    __asm__(".globl _savegpr_18\n_savegpr_18:");
    *(unsigned int *)(save_base - 0x38) = save_r18;
    __asm__(".globl _savegpr_19\n_savegpr_19:");
    *(unsigned int *)(save_base - 0x34) = save_r19;
    __asm__(".globl _savegpr_20\n_savegpr_20:");
    *(unsigned int *)(save_base - 0x30) = save_r20;
    __asm__(".globl _savegpr_21\n_savegpr_21:");
    *(unsigned int *)(save_base - 0x2C) = save_r21;
    __asm__(".globl _savegpr_22\n_savegpr_22:");
    *(unsigned int *)(save_base - 0x28) = save_r22;
    __asm__(".globl _savegpr_23\n_savegpr_23:");
    *(unsigned int *)(save_base - 0x24) = save_r23;
    __asm__(".globl _savegpr_24\n_savegpr_24:");
    *(unsigned int *)(save_base - 0x20) = save_r24;
    __asm__(".globl _savegpr_25\n_savegpr_25:");
    *(unsigned int *)(save_base - 0x1C) = save_r25;
    __asm__(".globl _savegpr_26\n_savegpr_26:");
    *(unsigned int *)(save_base - 0x18) = save_r26;
    __asm__(".globl _savegpr_27\n_savegpr_27:");
    *(unsigned int *)(save_base - 0x14) = save_r27;
    __asm__(".globl _savegpr_28\n_savegpr_28:");
    *(unsigned int *)(save_base - 0x10) = save_r28;
    __asm__(".globl _savegpr_29\n_savegpr_29:");
    *(unsigned int *)(save_base - 0xC) = save_r29;
    __asm__(".globl _savegpr_30\n_savegpr_30:");
    *(unsigned int *)(save_base - 0x8) = save_r30;
    __asm__(".globl _savegpr_31\n_savegpr_31:");
    *(unsigned int *)(save_base - 0x4) = save_r31;
}
