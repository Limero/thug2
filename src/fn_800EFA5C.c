// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFA5C-0x800EFB60 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301B48;
void fn_80131BAC(void *, s32);
s32 CStruct_new(s32);
CStruct *CStruct_ctor(CStruct *);
void AddChecksum(CStruct *, s32, s32);
void *GetChecksum_3(void *, s32);
void CStruct_delete(CStruct *, s32);
s32 fn_800F2A48(s32, s32, s32);
void fn_800F28E4(void *, void *);

void fn_800EFA5C(Unk_31DE137E *arg0) {
    CStruct *p;
    void *node;
    s32 vtbl;
    s32 mgr;
    s32 ret;

    if (arg0->unk0x1C != 0) {
        fn_80131BAC(arg0->unk0xC, QB_FAM_PLAY_STREAM);
        p = CStruct_ctor(CStruct_new(8));
        AddChecksum(p, QB_TYPE, QB_PARTIALANIM);
        AddChecksum(p, QB_ID, QB_JAWROTATION);
        if (arg0->unk0xC != 0) {
            node = GetChecksum_3(arg0->unk0xC, QB_ANIMBLENDER);
            vtbl = *(s32 *)((char *)node + 0x18);
            ((void (*)(void *, s32, void *, s32))*(s32 *)((char *)vtbl + 0x64))((char *)node + *(s16 *)((char *)vtbl + 0x60), QB_REMOVEANIMCONTROLLER, p, 0);
        }
        if (p != 0) {
            CStruct_delete(p, 3);
        }
        mgr = lbl_80301B48;
        ret = fn_800F2A48(mgr, arg0->unk0x1C, 0);
        if (ret != 0) {
            fn_800F28E4(mgr, ret);
        }
        arg0->unk0x1C = 0;
    }
}
