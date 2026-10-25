// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0B38-0x800F0EF0 (952B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern CScript *lbl_8030342C;
extern s32 ScriptSetEventHandler();
extern CStruct *CStruct_new(s32);
extern CStruct *CStruct_ctor(CStruct *);
extern void CStruct_dtor(CStruct *);
extern void CStruct_delete(CStruct *, s32);
extern u8 *fn_8012B2A0(u8 *);
extern u8 *fn_8012E168(u8 *);
extern void *fn_80125480(s32);
extern u8 *fn_8012DC0C(CStruct *, u8 *, CStruct *);
extern void *fn_8012CB2C();
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern u8 *fn_8013465C(CScript *, s32);
extern void fn_801347CC(CScript *, s32);

typedef struct { char pad0[2]; u8 type; char pad1[9]; void *pad2; } QBNode;

void fn_800F0B38(s32 arg0, s32 arg1, s32 (*arg2)(CStruct *, u8 *), CStruct *arg3, s32 arg4) {
    if (arg4 <= 5) {
        CScript *script = lbl_8030342C;
        s32 done = 0;
        s32 zero = 0;
        u8 *p = fn_8013465C(script, arg0);
        CStruct *sc = CStruct_ctor(CStruct_new(8));
        s32 sp8;
        s32 spC;
        s32 *sp10;
        s32 sp14;
        s32 sp18;
        s32 tok;
        u8 *tokp;

        p = fn_8012E168(p);
        do {
            switch (*p) {
            case 'C':
                p++;
                fn_8012CB2C(&sp8, p);
                p += 4;
                if (sp8 == (s32)ScriptSetEventHandler) {
                    CStruct_dtor(sc);
                    p = fn_8012DC0C(sc, p, arg3);
                    spC = zero;
                    GetChecksum_2(sc, QB_SCR, &spC, 0);
                    if (spC != 0)
                        fn_800F0B38(spC, arg1, arg2, 0, arg4 + 1);
                } else {
                    p = fn_8012E168(p);
                }
                break;
            case 0x16:
            case 'D':
            case 'F': {
                QBNode *node;
                tokp = p;
                if (*p == 'F') {
                    p++;
                    fn_8012CB2C(&sp10, p);
                    p += 4;
                    tok = *sp10;
                } else {
                    p++;
                    fn_8012CB2C(&sp14, p);
                    p += 4;
                    tok = sp14;
                }
                if (*p == 7)
                    break;
                node = fn_80125480(tok);
                if (node != NULL) {
                    switch (node->type) {
                    case 8:
                        if (tok == arg1) {
                            CStruct_dtor(sc);
                            p = fn_8012DC0C(sc, p, arg3);
                            arg2(sc, tokp);
                        } else {
                            p = fn_8012E168(p);
                        }
                        break;
                    case 9:
                        if (tok == arg1) {
                            CStruct_dtor(sc);
                            p = fn_8012DC0C(sc, p, arg3);
                            arg2(sc, tokp);
                            if (arg1 == QB_ENDGAP) {
                                sp18 = zero;
                                if (GetChecksum_2(sc, QB_GAPSCRIPT, &sp18, 0) != 0)
                                    fn_800F0B38(sp18, QB_ENDGAP, arg2, 0, arg4 + 1);
                            }
                        } else {
                            p = fn_8012E168(p);
                        }
                        break;
                    case 7:
                        CStruct_dtor(sc);
                        p = fn_8012DC0C(sc, p, arg3);
                        if (tok == arg1) {
                            arg2(sc, tokp);
                        } else {
                            p = fn_8012E168(p);
                        }
                        fn_800F0B38(tok, arg1, arg2, sc, arg4 + 1);
                        break;
                    }
                }
                break;
            }
            case '!':
                p = fn_8012B2A0(p);
                p = fn_8012E168(p);
                break;
            case 'G':
                p = fn_8012B2A0(p);
                if (*p == '9')
                    p = fn_8012B2A0(p);
                if (*p == 0x0E) {
                    p = fn_8012E168(p);
                    break;
                }
                break;
            case '$':
                done = 1;
                break;
            default:
                p = fn_8012B2A0(p);
                break;
            }
        } while (done == 0);

        fn_801347CC(script, arg0);
        if (sc != NULL)
            CStruct_delete(sc, 3);
    }
}
