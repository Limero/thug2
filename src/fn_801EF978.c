// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF978-0x801EFA44 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EC0;
s32 fn_8019878C(CStruct *);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8009F010(s32, s32, s32);
void fn_801EF978(Unk_31DE137E *arg0, s32 arg1) {
    s32 v;
    Unk_FFAD6788 *p;
    s32 var1;
    s32 var2;

    if (arg1 != 0) goto inner;
    if (fn_8019878C(lbl_80305EC0) == 0) goto else_lab;
inner:
    v = arg0->unk0x1C;
    var1 = 1;
    if ((v & 4) == 0) var1 = 0;
    if (var1 != 0) goto end;
    var2 = 1;
    if ((v & 2) == 0) var2 = 0;
    if (var2 != 0) goto end;
    arg0->unk0x1C = v | 4;
    p = *((s32 * *)&arg0->unk0xC);
    if (p->unk0xC8 == 0) goto end;
    Script_RunScript(QB_FORCEENDOFRUN, 0, p, 0, 0);
    goto end;
else_lab:
    p = *((s32 * *)&arg0->unk0xC);
    fn_8009F010(p, QB_RUNHASENDED, 0);
    arg0->unk0x1C &= QB_UNKNOWN_0xFFFFFFFD;
end:
    return;
}
