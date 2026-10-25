// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800242B8-0x80024344 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CObject_RemoveRefLink(void *, void *);
void fn_800242B8(Unk_C8FEE62D *arg0) {
    void *temp_r11;
    void *p;
    CStruct *vt;
    s16 off;
    s32 zero;
    void *t2;

    if (arg0->unk0x14 & 1) {
        temp_r11 = (void *)arg0->unk0x18;
        p = (char *)arg0 + 0x18;
        if (temp_r11 != NULL) {
            vt = (CStruct *)((Unk_9994C3F5 *)temp_r11)->unk0x8;
            off = *(s16 *)((char *)vt + 8);
            ((void (*)(void *, s32))*(void **)((char *)vt + 0xC))((char *)temp_r11 + off, 3);
        }
        t2 = (void *)arg0->unk0x18;
        zero = 0;
        if (t2 != NULL) {
            CObject_RemoveRefLink(t2, p);
            arg0->unk0x18 = zero;
        }
        arg0->unk0x18 = zero;
        arg0->unk0x14 = arg0->unk0x14 & ~1;
    }
}
