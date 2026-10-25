// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4454-0x801F4628 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801F2EA0(void *);
extern void fn_801F2AE0(Unk_31DE137E *, s32);
extern void fn_801F2CCC(void *, u8);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern f32 fn_8012570C(s32, s32);

bool fn_801F4454(Unk_13D0EFB0 *arg0, void *arg1, f32 arg2, f32 arg3) {
    volatile f32 _dummyf1;
    volatile f32 _dummyf2;
    volatile f32 _dummyf3;
    register f32 v130 __asm__("fr31");
    register f32 v134 __asm__("fr30");
    __ps_t temp_f0;
    register s32 off __asm__("r9");
    register s32 t130 __asm__("r11");
    s32 t134;
    s32 ni;
    s32 cur;
    register s32 m __asm__("r11");
    register s32 t130b __asm__("r9");
    register s32 t134b __asm__("r11");

    v130 = arg2;
    v134 = arg3;
    arg0->unk0x2BC = 0;
    if (fn_801F2EA0(arg0) == 0) {
        return false;
    }
    off = arg0->unk0x2BB;
    temp_f0 = *(__ps_t *)arg1;
    off <<= 5;
    off += (s32)arg0;
    off += 0x120;
    *(__ps_t *)off = temp_f0;
    ((__ps_t *)off)[1] = ((__ps_t *)arg1)[1];
    t130 = arg0->unk0x2BB;
    t130 <<= 5;
    t130 = (s32)arg0 + t130;
    ((Unk_8840B148 *)t130)->unk0x130 = v130;
    t134 = arg0->unk0x2BB;
    t134 <<= 5;
    __asm__("add %0, %1, %2" : "=r"(t134) : "r"((s32)arg0), "r"(t134));
    ((Unk_8840B148 *)t134)->unk0x134 = v134;
    if (arg0->unk0x2BB == arg0->unk0x2B8 - 1) {
        arg0->unk0x2BC = 1;
    }
    if (arg0->unk0x2BB == 0) {
        Script_RunScript(QB_CREATE_CAG_HELPER_TEXT, 0, 0, 0, 0);
    }
    fn_801F2AE0(arg0, arg0->unk0x2BB);
    ni = arg0->unk0x2BB + 1;
    arg0->unk0x2BB = ni;
    fn_801F2CCC(arg0, ni);
    cur = arg0->unk0x2BB;
    m = cur & 0xFF;
    if ((u32)m < (u32)arg0->unk0x2BA) {
        return true;
    }
    arg0->unk0x2BA = cur;
    if (m != arg0->unk0x2B8) {
        goto rewrite;
    }
    arg0->unk0x2BB = arg0->unk0x2B8 - 1;
    return true;
rewrite:
    m <<= 5;
    temp_f0 = *(__ps_t *)arg1;
    m += (s32)arg0;
    m += 0x120;
    *(__ps_t *)m = temp_f0;
    ((__ps_t *)m)[1] = ((__ps_t *)arg1)[1];
    t130b = arg0->unk0x2BB;
    t130b <<= 5;
    t130b = (s32)arg0 + t130b;
    ((Unk_8840B148 *)t130b)->unk0x130 = v130;
    t134b = arg0->unk0x2BB;
    t134b <<= 5;
    t134b = (s32)arg0 + t134b;
    ((Unk_8840B148 *)t134b)->unk0x134 = v134;
    if (arg0->unk0x114 == QB_COMBO || arg0->unk0x114 == QB_SKATE) {
        if (arg0->unk0x2BB == 2) {
            *(f32 *)((char *)arg0 + ((arg0->unk0x2BB & 0xFF) << 5) + 0x130) += fn_8012570C(QB_GOALEDITOR_OBJECTHEIGHT, 0);
        }
    }
    return true;
}
