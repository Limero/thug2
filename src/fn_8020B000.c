// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020B000-0x8020B0A8 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8020AA20(Unk_C7387A53 *);
extern void fn_801F0520(Unk_C9CA854A *, s32 *, CStruct *);
extern void fn_80209FF0(Unk_CF8B1206 *);
extern void fn_802099A0(Unk_90685748 *);
extern void fn_80209D4C(Unk_76553646 *);
extern void fn_80209DE4(Unk_8D6DF6EE *);
extern void fn_8020A724(Unk_90685748 *);
extern void fn_8020A7A8(Unk_D386C1E6 *);
extern void fn_8020ACB0(Unk_CEAF6E85 *);
void fn_8020B000(Unk_C8FEE62D *arg0) {
    Unk_DB0E2BAB *temp_r9;

    if (*(s32 *)(arg0->unk0xC + 0xC8) == 0) {
        temp_r9 = *((void * *)&arg0->unk0x18);
        ((void (*)(void *, s32)) temp_r9->unk0x44)(
            (char *)arg0 + temp_r9->unk0x40, 1);
        return;
    }
    fn_8020AA20(arg0);
    fn_801F0520(arg0->unk0x28, (char *)arg0 + 0xA5C, (char *)arg0 + 0xA60);
    fn_80209FF0(arg0);
    fn_802099A0(arg0);
    fn_80209D4C(arg0);
    fn_80209DE4(arg0);
    fn_8020A724(arg0);
    fn_8020A7A8(arg0);
    fn_8020ACB0(arg0);
}
