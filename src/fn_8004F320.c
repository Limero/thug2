// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F320-0x8004F4E4 (452B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80292C68;
extern f64 lbl_80292C60;
#include "qb_constants.h"
#include "structs.h"

/* arg0: the screen-element "window" object.  Real member types matter here:
 * +0x1B4/+0x1B8/+0x1C4/+0x1C8/+0x1D0 are stfs/lfs in retail. */
typedef struct F4F320_obj {
    char pad000[0x1AC];
    void *unk0x1AC;
    char pad1B0[0x4];
    f32 unk0x1B4;
    f32 unk0x1B8;
    char pad1BC[0x4];
    s32 unk0x1C0;
    f32 unk0x1C4;
    f32 unk0x1C8;
    s32 unk0x1CC;
    f32 unk0x1D0;
} F4F320_obj;

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *arg0, s32 arg1);
void CObject_AddRefLink(CStruct *, void *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CScreenElement_SetProperties(F4F320_obj *, CStruct *);
s32 CScreenElement_resolve_just(F4F320_obj *, CStruct *, s32, void *, void *);
s32 fn_8003FED0(void *);
void fn_8004FF24(F4F320_obj *, s32 *, s32 *, f32 *, s32 *, f32 *);

void fn_8004F320(F4F320_obj *arg0, CStruct *arg1) {
    s32 sp18;
    s32 sp1C;
    s32 sp8[3];
    s32 sp20;
    s32 sp24;
    f32 sp28;
    s32 sp2C;
    f32 sp30;
    s32 temp_r3;
    s32 temp_r3_2;
    register s32 bp __asm__("r30");

    __asm__("li %0,0" : "=b"(sp18));
    bp = (s32) &sp18;
    /* the "r11" clobber is load-bearing but emits nothing: without it the
     * second birth allocates r11 and the prologue is `li r11,0` where want
     * has `li r10,0`. r11 holds nothing live here (verified: the object is
     * byte-identical, so no spill/reload was needed), and the asm writes
     * only its output. Measured: "=r" gives r0, plain "=b" gives r11. */
    __asm__("li %0,0" : "=b"(sp1C) : : "r11");
    if (CScreenElement_resolve_just(arg0, arg1, QB_INTERNAL_JUST, (void *) bp, &sp1C) != 0) {
        arg0->unk0x1B8 = *(f32 *) ((char *) bp + 4);
        arg0->unk0x1B4 = *(f32 *) bp;
    }
    if (GetInteger(arg1, QB_SCROLL_SPEED, &sp20, 0) != 0) {
        arg0->unk0x1C8 = sp20;
    }
    GetInteger(arg1, QB_NUM_ITEMS_TO_SHOW, &arg0->unk0x1CC, 0);
    temp_r3 = ContainsFlag(arg1, QB_RESET_WINDOW_TOP);
    if (temp_r3 != 0) {
        arg0->unk0x1C0 = 1;
        arg0->unk0x1C4 = lbl_80292C68;
    } else if (ContainsFlag(arg1, QB_RESET_WINDOW_BOTTOM) != 0) {
        temp_r3_2 = fn_8003FED0(arg0->unk0x1AC);
        bp = (s32) sp8;
        ((s32 *) bp)[1] = temp_r3;
        ((s32 *) bp)[2] = temp_r3;
        sp8[0] = temp_r3_2;
        if (temp_r3_2 != 0) {
            CObject_AddRefLink(temp_r3_2, (void *) bp);
        }
        fn_8004FF24(arg0, (s32 *) bp, &sp24, &sp28, &sp2C, &sp30);
        arg0->unk0x1C0 = 1;
        arg0->unk0x1C4 = (sp28 + sp30) - arg0->unk0x1D0;
        if (sp8[0] != 0) {
            CObject_RemoveRefLink(sp8[0], (CStruct *) bp);
            sp8[0] = temp_r3;
        }
    } else if (ContainsFlag(arg1, QB_RESET_WINDOW) != 0) {
        arg0->unk0x1C0 = 1;
    }
    CScreenElement_SetProperties(arg0, arg1);
}
