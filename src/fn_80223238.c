// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80223238-0x8022335C (292B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_8022AA50(Unk_A9157FE7 *);
void strncpy(void *, void *, s32);
void fn_801A4C68(Unk_31DE137E *, void *);
void fn_8021C4FC(CStruct *, Unk_A1F83658 *, s32);
void fn_8021FAB4(Unk_9994C3F5 *, s32, s32, char *, char *, s32, s32, s32, s32);
void fn_8022AABC(Unk_31DE137E *, s32);

bool fn_80223238(CScript *arg0) {
    struct ctx_t {
        u8 pad0;
        char name[0xF];
        u8 b10;
        u8 b11;
        u8 _12[2];
        s32 f14;
        u8 _18[4];
        s32 f1C;
        s32 f20;
        s32 _24;
        s32 f28;
        s32 f2C;
        s32 f30;
        s32 f34;
        s32 f38;
        s32 _3C;
        s32 f40;
    } c;
    s32 fab9;
    char *nm = c.name;
    void *obj = *(void **)arg0;
    void *mgr = *((void * *)&arg0->unk0x18);
    s32 temp;

    fn_8022AA50(&c);
    strncpy(nm, (char *)obj + 0x20, 0xF);
    c.b10 = 0;
    c.b11 = ((Unk_F0FD48D1 *)obj)->unk0x18;
    c.f14 = 0;
    temp = ((Unk_F0FD48D1 *)obj)->unk0x8;
    c.f20 = temp;
    c.f28 = ((Unk_F0FD48D1 *)obj)->unk0x19;
    c.f2C = *(s32 *)((char *)obj);
    c.f30 = ((Unk_F0FD48D1 *)obj)->unk0x4;
    c.f38 = ((Unk_F0FD48D1 *)obj)->unk0x14;
    c.f40 = ((Unk_F0FD48D1 *)obj)->unk0x1C;
    c.f34 = ((Unk_F0FD48D1 *)obj)->unk0xC;
    if ((temp & 5) == 0) {
        fn_801A4C68(c.f1C, (char *)obj + 0x30);
    }
    if (((Unk_C7387A53 *)mgr)->unk0x1B4 == 0) {
        fn_8021C4FC(mgr, &c, 0);
    } else {
        fn_8021FAB4(mgr, 0, (s32)0x640D3C87u, nm, 0, 0, 0, 0, 0x7D0);
        fn_8021C4FC(mgr, &c, 0xA);
    }
    fn_8022AABC(&c, 2);
    return true;
}
