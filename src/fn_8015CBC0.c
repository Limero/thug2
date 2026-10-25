// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CBC0-0x8015CBF0 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
void fn_8019BA64(CStruct *);
typedef struct { char _0[0x374]; s32 fld; } G_t;
bool ScriptSwitchHorsePlayers(CStruct *pParams, CScript *pScript) {
    register G_t *g __asm__("r11");
    g = (G_t *)lbl_80305EAC;
    fn_8019BA64(g->fld);
    return true;
}
