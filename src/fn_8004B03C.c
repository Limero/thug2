// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004B03C-0x8004B0E8 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80301A78[];
void *fn_800A5308(s32, s32);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

// GetElement_2 @ 0x8004B03C
void *GetElement_2(CStruct *arg0, s32 arg2, s32 arg1, s32 arg3) {
    struct { void *f0; s32 f4; s32 f8; } sp8;
    void *temp_r3;

    temp_r3 = fn_800A5308(*(s32 *)lbl_80301A78, arg1);
    if (temp_r3 != NULL) {
        struct { void *f0; s32 f4; s32 f8; } *p30 = &sp8;
        void *t2;
        p30->f4 = 0;
        p30->f8 = 0;
        sp8.f0 = temp_r3;
        CObject_AddRefLink(temp_r3, (Unk_9994C3F5 *)p30);
        t2 = sp8.f0;
        arg0->unk0x4 = 0;
        arg0->unk0x8 = 0;
        arg0->unk0x0 = t2;
        if (t2 != NULL) {
            CObject_AddRefLink(t2, (Unk_9994C3F5 *)arg0);
        }
        t2 = sp8.f0;
        if (t2 != NULL) {
            CObject_RemoveRefLink(t2, (CStruct *)p30);
            sp8.f0 = NULL;
        }
    } else {
        arg0->unk0x4 = temp_r3;
        arg0->unk0x8 = temp_r3;
        arg0->unk0x0 = temp_r3;
    }
    return arg0;
}
