// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016A714-0x8016A82C (280B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_802A89CC[];
extern char lbl_802A89E4[];
extern char lbl_802A89F4[];
extern char lbl_802A8A0C[];
extern char lbl_802A8A18[];
extern char lbl_802A8A2C[];
extern char lbl_802A8A44[];
extern char lbl_80303464[];
extern char lbl_803059F4[];
void fn_8001075C(s32);
void fn_80010760(void);
void Script_AllocatePools(void);
void fn_8005469C(void);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8016A85C(s32, s32);
void fn_8016A8D0(s32, s32);
void fn_8016A944(s32, s32);
void fn_8016A9B8(s32, s32);
void fn_8016AA2C(s32, s32);
s32 fn_80146EB8(void);
s32 fn_80146EC0(void);
void fn_80125C70(void *, u32);
void fn_80125CE4(s32, u32);

void fn_8016A714(void) {
    Unk_C7387A53 *g;

    fn_8001075C(lbl_802A89CC);
    Script_AllocatePools();
    fn_8005469C();
    fn_80010760();
    g = *(void **)&lbl_802FFE98;
    fn_8000F2F8(g, g->unk0x164);
    fn_8001075C(lbl_802A89E4);
    fn_8016A85C(0x96, (s32)lbl_802A89E4);
    fn_80010760();
    fn_8001075C(lbl_802A89F4);
    fn_8016A8D0(0x96, (s32)lbl_802A89F4);
    fn_80010760();
    fn_8001075C(lbl_802A8A0C);
    fn_8016A944(0xAF, (s32)lbl_802A8A0C);
    fn_80010760();
    fn_8001075C(lbl_802A8A18);
    fn_8016A9B8(0x4B, (s32)lbl_802A8A18);
    fn_80010760();
    fn_8001075C(lbl_802A8A2C);
    fn_8016AA2C(0xAF, (s32)lbl_802A8A2C);
    fn_80010760();
    fn_8000F320(*(void **)&lbl_802FFE98);
    fn_8001075C(lbl_802A8A44);
    fn_80125C70(lbl_80303464, fn_80146EB8());
    fn_80125CE4((s32)lbl_803059F4, fn_80146EC0());
    fn_80010760();
}
