// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80175504-0x8017561C (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct Unk_80175504_VT {
    char pad0x0[0x18];
    s16 unk0x18;
    void (*unk0x1C)(void *, void *);
} Unk_80175504_VT;

typedef struct Unk_80175504_Mgr {
    char pad0x0[0x1A4];
    s32 arr[1];
} Unk_80175504_Mgr;

s32 GetChecksum_3(void *, s32);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
s32 ScriptInSplitScreenGame(void *, void *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_8012772C(void *, s32, f32);
void AddString(void *, s32, void *);
void CStruct_delete(void *, s32);
void fn_800DDCB8(void *);
void fn_800DDAF0(void *, s32, void *);
s32 fn_80141FA4(void *);
extern char lbl_802FFE98[];
extern char lbl_802A8DB4[];
extern char lbl_802A8DC0[];

void fn_80175504(void *arg0, void *arg1) {
    Unk_80175504_Mgr *mgr;
    Unk_80175504_VT *vt;
    void *script;
    void *t;
    s32 v = 1;

    script = GetChecksum_3(arg1, QB_SHADOW);
    mgr = *(Unk_80175504_Mgr **)lbl_802FFE98;
    fn_8000F2F8(mgr, mgr->arr[fn_80141FA4(arg1)]);
    if (ScriptInSplitScreenGame(0, 0) != 0) {
        v = 2;
    }
    if (*(s32 *)((char *)arg1 + 0xC8) == 0) {
        v = 2;
    }
    t = CStruct_ctor(CStruct_new(8));
    fn_8012772C(t, QB_SHADOWSCALE, *(f32 *)lbl_802A8DC0);
    AddString(t, QB_SHADOWMODEL, lbl_802A8DB4);
    vt = *(Unk_80175504_VT **)((char *)script + 0x18);
    vt->unk0x1C((char *)script + vt->unk0x18, t);
    if (t != 0) {
        CStruct_delete(t, 3);
    }
    fn_800DDCB8(script);
    fn_800DDAF0(script, v, lbl_802A8DB4);
    fn_8000F320(*(void **)lbl_802FFE98);
}
