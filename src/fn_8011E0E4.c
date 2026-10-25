// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E0E4-0x8011E2B8 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0[0xC80];
    s32 unk0xC80;
    char pad0xC84[4];
    s32 unk0xC88;
    s32 unk0xC8C;
    s32 unk0xC90;
    s32 unk0xC94;
    char pad1[0x10];
    s32 unk0xCA8;
} Track_t;
extern char lbl_8038C8C0[];
extern s32 lbl_80302CD4;
s32 fn_8011BC38(void);
s32 fn_8011E2B8(s32, s32);
void StopMusic(void);
u64 fn_80273480();
u64 fn_80273B68();

void SetTrackForbiddenStatus(s32 arg0, s32 arg1, s32 arg2) {
    Track_t *base;
    char *tr;
    s32 cnt;
    s32 i;
    s32 res;
    unsigned long long alo;
    unsigned long long t;

    if (fn_8011BC38() == 0) {
        base = (char *)(arg2 * 0xCB0 + (s32)lbl_8038C8C0);
        lbl_80302CD4 = 1;
        tr = (char *)base;
        if (arg1 != 0) {
            if (arg0 <= 63) {
                *((unsigned long long *)&base->unk0xC88) |= fn_80273480(1ULL, arg0);
            } else {
                *((unsigned long long *)&base->unk0xC90) |= fn_80273480(1ULL, arg0 - 64);
            }
            if (fn_8011E2B8(arg2, arg0) != 0) {
                StopMusic();
            }
            i = 0;
            if (i < base->unk0xC80) {
                cnt = *(s32 *)((char *)tr + 0xC80);
                res = 0;
                alo = *((unsigned long long *)&base->unk0xC88);
                do {
                    t = fn_80273B68(alo, i);
                    if ((((u32)t ^ 1) & 1) != 0) goto fail;
                    t = fn_80273B68(*((unsigned long long *)&base->unk0xC90), i - 64);
                    if ((((u32)t ^ 1) & 1) == 0) goto next;
                fail:
                    base->unk0xCA8 = res;
                    return;
                next:
                    i = i + 1;
                } while (i < cnt);
            }
            base->unk0xCA8 = 1;
        } else {
            if (arg0 <= 63) {
                *((unsigned long long *)&base->unk0xC88) &= ~fn_80273480(1ULL, arg0);
            } else {
                *((unsigned long long *)&base->unk0xC90) &= ~fn_80273480(1ULL, arg0 - 64);
            }
            base->unk0xCA8 = 0;
        }
    }
}
