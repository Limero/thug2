// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80122304-0x80122450 (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

s32 fn_80123864(void *, s32);
s32 fn_80249998(void *, void *, s32, void *);
void fn_8012156C(void);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);

/* One 10-slot ring-buffer record of the stream manager: cursor, length,
   copied-to-0x2E0 word, and the "still live" pointer tested at entry. */
typedef struct {
    char *buf;
    u32 len;
    u32 seq;
    void *active;
} Slot;

typedef struct {
    char pad0x0[0x2D0];
    s32 unk0x2D0;
    char pad0x2D4[0xC];
    s32 unk0x2E0;
    char pad0x2E4[0x8];
    u32 unk0x2EC;
    u32 unk0x2F0;
    Slot slots[10];
    char pad0x394[4];
    void *unk0x398;
    char unk0x39C[4];
} Unk_mgr;

extern Unk_mgr lbl_8039BA58;

bool fn_80122304(void) {
    char *ptr;
    u32 csz;
    u32 rem;
    u32 idx;
    s32 level;

    idx = lbl_8039BA58.unk0x2F0;
    if (lbl_8039BA58.slots[idx].active != 0) {
        rem = lbl_8039BA58.slots[idx].len - 0x20;
        ptr = lbl_8039BA58.slots[idx].buf;
        if (rem > 0x1FU) {
            do {
                csz = *(u32 *)(ptr + 4);
                if (*(u32 *)ptr == QB_FOURCC_VIDD) {
                    fn_80249998(lbl_8039BA58.unk0x398, ptr + 0xC, csz - 0xC,
                                lbl_8039BA58.unk0x39C);
                } else if (*(u32 *)ptr == QB_FOURCC_AUDD) {
                    fn_80123864(ptr + 0xC, csz - 0xC);
                }
                rem -= csz;
                ptr += csz;
            } while (rem > 0x1FU);
        }
        idx = lbl_8039BA58.unk0x2F0;
        lbl_8039BA58.unk0x2E0 = lbl_8039BA58.slots[idx].seq;
        lbl_8039BA58.slots[idx].active = 0;
        lbl_8039BA58.unk0x2F0 = (lbl_8039BA58.unk0x2F0 + 1) % 10;
        level = OSDisableInterrupts();
        if ((lbl_8039BA58.slots[lbl_8039BA58.unk0x2EC].active == 0) &&
            (lbl_8039BA58.unk0x2D0 == 0)) {
            fn_8012156C();
        }
        OSRestoreInterrupts(level);
        return true;
    }
    return false;
}
