// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF844-0x800AF938 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_80129528(CStruct *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
extern f32 lbl_8029866C;

// File-local layout: the shared Unk_* classes mis-type the f32 slots around
// 0x34C4..0x34CC (0x3484 is read as f32 by the guard), which would drag in
// fctiwz/stw conversions and a phantom frame. True layout, absolute offsets.
typedef struct {
    char pad0x0[0x3484];
    f32 unk0x3484;
    char pad0x3488[0x38];
    CStruct *unk0x34C0;
    f32 unk0x34C4;
    f32 unk0x34C8;
    f32 unk0x34CC;
    u32 unk0x34D0;
} SubtitleT;

void fn_800AF844(SubtitleT *arg0) {
    f32 sp8;
    f32 padA;
    f32 padB;
    s32 handle;
    s32 idx;
    s32 nxt;
    s32 next;
    f32 old_cc;
    f32 zero;
    __asm__("" : : "m"(sp8), "m"(padA), "m"(padB));
    if (arg0->unk0x34C0 != NULL) {
        zero = lbl_8029866C;
        if (arg0->unk0x34CC >= zero) {
            if (arg0->unk0x3484 >= arg0->unk0x34CC) {
                handle = fn_80129528(arg0->unk0x34C0, arg0->unk0x34D0);
                arg0->unk0x34C4 = zero;
                GetFloat((CStruct *)handle, QB_DURATION, &arg0->unk0x34C4, 0);
                Script_RunScript(QB_CUTSCENE_SUBTITLE_CREATE, handle, 0, 0, 0);
                idx = arg0->unk0x34D0;
                old_cc = arg0->unk0x34CC;
                arg0->unk0x34CC = -1.0f;
                arg0->unk0x34C8 = old_cc;
                nxt = idx + 1;
                arg0->unk0x34D0 = nxt;
                if ((u32)nxt < (u32)((CStruct *)arg0->unk0x34C0)->unk0x4) {
                    next = fn_80129528(arg0->unk0x34C0, nxt);
                    GetFloat((CStruct *)next, QB_TIME, &sp8, 1);
                    arg0->unk0x34CC = sp8;
                }
            }
        }
    }
}
