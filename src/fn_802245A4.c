// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802245A4-0x802246D4 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_80305EAC;
void *fn_8021D2C4(void *, s32);
s32 fn_8022986C(CScript *);
s32 fn_8022989C(CScript *);
void fn_8021DAD4(Unk_9994C3F5 *, CScript *, s32);
void fn_80173910(void *, Unk_9D99273B *);
void fn_8013E098(s32, s32);
void fn_8022AABC(Unk_31DE137E *, s32);

s32 fn_802245A4(Unk_C8FEE62D *arg0) {
    s32 base = lbl_80305EAC;
    void *mgr = *((void * *)&arg0->unk0x18);
    void *entry = fn_8021D2C4(mgr, arg0->unk0x10);

    if (entry != NULL) {
        void *p18;
        s32 chk;
        if (fn_8022986C(entry) != 0) {
            goto ret5;
        }
        p18 = *((void * *)&((CScript *)entry)->unk0x18);
        chk = fn_8022989C(entry);
        fn_8021DAD4(mgr, entry, 0);
        if (chk != 0) {
            goto ret5;
        }
        fn_80173910(base, p18);
    } else {
        void *head = *((void * *)&((Unk_C7387A53 *)mgr)->unk0x154);
        void *var;
        s32 sent;
        sent = ((CStruct *)head)->unk0x4;
        __asm__ volatile("mr %0,%1" : "=&r"(var) : "r"(head));
        if (sent == -1) {
            __asm__ volatile("li %0,0" : "=r"(var));
        }
        if (var != NULL) {
            for (;;) {
                register void *nxt __asm__("r9");
                s32 dat;
                s32 t;
                nxt = *((void * *)&((Unk_C8FEE62D *)var)->unk0xC);
                if (((CStruct *)nxt)->unk0x4 == -1) {
                    nxt = NULL;
                }
                dat = ((Unk_C8FEE62D *)var)->unk0x4;
                t = arg0->unk0x10;
                if (((Unk_C8FEE62D *)dat)->unk0x14 == t) {
                    void *vt;
                    fn_8013E098(arg0->unk0xC,
                                 ((Unk_C8FEE62D *)dat)->unk0x14);
                    if (var != NULL) {
                        vt = *((void * *)&((Unk_C8FEE62D *)var)->unk0x14);
                        ((void (*)(s32, s32)) ((Unk_F5317C5D *)vt)->unk0xC)(
                            (s32)var + ((Unk_F5317C5D *)vt)->unk0x8, 3);
                    }
                    if (dat != NULL) {
                        fn_8022AABC((void *)dat, 3);
                    }
                    goto ret5;
                }
                var = nxt;
                if (var == NULL) {
                    break;
                }
            }
        }
        return 2;
    }
ret5:
    return 5;
}
