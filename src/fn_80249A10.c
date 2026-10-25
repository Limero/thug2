// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80249A10-0x80249B70 (352B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"
#include "structs.h"

typedef struct CFontSub_80249A10 {
    char pad0x0[0x10];
    void *unk0x10;
    void *unk0x14;
} CFontSub_80249A10;

typedef struct CFont_80249A10 {
    char pad0x0[0xC];
    void *unk0xC;
    void *unk0x10;
    void *unk0x14;
    void *unk0x18;
    void *unk0x1C;
    void *unk0x20;
    void *unk0x24;
    void *unk0x28;
    void *unk0x2C;
    char pad0x30[0x18];
    CFontSub_80249A10 sub0x48;
    char pad0x60[0xAC];
    void *unk0x10C;
    void *unk0x110;
} CFont_80249A10;

typedef void (*hook_t)(void *);
extern hook_t lbl_803CA324;
extern s32 lbl_803CA328;
extern void fn_8024C474(void *, s32);
extern void fn_8024C5E8(void);
extern void fn_8024D390(CFontSub_80249A10 *, s32);
extern void fn_8028E008(void *);

void fn_80249A10(CFont_80249A10 *arg0, s32 arg1) {
    s32 flag;
    if (arg0->unk0xC != NULL) {
        fn_8024C474(arg0->unk0xC, 3);
    }
    if (arg0->unk0x10 != NULL) {
        fn_8024C474(arg0->unk0x10, 3);
    }
    if (arg0->unk0x14 != NULL) {
        fn_8024C474(arg0->unk0x14, 3);
    }
    if (arg0->unk0x18 != NULL) {
        fn_8024C474(arg0->unk0x18, 3);
    }
    if (arg0->unk0x1C != NULL) {
        fn_8024C474(arg0->unk0x1C, 3);
    }
    if (arg0->unk0x20 != NULL) {
        fn_8024C474(arg0->unk0x20, 3);
    }
    flag = 1;
    if (lbl_803CA328 == 0) {
        flag = 0;
    }
    if (flag == 0) {
        if (arg0->unk0x10C != NULL) {
            lbl_803CA324(arg0->unk0x10C);
        }
        if (arg0->unk0x110 != NULL) {
            lbl_803CA324(arg0->unk0x110);
        }
    }
    if (arg0->unk0x24 != NULL) {
        lbl_803CA324(arg0->unk0x24);
    }
    if (arg0->unk0x28 != NULL) {
        lbl_803CA324(arg0->unk0x28);
    }
    if (arg0->unk0x2C != NULL) {
        fn_8028E008(arg0->unk0x2C);
    }
    fn_8024C5E8();
    fn_8024D390(&arg0->sub0x48, 2);
    if ((arg1 & 1) && (arg0 != NULL)) {
        lbl_803CA324(arg0);
    }
}
