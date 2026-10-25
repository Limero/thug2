// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80274AC4-0x80274B10 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
register unsigned int rest_base __asm__("r11");
register unsigned int rest_r14 __asm__("r14");
register unsigned int rest_r15 __asm__("r15");
register unsigned int rest_r16 __asm__("r16");
register unsigned int rest_r17 __asm__("r17");
register unsigned int rest_r18 __asm__("r18");
register unsigned int rest_r19 __asm__("r19");
register unsigned int rest_r20 __asm__("r20");
register unsigned int rest_r21 __asm__("r21");
register unsigned int rest_r22 __asm__("r22");
register unsigned int rest_r23 __asm__("r23");
register unsigned int rest_r24 __asm__("r24");
register unsigned int rest_r25 __asm__("r25");
register unsigned int rest_r26 __asm__("r26");
register unsigned int rest_r27 __asm__("r27");
register unsigned int rest_r28 __asm__("r28");
register unsigned int rest_r29 __asm__("r29");
register unsigned int rest_r30 __asm__("r30");
register unsigned int rest_r31 __asm__("r31");

void __restore_gpr(void) {
    __asm__(".globl _restgpr_14\n_restgpr_14:");
    rest_r14 = *(unsigned int *)(rest_base - 0x48);
    __asm__(".globl _restgpr_15\n_restgpr_15:");
    rest_r15 = *(unsigned int *)(rest_base - 0x44);
    __asm__(".globl _restgpr_16\n_restgpr_16:");
    rest_r16 = *(unsigned int *)(rest_base - 0x40);
    __asm__(".globl _restgpr_17\n_restgpr_17:");
    rest_r17 = *(unsigned int *)(rest_base - 0x3C);
    __asm__(".globl _restgpr_18\n_restgpr_18:");
    rest_r18 = *(unsigned int *)(rest_base - 0x38);
    __asm__(".globl _restgpr_19\n_restgpr_19:");
    rest_r19 = *(unsigned int *)(rest_base - 0x34);
    __asm__(".globl _restgpr_20\n_restgpr_20:");
    rest_r20 = *(unsigned int *)(rest_base - 0x30);
    __asm__(".globl _restgpr_21\n_restgpr_21:");
    rest_r21 = *(unsigned int *)(rest_base - 0x2C);
    __asm__(".globl _restgpr_22\n_restgpr_22:");
    rest_r22 = *(unsigned int *)(rest_base - 0x28);
    __asm__(".globl _restgpr_23\n_restgpr_23:");
    rest_r23 = *(unsigned int *)(rest_base - 0x24);
    __asm__(".globl _restgpr_24\n_restgpr_24:");
    rest_r24 = *(unsigned int *)(rest_base - 0x20);
    __asm__(".globl _restgpr_25\n_restgpr_25:");
    rest_r25 = *(unsigned int *)(rest_base - 0x1C);
    __asm__(".globl _restgpr_26\n_restgpr_26:");
    rest_r26 = *(unsigned int *)(rest_base - 0x18);
    __asm__(".globl _restgpr_27\n_restgpr_27:");
    rest_r27 = *(unsigned int *)(rest_base - 0x14);
    __asm__(".globl _restgpr_28\n_restgpr_28:");
    rest_r28 = *(unsigned int *)(rest_base - 0x10);
    __asm__(".globl _restgpr_29\n_restgpr_29:");
    rest_r29 = *(unsigned int *)(rest_base - 0xC);
    __asm__(".globl _restgpr_30\n_restgpr_30:");
    rest_r30 = *(unsigned int *)(rest_base - 0x8);
    __asm__(".globl _restgpr_31\n_restgpr_31:");
    rest_r31 = *(unsigned int *)(rest_base - 0x4);
}
