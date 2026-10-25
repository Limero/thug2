// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023F980-0x8023FAC4 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
register s32 g31 __asm__("r31");
extern s32 lbl_802FFE98;
extern s32 lbl_80306084;
extern s32 lbl_80306088;
extern bool lbl_8030608C;
extern char lbl_802B0F4C[];
extern char lbl_802B0F5C[];
extern char lbl_802B0F68[];
extern char lbl_802B0F78[];
extern char lbl_802B0F88[];
void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
s32 Mem_NewZero(s32 arg0);
s32 fn_8001094C(Unk_C8FEE62D * arg0, s32 arg1);
s32 fn_8023FB5C(s32 arg0, s32 arg1);
s32 fn_8000F95C(Unk_FFAD6788 * arg0, void * arg1, void * arg2, void * arg3);
void fn_8024079C(s32 arg0, s32 arg1);
void fn_80240810(void);
void fn_80240814(s32 arg0, s32 arg1);
void fn_80240888(s32 arg0, s32 arg1);
void fn_8000F320(Unk_F12C5E01 * arg0);
void fn_80240614(void);
void fn_8023F980(s32 arg0) {
    char *pa;
    Unk_16E0D26E *pb;
    s32 temp_r0;
    register s32 temp_r3 __asm__("r3");
    s32 var_r5;

    if (arg0 == QB_REGULAR_PLAY) {
        pa = (char *)0x80300000;
        __asm__("" : "+r"(pa));
        pb = (char *)0x80300000;
        __asm__("" : "+r"(pb));
        fn_8000F2F8(*(s32 *)(pa - 0x168), *(s32 *)(*(s32 *)(pa - 0x168) + 0x118));
        temp_r0 = fn_8001094C(Mem_NewZero(0x1C), fn_8023FB5C((s32)lbl_802B0F4C, -1));
        temp_r3 = *(s32 *)(pa - 0x168);
        pb->unk0x6084 = temp_r0;
        lbl_80306088 = fn_8000F95C(temp_r3, temp_r0, (var_r5 = -1), (s32)lbl_802B0F5C);
    } else {
        pa = (char *)0x80300000;
        __asm__("" : "+r"(pa));
        pb = (char *)0x80300000;
        __asm__("" : "+r"(pb));
        fn_8000F2F8(*(s32 *)(pa - 0x168), *(s32 *)(*(s32 *)(pa - 0x168) + 0x11C));
        temp_r0 = fn_8001094C(Mem_NewZero(0x1C), fn_8023FB5C((s32)lbl_802B0F4C, -1));
        temp_r3 = *(s32 *)(pa - 0x168);
        pb->unk0x6084 = temp_r0;
        lbl_80306088 = fn_8000F95C(temp_r3, temp_r0, (var_r5 = 1), (s32)lbl_802B0F5C);
    }
    fn_8024079C(0x3E80, (s32)lbl_802B0F68);
    fn_80240810();
    fn_80240814(0x3E8, (s32)lbl_802B0F78);
    fn_80240888(6, (s32)lbl_802B0F88);
    fn_8000F320(lbl_802FFE98);
    lbl_8030608C = 0;
    fn_80240614();
}
