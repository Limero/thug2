// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054720-0x8005481C (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_80293074[];
extern char lbl_80293084[];
extern char lbl_80293098[];
extern char lbl_802930AC[];
extern char lbl_802930C8[];
extern char lbl_802930DC[];
extern f32 lbl_802930F0;
extern f32 lbl_802930F4;
extern void *lbl_8030044C;
extern void *lbl_80300448;
void fn_8001075C(s32);
void fn_80058EC4(s32);
void fn_80010760(void);
void fn_8005DBE0(void);
void fn_8005E1B8(f32);
f32 fn_8012570C(s32, s32);
void fn_8005E1D0(f32);
void fn_8005E1E8(f32);
void fn_8005DCF0(void);
void fn_8005E08C(s32);
void *Mem_Alloc2(s32);
void *fn_80068338(void *);
void *fn_8006FC80(void *);
void fn_8006C498(void);
void fn_80075854(void);
void fn_80054720(s32 arg0) {
    void **slot1 = &lbl_8030044C;
    void **slot2 = &lbl_80300448;

    fn_8001075C(lbl_80293074);
    fn_80058EC4(arg0);
    fn_80010760();
    fn_8001075C(lbl_80293084);
    fn_8005DBE0();
    fn_80010760();
    fn_8005E1B8(lbl_802930F0);
    fn_8005E1D0(fn_8012570C(QB_CAMERA_FOV, 0));
    fn_8005E1E8(lbl_802930F4);
    fn_8001075C(lbl_80293098);
    fn_8005DCF0();
    fn_8005E08C(0);
    fn_80010760();
    fn_8001075C(lbl_802930AC);
    *slot1 = fn_80068338(Mem_Alloc2(0x30));
    fn_80010760();
    fn_8001075C(lbl_802930C8);
    *slot2 = fn_8006FC80(Mem_Alloc2(8));
    fn_80010760();
    fn_8001075C(lbl_802930DC);
    fn_8006C498();
    fn_80010760();
    fn_80075854();
}
