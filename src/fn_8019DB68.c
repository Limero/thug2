// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019DB68-0x8019DCE8 (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: memory-card / menu banner maintenance tick called from
// fn_8019D9E4 (card-action handler). Every 8th call (round-robin counter
// lbl_80305EEC & 7) it rewrites the "opening.bnr" card banner via the debug
// file-IO wrappers (fn_8001B5B8/B658/B6DC/B754); ticks the card manager
// (fn_8011BC18/fn_80119E48/fn_80174098), syncs a global flag from the
// manager's +0x388 magic, and broadcasts script message 0xFB11E6CD when a
// dirty flag is set. arg1==0 selects the no-filesystem path.
// Suggested rename: CardBannerMaintenanceTick.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *lbl_802FFE98;
extern void *lbl_80302C34;
extern void *lbl_80305EAC;
extern s32 lbl_80305EEC;
extern bool lbl_80305E94;
extern bool lbl_803016A4;
extern char lbl_802AAE50[];
void fn_8009DE5C(void);
void fn_8011DED0(void);
void fn_8011BC18(void *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_80119E48(Unk_C8FEE62D *);
void fn_8001B5B8(Unk_A07EDCEF *);
void fn_8001B658(void *, char *);
s32 fn_8001B6DC(char *, char *, s32);
void fn_8001B754(void *);
void fn_80131334(void);
void fn_80174098(Unk_40426380 *);
s32 fn_801745B4(void *);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8019DB68(void *arg0, s32 arg1) {
    char sp8[0x78];
    s32 sp80;
    s32 temp_r11;
    s32 var_r0;
    void *mgr;

    fn_8009DE5C();
    fn_8011DED0();
    mgr = lbl_80302C34;
    fn_8011BC18(mgr);
    if (arg1 == 0) {
        fn_8000F2F8(lbl_802FFE98, ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C);
        fn_80119E48(mgr);
        fn_8000F320(lbl_802FFE98);
    } else if (*((s32 *)&((Unk_C5855798 *)lbl_80305EAC)->unk0x384) != -QB_UNKNOWN_0x16D13502) {
        temp_r11 = lbl_80305EEC;
        var_r0 = (temp_r11 + 3) & 7;
        __asm__("" : "+r"(var_r0));
        lbl_80305EEC = temp_r11 + 1;
        if (var_r0 == 7) {
            fn_8001B5B8(sp8);
            fn_8001B658(sp8, lbl_802AAE50);
            fn_8001B6DC(sp8, &sp80, 4);
            fn_8001B754(sp8);
        }
    }
    if (*((s32 *)&((Unk_C5855798 *)lbl_80305EAC)->unk0x388) == -QB_UNKNOWN_0x174B47CA) {
        lbl_803016A4 = 1;
    } else {
        lbl_803016A4 = 0;
    }
    fn_8000F2F8(lbl_802FFE98, ((Unk_9994C3F5 *)lbl_802FFE98)->unk0x11C);
    fn_80131334();
    fn_80174098(lbl_80305EAC);
    if (lbl_80305E94 != 0) {
        lbl_80305E94 = 0;
        Script_RunScript(QB_RUNMENOW, 0, fn_801745B4(lbl_80305EAC), 0, 0);
    }
    fn_8000F320(lbl_802FFE98);
}
