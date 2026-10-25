// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165660-0x80165790 (304B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Script_GenerateCRC(s32);
void *fn_80165660(Unk_F96D0DC8 *arg0, s32 arg1, u32 arg2) {
    s32 temp_r9;
    s32 var_ctr;
    s32 var_r10;
    s8 var_r0;
    u32 h;

    h = Script_GenerateCRC(arg1);
    var_ctr = 8;
    var_r10 = 0;
    do {
        temp_r9 = h % 26;
        *(s8 *)((char *)arg0 + var_r10) = temp_r9 + 0x61;
        var_r10 += 1;
        h = (h - temp_r9) / 26;
        var_ctr -= 1;
    } while (var_ctr != 0);
    switch (arg2) {
    case QB_OPTIONSANDPROS:
        var_r0 = 0x61;
        goto block_19;
    case QB_CAT:
        var_r0 = 0x66;
        goto block_19;
    case QB_PARK:
        var_r0 = 0x63;
        goto block_19;
    case QB_NETWORKSETTINGS:
        var_r0 = 0x65;
        goto block_19;
    case QB_UNKNOWN_0xE0000000:
        break;
    case QB_CREATEDGOALS:
        var_r0 = 0x67;
        goto block_19;
    case QB_CREATEDGRAPHIC:
        var_r0 = 0x68;
    block_19:
        *((s8 *)&arg0->unk0x7) = var_r0;
        break;
    }
    *((s8 *)&arg0->unk0x8) = 0;
    return arg0;
}
