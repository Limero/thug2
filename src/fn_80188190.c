// range 0x80188190-0x801881B8 (0x28). Byte-identical.
// Identification: singleton getter — returns fn_80174A50(global) where the
// arg is the object pointer stored at lbl_80305EAC.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_80174A50(Unk_40426380 *);
// Game_GetGoalManager @ 0x80188190
s32 Game_GetGoalManager(void) {
    return fn_80174A50(*(void **)lbl_80305EAC);
}
