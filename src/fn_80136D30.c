// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136D30-0x80136E50 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_8039D940[];
extern char lbl_8039D9F4[];
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
s32 AUDSimpleAudioDecode(Unk_897A0ACF *, s32);
void fn_80136280(void);

bool fn_80136D30(void) {
    char *stsp;
    char *szp;
    char *ptp;
    char *b1;
    char *b2;
    char *nxt4;
    char *sts8;
    char *ptr;
    register s32 next __asm__("r9");
    s32 level;
    register u32 idx __asm__("r11");
    u32 off;
    u32 nidx;
    u32 size;
    u32 csz;
    u32 rem;

    b1 = lbl_8039D940;
    b1 = lbl_8039D940;
    idx = ((Unk_E3099A99 *)b1)->unk0xE8;
    off = idx << 4;
    stsp = b1 + 0xF8;
    if (*(s32 *)(stsp + off) != 0) {
        ptp = b1 + 0xEC;
        szp = b1 + 0xF0;
        size = *(u32 *)(szp + off);
        ptr = *(char **)(ptp + off);
        rem = size - 0x20;
        if (rem > 0x1FU) {
            do {
                csz = ((Unk_C7780169_2 *)ptr)->unk0x4;
                if (*(u32 *)ptr == QB_FOURCC_AUDD) {
                    AUDSimpleAudioDecode(ptr + 0xC, csz - 0xC);
                }
                rem -= csz;
                ptr += csz;
            } while (rem > 0x1FU);
        }
        b2 = lbl_8039D9F4 - 0xB4;
        idx = ((Unk_74BF3C95 *)b2)->unk0xE8;
        idx <<= 4;
        nxt4 = b2 + 0xF4;
        sts8 = b2 + 0xF8;
        next = *(s32 *)(nxt4 + idx);
        ((Unk_74BF3C95 *)b2)->unk0xD8 = next;
        *(s32 *)(sts8 + idx) = 0;
        nidx = (((Unk_74BF3C95 *)b2)->unk0xE8 + 1) % 10;
        ((Unk_74BF3C95 *)b2)->unk0xE8 = nidx;
        level = OSDisableInterrupts();
        if ((*(s32 *)(sts8 + (((Unk_AC288993 *)b2)->unk0xE4 << 4)) == 0) &&
            (((Unk_74BF3C95 *)b2)->unk0xBC == 0)) {
            fn_80136280();
        }
        OSRestoreInterrupts(level);
        return true;
    }
    return false;
}
