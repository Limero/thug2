// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AA158-0x801AA2D4 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: creates an entity instance for hash 0x118
// (fn_8009F678(Mem_NewZero(0x118))), configures it (fn_801A0D50/DA8,
// fn_8009E274(_, 0xD2DB7F97)), links it into a global list
// (lbl_80301A38->+0x1A38 via vtable +0x14), attaches it to the skater
// (fn_800F078C(arg0, obj+0x58), fn_801A0E48), broadcasts script messages
// 0xF3EEC45E and 0x955A2767, and wires float params (lbl_802ABAA0-AC).
// Likely a script-command handler that creates and registers an attached
// skater object. Suggested rename: ScriptCreateSkaterAttachedObject.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ABAAC;
extern f32 lbl_802ABAA0;
extern f32 lbl_802ABAA4;
extern f32 lbl_802ABAA8;
extern s32 Mem_NewZero(s32);
extern s32 fn_8009F678(Unk_6A70655D *);
extern void fn_801A0D50(Unk_6A70655D *);
extern void fn_801A0DA8(Unk_6A70655D *);
extern void fn_8009E274(Unk_31DE137E *, s32);
extern char lbl_80301A38[];
extern void fn_800F078C(CStruct *, Unk_9994C3F5 *);
extern void fn_801A0E48(Unk_6A70655D *, CStruct *);
extern s32 Script_RunScript(s32, s32, s32, s32, s32);
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern void fn_800D6490(CScript *, s32);
extern s32 fn_800D64DC(CScript *);
extern void fn_800B61F4(CScript *);
void fn_801AA158(CStruct *arg0) {
    volatile double _dummy;
    f32 temp_f31;
    f32 v30;
    f32 v28;
    f32 v2C;
    void *temp_r29;
    Unk_C7387A53 *temp_r3;
    Unk_89391A04 *temp_r9;

    temp_r29 = fn_8009F678(Mem_NewZero(0x118));
    fn_801A0D50(temp_r29);
    fn_801A0DA8(temp_r29);
    fn_8009E274(temp_r29, QB_OBJECT_TYPE_PED);
    {
        register void *anch __asm__("r11");
        register void *lv __asm__("r10");
        __asm__ volatile("lis %0,%1@ha" : "=r"(anch) : "s"(lbl_80301A38));
        {
            register void *a2 __asm__("r4");
            a2 = temp_r29;
            __asm__("" : "+r"(a2) : : "memory");
        lv = *((void * *)&((Unk_9C44AE00 *)anch)->unk0x1A38);
        temp_r9 = *((void * *)&((Unk_C7387A53 *)lv)->unk0x2C);
            ((void (*)(void *, void *))(*((void * *)&temp_r9->unk0x14)))((char *)lv + temp_r9->unk0x10, a2);
        }
    }
    fn_800F078C(arg0, temp_r29 + 0x58);
    fn_801A0E48(temp_r29, arg0);
    Script_RunScript(QB_PED_ADD_COMPONENTS, arg0, temp_r29, 0, 0);
    temp_r9 = *((void * *)&((Unk_9994C3F5 *)temp_r29)->unk0x8);
    ((void (*)(void *))(*((void * *)&temp_r9->unk0x4C)))((char *)temp_r29 + temp_r9->unk0x48);
    Script_RunScript(QB_PED_INIT_MODEL, arg0, temp_r29, 0, 0);
    temp_r3 = GetChecksum_3(temp_r29, QB_MOTION);
    temp_f31 = lbl_802ABAAC;
    v30 = lbl_802ABAA0;
    v28 = lbl_802ABAA4;
    v2C = lbl_802ABAA8;
    *((f32 *)&temp_r3->unk0x38) = temp_f31;
    *((f32 *)&temp_r3->unk0x30) = v30;
    *((f32 *)&temp_r3->unk0x28) = v28;
    *((f32 *)&temp_r3->unk0x2C) = v2C;
    fn_800D6490(temp_r3, temp_r29);
    *(f32 *)((char *)fn_800D64DC(temp_r3) + (s32)0xA0) = temp_f31;
    temp_r3->unk0x20 = (s32)(temp_r3->unk0x20 | 0x400);
    fn_800B61F4(GetChecksum_3(temp_r29, QB_MODEL));
    Script_RunScript(QB_PED_DISABLE_BONES, 0, temp_r29, 0, 0);
}
