// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023104C-0x80231248 (508B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CStruct_ctor(void *);
void AddChecksum(void *, s32, s32);
bool ScriptPauseSkaters(void *, s32);
void CStruct_delete(void *, s32);
void ScriptUnPauseSkaters(s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void *fn_8023C598(s32);
void *fn_801FC0E0(void *);
void fn_80231248(void *);
void fn_8023C2C4(void);
s32 fn_80231284(s32);
void fn_8023104C(Unk_C7387A53 *arg0) {
    volatile s32 sp8;
    s32 show;
    s32 rail;
    s32 rail2;
    void *e;

    show = 1;
    if (!(arg0->unk0x4C & 2)) {
        show = 0;
    }
    if (show == 0) {
        if (arg0->unk0x44 == QB_EDIT) {
            CStruct_ctor(&sp8);
            AddChecksum(&sp8, 0, QB_HIDE);
            ScriptPauseSkaters(&sp8, 0);
            CStruct_delete(&sp8, 2);
        } else if (arg0->unk0x44 == QB_TEST_PLAY) {
            ScriptUnPauseSkaters(0, 0);
        }
    }
    if ((arg0->unk0x44 == QB_EDIT) && (fn_8023C598(0) != NULL)) {
        show = 1;
        if (!(arg0->unk0x4C & 2)) {
            show = 0;
        }
        if (show == 0) {
            e = fn_8023C598(1);
            if (*(s32 *)((char *)e + 0x74) == 6) {
                s32 f = *(s32 *)((char *)fn_801FC0E0(e) + 8);
                rail = 1;
                if (!(f & 1)) {
                    rail = 0;
                }
                if (rail != 0) {
                    Script_RunScript(QB_SWITCHONRAILEDITOR, 0, 0, 0, 0);
                }
                fn_80231248(arg0);
                if (*(s32 *)((char *)fn_8023C598(1) + 0x74) != 6) {
                    Script_RunScript(QB_SWITCHOFFRAILEDITOR, 0, 0, 0, 0);
                }
            } else {
                s32 f = *(s32 *)((char *)fn_801FC0E0(e) + 8);
                rail2 = 1;
                if (!(f & 1)) {
                    rail2 = 0;
                }
                if (rail2 == 0) {
                    Script_RunScript(QB_SWITCHOFFRAILEDITOR, 0, 0, 0, 0);
                }
                fn_80231284((s32)arg0);
                if (*(s32 *)((char *)fn_8023C598(1) + 0x74) == 6) {
                    Script_RunScript(QB_SWITCHONRAILEDITOR, 0, 0, 0, 0);
                }
            }
            fn_8023C2C4();
        }
    } else {
        arg0->unk0x48 = 0;
    }
}
