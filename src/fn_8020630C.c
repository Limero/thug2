// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020630C-0x802063D0 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005CC88(void *, void *);
s32 fn_8005C580(s32);
s32 fn_8005C6C0(CStruct *, void *);
void fn_8005C5B4(void);
void fn_8006C780(void);
s32 fn_8009F558(void *, s32);
extern void * lbl_80366478;
extern char lbl_802AF278[];
void fn_8020630C(CScript *arg0, s32 arg1) {
    register s32 t20 __asm__("r3");
    register s32 t24 __asm__("r3");
    arg0->unk0x18 = (s32)lbl_802AF278;
    t20 = arg0->unk0x20;
    if (t20 != 0) {
        fn_8005C5B4();
        fn_8006C780();
        fn_8005C6C0((CStruct *)arg0->unk0x20, 0);
        fn_8005C580(arg0->unk0x20);
        fn_8005CC88(lbl_80366478, arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
    t24 = arg0->unk0x24;
    if (t24 != 0) {
        fn_8005C5B4();
        fn_8006C780();
        fn_8005C6C0((CStruct *)arg0->unk0x24, 0);
        fn_8005C580(arg0->unk0x24);
        fn_8005CC88(lbl_80366478, arg0->unk0x24);
        arg0->unk0x24 = 0;
    }
    fn_8009F558(arg0, arg1);
}
