// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113ADC-0x80113B54 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802FFE98[];

s32 GetText(CStruct *, s32, void *, s32);
void fn_8000F2F8(Unk_9994C3F5 *, s32);
s32 Pcm_LoadMusicHeader(s32);
void fn_8000F320(Unk_9994C3F5 *);

s32 ScriptLoadMusicHeader(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;
    s32 ret;

    GetText(pParams, 0, &sp8, 0);
    if (sp8 != 0) {
        fn_8000F2F8(*(Unk_9994C3F5 **)lbl_802FFE98,
                    (*(Unk_9994C3F5 **)lbl_802FFE98)->unk0x11C);
        ret = Pcm_LoadMusicHeader(sp8);
        fn_8000F320(*(Unk_9994C3F5 **)lbl_802FFE98);
        return ret;
    }
    return 0;
}
