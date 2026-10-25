// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012C48C-0x8012C678 (492B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80117E28(s32);
s32 fn_801266EC(Unk_5D1D68CC *);
u8 *fn_8012BFD8(CStruct *, void *, u8 *, CStruct *);
s32 fn_80127438(CStruct *, CStruct *);
s32 fn_80126FF4(Unk_80577C09 *, CStruct *);
u8 *fn_8012CBE8(u8 *);
u8 *fn_8012CD84(void);
void fn_8009F4C4(s32);
void *fn_801252BC(void);
u8 *fn_8012D62C(u8 *, CStruct *, CStruct *);
u8 *fn_8012C48C(CStruct *arg0, u8 *arg1, CStruct *arg2) {
    s32 sp8;
    register s32 v __asm__("r29");
    CStruct *obj;
    u8 *p = arg1 + 1;
    u8 *base;

    goto lbl_walk;

lbl_dispatch:
    switch (*p) {
    case 0x16:
        p = p + 1;
        fn_8012CB2C(&sp8, p);
        v = sp8;
        fn_8012CBE8(p + 4);
        p = fn_8012CD84();
        if (*p == 7) {
            fn_8012CBE8(p + 1);
            p = fn_8012CD84();
            if (*p == 0xE) {
                fn_8009F4C4(0x10);
                obj = fn_801252BC();
                p = fn_8012D62C(p, arg2, obj);
                if (obj->unk0x0 & 0x7F0000) {
                    obj->unk0x4 = v;
                    fn_80127438(arg0, obj);
                } else {
                    fn_80117E28(obj);
                }
                break;
            }
            p = fn_8012BFD8(arg0, v, p, arg2);
            break;
        }
        p = fn_8012BFD8(arg0, 0, base, arg2);
        break;
    case 3:
        p = fn_8012C48C(arg0, p, arg2);
        break;
    case 9:
        p++;
        break;
    case 1:
    case 2:
        p = fn_8012CBE8(p);
        break;
    default:
        if (*p == 0xE) {
            fn_8009F4C4(0x10);
            obj = fn_801252BC();
            p = fn_8012D62C(p, arg2, obj);
            if ((obj->unk0x0 & 0x7F0000) == 0xA0000) {
                fn_80126FF4(arg0, obj->unk0x8);
                fn_801266EC(obj);
                fn_80117E28(obj);
            } else if (obj->unk0x0 & 0x7F0000) {
                obj->unk0x4 = 0;
                fn_80127438(arg0, obj);
            } else {
                fn_80117E28(obj);
            }
        } else {
            p = fn_8012BFD8(arg0, 0, p, arg2);
        }
        break;
    }

lbl_walk:
    fn_8012CBE8(p);
    p = fn_8012CD84();
    base = p;
    if (*p == 4) {
        return p + 1;
    }
    goto lbl_dispatch;
}
