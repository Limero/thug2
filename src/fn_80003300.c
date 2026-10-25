// fn_80003300 — Clear GQR0..GQR7 (Gekko graphics-quantization registers).
// range 0x80003300-0x80003328 (40B). Byte-identical.
// .init leaf, called first from __start: li r3,0 then mtspr 0x390..0x397.
// Inline-asm wedges for the privileged SPR writes (ngccc has no C route),
// same precedent as src/fn_8025AF7C.c and src/fn_80003334.c. The zero web
// is pinned to r3 so all eight wedges share one `li r3,0`.
#include "types.h"

__attribute__((section(".init"))) void fn_80003300(void) {
    register s32 z __asm__("r3");
    z = 0;
    __asm__ volatile("mtspr 0x390, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x391, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x392, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x393, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x394, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x395, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x396, %0" :: "r"(z));
    __asm__ volatile("mtspr 0x397, %0" :: "r"(z));
}
