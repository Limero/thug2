// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802336D8-0x80233764 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029FD38[];
s32 fn_8009CFB8(s32);
void fn_80009C00(s32);
s32 fn_8000A578(s32, s32);
void fn_8009D020(void);
void fn_802336D8(s32 arg0, s32 arg1) {
    f64 dbl;
    s32 sp10;
    register s32 lblv __asm__("r26");
    register s32 mul __asm__("r27");
    register s32 obj __asm__("r28");
    register s32 v __asm__("r29");
    register s32 w __asm__("r30");

    lblv = (s32)lbl_8029FD38;
    __asm__("mr %0,%1" : "=&r"(mul) : "r"(arg1));
    w = arg0;
    ((Unk_59AB5482 *)&dbl)->unk0xC = lblv;
    mul = mul * 0x94;
    v = fn_8009CFB8(0);
    obj = ((Unk_C7387A53 *)w)->unk0x40;
    sp10 = v;
    fn_80009C00(obj);
    __asm__ __volatile__("");
    w = mul + 8;
    w = v + w;
    fn_8000A578(w + 4, obj);
    __asm__ __volatile__("");
    w = w + 0x50;
    v += 8;
    ((CScript *)obj)->unk0x1C = w;
    ((CScript *)obj)->unk0x20 = *(s32 *)((char *)v + mul);
    ((Unk_59AB5482 *)&dbl)->unk0xC = lblv;
    fn_8009D020();
    __asm__("" : : "m"(dbl), "m"(sp10));
}
