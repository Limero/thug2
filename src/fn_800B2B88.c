// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B2B88-0x800B2CB8 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// Real prototypes (audited from each callee's first ~8 insns). Without these
// every call is an implicit decl and ngccc emits `crclr cr1eq` before the bl.
s32 ContainsFlag(void *arg0, s32 arg1);        // 0x801289E4  lwz r31,4(r3); mr r30,r4 -> s32
void *fn_80060DE4(void *arg0);                // 0x80060DE4  lwz r3,0x30(r3); blr -> obj
s32 fn_80060CD8(void *arg0);                  // 0x80060CD8  mr r31,r3
s32 fn_8005B7C4(void *arg0, void *arg1);      // 0x8005B7C4  stw r4,0x14(r3); li r3,1
s32 GetInteger(void *arg0, s32 arg1, s32 *arg2, s32 arg3); // 0x80128228 4-arg script wrapper
void fn_8005B558(void *arg0, s32 arg1);       // 0x8005B558  stw r4,0(r3); blr
s32 fn_80060D5C(void *arg0);                  // 0x80060D5C  mr r30,r3
void *GetChecksum_3(void *arg0, s32 arg1);    // 0x8009FDD8  cmpw r0,r4; li r3,0 -> node|NULL
void *fn_800C9780(void *arg0);                // 0x800C9780  lwz r3,0x1c(r3); blr -> node
s32 fn_8005FCB4(void *arg0, void *arg1);      // 0x8005FCB4  mr r31,r3; mr r28,r4; li r3,1
void fn_80062924(void *arg0, s32 arg1);       // 0x80062924  rlwimi; stw; blr
void fn_800B2CB8(void *arg0, void *arg1);     // 0x800B2CB8  mr r27,r3; mr r29,r4

// File-local layout: the shared Unk_F8D48A89 class types unk0xC/unk0x210 as
// s32, but both are pointers here (arg0->unk0xC is the model/scene object
// GetChecksum_3 derefs at +0x110; arg0->unk0x210 is the model-lights object
// every fn_80060xxx / fn_8005Bxxx below takes as `this`). Both are plain
// `lwz` loads either way, so the field type only silences the int->pointer
// diagnostics; the emitted code is unchanged.
typedef struct Unk_800B2B88 {
    char pad0x0[0xC];
    void *unk0xC;
    char pad0x10[0x200];
    void *unk0x210;
} Unk_800B2B88;

void fn_800B2B88(Unk_800B2B88 *arg0, struct CStruct *arg1) {
    s32 spC;
    s32 sp8;
    void *temp_r30;
    void *temp_r3;

    if (ContainsFlag(arg1, QB_USEMODELLIGHTS) != 0) {
        if (fn_80060DE4(arg0->unk0x210) == 0) {
            fn_80060CD8(arg0->unk0x210);
            temp_r30 = fn_80060DE4(arg0->unk0x210);
            fn_8005B7C4(temp_r30, arg0->unk0xC + 0x58);
            sp8 = 1;
            GetInteger(arg1, QB_MAX_SCENE_LIGHTS, &sp8, 0);
            fn_8005B558(temp_r30, sp8);
        }
    } else if (fn_80060DE4(arg0->unk0x210) != 0) {
        fn_80060D5C(arg0->unk0x210);
    }
    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    if (temp_r3 != 0) {
        fn_8005FCB4(arg0->unk0x210, fn_800C9780(temp_r3));
    }
    spC = 0;
    GetInteger(arg1, QB_SHADOWVOLUME, &spC, 0);
    fn_80062924(arg0->unk0x210, spC != 0 ? 1 : 0);
    fn_800B2CB8(arg0, arg1);
}
