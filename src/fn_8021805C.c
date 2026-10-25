// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021805C-0x802183E0 (900B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80137B4C(Unk_F386DC9F *);
void fn_80137B54(Unk_F386DC9F *, s32);
void fn_80137734(Unk_F386DC9F *);
s32 fn_80137AD4(Unk_F386DC9F *);
s32 fn_80137A34(void *);
s32 fn_80137754(Unk_837F3EFF *);
void *fn_801258B0(s32, s32);
void AddComponent(CStruct *, s32, s32, void *);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 fn_800145AC(void);
void CStruct_delete(CStruct *, s32);
extern s32 lbl_80303448;
extern u32 lbl_803A3144;
extern char lbl_802AFD7C[];
extern char lbl_802AFD80[];
extern char lbl_802AFD88[];

void fn_8021805C(Unk_C7387A53 *arg0) {
    char sp8[128];
    CScript *o;
    register s32 mgr __asm__("r29");
    s32 v;
    s32 temp_r31;
    s32 emithash;
    void *t;

    o = *((void * *)&arg0->unk0x20);
    mgr = lbl_80303448;
    v = fn_80137B4C(mgr);
    if ((v != o->unk0x1D0) || (v == 8)) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        switch (v) {
        case 7:
            sprintf(sp8, (s32)lbl_802AFD7C, fn_801258B0(QB_NET_MODEM_STATE_REDIAL_PAUSE, 0));
            AddComponent(temp_r31, QB_TEXT, 3, sp8);
            Script_RunScript(QB_CREATE_MODEM_STATE_DIALOG, temp_r31, 0, 0, 0);
            lbl_803A3144 = fn_800145AC() + 0x1388;
            fn_80137B54(mgr, 8);
            break;
        case 8:
            if (fn_800145AC() > lbl_803A3144) {
                o->unk0x1D0 = -1;
                fn_80137734(mgr);
                return;
            }
            break;
        case 0:
            if (fn_80137AD4(mgr) == 3) {
                sprintf(sp8, (s32)lbl_802AFD7C, fn_801258B0(QB_NET_MODEM_STATE_CONENCTING, 0));
            } else {
                t = fn_801258B0(QB_NET_MODEM_STATE_DIALING, 0);
                sprintf(sp8, (s32)lbl_802AFD80, t, fn_80137A34(mgr));
            }
            AddComponent(temp_r31, QB_TEXT, 3, sp8);
            Script_RunScript(QB_CREATE_MODEM_STATE_DIALOG, temp_r31, 0, 0, 0);
            break;
        case 1:
            AddComponent(temp_r31, QB_TEXT, 3, fn_801258B0(QB_NET_MODEM_STATE_CONNECTED, 0));
            Script_RunScript(QB_CREATE_MODEM_STATE_DIALOG, temp_r31, 0, 0, 0);
            break;
        case 2:
            if (fn_80137AD4(mgr) == 1) {
                t = fn_801258B0(QB_NET_MODEM_STATE_LOGGED_IN, 0);
                sprintf(sp8, (s32)lbl_802AFD88, t, fn_80137754(mgr));
            } else {
                sprintf(sp8, (s32)lbl_802AFD7C, fn_801258B0(QB_NET_MODEM_STATE_LOGGED_IN, 0));
            }
            AddComponent(temp_r31, QB_TEXT, 3, sp8);
            Script_RunScript(QB_CREATE_MODEM_FINAL_STATE_DIALOG, temp_r31, 0, 0, 0);
            break;
        case 3:
            AddComponent(temp_r31, QB_TEXT, 3, fn_801258B0(QB_NET_MODEM_STATE_DISCONNECTING, 0));
            Script_RunScript(QB_CREATE_MODEM_STATUS_DIALOG, temp_r31, 0, 0, 0);
            break;
        case 4:
            AddComponent(temp_r31, QB_TEXT, 3, fn_801258B0(QB_NET_MODEM_STATE_HANGING_UP, 0));
            Script_RunScript(QB_CREATE_MODEM_STATUS_DIALOG, temp_r31, 0, 0, 0);
            break;
        case 5:
            AddComponent(temp_r31, QB_TEXT, 3, fn_801258B0(QB_NET_MODEM_STATE_DISCONNECTED, 0));
            Script_RunScript(QB_CREATE_MODEM_FINAL_STATE_DIALOG, temp_r31, 0, 0, 0);
            break;
    case 6:
        break;
    case 9:
        break;
        default:
            break;
        }
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    o->unk0x1D0 = v;
}
