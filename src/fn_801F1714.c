// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1714-0x801F1838 (292B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern char lbl_802AE0AC[];
extern char lbl_802AE0D4[];
extern char lbl_802AE0FC[];
extern char lbl_802AE124[];
extern char lbl_802AE14C[];
extern char lbl_802AE174[];
extern char lbl_802AE1A4[];
extern char lbl_802AE1D4[];
extern char lbl_802AE204[];
extern char lbl_802AE234[];
s32 fn_801F1714(s32 arg0, s32 arg1) {
    s32 var_r9;

    var_r9 = 0;
    switch ((u32)arg0) {                                 
    case QB_SKATE:                                
        switch (arg1) {                             
        case 0:                                     
            var_r9 = (s32)lbl_802AE0AC;
            break;
        case 1:                                     
            var_r9 = (s32)lbl_802AE0D4;
            break;
        case 2:                                     
            var_r9 = (s32)lbl_802AE0FC;
            break;
        case 3:                                     
            var_r9 = (s32)lbl_802AE124;
            break;
        case 4:                                     
            var_r9 = (s32)lbl_802AE14C;
            break;
        }
        break;
    case QB_COMBO:                                
        switch (arg1) {                             
        case 0:                                     
            var_r9 = (s32)lbl_802AE174;
            break;
        case 2:                                     
            var_r9 = (s32)lbl_802AE1D4;
            break;
        case 3:                                     
            var_r9 = (s32)lbl_802AE204;
            break;
        case 4:                                     
        case 1:                                     
            var_r9 = (s32)lbl_802AE1A4;
            break;
        }
        break;
    case QB_RACE:                                
        var_r9 = (s32)lbl_802AE234;
        break;
    }
    return var_r9;
}
