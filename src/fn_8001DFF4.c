// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DFF4-0x8001E17C (392B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern bool lbl_8030025C;
extern s32 lbl_80300260;
extern s32 lbl_80300264;
extern s32 lbl_80300268;
extern s32 lbl_8030026C;
extern s32 lbl_80300270;
extern s32 lbl_80300274;
extern s32 lbl_80300278;
extern s32 lbl_8030027C;
extern s32 lbl_80300280;
extern s32 lbl_80300284;
extern s32 lbl_80300288;
extern s32 lbl_8030028C;
extern s32 lbl_80300290;
extern s32 lbl_80300294;
extern s32 lbl_80300298;
extern s32 lbl_8030029C;
extern void *lbl_803CAF18;
void fn_8028D36C(void);
void DBGFlushBuffer(void);
s32 fn_8001DBC0(s32);
s32 fn_8001DBCC(s32);
s32 fn_8001DBD8(s32);
s32 fn_8001DBE4(s32);
s32 fn_8001DBF0(s32);
s32 fn_8001DBFC(s32);
s32 fn_8001DC08(s32);
s32 fn_8001DC14(s32);
s32 fn_8001DC30(s32);
s32 fn_8001DC44(s32);
s32 fn_8001DC5C(s32);
s32 fn_8001DC7C(s32);
s32 fn_8001DC98(s32);
s32 fn_8001DCBC(s32);
s32 fn_8001DCE0(s32);
s32 fn_8001DD04(s32);
s32 fn_8001DFF4(void) {
    s32 *temp_r11;
    s32 var_r27;

    if (lbl_8030025C == 1) {
        fn_8028D36C();
        DBGFlushBuffer();
        temp_r11 = (s32 *)lbl_803CAF18;
        var_r27 = temp_r11[2] - temp_r11[0];
    } else {
        var_r27 = 0;
    }
    if (lbl_8030025C != 0) {
        lbl_80300260 = (s32)fn_8001DBC0;
        lbl_80300264 = (s32)fn_8001DBCC;
        lbl_80300268 = (s32)fn_8001DBD8;
        lbl_8030026C = (s32)fn_8001DBE4;
        lbl_80300270 = (s32)fn_8001DBF0;
        lbl_80300274 = (s32)fn_8001DBFC;
        lbl_80300278 = (s32)fn_8001DC08;
        lbl_8030027C = (s32)fn_8001DC14;
        lbl_80300280 = (s32)fn_8001DC30;
        lbl_80300284 = (s32)fn_8001DC44;
        lbl_80300288 = (s32)fn_8001DC5C;
        lbl_8030028C = (s32)fn_8001DC7C;
        lbl_80300290 = (s32)fn_8001DC98;
        lbl_80300294 = (s32)fn_8001DCBC;
        lbl_80300298 = (s32)fn_8001DCE0;
        lbl_8030029C = (s32)fn_8001DD04;
        lbl_8030025C = 0;
    }
    return var_r27;
}
