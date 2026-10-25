// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021BEE0-0x8021C080 (416B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_802FFE98;
extern s32 lbl_80303448;
extern s32 lbl_80305EAC;
extern char lbl_8029F480[];
extern char lbl_802AFE18[];
s32 fn_80137AD4(s32);
s32 fn_80174AB8(s32, s32);
s32 fn_8003AE20(s32);
s32 fn_8003EDD0(s32);
s32 fn_8003EA2C(s32, s32, s32);
s32 fn_80219698(s32);
void *NextItem(s32);
s32 fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
s32 fn_8021B55C(s32, s32);
s32 fn_8013E034(s32, void *);
s32 fn_8013FB8C(s32);
void fn_8013DDE4(s32, s32, s32, s32, s32, s32, s32, s32);

s32 fn_8021BEE0(s32 arg0) {
    s32 zPadA;
    s32 zPadB;
    s32 zPadC;
    s32 sp8;
    s32 temp_r28;
    CScript *temp_r30;
    s32 temp_r29;
    s32 var_r27;

    if (fn_80137AD4(lbl_80303448) == 1) {
        return 0;
    }
    var_r27 = 0;
    temp_r28 = fn_8003AE20(fn_80174AB8(lbl_80305EAC, 0) + 4);
    if ((temp_r28 != 0) && (fn_8003EDD0(temp_r28) != 0)) {
        if (fn_80219698(arg0) != 0) {
            temp_r30 = NextItem(arg0);
            fn_8000F2F8((void *)lbl_802FFE98, ((Unk_FFAD6788 *)lbl_802FFE98)->unk0x13C);
            temp_r30->unk0x1F0 = Mem_Alloc(0x4499);
            fn_8000F320((void *)lbl_802FFE98);
            *(u8 *)temp_r30->unk0x1F0 = var_r27;
            var_r27 = 1;
            fn_8003EA2C(temp_r28, temp_r30->unk0x1F0 + 1, 0x4498);
        } else {
            ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F480;
            ((Unk_59AB5482 *)&sp8)->unk0x4 = var_r27;
            if (fn_8013FB8C(fn_8013E034(fn_8021B55C(arg0, 0), (void *)&sp8)) == 0) {
                fn_8000F2F8((void *)lbl_802FFE98, ((Unk_FFAD6788 *)lbl_802FFE98)->unk0x134);
                temp_r29 = Mem_Alloc(0x4498);
                fn_8000F320((void *)lbl_802FFE98);
                fn_8003EA2C(temp_r28, temp_r29, 0x4498);
                fn_8013DDE4(fn_8021B55C(arg0, 0), 0x7E, 0x4498, temp_r29, (s32)lbl_802AFE18, 9, 0, 0);
                if (temp_r29 != NULL) {
                    Mem_Free2(temp_r29);
                }
                var_r27 = 1;
            }
            ((Unk_59AB5482 *)&sp8)->unk0x8 = (s32)lbl_8029F480;
        }
    }
    __asm__("" : : "m"(zPadA), "m"(zPadB), "m"(zPadC));
    return var_r27;
}
/* frame anchor */
