// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80140164-0x8014030C (424B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 GetStructure(s32, s32);
s32 fn_80140164(Unk_FFAD6788 *arg0) {
    Unk_E9D95610 *temp_r3;

    if ((arg0 != NULL) && (arg0->unk0xC8 != 0)) {
        temp_r3 = GetChecksum_3(arg0, QB_SKATERCOREPHYSICS);
        if (temp_r3->unk0x340 != 0) {
            switch (*((u32 *)&temp_r3->unk0x344)) {
            case QB_SEGWAY:
                return GetStructure(QB_SEGWAY_PHYSICS, 0);
            case QB_GURNEY:
                return GetStructure(QB_GURNEY_PHYSICS, 0);
            case QB_TRICYCLE:
                return GetStructure(QB_TRICYCLE_PHYSICS, 0);
            case QB_WHEELCHAIR:
                return GetStructure(QB_WHEELCHAIR_PHYSICS, 0);
            case QB_MINIKART:
                return GetStructure(QB_MINIKART_PHYSICS, 0);
            case QB_MECHBULL:
                return GetStructure(QB_MECHBULL_PHYSICS, 0);
            case QB_CHAINSAW:
                return GetStructure(QB_CHAINSAW_PHYSICS, 0);
            case QB_SHOPPINGCART:
                return GetStructure(QB_SKATER_PHYSICS, 0);
            case QB_SLALOM:
                return GetStructure(QB_SKATER_PHYSICS, 0);
            case QB_LUGE:
                return GetStructure(QB_SKATER_PHYSICS, 0);
            }
        } else if (temp_r3->unk0x35C != 0) {
            return GetStructure(QB_CHAINSAW_PHYSICS, 0);
        }
    }
    return GetStructure(QB_SKATER_PHYSICS, 0);
}
