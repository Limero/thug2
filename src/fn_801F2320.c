// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2320-0x801F23F0 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802AE2B8[];
extern char lbl_802AE2C0[];

/* Goal editor node, 0x20B stride from +0x120. m2c's Unk_8B4F0B1C shape. */
typedef struct GoalNode {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    s32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
} GoalNode;

void fn_801F21A8(Unk_7258DEBD *, s32);
CStruct *CStruct_ctor(CStruct *);
s32 fn_801F2A60(Unk_7258DEBD *, s32);
void fn_80127848(CStruct *, void *, s32);
void fn_80127934(CStruct *, void *, f32, f32, f32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);

void fn_801F2320(Unk_7258DEBD *arg0) {
    u8 *base;
    GoalNode *node;
    s32 i;
    /* Script-builder object at r1+8. See the frame note in the header: the
       size must be 5-8 bytes and NOT a power of two (see "LOCAL-SIZE TRICK"). */
    char sp8[5];
    s32 temp;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;

    register const char *nm __asm__("r27");
    register const char *ps __asm__("r28");
    base = (u8 *)arg0;
    i = 0;
    if (i < (s32)base[0x2BA]) {
        __asm__ volatile("lis %0,%1@ha" : "=r"(nm) : "s"(lbl_802AE2B8));
        __asm__ volatile("lis %0,%1@ha" : "=r"(ps) : "s"(lbl_802AE2C0));
        node = (GoalNode *)(base + 0x120);
        do {
            fn_801F21A8(arg0, i);
            CStruct_ctor((CStruct *)sp8);
            temp = fn_801F2A60(arg0, i);
            i++;
            fn_80127848((CStruct *)sp8, (void *)(nm - 0x1D48), temp);
            temp_f1 = node->unk0x0;
            temp_f3 = node->unk0x8;
            temp_f2 = node->unk0x4 + node->unk0x10;
            node++;
            fn_80127934((CStruct *)sp8, (void *)(ps - 0x1D40), temp_f1, temp_f2, temp_f3);
            Script_RunScript(QB_GOAL_EDITOR_REFRESH_GOAL_OBJECT_POSITION, (s32)sp8, 0, 0, 0);
            CStruct_delete((CStruct *)sp8, 2);
        } while (i < (s32)base[0x2BA]);
    }
}
