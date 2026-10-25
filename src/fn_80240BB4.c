// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240BB4-0x80240C7C (200B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802B0544;
extern f32 lbl_802B0548;
extern f32 lbl_802B054C;
extern f32 lbl_802B110C;
void fn_80240BB4(void *arg0, Unk_F96D0DC8 *arg1) {
    struct { f32 _f0; f32 _f1; f32 _f2; } sp8;
    register char *base __asm__("r11");
    Unk_F5317C5D *vt;
    s16 off;
    void (*fp)(void *, void *);
    f32 *p;
    f32 a;
    f32 b;
    f32 c;

    base = (char *)arg0;
    vt = ((Unk_1D62F22E_2 *)base)->unk0xC;
    off = vt->unk0x8;
    fp = (void (*)(void *, void *))vt->unk0xC;
    {
        void *this2 = base + off;
        fp(&sp8, this2);
    }
    a = (sp8._f0 + lbl_802B110C) / lbl_802B0544;
    p = (f32 *)&sp8;
    b = (p[1] + lbl_802B110C) / lbl_802B0548;
    c = (p[2] + lbl_802B110C) / lbl_802B054C;
    *((s8 *)&arg1->unk0x3) = (s8)a;
    *((s8 *)&arg1->unk0x4) = (s8)b;
    *((s8 *)&arg1->unk0x5) = (s8)c;
}
