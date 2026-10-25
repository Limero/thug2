// Promoted from src/wip (m2c draft hand-refined to exact match; args are plain s32 relayed
// through the lbl_8030026C dispatch slot — draft's function-pointer arg types were wrong).
// range 0x8001F250-0x8001F298 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_8030026C;
void fn_8001F250(s32 arg0, s32 arg1) {
    ((s32 (*)(s32)) lbl_8030026C)(arg0);
    ((s32 (*)(s32)) lbl_8030026C)(arg1);
}
