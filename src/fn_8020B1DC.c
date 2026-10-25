// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020B1DC-0x8020B280 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8020B1DC(CScript *arg0, Unk_F5317C5D *arg1, void *arg2, void *arg3) {
    register s32 temp_r10 __asm__("r10");
    register s32 entry __asm__("r11");
    register s32 (*fnptr)() __asm__("r9");
    char *p;
    Unk_E71E4713 *temp_r9;
    s16 off8;
    register s32 off __asm__("r0");

    temp_r10 = arg1->unk0xA;
    if (temp_r10 != 0) {
        if (temp_r10 >= 0) {
            register s32 base __asm__("r11");
            register s32 fntmp __asm__("r12");
            register char *pw __asm__("r9");

            base = *(s32 *)((char *)arg0 + (s32)(*((s16 *)&arg1->unk0xC)));
            pw = (char *)((temp_r10 << 3) + base);
            entry = *(s32 *)(pw - 8);
            __asm__ volatile("" : "+r"(entry));
            fntmp = *(s32 *)(pw - 4);
            __asm__ volatile("mr %0,%1" : "=r"(fnptr) : "r"(fntmp));
        } else {
            fnptr = (s32 (*)()) arg1->unk0xC;
        }
        off8 = arg1->unk0x8;
        if (temp_r10 >= 0) {
            off = (entry >> 0x10) + off8;
        } else {
            off = off8;
        }
        return ((s32 (*)(void *, void *, void *))fnptr)((char *)arg0 + off, arg2, arg3);
    }
    temp_r9 = *((void * *)&arg0->unk0x18);
    return ((s32 (*)(void *, void *, void *, void *)) temp_r9->unk0x64)(
        (char *)arg0 + temp_r9->unk0x60, *(void **)arg1, arg2, arg3);
}
