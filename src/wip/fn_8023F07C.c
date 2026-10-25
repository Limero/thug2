// WIP DRAFT (non-matching) — m2c body + proto/arity repair pass
// family=m2c range=0x8023F07C-0x8023F5E0 size=1380B
// PARKED ~3%: full hand-rebuild required; decode notes for a future attempt:
// - 3-arg void fn(arg0=r26 obj-mgr, arg1=r27 skater-entry, arg2=r17 new-id).
//   Frame 0xA0, saves f30/f31 + stmw r16..r31 (21 GPRs!) — FPR frame quirk
//   territory: needs N volatile-double dummies (recipe 63) once body matches.
// - Prologue gate: *(u8*)(arg1+0x151) != 0 -> [fn_8023C598(1); r19 =
//   fn_8023DDA8(); fn_8023C598(1); fn_8023D848()] (r19 = "insert index").
// - temp_r24 = *(s32*)0x80301A78 (lbl). If *(arg0+4): idx=*(arg0+0xC);
//   r31 = arg1tbl[idx*8] via addi+slwi+lwzx (r25=arg1+8 base); if
//   fn_800A5308(mgr,r31): fn_800A54AC(mgr,0x4ADF0CD3,r31,0x36B2EE74,0,0,
//   f1=lfs lbl_802B0ED8) -- SIX int args + f32 in f1 (7b zone truth).
// - Main loop over *(s32*)(arg1+0x148) entries of tbl@arg1+8 (idx*4! slwi
//   r29,3 then lwzx r30,r25,r0 -> stride 8 via s32*?): two arms keyed on
//   var_r18(=gate): arm A script-writes via 80126EAC/801277E4/80127684 with
//   (var_r29 < r19) ? 80127684(...,var_r29+1) : 801277E4(...,0,hash), tail
//   801277E4(42D6DD1E, QB_TOPDOWN) + 31008(277B7B33)+2701C(2);
//   arm B: r31=fn_80236EF4(*arg0,entry,0) homed r31, same 26EAC/277E4 pair,
//   then *(u16*)(r31+8)&0x80 ? [277E4(B45C2617,entry);31008;->2701C]
//   : [80128F94(&sp10); 80241C94(r31,&sp10); 80127AAC(sp8,4A6BF967,&sp10);
//      31008(277B7B33); 80126A30(&sp10); 80128FB4(&sp10,2)] then 2701C.
// - After loop: 31008(ED885B50); 26EAC; 27684(CD2AD53A,arg3); 27684(245EBFD0,
//   *(arg0+8)); 31008(C7A76116); *(arg0+8)=arg3; *(arg0+4)=arg1; 2701C(2).
// - Focus block: A5308/A54AC on entry[arg1+0x14C]; *(arg0+0xC)=that idx.
// - Window math (r10=idx@14C): r29=max(idx-3,0-ish clamps vs cnt@148),
//   r31=min(idx+3,cnt-1) — see E408-E45C region; feeds xoris-0x80000000 +
//   0x43300000 int->f64 dances (f30=(double)r29 etc.) divided by
//   (double)*(arg1+0x148), scaled by lfs lbl_802B0EE8 (f12), f13 = magic
//   lfd lbl_802B0EE0. DOC-14 TERRITORY: use manual union dance referencing
//   REAL rodata2 doubles lbl_802B0EE0/EE8 (§6j-1 + §6ag-5 volatile f64
//   member) — plain casts synthesize private pool, never promotable.
// - fn_8003F710(handle=&sp8val, &sp30, &sp34); CScreenElement_SetPos(h,1,f30,sp34);
//   CScreenElement_SetScale(h,0,1,fmul(f31-f30,lbl_802B0EEC),lbl_802B0EF0);
//   GetElement_2(&sp20,lbl_80300434val,0x84A689EB,1);
//   fn_800427AC(sp20v, field@arg1[0xC+idx*8] ? NULL-path... (see 56C-588:
//   one site passes only r3 — leftover-r4 shape, needs dead-arg trick);
//   CObject_RemoveRefLink cleanup pairs zero the sp20/sp8 handles.
// Resists this round: time budget. Start from protos already injected +
// A54AC 6-int+f32 arity fix + 8004B03C 4-arg fix (done in body below).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 4.0% ([7]rev->4.0% [6]rev->4.0%).
#include "types.h"
extern f32 lbl_802B0ED8;
extern f32 lbl_802B0EE8;
extern f32 lbl_802B0EEC;
extern f32 lbl_802B0EF0;
extern char lbl_80300434[];
extern char lbl_80301A78[];
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os -fno-expensive-optimizations
extern char lbl_802B0ED4[];
void Script_RunScript(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
void CStruct_ctor(s32 arg0);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
void CStruct_delete(CStruct * arg0, s32 arg1);
s32 fn_800A5308(CStruct * arg0, void *arg1);
void fn_800A54AC(Unk_AD65BA9A * arg0, void * arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, f32 farg1);
void GetElement_2(void *arg0, void *arg1, s32 arg2, s32 arg3);
s32 fn_8003F710(void *arg0, void *arg1, void *arg2);
void CScreenElement_SetPos(Unk_C7387A53 * arg0, s32 arg1, f32 farg1, f32 farg2);
void CScreenElement_SetScale(Unk_C7387A53 * arg0, s32 arg1, s32 arg2, f32 farg1, f32 farg2);
void fn_800427AC(Unk_E80761A5 * arg0, u8 * arg1);
void fn_80128F94(Unk_9D4ED6AF * arg0);
void fn_80241C94(Unk_C7387A53 * arg0, void *arg1);
void fn_80127AAC(CStruct * arg0, s32 arg1, Unk_5AA7B5D7 * arg2);
void fn_80126A30(Unk_5AA7B5D7 * arg0);
void fn_80128FB4(Unk_F8A5095F * arg0, s32 arg1);
void *fn_80236EF4(CStruct * arg0, s32 arg1, s32 *arg2);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8023F07C(CStruct *arg0, Unk_4DBDA49F *arg1, s32 arg3) {
    f32 sp34;
    s32 sp30;
    s32 sp20;
    s32 sp10;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f30;
    s32 temp_r0;
    s32 temp_r10;
    s32 temp_r11_2;
    s32 temp_r24;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    s32 var_r18;
    s32 var_r19;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r30;
    s32 var_r31;
    void *temp_r11;
    void *temp_r25;
    Unk_9994C3F5 *temp_r31_2;
    var_r18 = 0;
    var_r19 = 0;
    if ((s32) *(s32 *)((char *)arg1 + (s32)0x151) != 0) {
        var_r18 = 1;
        fn_8023C598(1);
        var_r19 = fn_8023DDA8();
        fn_8023C598(1);
        fn_8023D848();
    }
    temp_r11 = arg0->unk0x4;
    temp_r24 = *(s32 *)&lbl_80301A78;
    if (temp_r11 != NULL) {
        temp_r31 = *((s32 *)((char *)temp_r11 + 8 + (arg0->unk0xC * 8)));
        if (fn_800A5308(temp_r24, temp_r31) != 0) {
            fn_800A54AC(temp_r24, QB_UNFOCUS, temp_r31, QB_SYSTEM, 0, 0, lbl_802B0ED8);
        }
    }
    temp_r25 = (char *)arg1 + 8;
    if (arg1 !=  arg0->unk0x4) {
        Script_RunScript(QB_PARKED_MAKE_PIECE_MENU, NULL, 0, 0, 0);
        var_r29 = 0;
        if ((s32) arg1->unk0x148 > 0) {
            do {
                temp_r30 = *((s32 *)((char *)temp_r25 + (var_r29 * 8)));
                if (var_r18 != 0) {
                    CStruct_ctor(&sp8);
                    AddChecksum(&sp8, QB_METAPIECE_ID, temp_r30);
                    if (var_r29 < var_r19) {
                        temp_r0 = var_r29 + 1;
                        var_r30 = temp_r0;
                        AddInteger(&sp8, QB_CLIPBOARDINDEX, temp_r0);
                    } else {
                        AddChecksum(&sp8, 0, QB_EMPTYCLIPBOARD);
                        var_r30 = var_r29 + 1;
                    }
                    AddChecksum(&sp8, QB_HEAP, QB_TOPDOWN);
                    Script_RunScript(QB_PARKED_MAKE_PIECE_MENU_ITEM, &sp8, 0, 0, 0);
                    CStruct_delete(&sp8, 2);
                } else {
                    temp_r31_2 = fn_80236EF4(arg0->unk0x0, temp_r30, 0);
                    CStruct_ctor(&sp8);
                    AddChecksum(&sp8, QB_HEAP, QB_TOPDOWN);
                    AddChecksum(&sp8, QB_METAPIECE_ID, temp_r30);
                    if (temp_r31_2->unk0x8 & 0x80) {
                        AddChecksum(&sp8, QB_SECTOR, temp_r30);
                        Script_RunScript(QB_PARKED_MAKE_PIECE_MENU_ITEM, &sp8, 0, 0, 0);
                    } else {
                        fn_80128F94(&sp10);
                        fn_80241C94(temp_r31_2, &sp10);
                        fn_80127AAC(&sp8, QB_SECTORS, &sp10);
                        Script_RunScript(QB_PARKED_MAKE_PIECE_MENU_ITEM, &sp8, 0, 0, 0);
                        fn_80126A30(&sp10);
                        fn_80128FB4(&sp10, 2);
                    }
                    CStruct_delete(&sp8, 2);
                    var_r30 = var_r29 + 1;
                }
                var_r29 = var_r30;
            } while (var_r29 < (s32) arg1->unk0x148);
        }
        Script_RunScript(QB_PARKED_MAKE_SET_MENU, NULL, 0, 0, 0);
        CStruct_ctor(&sp8);
        AddInteger(&sp8, QB_SET_NUMBER, arg3);
        AddInteger(&sp8, QB_LAST_SET_NUMBER, arg0->unk0x8);
        Script_RunScript(QB_PARKED_LOCK_PIECE_AND_SET_MENUS, &sp8, 0, 0, 0);
        arg0->unk0x8 = arg3;
        arg0->unk0x4 = arg1;
        CStruct_delete(&sp8, 2);
    }
    if (fn_800A5308(temp_r24, *((s32 *)((char *)temp_r25 + (arg1->unk0x14C * 8)))) != 0) {
        fn_800A54AC(temp_r24, QB_FOCUS, *((s32 *)((char *)temp_r25 + (arg1->unk0x14C * 8))), QB_SYSTEM, 0, 0, lbl_802B0ED8);
    }
    temp_r10 = arg1->unk0x14C;
    arg0->unk0xC = temp_r10;
    var_r29_2 = temp_r10 - 3;
    var_r31 = temp_r10 + 3;
    temp_r11_2 = arg1->unk0x148;
    if (temp_r11_2 <= 7) {
        var_r31 = temp_r11_2 - 1;
        var_r29_2 = 0;
    } else if (var_r29_2 < 0) {
        var_r29_2 = 0;
        var_r31 -= var_r29_2;
    } else if (var_r31 >= temp_r11_2) {
        var_r31 = temp_r11_2 - 1;
        var_r29_2 = temp_r10 - 4 + (temp_r11_2 - var_r31);
    }
    temp_r30_2 = *(s32 *)&lbl_80300434;
    GetElement_2(&sp8, temp_r30_2, QB_PIECE_SLIDER_ORANGE, 1);
    fn_8003F710(sp8, &sp30, &sp34);
    temp_f12 = lbl_802B0EE8;
    temp_f0 = (f32) (f64) arg1->unk0x148;
    temp_f30 = ((f32) (f64) var_r29_2 * temp_f12) / temp_f0;
    CScreenElement_SetPos(sp8, 1, temp_f30, sp34);
    CScreenElement_SetScale(sp8, 0, 1, ((((f32) (f64) (var_r31 + 1) * temp_f12) / temp_f0) - temp_f30) * lbl_802B0EEC, lbl_802B0EF0);
    GetElement_2(&sp20, temp_r30_2, QB_PIECE_MENU_NAME_TEXT, 1);
    if ((s32) *((s32 *)((char *)arg1 + 0xC + (arg0->unk0xC * 8))) != 0) {
        fn_800427AC(sp20, NULL);
    } else {
        fn_800427AC(sp20, (s32)lbl_802B0ED4);
    }
    if (sp20 != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)&sp20), &sp20);
        sp20 = 0;
    }
    if (sp8 != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)&sp8), &sp8);
        sp8 = 0;
    }
}
