// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118DF8-0x80118E90 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x00[0x84];
    s32 unk0x84;
} Sc;

void GetText(CStruct *, s32, void *, s32);
Sc *fn_80054E1C(s32 name);
Sc *fn_80054E40(void);
void fn_80054C6C(Sc *, s32);
void fn_8005D734(s32 *);

s32 ScriptUnloadScene(CStruct *arg0) {
    s32 sp8;
    s32 res;
    Sc *p;
    s32 n;

    sp8 = 0;
    GetText(arg0, QB_SCENE, &sp8, 0);
    res = 0;
    if (sp8 != 0) {
        p = fn_80054E1C(sp8);
        if (p != 0) {
            res = 1;
        } else {
            p = fn_80054E40();
        }
        if (p != 0) {
            n = p->unk0x84;
            fn_80054C6C(p, 1);
            if (n != 0) {
                fn_8005D734(n);
            }
        }
    }
    return res;
}
