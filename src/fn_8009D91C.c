// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D91C-0x8009D9C4 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[3];
    u8 unk0x3;    /* raw X reading, 0..255, centre 0x80 */
    u8 unk0x4;    /* raw Y reading, 0..255, centre 0x80 */
    s8 unk0x5;    /* X excursion above centre: raw - 0x80 */
    s8 unk0x6;    /* X excursion below centre: 0x80 - raw */
    s8 unk0x7;    /* Y excursion below centre: raw - 0x80 */
    s8 unk0x8;    /* Y excursion above centre: 0x80 - raw */
    char pad0x9[0x13];
    u32 unk0x1C;  /* per-axis calibration flags 0x1000/0x2000/0x4000/0x8000 */
} Unk_8009D91C_t;

void fn_8009D91C(Unk_8009D91C_t *arg0) {
    register s32 flags __asm__("r9");   /* top 0x1C read, X-axis flag ops */
    register s32 t __asm__("r10");      /* the `>> 31` sign temp of abs   */
    register s32 dres __asm__("r11");   /* the absolute value itself      */
    register s32 fb __asm__("r0");      /* Y-axis 0x1C re-read           */
    register u32 b __asm__("r9");       /* raw Y byte (r9 after flags)    */
    u32 a;
    u32 av;
    u32 bv;

    flags = arg0->unk0x1C;
    if (flags & 0xF000) {
        return;
    }
    a = arg0->unk0x3;
    av = a & 0xFF;
    if (av > 0x80) {
        arg0->unk0x5 = (s8)(a + 0x80);
        arg0->unk0x1C = flags | 0x2000;
    } else if ((a & 0x80) == 0) {
        av = 0x80 - av;
        t = (s32)av >> 0x1F;
        dres = (t ^ (s32)av) - t;
        arg0->unk0x1C = flags | 0x8000;
        arg0->unk0x6 = (s8)dres;
    }
    b = arg0->unk0x4;
    if ((b & 0x80) == 0) {
        fb = arg0->unk0x1C;
        arg0->unk0x7 = (s8)(b + 0x80);
        arg0->unk0x1C = fb | 0x1000;
        return;
    }
    bv = b & 0xFF;
    if (bv > 0x80) {
        bv = 0x80 - bv;
        t = (s32)bv >> 0x1F;
        dres = (t ^ (s32)bv) - t;
        fb = arg0->unk0x1C;
        arg0->unk0x1C = fb | 0x4000;
        arg0->unk0x8 = (s8)dres;
    }
}
