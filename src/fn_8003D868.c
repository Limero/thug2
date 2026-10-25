// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003D868-0x8003D9DC (372B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_801259C8(s32 arg0, s32 arg1);
s32 fn_80129528(s32 list, s32 idx);
s32 ContainsFlag(CStruct *entry, s32 hash);
s32 GetInteger(CStruct *entry, s32 hash, s32 *out, s32 flag);
s32 GetChecksum_2(CStruct *entry, s32 hash, s32 *out, s32 flag);

s32 fn_8003D868(s32 list_owner, s32 want_index, s32 weight) {
    s32 sp[4];                   /* sp[0] = random_index out, sp[1] = allow out,
                                    sp[2] = random_set out, sp[3] = frame pad */
    s32 i;
    s32 j;
    s32 entry;
    s32 count;
    s32 list;
    s32 wzero;

    list = fn_801259C8(list_owner, 1);
    count = *(s32 *)((char *)list + 4);
    if (weight == 0) {
        j = 0;
        if (weight >= count) {
            goto ret0;
        }
        for (; j < count; j++) {
            entry = fn_80129528(list, j);
            sp[0] = -1;
            if ((GetInteger(entry, QB_RANDOM_INDEX, &sp[0], 1) != 0) && (sp[0] == want_index)) {
                return entry;
            }
        }
        goto ret0;
    }
    for (;;) {
        for (i = 0; i < count; i++) {
            entry = fn_80129528(list, i);
            sp[1] = ContainsFlag(entry, QB_NO_RANDOM) ^ 1;
            GetInteger(entry, QB_ALLOW_RANDOM, &sp[1], 1);
            sp[2] = 0;
            GetChecksum_2(entry, QB_RANDOM_SET, &sp[2], 0);
            wzero = (sp[2] == 0);
            if ((sp[1] != 0) && (((s32)sp[2] == weight) || wzero)) {
                if (want_index <= 0) {
                    return entry;
                }
                want_index--;
            }
        }
    }
ret0:
    return 0;
}
