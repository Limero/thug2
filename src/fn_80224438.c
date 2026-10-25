// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224438-0x802245A4 (364B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_80305EAC;
void *fn_8021D2C4(void *, s32);
s32 fn_8022989C(CScript *);
s32 fn_8022986C(CScript *);
s32 fn_8021B6C8(Unk_C7387A53 *);
s32 fn_80219D34(void *);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void fn_8021DAD4(Unk_9994C3F5 *, CScript *, s32);
void fn_80173910(void *, Unk_9D99273B *);
s32 fn_80229884(CScript *);
void fn_80229B84(CScript *);
void fn_8021CDA0(Unk_9994C3F5 *);
void *fn_8021C9B8(CScript *);
void fn_8021CB74(CScript *, CScript *);

s32 fn_80224438(Unk_C8FEE62D *arg0) {
    struct frt {
        u8 cmd;
        u8 _p[0x27];
    } fr;
    s32 base = lbl_80305EAC;
    void *mgr = *((void * *)&arg0->unk0x18);
    void *entry = fn_8021D2C4(mgr, arg0->unk0x10);
    s32 chk;

    if (entry == NULL || fn_8022989C(entry) != 0) {
        return 4;
    }
    if (fn_8022986C(entry) == 0 && fn_8021B6C8(mgr) >= fn_80219D34(mgr)) {
        void *f10;
        fn_80137CB4(&fr);
        f10 = *((void * *)&arg0->unk0x10);
        fr.cmd = 0x4E;
        fn_8013CC84(((Unk_DAB252EF *)mgr)->unk0x8,
                    ((Unk_C7387A53 *)f10)->unk0x48,
                    &fr);
    } else {
        fn_80137CB4(&fr);
        chk = fn_8022986C(entry);
        if (chk == 0) {
            void *p18 = *((void * *)&((CScript *)entry)->unk0x18);
            s32 t;
            fn_8021DAD4(mgr, entry, 2);
            fn_80173910(base, p18);
            *((void * *)&((CScript *)entry)->unk0x18) = (void *)chk;
            ((CScript *)entry)->unk0x1D8 |= 4;
            if (fn_80229884(entry) != 0) {
                fn_80229B84(entry);
                fn_8021CDA0(mgr);
            }
            if (entry == ((Unk_DAB252EF *)mgr)->unk0x1F8) {
                t = (s32)fn_8021C9B8(mgr);
                ((Unk_DAB252EF *)mgr)->unk0x1F8 = (void *)t;
                if (entry == (void *)t) {
                    ((Unk_DAB252EF *)mgr)->unk0x1F8 = (void *)chk;
                }
                fn_8021CB74(mgr, ((Unk_DAB252EF *)mgr)->unk0x1F8);
            }
        }
        fr.cmd = 0x4D;
        fn_8013CC84(((Unk_DAB252EF *)mgr)->unk0x8,
                    ((Unk_C7387A53 *)arg0->unk0x10)->unk0x48,
                    &fr);
    }
    return 1;
}
