// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AD750-0x800AD890 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddInteger(CStruct *arg0, s32 arg1, s32 arg2);
void AddArrayPointer(CStruct *arg0, s32 arg1, s32 arg2);
void AddChecksum(CStruct *arg0, s32 arg1, s32 arg2);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 fn_8003E7CC(s32 arg0);
s32 fn_80128F94(s32 arg0);
void fn_80129068(s32 arg0, s32 arg1, s32 arg2);
void fn_80129314(CStruct *arg0, s32 arg1, s32 arg2);
bool fn_800AD750(CStruct *arg0, CStruct *arg1, CStruct *arg2) {
    s32 temp_r26;
    s32 temp_r27;
    s32 var_r28;
    register s32 *var_r29 __asm__("r29");
    register s32 temp_r30 __asm__("r30");
    CStruct *temp_r31;
    AddInteger(arg1, QB_VERSION, arg2->unk0x0);
    var_r28 = 0;
    var_r29 = (s32 *)arg2;
    temp_r26 = *++var_r29;
    temp_r27 = fn_80128F94(fn_8003E7CC(0xC));
    var_r29 += 1;
    fn_80129068(temp_r27, temp_r26, 0xA);
    if (var_r28 < temp_r26) {
        do {
            temp_r31 = (CStruct *)CStruct_ctor(CStruct_new(8));
            AddChecksum(temp_r31, QB_OBJECTNAME, *var_r29);
            AddChecksum(temp_r31, QB_MODELNAME, *++var_r29);
            AddChecksum(temp_r31, QB_SKELETONNAME, *++var_r29);
            AddChecksum(temp_r31, QB_ANIMNAME, *++var_r29);
            temp_r30 = *++var_r29;
            var_r29 += 1;
            if (temp_r30 & 0x40000000) {
                AddChecksum(temp_r31, 0, QB_ISHEADMODEL);
            }
            if (temp_r30 < 0) {
                AddChecksum(temp_r31, 0, QB_ISPLAYERMODEL);
            }
            fn_80129314(temp_r27, var_r28, temp_r31);
            var_r28 += 1;
        } while (var_r28 < temp_r26);
    }
    AddArrayPointer(arg1, QB_OBJECTS, temp_r27);
    return true;
}
