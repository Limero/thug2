// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DD28-0x8001DFF4 (716B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void fn_8002321C(void);
extern void fn_80023278(void);
extern void fn_800232D4(void);
extern void fn_80023348(void);
extern void fn_800233BC(void);
extern void fn_80023460(void);
extern void fn_80023504(void);
extern void fn_800235AC(void);
extern void fn_80023638(void);
extern void fn_80023710(void);
extern void fn_8002381C(void);
extern void fn_80023988(void);
extern void fn_80023A84(void);
extern void fn_80023B88(void);
extern void fn_80023C8C(void);
extern void fn_80023D90(void);
extern void fn_8001DBC0(void);
extern void fn_8001DBCC(void);
extern void fn_8001DBD8(void);
extern void fn_8001DBE4(void);
extern void fn_8001DBF0(void);
extern void fn_8001DBFC(void);
extern void fn_8001DC08(void);
extern void fn_8001DC14(void);
extern void fn_8001DC30(void);
extern void fn_8001DC44(void);
extern void fn_8001DC5C(void);
extern void fn_8001DC7C(void);
extern void fn_8001DC98(void);
extern void fn_8001DCBC(void);
extern void fn_8001DCE0(void);
extern void fn_8001DD04(void);
extern s32 lbl_80300254;
extern s32 lbl_80300258;
extern bool lbl_8030025C;
typedef void (*fnptr)(void);
extern fnptr lbl_80300260;
extern fnptr lbl_80300264;
extern fnptr lbl_80300268;
extern fnptr lbl_8030026C;
extern fnptr lbl_80300270;
extern fnptr lbl_80300274;
extern fnptr lbl_80300278;
extern fnptr lbl_8030027C;
extern fnptr lbl_80300280;
extern fnptr lbl_80300284;
extern fnptr lbl_80300288;
extern fnptr lbl_8030028C;
extern fnptr lbl_80300290;
extern fnptr lbl_80300294;
extern fnptr lbl_80300298;
extern fnptr lbl_8030029C;
extern void *lbl_803CAF18;
extern char lbl_80362AC0[0x10];
void fn_8028D328(char *, s32, s32);
void fn_8001DD28(s32 arg0, s32 arg1) {
    s32 sp8;

    sp8 = arg0;
    if ((arg0 != 0) && (arg1 != 0)) {
        if (lbl_8030025C != 1) {
            lbl_80300260 = fn_8002321C;
            lbl_80300264 = fn_80023278;
            lbl_80300268 = fn_800232D4;
            lbl_8030026C = fn_80023348;
            lbl_80300270 = fn_800233BC;
            lbl_80300274 = fn_80023460;
            lbl_80300278 = fn_80023504;
            lbl_8030027C = fn_800235AC;
            lbl_80300280 = fn_80023638;
            lbl_80300284 = fn_80023710;
            lbl_80300288 = fn_8002381C;
            lbl_8030028C = fn_80023988;
            lbl_80300290 = fn_80023A84;
            lbl_80300294 = fn_80023B88;
            lbl_80300298 = fn_80023C8C;
            lbl_8030029C = fn_80023D90;
            lbl_8030025C = 1;
        }
        fn_8028D328(lbl_80362AC0, sp8, arg1);
        lbl_803CAF18 = lbl_80362AC0;
    } else if (lbl_8030025C != 0) {
        lbl_80300260 = fn_8001DBC0;
        lbl_80300264 = fn_8001DBCC;
        lbl_80300268 = fn_8001DBD8;
        lbl_8030026C = fn_8001DBE4;
        lbl_80300270 = fn_8001DBF0;
        lbl_80300274 = fn_8001DBFC;
        lbl_80300278 = fn_8001DC08;
        lbl_8030027C = fn_8001DC14;
        lbl_80300280 = fn_8001DC30;
        lbl_80300284 = fn_8001DC44;
        lbl_80300288 = fn_8001DC5C;
        lbl_8030028C = fn_8001DC7C;
        lbl_80300290 = fn_8001DC98;
        lbl_80300294 = fn_8001DCBC;
        lbl_80300298 = fn_8001DCE0;
        lbl_8030029C = fn_8001DD04;
        lbl_8030025C = 0;
    }
    lbl_80300254 = 0;
    lbl_80300258 = 0;
}
