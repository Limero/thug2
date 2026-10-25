// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021C080-0x8021C1B4 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern char lbl_802AFE18[];
extern char lbl_80303448[];
s32 fn_80137AD4(Unk_F386DC9F *);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_8013FB8C(Unk_72BBAD33 *);
s32 fn_80229718(CScript *);
s32 fn_8022986C(CScript *);
s32 fn_8021BEE0(void *);
void fn_8013DA08(s32, Unk_1EE3EA6A *, s32, s32, void *, char *, s32, s32, s32);

void fn_8021C080(Unk_9994C3F5 *arg0, Unk_31DE137E *arg1) {
    struct {
        s32 it0;
        s32 it4;
        s32 it8;
    } fr;
    register s32 *itv __asm__("r9");
    register s32 *it __asm__("r27");
    s32 entry;
    s32 var_r30;
    s32 temp_r7;
    s32 hookv;
    char *hop;
    register s32 mgr __asm__("r3");

    hookv = (s32)lbl_802A83F8;
    mgr = *(s32 *)lbl_80303448;
    itv = &fr.it0;
    itv[2] = hookv;
    itv[1] = 0;
    hop = (char *)itv;
    it = (s32 *)hop;
    if (fn_80137AD4(mgr) == 1) {
        it[2] = hookv;
        return;
    }
    entry = fn_8021D454((s32)arg0, it, 0);
    if (entry != 0) {
        do {
            if (entry != arg1) {
                if (fn_8013FB8C(arg1->unk0x1C) != 1) {
                    var_r30 = 0;
                    if (fn_80229718(entry) != 0) {
                        var_r30 = 1;
                    } else if (fn_8022986C(entry) != 0) {
                        var_r30 = fn_8021BEE0(arg0);
                    }
                    if (var_r30 != 0) {
                        temp_r7 = fn_80229718(entry);
                        fn_8013DA08(arg0->unk0x8,
                                    arg1->unk0x1C, 0x7E, 0x4499,
                                    temp_r7, (s32)lbl_802AFE18, 9, 0, 1);
                    }
                }
            }
            entry = fn_8021D4E8((s32)arg0, &fr.it0, 0);
        } while (entry != 0);
    }
    it[2] = (s32)lbl_802A83F8;
}

// STATUS 2026-10-03: MATCHES (masked 100.00, size exact, REL14/REL24 + lis/addi verified).
