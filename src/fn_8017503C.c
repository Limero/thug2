// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017503C-0x801751B8 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { s32 unk0; s32 unk4; s32 unk8; s32 unkC; } Sp_8017503C;
extern void* lbl_802FFE98;
extern void* lbl_80305EC0;
extern s32 lbl_80305EE4;
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];
extern void fn_8019D438(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern s32 NextItem(s32 arg0);
extern s32 fn_80198D38(s32 arg0);
extern void fn_800101A0(void *arg0, s32 arg1);
extern void fn_80199490(CStruct * arg0, s32 arg1);
extern void fn_801994A0(CStruct * arg0);
extern void fn_80174ED8(Unk_C7387A53 * arg0);
extern s32 NextNewPlayerInfo(s32 arg0);
extern void fn_8022A510(void * arg0, s32 arg1);
extern s32 fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern void fn_80229C38(CScript * arg0);
extern s32 fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 fn_80198F7C(s32 arg0);
extern s32 fn_80198B68(s32 arg0);
extern void fn_802199E4(s32 arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
void fn_8017503C(Unk_40426380 *arg0) {
    Sp_8017503C sp;
    Sp_8017503C *p;
    register Sp_8017503C *ptmp __asm__("r11");
    s32 mgr;
    Unk_9994C3F5 *t1;
    s32 t2;
    s32 t3;
    s32 v;
    s32 k8;

    mgr = lbl_80305F9C;
    fn_8019D438((void *)lbl_80305EE4, 0);
    t1 = lbl_802FFE98;
    fn_8000F2F8(t1, t1->unk0x11C);
    if (NextItem(mgr) == 0) {
        if (fn_80198D38(lbl_80305EC0) > 1U) {
            t2 = lbl_802FFE98;
            fn_800101A0(t2, fn_80198D38(lbl_80305EC0));
        }
        fn_80199490(arg0->unk0x398, QB_INITIALIZEGAMEFLOW);
        fn_801994A0(arg0->unk0x398);
    } else {
        fn_80174ED8(arg0);
        fn_80199490(arg0->unk0x398, QB_STANDARDGAMEFLOW);
    }
    k8 = (s32)lbl_802A83F8;
    ptmp = &sp;
    ptmp->unk8 = k8;
    ptmp->unk4 = 0;
    p = ptmp;
    t3 = NextNewPlayerInfo(mgr);
    if (t3 != 0) {
        fn_8022A510(t3, 0);
    }
    v = fn_8021D454(mgr, p, 1);
    while (v != 0) {
        fn_80229C38(v);
        v = fn_8021D4E8(mgr, &sp, 1);
    }
    if (fn_80198F7C(lbl_80305EC0) == QB_NETLOBBY) {
        fn_802199E4(mgr, fn_80198B68(lbl_80305EC0));
    }
    fn_8000F320(lbl_802FFE98);
    p->unk8 = (s32)lbl_802A83F8;
}
