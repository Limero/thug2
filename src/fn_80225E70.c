// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80225E70-0x80226068 (504B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 NextNewPlayerInfo(s32 arg0);
void fn_8022A510(void * arg0, s32 arg1);
s32 fn_8022986C(CScript * arg0);
s32 fn_8009CF2C(CStruct * arg0);
s32 fn_8021D358(s32 arg0, s32 arg1);
void fn_8021FAB4(Unk_9994C3F5 * arg0, s32 arg1, s32 arg2, char * arg3, char * arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
s32 fn_802203E4(Unk_C7387A53 * arg0);
s32 fn_800F0FB8(s32 arg0);
s32 fn_800F0FE4(void);
void fn_800F100C(void);
void fn_800F078C(CStruct * arg0, Unk_9994C3F5 * arg1);
void GetChecksum_2(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
void fn_801AAC90(Unk_EE1FD121 * arg0);

bool fn_80225E70(void *a0) {
    volatile u8 cnt;
    f32 pr[4];
    s32 hsh;
    CScript *tp;
    s32 zz;
    s32 dtmp;
    register s32 ctmp __asm__("r9");
    s32 found;
    s32 idx;
    register void *ap __asm__("r30");
    register s32 mp __asm__("r29");

    ap = a0;
    mp = ((CScript *)ap)->unk0x18;
    tp = NextNewPlayerInfo(mp);
    cnt = *(u8 *)*(s32 *)ap;
    if (tp != 0) {
        fn_8022A510(tp, 0);
        if (fn_8022986C(tp) != 0) {
            fn_8021FAB4(mp, 0, (s32)QB_NET_MESSAGE_DROPPED_CROWN_YOU, 0, 0,
                        tp->unk0x18, 0, 0, 0x7D0);
            goto post;
        }
    }
    if (fn_8009CF2C(mp) != 0) {
        fn_8021FAB4(mp, 0, (s32)QB_NET_MESSAGE_DROPPED_CROWN_OTHER, 0, 0, 0, 0, 0, 0x7D0);
    } else if (tp != 0) {
        s32 t2;
        s32 ret;
        t2 = tp->unk0x18;
        if (t2 != 0) {
            ret = fn_8021D358(mp, (((CScript *)t2)->unk0x18 == 0));
            if (ret != 0) {
                fn_8021FAB4(mp, 0, (s32)QB_NET_MESSAGE_DROPPED_CROWN_OTHER, 0, 0,
                            ((CScript *)ret)->unk0x18, 0, 0, 0x7D0);
            }
        }
    }
post:
    mp = fn_802203E4(mp);
    if (mp == 0) {
        return true;
    }
    found = 0;
    idx = 1;
    do {
        fn_800F0FB8(0);
        ap = (void *)fn_800F0FE4();
        if (ap != NULL) {
            tp = QB_CROWN;
            zz = 0;
            do {
                GetChecksum_2((s32)ap, (s32)QB_TYPE, (hsh = zz, &hsh), 0);
                if (hsh == tp) {
                    ctmp = cnt;
                    if (ctmp == 0) {
                        fn_800F078C((s32)ap, pr);
                        found = 1;
                        ((Unk_DF2324A8 *)mp)->unk0x58 = *(__ps_t *)&pr[0];
                        ((Unk_DF2324A8 *)mp)->unk0x60 = *(__ps_t *)&pr[2];
                        goto exit;
                    } else {
                        __asm__("addi %0,%1,-1" : "=&r"(dtmp) : "r"(ctmp));
                        cnt = dtmp;
                    }
                }
                ap = (void *)fn_800F0FE4();
            } while (ap != NULL);
        }
exit:;
        fn_800F100C();
    } while (found == 0 && 0x31 != idx++);
    fn_801AAC90(mp);
    return true;
}
