// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80223394-0x80223448 (180B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_80305EAC;
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8022019C(CScript *, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
s32 fn_80219698(CStruct *);
void *fn_8021B55C(void *, s32);
void fn_8017D524(Unk_C7387A53 *, void *, s32);

bool fn_80223394(Unk_C8FEE62D *arg0) {
    struct frt {
        u8 cmd;
        u8 _p[0xB];
        s32 f14;
        s8 f18;
        u8 _tail[0x10];
    } fr;
    s32 base = lbl_80305EAC;
    void *mgr;
    fn_80137CB4(&fr);
    mgr = *((void * *)&arg0->unk0x18);
    fn_8022019C(mgr, 5);
    fr.cmd = 0x54;
    fr.f14 = 2;
    fr.f18 = 8;
    fn_8013DE78(*((void * *)&arg0->unk0xC), &fr);
    if (fn_80219698(mgr) == 0) {
        s32 i;
        for (i = 0; i <= 1; i++) {
            void *entry = fn_8021B55C(mgr, i);
            if (entry != NULL) {
                fn_8017D524(base, entry, i);
            }
        }
    }
    return true;
}
