// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801309EC-0x80130C4C (608B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_803032D4;
void fn_8012F948(void *);
u8 *fn_8012CD84(u8 *);
u8 *fn_8012DC0C(s32, u8 *, s32);
void CStruct_dtor(void *);
void fn_80130250(void *);
void fn_801302F0(void *);
void fn_801303B4(void *);
void fn_80130598(void *);
void fn_801306F4(void *);
void fn_801307E0(void *);
u32 fn_80130898(void *, void *);
void fn_801321B8(void *);
void fn_8012FDC0(void *);
s32 fn_801309EC(u8 *arg0) {
    u8 *p;
    register u32 f __asm__("r0");
    register s32 v __asm__("r11");

    *(u32 *)((char *)arg0 + 0xB4) &= 0xBFFFFFFF;
    for (;;) {
        p = *(u8 **)((char *)arg0 + 0x10);
        if (p == NULL) {
            f = *(u32 *)((char *)arg0 + 0xB4);
            lbl_803032D4 = NULL;
            *(u32 *)((char *)arg0 + 0xB4) = f & 0x7FFFFFFF;
            return 0;
        }
        f = *(u32 *)((char *)arg0 + 0xB4);
        lbl_803032D4 = arg0;
        if (!(f & 0x40000000)) {
            fn_8012F948(arg0);
        }
        v = *(s32 *)((char *)arg0 + 0xA4);
        if (v != 0) {
            f = *(u32 *)((char *)arg0 + 0xB4);
            lbl_803032D4 = NULL;
            v -= 3;
            *(u32 *)((char *)arg0 + 0xB4) = (f & 0x7FFFFFFF) | 0x40000000;
            if ((u32)v <= 1) {
                return 1;
            }
            return 2;
        }
        p = *(u8 **)((char *)arg0 + 0x10);
        switch (*p) {
        case 0x47:
            fn_80130250(arg0);
            break;
        case 0x48:
            fn_801302F0(arg0);
            break;
        case 0x3c:
            fn_801303B4(arg0);
            break;
        case 0x20:
            fn_80130598(arg0);
            break;
        case 0x21:
            fn_801306F4(arg0);
            break;
        case 0x22:
            fn_801307E0(arg0);
            break;
        case 0x24:
            fn_801321B8(arg0);
            if (fn_80130898(arg0, NULL) != 0) {
                return 5;
            }
            break;
        case 0x29:
            fn_801321B8(arg0);
            *(u8 **)((char *)arg0 + 0x10) = *(u8 **)((char *)arg0 + 0x10) + 1;
            CStruct_dtor(*(s32 *)((char *)arg0 + 0x14));
            *(u8 **)((char *)arg0 + 0x10) = fn_8012DC0C(*(s32 *)((char *)arg0 + 0x14),
                                                         *(u8 **)((char *)arg0 + 0x10),
                                                         *(s32 *)((char *)arg0 + 0x18));
            if (fn_80130898(arg0, *(void **)((char *)arg0 + 0x14)) != 0) {
                return 5;
            }
            break;
        case 0x2e:
        case 0x2f:
        case 0x37:
        case 0x40:
        case 0x41:
        case 0x49:
            *(u8 **)((char *)arg0 + 0x10) = fn_8012CD84(*(u8 **)((char *)arg0 + 0x10));
            break;
        case 0x25:
        case 0x26:
            break;
        case 0x3e:
        case 0x3f:
            break;
        case 1:
            *(u8 **)((char *)arg0 + 0x10) = p + 1;
            break;
        case 0x28:
            *(u8 **)((char *)arg0 + 0x10) = p + 1;
            break;
        case 0x3d:
            *(u8 **)((char *)arg0 + 0x10) = p + 1;
            break;
        case 2:
            *(u8 **)((char *)arg0 + 0x10) = p + 5;
            break;
        default:
            fn_8012FDC0(arg0);
            break;
        }
    }
}
