// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F010-0x8021F120 (272B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_8021E024(void * arg0);
extern s32 fn_80140068(s32 arg0, void * arg1, void * arg2);

s32 fn_8021F010(Unk_C7387A53 *arg0) {
    s32 temp_r9;
    s32 var_r3;

    temp_r9 = arg0->unk0x28;
    if ((temp_r9 == QB_NETGOALATTACK) || (temp_r9 == QB_KING) || (temp_r9 == QB_NETKING) ||
        (temp_r9 == QB_NETSCORECHALLENGE) || (temp_r9 == QB_SCORECHALLENGE)) {
        return 1;
    }
    if (fn_8009CF2C((s32)arg0) == 0) {
        return 0;
    }
    if (arg0->unk0x28 == QB_NETCTF) {
        if (fn_80140068(fn_8021E024((s32)arg0), QB_CTF_GAME_TYPE, QB_CHECKSUM) != QB_TIMED_CTF) {
            return 1;
        }
    }
    return (fn_80140068(fn_8021E024((s32)arg0), QB_STOP_AT_ZERO, QB_CHECKSUM) ^ QB_BOOLEAN_TRUE) == 0;
}
