// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-24
// PARKED 32.7%: ring-buffer switch dispatcher (12 case bodies, all byte-modeled).
// Frame/prologue/case structure match (stmw r24 + f28-f31 saves exact); remaining
// diffs are global register-home assignments (limit/start/magic homes rotate vs
// want), the walker-latch copy+test fusion (want or. r3,rX,rX; got mr+cmpwi —
// entry site fuses, latch resists every shape/flag), and rodata page-anchor
// sharing order. §6y big-function allocator-order wall class.
// family=m2c range=0x801C9F40-0x801CA5C8 size=1672B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 52.2% ([4]asc->51.4% [8]rev->52.2%).
// FLAG: -fno-expensive-optimizations
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 55.0%.
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ACE4C;
extern f32 lbl_802ACE50;
extern f32 lbl_802ACE54;
extern f64 lbl_802ACE58;
extern s32 lbl_80303150;
extern s32 lbl_80305F9C;
void *fn_8021B55C(s32 arg0, s32 arg1);
u32 fn_801CD1C8(Unk_897A0ACF * arg0);
void fn_8002FC8C(Unk_A9157FE7 * arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void fn_801F0DC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_8002FFA8(Unk_C7387A53 * arg0, f32 arg1, s32 arg2);
void fn_80030290(Unk_C7387A53 * arg0, Unk_6A78CE27 * arg1, s32 arg2);
void fn_80030580(Unk_C7387A53 * arg0, s32 arg1, s32 arg2);
void fn_800B33EC(CScript * arg0, Unk_C8FEE62D * arg1, s32 arg2, s32 arg3);
void fn_80030750(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
void fn_80031EC8(CStruct * arg0, s32 arg1, void * arg2, s32 arg4);
void fn_800B62EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7);
void fn_800B62A4(Unk_C7387A53 * arg0);
s32 Tmr_GetTime();
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void CStruct_delete(CStruct * arg0, s32 arg2);
s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
s32 fn_80203BB8(Unk_C7387A53 * arg0, s32 arg1, CStruct * arg2);
void fn_80203D4C(s32 arg0, s32 arg1);
s32 GetStructure(s32 arg0, s32 arg1);
void fn_801C9F40(Unk_B46CA436 *arg0) {
    struct {
        f32 fl[5];
        u8 pad[0x24];
        union {
            u32 w[2];
            f64 d;
        } cvt;
    } fr;
    f32 c4C;
    f32 c50;
    f32 c54;
    f64 c58;
    s32 mgrval;
    s32 *list;
    s32 limit;
    s32 start;
    s32 i;
    s32 off;
    u8 *base;
    Unk_1D62F22E *entry;
    CStruct *head;
    CStruct *nxt;
    Unk_C7387A53 *cur;
    s32 rsum;
    s32 handle;
    CScript *found;
    u32 hi43;
    mgrval = *(s32 *)&lbl_80305F9C;
    list = fn_8021B55C(mgrval, 0);
    if (list == NULL) {
        return;
    }
    if (*(s32 *)((char *)(arg0->unk0x2AC) + 0x1C) <= 0x13) {
        return;
    }
    c4C = lbl_802ACE4C;
    hi43 = QB_INT_TO_DOUBLE_BIAS;
    __asm__("" : "+r"(hi43));
    start = *(s32 *)((char *)(arg0->unk0x2AC) + 0xAC0) % 20;
    limit = arg0->unk0x20 + (*list - arg0->unk0x1C);
    c50 = lbl_802ACE50;
    c54 = lbl_802ACE54;
    c58 = lbl_802ACE58;
    i = start;
    do {
        off = i * 0x5C;
        base = (u8 *)(*((s32 *)&arg0->unk0x2AC) + 0xAC4);
        entry = base + off;
        if ((((u32)fn_801CD1C8(entry) > arg0->unk0x24) && ((u32)fn_801CD1C8(entry) <= (u32)limit))) {
            switch (base[off]) {
            case 0x29:
                head = *(s32 *)(arg0->unk0x2B0 + 0x38);
                if (head->unk0x4 == -1) {
                    head = NULL;
                }
                if ((cur = head) == NULL) {
                    goto w29;
                }
                do {
                    if (cur->unk0x30 == 0) {
                        break;
                    }
                    nxt = cur->unk0xC;
                    if (nxt->unk0x4 == -1) {
                        nxt = NULL;
                    }
                } while ((cur = nxt) != NULL);
                goto wdone0;
            w29:
                cur = NULL;
            wdone0:
                if (cur == NULL) {
                    goto latch;
                }
                fn_8002FC8C((s32)cur, entry->unk0x28, 0, (s8)*((s8 *)&entry->unk0x2), 0, *((f32 *)&entry->unk0x18), *((f32 *)&entry->unk0x1C), *((f32 *)&entry->unk0x20), entry->unk0x24);
                break;
            case 0x2B:
                head = *(s32 *)(arg0->unk0x2B0 + 0x38);
                if (head->unk0x4 == -1) {
                    head = NULL;
                }
                if ((cur = head) == NULL) {
                    goto w2b;
                }
                do {
                    if (cur->unk0x30 == 0) {
                        break;
                    }
                    nxt = cur->unk0xC;
                    if (nxt->unk0x4 == -1) {
                        nxt = NULL;
                    }
                } while ((cur = nxt) != NULL);
                goto wdone1;
            w2b:
                cur = NULL;
            wdone1:
                if (cur == NULL) {
                    goto latch;
                }
                fn_8002FFA8((s32)cur, *((f32 *)&entry->unk0x14), 0);
                break;
            case 0x2A:
                fn_801F0DC8(arg0->unk0x2C0, (s8)*((s8 *)&entry->unk0x1), entry->unk0xC, 0, 0);
                break;
            case 0x3C:
                fr.fl[0] = entry->unk0x30;
                fr.fl[1] = *((f32 *)&entry->unk0x34);
                fr.fl[2] = entry->unk0x38;
                fr.fl[3] = entry->unk0x3C;
                fr.fl[4] = entry->unk0x40;
                nxt = *((s32 * *)&nxt->unk0x38);
                nxt = *(s32 *)(arg0->unk0x2B0 + 0x38);
                goto ltest;
                do {
                    if (cur->unk0x30 == 0) {
                        goto lfound;
                    }
                    nxt = *((s32 * *)&cur->unk0xC);
                ltest:
                    if (nxt->unk0x4 == -1) {
                        nxt = NULL;
                    }
                    cur = nxt;
                } while (cur != NULL);
                cur = NULL;
            lfound:
                if (cur == NULL) {
                    goto latch;
                }
                fn_80030290((s32)cur, &fr.fl[0], 0);
                break;
            case 0x3D:
                head = *(s32 *)(arg0->unk0x2B0 + 0x38);
                if (head->unk0x4 == -1) {
                    head = NULL;
                }
                if ((cur = head) == NULL) {
                    goto w3d;
                }
                do {
                    if (cur->unk0x30 == 0) {
                        break;
                    }
                    nxt = cur->unk0xC;
                    if (nxt->unk0x4 == -1) {
                        nxt = NULL;
                    }
                } while ((cur = nxt) != NULL);
                goto wdone2;
            w3d:
                cur = NULL;
            wdone2:
                if (cur == NULL) {
                    goto latch;
                }
                fn_80030580((s32)cur, (s8)*((s8 *)&entry->unk0x2), 0);
                break;
            case 0x3E:
                fn_800B33EC(arg0->unk0x2B4, entry->unk0x28, entry->unk0x10, 0);
                break;
            case 0x41:
                head = *(s32 *)(arg0->unk0x2B0 + 0x38);
                if (head->unk0x4 == -1) {
                    head = NULL;
                }
                if ((cur = head) == NULL) {
                    goto w41;
                }
                do {
                    if (cur->unk0x30 == 0) {
                        break;
                    }
                    nxt = cur->unk0xC;
                    if (nxt->unk0x4 == -1) {
                        nxt = NULL;
                    }
                } while ((cur = nxt) != NULL);
                goto wdone3;
            w41:
                cur = NULL;
            wdone3:
                if (cur == NULL) {
                    goto latch;
                }
                fn_80030750((s32)cur, 0, 0, 0, entry->unk0x24);
                break;
            case 0x2C:
                head = *(s32 *)(arg0->unk0x2B0 + 0x38);
                if (head->unk0x4 == -1) {
                    head = NULL;
                }
                if ((cur = head) == NULL) {
                    goto w2c;
                }
                do {
                    if (cur->unk0x30 == 0) {
                        break;
                    }
                    nxt = cur->unk0xC;
                    if (nxt->unk0x4 == -1) {
                        nxt = NULL;
                    }
                } while ((cur = nxt) != NULL);
                goto wdone4;
            w2c:
                cur = NULL;
            wdone4:
                if (cur == NULL) {
                    goto latch;
                }
                fn_80031EC8((s32)cur, (s8)*((s8 *)&entry->unk0x1), entry->unk0x8, 0);
                break;
            case 0x76:
                *(f32 *)(arg0->unk0x2B4 + 0x30) = c4C;
                nxt = (s32 *)((char *)arg0->unk0x2B4 + 0x30);
                *((f32 *)&nxt->unk0xC) = c54;
                *((f32 *)&nxt->unk0x4) = c50;
                *((f32 *)&nxt->unk0x8) = c4C;
                rsum = lbl_80303150 + Tmr_GetTime();
                if (*((s8 *)&entry->unk0x3) & 1) {
                    fr.cvt.w[1] = entry->unk0x44 ^ 0x80000000;
                    fr.cvt.w[0] = hi43;
                    fn_800B62EC(arg0->unk0x2B4 + 0x40, rsum, entry->unk0x48, entry->unk0x58, 0, (f32)(fr.cvt.d - c58), entry->unk0x50, entry->unk0x54);
                }
                if (*((s8 *)&entry->unk0x3) & 2) {
                    fr.cvt.w[1] = entry->unk0x44 ^ 0x80000000;
                    fr.cvt.w[0] = hi43;
                    fn_800B62EC(arg0->unk0x2B4 + 0xD4, rsum, entry->unk0x48, entry->unk0x58, 0, (f32)(fr.cvt.d - c58), entry->unk0x50, entry->unk0x54);
                }
                if (*((s8 *)&entry->unk0x3) & 4) {
                    fr.cvt.w[1] = entry->unk0x44 ^ 0x80000000;
                    fr.cvt.w[0] = hi43;
                    fn_800B62EC(arg0->unk0x2B4 + 0x168, rsum, entry->unk0x48, entry->unk0x58, 0, (f32)(fr.cvt.d - c58), entry->unk0x50, entry->unk0x54);
                }
                break;
            case 0x8C:
                fn_800B62A4(arg0->unk0x2B4 + 0x40);
                fn_800B62A4(arg0->unk0x2B4 + 0xD4);
                fn_800B62A4(arg0->unk0x2B4 + 0x168);
                break;
            case 0x77:
                handle = CStruct_ctor(CStruct_new(8));
                found = GetChecksum_3(arg0->unk0xC, QB_SPECIALITEM);
                AddChecksum(handle, QB_BONE, entry->unk0x2C);
                AddChecksum(handle, QB_ID, *(s32 *)(arg0->unk0xC + 0x18));
                found = GetChecksum_3(found, QB_LOCKOBJ);
                {
                    s32 vt = found->unk0x18;
                    ((s32 (*)(s32, s32)) ((Unk_4E705049 *)vt)->unk0x1C)((s32)((char *)found + ((Unk_4E705049 *)vt)->unk0x18), handle);
                }
                if (handle != 0) {
                    CStruct_delete(handle, 3);
                }
                break;
            case 0x78:
                fn_80203D4C(GetChecksum_3(arg0->unk0xC, QB_SPECIALITEM), entry->unk0x4C);
                break;
            }
        }
    latch:
        i = (i + 1) % 20;
    } while (i != start);
    *((s32 *)&arg0->unk0x24) = limit;
}
