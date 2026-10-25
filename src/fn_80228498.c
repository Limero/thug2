// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80228498-0x80228568 (208B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern char lbl_803A314C[];
extern char lbl_80305EAC[];
s32 fn_800145AC(void);
void fn_80174DB8(Unk_6BAF5070 *, s32);
s32 NextNewPlayerInfo(s32);
s32 fn_8022A510(void *, s32);
s32 fn_8021D454(s32, CStruct *, s32);
void fn_80229C38(CScript *);
s32 fn_8021D4E8(s32, CStruct *, s32);
void fn_80009C00(CStruct *);

void fn_80228498(Unk_C7387A53 *arg0) {
    s32 sp8[4];
    register s32 *it __asm__("r29");
    register s32 lblv __asm__("r30");
    register s32 obj __asm__("r31");
    s32 *p;
    register s32 page __asm__("r11");
    s32 z;

    __asm__ volatile("lis %0,%1@ha" : "=r"(page) : "s"(lbl_802A83F8));
    p = &sp8[0];
    obj = arg0->unk0x20;
    __asm__("" : "+r"(p));
    __asm__ volatile("li %0,0" : "=r"(z));
    __asm__ volatile("addi %0,%1,%2@l" : "=r"(lblv) : "r"(page), "s"(lbl_802A83F8));
    p[1] = z;
    it = p;
    __asm__("" : "+r"(p));
    p[2] = lblv;
    if ((u32)fn_800145AC() < *(u32 *)&lbl_803A314C) {
        it[2] = lblv;
        return;
    }
    fn_80174DB8(*(s32 *)&lbl_80305EAC, ((Unk_52F5DCA2 *)obj)->unk0x2C);
    {
        s32 t = NextNewPlayerInfo(obj);
        if (t != 0) {
            fn_8022A510(t, 0);
        }
    }
    {
        s32 var = fn_8021D454(obj, it, 1);
        while (var != 0) {
            fn_80229C38(var);
            var = fn_8021D4E8(obj, &sp8[0], 1);
        }
    }
    fn_80009C00(((Unk_52F5DCA2 *)obj)->unk0xF8);
    it[2] = (s32)lbl_802A83F8;
}
