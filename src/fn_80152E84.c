// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152E84-0x80152EC8 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EE4[];
extern void fn_8019D438(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_80131314(Unk_FFAD6788 * arg0);
bool ScriptPauseGame(void *arg0, Unk_FFAD6788 *arg1) {
    fn_8019D438(*(s32 *)&lbl_80305EE4, 1);
    fn_80131314(arg1);
    return true;
}
