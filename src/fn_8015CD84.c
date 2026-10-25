// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015CD84-0x8015CDFC (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_8019B834(Unk_9994C3F5 *);
typedef struct { char _0[0x374]; s32 fld; } G_t;
bool ScriptIsCurrentHorseSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    register G_t *g __asm__("r11");

    if (fn_80128C80(pParams, 0, &sp8, 0) == 0) {
        fn_80128E34(pParams, 0, &sp8, 1);
    }
    g = (G_t *)lbl_80305EAC;
    return fn_8019B834(g->fld) == sp8;
}
