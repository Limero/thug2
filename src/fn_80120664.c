// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120664-0x80120824 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80269EF8(void *, void *, void *, void *);
extern char lbl_8029D778[];
#include "qb_constants.h"
void fn_80136708(s32);
extern char lbl_8029D7AC[];
extern char lbl_8029D7D4[];
extern char lbl_8029D7F8[];
extern char lbl_8039D940[];
extern s32 lbl_80302F04;
extern s32 lbl_80302F20;
extern f32 lbl_80302F24;
extern s32 lbl_80302F28;
void fn_80269EC0(void *, void *, void *, void *);
void fn_801204CC(f32);
void fn_80120664(s32 arg0) {
    s32 temp_r0;
    char *base;
    base = lbl_8039D940;
    temp_r0 = *(s32 *)(base + (s32)0xC0);
    if (temp_r0 != 0) {
        lbl_80302F04 |= 0x100;
        if (temp_r0 == 0x3E7) {
            *(s32 *)(base + (s32)0xC0) = 0;
            if (fn_8013644C() == 0) {
                OSPanic((s32)lbl_8029D778, 0x466, (s32)lbl_8029D7AC);
            }
            if (fn_80136510() == 0) {
                OSPanic((s32)lbl_8029D778, 0x468, (s32)lbl_8029D7D4);
            }
            if (AUDSimpleInitAudioDecoder() == 0) {
                OSPanic((s32)lbl_8029D778, 0x46A, (s32)lbl_8029D7F8);
            }
            fn_801204CC(lbl_80302F24);
            fn_80136708(0);
        }
    } else {
        if ((*(s32 *)(base + (s32)0x190) != 0) && (lbl_80302F20 == 0)) {
            lbl_80302F04 = (s32) (lbl_80302F04 | 0x100);
            if (*(s32 *)(base + (s32)0xC4) != 0) {
                if (*(s32 *)(base + (s32)0xC8) != 0) {
                    fn_801367D8();
                    fn_80136CAC();
                    fn_801364DC();
                    fn_801365B0();
                    AUDSimpleExitAudioDecoder();
                    lbl_80302F04 = (s32) (lbl_80302F04 & QB_UNKNOWN_0xFFFFFEFF);
                }
            } else if ((*(s32 *)(base + (s32)0xB4) != 0) && (lbl_80302F28 == 0) && ((AUDSimpleAudioGetFreeReadBufferSamples() > 0x4E20U) || (*(s32 *)(base + (s32)0xC8) != 0)) && (fn_80136D30() == 0)) {
                *(s32 *)(base + (s32)0xC4) = 1;
            }
        }
        fn_80269EC0(6, 7, 6, 7);
        fn_80269EF8(0xE, 7, 0xE, 7);
    }
}
