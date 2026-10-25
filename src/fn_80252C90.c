// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80252C90-0x80252D7C (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8025462C(void *, void *);
void fn_80253FF4(void *);
s32 fn_80253BF0(void *, void *, void *);
void fn_8024EEC0(void *);
void fn_80253EA0(void *, void *);
void fn_80253054(void *, void *, void *);
s32 fn_80254720(void *);
s32 fn_80252EC8(void *, void *);
extern s32 lbl_803CA340;

bool fn_80252C90(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp8;
    char *p0c;
    char *p04;
    char *p30;

    p0c = arg0 + 0xC;
    p04 = arg0 + 4;
    fn_80254720(p0c);
    fn_80253054(p04, (void *)arg1, (void *)arg2);
    if ((fn_80252EC8(p04, &sp8) != 0) && (fn_8025462C(p0c, &sp8) == 0) &&
        (fn_80252EC8(p04, &sp8) != 0) && (fn_8025462C(p0c, &sp8) == 0)) {
        p30 = arg0 + 0x30;
        fn_80253EA0(p30, p0c);
        fn_80253BF0(p30, arg0 + 0x88, (void *)arg3);
        {
            s32 heap;
            heap = lbl_803CA340;
            fn_8024EEC0((void *)heap);
        }
        *(s32 *)arg0 = 1;
        return true;
    }
    fn_80253FF4(arg0 + 0xC);
    return false;
}
