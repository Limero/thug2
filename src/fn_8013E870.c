// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E870-0x8013EA38 (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8029F590[];
extern char lbl_8029F638[];
extern char lbl_8029F650[];
extern char lbl_8029F668[];
extern char lbl_8029F680[];
s32 Mem_Alloc(s32);
void fn_8013B6A0(CStruct *);
void fn_8013725C(Unk_1624B368 *);
s32 memset(void *, s32, s32);
void *fn_8013E870(Unk_A99C4F7E *arg0, s32 arg1) {
    volatile s32 sp8;
    Unk_4C649A8C *p18;
    Unk_4C649A8C *p30;
    Unk_4C649A8C *p2084;
    Unk_4C649A8C *p209c;
    Unk_4C649A8C *p4910;
    char *w;
    char *d1;
    s32 i;
    register s32 t1 __asm__("r0");
    register s32 t2 __asm__("r9");

    arg0->unk0x4 = -1;
    arg0->unk0x8 = 0;
    arg0->unk0xC = (s32)arg0;
    arg0->unk0x10 = (s32)arg0;
    arg0->unk0x14 = (s32)lbl_8029F680;
    p18 = (char *)arg0 + 0x18;
    p18->unk0x4 = -1;
    p18->unk0x8 = 0;
    ((Unk_41EA2015 *)p18)->unk0xC = (s32)p18;
    p18->unk0x10 = (s32)p18;
    p18->unk0x14 = (s32)lbl_8029F668;
    p30 = (char *)arg0 + 0x30;
    p30->unk0x14 = (s32)lbl_8029F650;
    p30->unk0x8 = 0;
    ((Unk_41EA2015 *)p30)->unk0xC = (s32)p30;
    p30->unk0x10 = (s32)p30;
    p30->unk0x4 = -1;
    arg0->unk0x68 = 0;
    arg0->unk0x6C = 0;
    w = (char *)arg0 + 0x884;
    for (i = 0; i < 0x100; i++) {
        ((Unk_4C649A8C *)w)->unk0x4 = -1;
        ((Unk_4C649A8C *)w)->unk0x8 = 0;
        ((Unk_41EA2015 *)w)->unk0xC = (s32)w;
        ((Unk_4C649A8C *)w)->unk0x10 = (s32)w;
        ((Unk_4C649A8C *)w)->unk0x14 = (s32)lbl_8029F650;
        w += 0x18;
    }
    p2084 = (char *)arg0 + 0x2084;
    p2084->unk0x4 = -1;
    p2084->unk0x8 = 0;
    ((Unk_41EA2015 *)p2084)->unk0xC = (s32)p2084;
    p2084->unk0x10 = (s32)p2084;
    p2084->unk0x14 = (s32)lbl_8029F638;
    p209c = (char *)arg0 + 0x209C;
    p209c->unk0x4 = -1;
    p209c->unk0x8 = 0;
    ((Unk_41EA2015 *)p209c)->unk0xC = (s32)p209c;
    p209c->unk0x10 = (s32)p209c;
    p209c->unk0x14 = (s32)lbl_8029F638;
    fn_8013B6A0((char *)arg0 + 0x20B4);
    fn_8013725C((char *)arg0 + 0x20EC);
    fn_8013725C((char *)arg0 + 0x34FC);
    p4910 = (char *)arg0 + 0x4910;
    p4910->unk0x14 = (s32)lbl_8029F590;
    p4910->unk0x4 = (s32)arg0;
    p4910->unk0x8 = 0;
    ((Unk_41EA2015 *)p4910)->unk0xC = (s32)p4910;
    p4910->unk0x10 = (s32)p4910;
    arg0->unk0x68 = 1;
    arg0->unk0x6C = arg1;
    sp8 = arg0->unk0x6C;
    t1 = Mem_Alloc(0xA28);
    arg0->unk0x5C = t1;
    *((s32 *)&arg0->unk0x60) = t1;
    t2 = Mem_Alloc(0x514);
    arg0->unk0x7C = 0;
    arg0->unk0x78 = 0;
    arg0->unk0x490C = 0;
    arg0->unk0x4928 = 0;
    arg0->unk0x4930 = 0;
    arg0->unk0x4934 = 0;
    arg0->unk0x880 = 0;
    arg0->unk0x4938 = 0x61A80;
    arg0->unk0x54 = t2;
    arg0->unk0x58 = t2;
    memset((char *)arg0 + 0x80, 0, 0x100);
    memset((char *)arg0 + 0x480, 0, 0x100);
    return arg0;
}
