// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022F434-0x8022F5B0 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -mps-float

void *fn_80240C80(void *);
s32 fn_80129528(CStruct *, s32);
void fn_801279A0(CStruct *, u32, CStruct *);
void AddChecksum(CStruct *, s32, s32);
s32 fn_80240ED0(CStruct *);
s32 fn_80243EF0(void);
s32 fn_80243B70(s32, s32);

void fn_8022F434(Unk_9994C3F5 *arg0, CStruct *arg1, s32 *arg2) {
    __ps_t sp8[2];
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r30;
    s32 temp_r3_2;
    void *temp_r3;
    Unk_69F3F3BE *temp_r31;
    Unk_9994C3F5 *var_r29;

    var_r29 = *((void * *)&arg0->unk0x8);
    if (var_r29 != NULL) {
        do {
            temp_r31 = fn_80240C80(var_r29);
            temp_r0 = temp_r31->unk0x4;
            if (!(temp_r0 & 0x20)) {
                if (!(temp_r0 & 0x80)) {
                    fn_801279A0((temp_r30 = fn_80129528(arg1, *arg2)), QB_POS,
                                (sp8[0] = temp_r31->unk0x18,
                                 sp8[1] = temp_r31->unk0x20, sp8));
                    AddChecksum(temp_r30, QB_NAME, temp_r31->unk0x0);
                    temp_r0_2 = *(s32 *)(temp_r31->unk0x14 + (s32)0x4);
                    if (temp_r0_2 & 0x400) {
                        if (temp_r0_2 & 0x800) {
                            AddChecksum(temp_r30, 0, QB_NCOMP_GAMEOBJ_PARK_NONET);
                        } else {
                            AddChecksum(temp_r30, 0, QB_NCOMP_GAMEOBJ_PARK);
                        }
                    } else {
                        AddChecksum(temp_r30, 0, QB_NCOMP_LVLGEOM_PARK);
                        temp_r3_2 = fn_80240ED0(temp_r31);
                        AddChecksum(temp_r30, QB_CLUSTER, ~(temp_r3_2 | temp_r3_2));
                    }
                    if (temp_r31->unk0x4 & 0x40) {
                        AddChecksum(temp_r30, QB_TRIGGERSCRIPT, fn_80243B70(fn_80243EF0(), (s32)temp_r31));
                    } else {
                        temp_r3_2 = *(s32 *)(temp_r31->unk0x14 + (s32)0x24);
                        if (temp_r3_2 != 0) {
                            AddChecksum(temp_r30, QB_TRIGGERSCRIPT, temp_r3_2);
                        }
                    }
                    *arg2 += 1;
                }
            }
            var_r29 = *((void * *)&var_r29->unk0x8);
        } while (var_r29 != NULL);
    }
}
