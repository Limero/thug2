// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011DC88-0x8011DED0 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_8038C8C0[];
extern char lbl_8038E220[];
extern char lbl_80302CA0[];
extern s32 lbl_80302CA4;
extern s32 lbl_80302CB4;
extern s32 lbl_80302CD0;
typedef struct {
    char pad0[0xC80];
    s32 unk0xC80;
    char pad84[4];
    unsigned long long unk0xC88;
    unsigned long long unk0xC90;
    unsigned long long unk0xC98;
    unsigned long long unk0xCA0;
    s32 unk0xCA8;
} T11DC88;
s32 fn_8011BC38();
s32 fn_801209CC(void);
void fn_8011D81C(void);
void PlayTrack(void *, s32);
u64 fn_80273480();
u64 fn_80273B68();
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddInteger(s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(s32, s32);
void fn_8011DC88(void) {
    T11DC88 *base;
    s32 t;
    char *pA;
    char *pB;
    s32 i;
    s32 j;
    s32 cnt;
    register s32 lim __asm__("r23");
    register s32 pg __asm__("r24");
    s32 t2;
    unsigned long long a;
    unsigned long long c;
    unsigned long long mask;
    if (fn_8011BC38() == 0) {
        base = (char *)lbl_8038C8C0 + lbl_80302CA4 * 0xCB0;
        t2 = base->unk0xCA8;
        if ((t2 == 0) && (fn_801209CC() == 1)) {
            lbl_80302CD0 = t2;
            fn_8011D81C();
            if (lbl_80302CB4 != 0) {
                PlayTrack((s32)lbl_8038E220, 1);
                return;
            }
            cnt = base->unk0xC80;
            i = 0;
            lim = cnt;
            __asm__("" : "+r"(lim));
            if (i < cnt) {
                __asm__ ("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_80302CA0));
                pA = (char *)base;
                pB = (char *)base;
                do {
                    t2 = (((u32)fn_80273B68(base->unk0xC88, i) ^ 1) & 1);
                    if ((t2 != 0) && (i <= 63)) {
                        a = base->unk0xC98;
                        t2 = (((u32)fn_80273B68(a, i) ^ 1) & 1);
                        if (t2 != 0) {
                            mask = fn_80273480(1ULL, i);
                            a |= mask;
                            base->unk0xC98 = a;
                            PlayTrack(pB, 0);
                            *(s32 *)((char *)pg + 0x2CA0) = i;
                            t = CStruct_ctor(CStruct_new(8));
                            AddInteger(t, QB_CURRENT_TRACK, *(s32 *)((char *)pg + 0x2CA0));
                            Script_RunScript(QB_SPAWN_UPDATE_MUSIC_TRACK_TEXT, t, 0, 0, 0);
                            if (t != 0) {
                                CStruct_delete(t, 3);
                            }
                            return;
                        }
                    }
                    j = i - 64;
                    t2 = (((u32)fn_80273B68(base->unk0xC90, j) ^ 1) & 1);
                    if ((t2 != 0) && (i > 63)) {
                        c = base->unk0xCA0;
                        t2 = (((u32)fn_80273B68(c, j) ^ 1) & 1);
                        if (t2 != 0) {
                            mask = fn_80273480(1ULL, j);
                            c |= mask;
                            base->unk0xCA0 = c;
                            PlayTrack(pA, 0);
                            *(s32 *)((char *)pg + 0x2CA0) = i;
                            t = CStruct_ctor(CStruct_new(8));
                            AddInteger(t, QB_CURRENT_TRACK, *(s32 *)((char *)pg + 0x2CA0));
                            Script_RunScript(QB_SPAWN_UPDATE_MUSIC_TRACK_TEXT, t, 0, 0, 0);
                            if (t != 0) {
                                CStruct_delete(t, 3);
                            }
                            return;
                        }
                    }
                    i++;
                    pA += 0x28;
                    pB += 0x28;
                } while (i < lim);
            }
            base->unk0xC98 = 0;
            base->unk0xCA0 = 0;
        }
    }
}
