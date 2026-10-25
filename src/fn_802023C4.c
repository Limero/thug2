// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802023C4-0x80202438 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_802010FC();                                  

void fn_802023C4(Unk_59E38960 *arg0, s32 arg1) {
    if (fn_802010FC() != 0) {
        switch (arg1) {                             
        case QB_FLIPTRICK:
            arg0->unk0xA8C = (s32) (arg0->unk0xA8C + 1);
            return;
        case QB_GRABTRICK:
            arg0->unk0xA90 = (s32) (arg0->unk0xA90 + 1);
            break;
        }
    }
}
