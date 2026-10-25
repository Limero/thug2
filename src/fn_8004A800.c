// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004A800-0x8004ADC8 (1480B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802FFE98[];
#include "qb_constants.h"
#include "structs.h"

void fn_8000F2F8(Unk_9F352E7C *, void *);
void fn_8000F320(Unk_F12C5E01 *);
void Mem_NewZero(s32);
void *fn_80041F08(void);
void *fn_800422E8(void);
void *fn_8004F108(void);
void *fn_8004F18C(void);
void *fn_80043A34(void);
void *fn_80044EA4(void);
void *fn_800454F4(void);
void *fn_80050068(void);
void *fn_800500F0(void);
void *fn_80045DC8(void);
void *fn_8004DC78(void);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void fn_8009E1F0(Unk_C8FEE62D *, void *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8004C458(void *, s32, s32);

void *fn_8004A800(CStruct *arg0, Unk_C7387A53 *arg1, s32 arg2, s32 arg3, CStruct *arg4) {
    struct { void *elem; s32 unk04; s32 unk08; } w;
    s32 sp18;
    u32 sw1v;
    u32 sw2v;
    s32 sp1C;
    s32 sp20;
    CStruct *p;
    register void *hp __asm__("r30");
    register s32 flag __asm__("r29");
    void *result;
    Unk_C7387A53 *g;
    register char *page __asm__("r11");
    register s32 var_r9 __asm__("r9");
    Unk_9994C3F5 *var_r11;
    Unk_89391A04 *temp_r9;
    void *e1;
    void *e2;

    p = &w;
    p->unk0x4 = 0;
    p->unk0x8 = 0;
    w.elem = NULL;
    sp1C = 0;
    flag = 0;
    hp = p;
    if (GetChecksum_2(arg4, QB_HEAP, &sp18, 0) != 0) {
        switch (sw1v = sp18) {
        case QB_TOPDOWN:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x118));
            break;
        case QB_BOTTOMUP:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x11C));
            break;
        case QB_SCRIPT:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x12C));
            break;
        case QB_NETWORK:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x134));
            break;
        case QB_UNKNOWN_0x03C84A59:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x180));
            break;
        case QB_DEBUG:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x178));
            break;
        case QB_SKATER:
        {
            s32 k, pp, zz, aa;
            __asm__("" : : "m"(sp1C));
            __asm__ volatile("lis %0,0x6e9c\n\t"
                             "addi %1,1,0x1c\n\t"
                             "ori %0,%0,0x34f7\n\t"
                             "li %2,0\n\t"
                             "mr %3,%5\n\t"
                             "li %4,1"
                             : "=&r"(k), "=&r"(pp), "=&r"(zz), "=&r"(aa), "=&r"(flag)
                             : "r"((s32)arg4));
            GetInteger((CStruct *)aa, k, (s32 *)pp, zz);
        }
            page = lbl_802FFE98;
            g = *(Unk_C7387A53 **)page;
            var_r9 = sp1C * 4;
            var_r11 = (char *)g + 0x1A4;
            goto block_31;
        case QB_SKATERINFO:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x5F8));
            break;
        case QB_UNKNOWN_0x39FB63CC:
        {
            s32 k, pp, zz, aa;
            __asm__("" : : "m"(sp1C));
            __asm__ volatile("lis %0,0x6e9c\n\t"
                             "addi %1,1,0x1c\n\t"
                             "ori %0,%0,0x34f7\n\t"
                             "li %2,0\n\t"
                             "mr %3,%5\n\t"
                             "li %4,1"
                             : "=&r"(k), "=&r"(pp), "=&r"(zz), "=&r"(aa), "=&r"(flag)
                             : "r"((s32)arg4));
            GetInteger((CStruct *)aa, k, (s32 *)pp, zz);
        }
            page = lbl_802FFE98;
            g = *(Unk_C7387A53 **)page;
            var_r9 = sp1C * 4;
            var_r11 = (char *)g + 0x1E4;
        block_31:
            fn_8000F2F8(g, *(s32 *)((char *)var_r11 + var_r9));
            break;
        case QB_DEFAULT:
            break;
        case QB_INTERNETTOPDOWN:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x144));
            break;
        case QB_INTERNETBOTTOMUP:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x148));
            break;
        default:
            flag = 1;
            fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x124));
            break;
        }
    } else {
        flag = 1;
        fn_8000F2F8(*(s32 *)lbl_802FFE98, *(s32 *)((char *)*(s32 *)lbl_802FFE98 + 0x124));
    }
    switch (sw2v = arg2) {
    case QB_CONTAINERELEMENT:
        Mem_NewZero(0x198);
        result = fn_80041F08();
        goto install;
    case QB_TEXTELEMENT:
        Mem_NewZero(0x1D0);
        result = fn_800422E8();
        goto install;
    case QB_VMENU:
        Mem_NewZero(0x1C8);
        result = fn_8004F108();
        goto install;
    case QB_HMENU:
        Mem_NewZero(0x1C8);
        result = fn_8004F18C();
        goto install;
    case QB_TEXTBLOCKELEMENT:
        Mem_NewZero(0x1E8);
        result = fn_80043A34();
        goto install;
    case QB_SPRITEELEMENT:
        Mem_NewZero(0x1A0);
        result = fn_80044EA4();
        goto install;
    case QB_UNKNOWN_0x118F6383:
        Mem_NewZero(0x198);
        result = fn_800454F4();
        goto install;
    case QB_VSCROLLINGMENU:
        Mem_NewZero(0x1E0);
        result = fn_80050068();
        goto install;
    case QB_HSCROLLINGMENU:
        Mem_NewZero(0x1E0);
        result = fn_800500F0();
        goto install;
    case QB_ELEMENT3D:
        Mem_NewZero(0x590);
        result = fn_80045DC8();
        goto install;
    install:
        if (w.elem != NULL) {
            CObject_RemoveRefLink(w.elem, hp);
            w.elem = NULL;
        }
        w.elem = result;
        if (result != NULL) {
            CObject_AddRefLink(result, hp);
        }
        break;
    case QB_WINDOWELEMENT:
        Mem_NewZero(0x198);
        result = fn_8004DC78();
        __asm__ volatile("");
        if (w.elem != NULL) {
            CObject_RemoveRefLink(w.elem, hp);
            w.elem = NULL;
        }
        w.elem = result;
        if (result != NULL) {
            CObject_AddRefLink(result, hp);
        }
        break;
    }
    fn_8009E1F0(w.elem, arg3);
    temp_r9 = arg1->unk0x2C;
    ((void (*)(void *, void *))temp_r9->unk0x14)((char *)arg1 + temp_r9->unk0x10, w.elem);
    var_r11 = w.elem;
    temp_r9 = var_r11->unk0x8;
    ((void (*)(void *, void *))temp_r9->unk0x14)((char *)var_r11 + temp_r9->unk0x10, arg4);
    var_r11 = w.elem;
    temp_r9 = var_r11->unk0x8;
    ((void (*)(void *, void *))temp_r9->unk0x54)((char *)var_r11 + temp_r9->unk0x50, arg4);
    sp20 = 0;
    if (GetInteger(arg4, QB_PRIORITY, &sp20, 0) != 0) {
        fn_8004C458(arg1, arg3, sp20);
    }
    if (flag != 0) {
        fn_8000F320(*(s32 *)lbl_802FFE98);
    }
    e1 = w.elem;
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    *(void **)arg0 = e1;
    if (e1 != NULL) {
        CObject_AddRefLink(e1, arg0);
    }
    e2 = w.elem;
    if (e2 != NULL) {
        CObject_RemoveRefLink(e2, hp);
        w.elem = NULL;
    }
    return arg0;
}
