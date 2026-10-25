// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001593C-0x800159B4 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80290B50[];
s32 BannerCheck(s32);
void fn_800158D8(s32);
/* Pool object returned by BannerCheck: 0x2C bytes, ref-counted by the
   globals at lbl_802FFF6C / lbl_802FFF70.  fn_800159B4 initialises the
   free-list at +0x18/+0x1C with this same 32-byte stride; fn_80015BDC
   zeroes the +0x24/+0x28 links.  One 32-byte record lives at +4. */
typedef struct { s32 unk0x0; u8 rec[8][0x20]; } Unk_8001593C_Pool;
void fn_8001593C(s32 arg0) {
    s32 sp8[4];
    register s32 p29 __asm__("r29");
    s32 temp_r3;
    Unk_C7387A53 *temp_r9;
    char *recs;

    p29 = (s32)sp8;
    *(s32 *)(p29 + 0xC) = (s32)lbl_80290B50;
    temp_r3 = BannerCheck(0);
    recs = (char *)temp_r3 + 4;
    __asm__ volatile("" : "+r"(recs));
    temp_r9 = (Unk_C7387A53 *)(recs + (arg0 << 5));
    /* Zero-code barrier: the pointer birth must stay ahead of the +0x8 slot
       store of sp8[2], which the scheduler otherwise hoists in front of it. */
    __asm__ volatile("");
    sp8[2] = temp_r3;
    if ((temp_r9 != NULL) && (temp_r9->unk0xC != 0)) {
        temp_r9->unk0xC = 0;
    }
    *(s32 *)(p29 + 0xC) = (s32)lbl_80290B50;
    fn_800158D8(temp_r3);
}
