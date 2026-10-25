// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E770-0x8019E990 (544B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AB040[];
extern char lbl_802AB0A8[];
extern s32 lbl_8030191C;
extern f32 lbl_802AAF84;
extern f32 lbl_802AAF88;
void fn_8009F678(Unk_6A70655D *);
void fn_801A0D50(Unk_6A70655D *);
void fn_8009E274(Unk_31DE137E *, s32);
s32 Mem_NewZero(s32);
void fn_80009B04(Unk_5EF41E38 *, void *);
void fn_8000A578(s32, void *);
s32 fn_80139510(void *, s32, Unk_C8FEE62D *, s32, void *, s32);
void fn_801A0824(CScript *);
s32 fn_8019E578(Unk_DB0E2BAB *);
s32 fn_8019E5A8(Unk_DB0E2BAB *);
s32 fn_8019E5D8(Unk_DB0E2BAB *);
s32 fn_8019E608(Unk_DB0E2BAB *);
s32 fn_8019E6F8(void *);
s32 fn_8019E638(Unk_DB0E2BAB *);
void *fn_8019E770(Unk_361D6392 *arg0, s32 arg1) {
    register f32 temp_f13 asm("fr13");
    f32 temp_f0;
    register s32 temp_r11 __asm__("r11");
    register char *temp_base8 __asm__("r8");
    register s32 temp_r28 __asm__("r28");
    s32 temp_r30;
    CScript *temp_r29;
    register s32 var_r27 __asm__("r27");
    var_r27 = 0;
    fn_8009F678(arg0);
    arg0->unk0x120 = var_r27;
    arg0->unk0x8 = (s32)lbl_802AB040;
    fn_801A0D50(arg0);
    fn_8009E274(arg0, QB_OBJECT_TYPE_COMPOSITE);
    temp_r28 = lbl_8030191C;
    fn_80009B04((s32)(temp_r29 = (void *)Mem_NewZero(0x30)), (temp_r30 = (s32)fn_801A0824, 0));
    temp_r29->unk0x24 = var_r27;
    temp_r29->unk0x28 = temp_r30;
    temp_r29->unk0x18 = (s32)lbl_802AB0A8;
    temp_r29->unk0x2C = (s32)arg0;
    arg0->unk0x118 = (s32)temp_r29;
    fn_8000A578((temp_r29->unk0x24 * 0x94) + temp_r28 + 0xC, temp_r29);
    temp_r11 = temp_r29->unk0x24 * 0x94;
    temp_base8 = (char *)temp_r28 + 8;
    temp_f0 = lbl_802AAF88;
    temp_f13 = lbl_802AAF84;
    temp_r28 = (s32)((char *)(temp_r11 + (s32)temp_r28));
    temp_r28 += 0x58;
    temp_r29->unk0x1C = temp_r28;
    temp_r29->unk0x20 = (s32)*(s32 *)(temp_base8 + temp_r11);
    *((volatile s32 *)&arg0->unk0x138) = 1;
    arg0->unk0xB0 = temp_f0;
    arg0->unk0xB4 = temp_f13;
    *((volatile s32 *)&arg0->unk0x130) = var_r27;
    *((volatile f32 *)&arg0->unk0x128) = temp_f13;
    *((volatile f32 *)&arg0->unk0x12C) = temp_f0;
    arg0->unk0x78 = temp_f13;
    arg0->unk0x7C = temp_f0;
    arg0->unk0x80 = temp_f0;
    arg0->unk0x84 = temp_f0;
    arg0->unk0x88 = temp_f0;
    arg0->unk0x8C = temp_f13;
    arg0->unk0x90 = temp_f0;
    arg0->unk0x94 = temp_f0;
    arg0->unk0x98 = temp_f0;
    arg0->unk0x9C = temp_f0;
    arg0->unk0xA0 = temp_f13;
    arg0->unk0xA4 = temp_f0;
    arg0->unk0xA8 = temp_f0;
    arg0->unk0xAC = temp_f0;
    *((volatile s32 *)&arg0->unk0x134) = var_r27;
    arg0->unk0x124 = arg1;
    if (arg1 != 0) {
        fn_80139510((void *)(arg1 + 4), 0x25, (s32)fn_8019E578, 3, arg0, 0x80);
        fn_80139510((void *)(arg0->unk0x124 + 4), 0x26, (s32)fn_8019E5A8, 3, arg0, 0x80);
        fn_80139510((void *)(arg0->unk0x124 + 4), 0x27, (s32)fn_8019E5D8, 3, arg0, 0x80);
        fn_80139510((void *)(arg0->unk0x124 + 4), 0x28, (s32)fn_8019E608, 3, arg0, 0x80);
        fn_80139510((void *)(arg0->unk0x124 + 4), 0x29, (s32)fn_8019E6F8, 3, arg0, 0x80);
        fn_80139510((void *)(arg0->unk0x124 + 4), 0x2C, (s32)fn_8019E638, 3, arg0, 0x80);
    }
    return arg0;
}