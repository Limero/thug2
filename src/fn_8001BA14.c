// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001BA14-0x8001BAEC (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8001CF80(void);
void fn_8001BAEC(void *);
void fn_8001BCA8(void);
void fn_8001BFA8(void);
void __hwInitVI(void);
void fn_8001CB60(void);
void fn_8001BA04(void);
void OSInit(void);
void DVDInit(void);
void VIInit(void);
void VIConfigure(s32);
s32 fn_8001FF14(void *, s32);
s32 OSCreateThread(void *, void *, void *, void *, u32, s32, s32);
s32 OSResumeThread(void *);
void fn_80269EC0(s32, s32, s32, s32);
void fn_80269EF8(s32, s32, s32, s32);
void OSSetResetCallback(void *);
extern s32 lbl_803613E0;
extern s32 lbl_803613E4;
extern char lbl_803213E0[];
extern char lbl_80361430[];
extern char lbl_80362748[];
void fn_8001BA14(void *arg0) {
    OSInit();
    DVDInit();
    VIInit();
    fn_8001CF80();
    fn_8001BAEC(arg0);
    fn_8001BCA8();
    VIConfigure(lbl_803613E4);
    lbl_803613E0 = fn_8001FF14(lbl_803213E0, 0x40000);
    fn_8001BFA8();
    __hwInitVI();
    OSCreateThread(lbl_80361430, fn_8001CB60, 0, lbl_80362748, 0x1000, 0x1F, 1);
    OSResumeThread(lbl_80361430);
    fn_80269EC0(6, 7, 6, 7);
    fn_80269EF8(0xE, 7, 0xE, 7);
    OSSetResetCallback(fn_8001BA04);
}
