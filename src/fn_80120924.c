// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120924-0x801209CC (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern u32 lbl_800000F8;
u32 OSGetTick(void);
void AUDSimpleAudioReset(void);
void fn_801367D8(void);
void fn_80136CAC(void);
void fn_801364DC(void);
void fn_801365B0(void);
void AUDSimpleExitAudioDecoder(void);
typedef struct S20924 {
    char pad0x0[0xB0];
    s32 unk0xB0;
    s32 unk0xB4;
    char pad0xB8[8];
    s32 unk0xC0;
    char pad0xC4[0xCC];
    s32 unk0x190;
} S20924;
extern S20924 lbl_8039D940;
void fn_80120924(s32 arg0) {
    s32 start;

    if (lbl_8039D940.unk0xC0 != 0) {
        lbl_8039D940.unk0xB0 = 1;
        return;
    }
    if (lbl_8039D940.unk0x190 == 0) {
        return;
    }
    if (lbl_8039D940.unk0xB4 == 0) {
        start = OSGetTick();
        while (lbl_8039D940.unk0xB4 == 0) {
            if ((s32)(OSGetTick() - start) > (s32)(lbl_800000F8 >> 4)) {
                break;
            }
        }
    }
    AUDSimpleAudioReset();
    fn_801367D8();
    fn_80136CAC();
    fn_801364DC();
    fn_801365B0();
    AUDSimpleExitAudioDecoder();
}
