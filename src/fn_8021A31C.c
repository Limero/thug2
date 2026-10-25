// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A31C-0x8021A784 (1128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303148;
extern s32 lbl_80303448;
extern char lbl_802AFDE8[];
s32 fn_80136FA0(Unk_F386DC9F * arg0, s32 arg1, char * arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_802195C4(Unk_C7387A53 * arg0, s32 arg1);
void fn_8000A578(s32 arg0, s32 arg1);
void *fn_80139510(s32 arg0, s32 arg1, Unk_C8FEE62D * arg2, s32 arg3, s32 arg4, s32 arg5);
void fn_8021EB8C(Unk_C7387A53 * arg0);
s32 fn_80223FA0(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80226F54(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802241F0(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80223C68(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802245A4(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80224438(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80223C14(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80223448(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80224E28(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80227024(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8022527C(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802273FC(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802261D8(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80227794(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80227D64(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802263BC(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8022640C(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802281C4(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802282B8(s32 arg0, s32 arg1, s32 arg2);
s32 fn_802281CC(s32 arg0, s32 arg1, s32 arg2);

s32 fn_8021A31C(Unk_F1892E68 *arg0, s32 arg1, s32 arg2) {
    s32 var_r9;
    s32 mgr;
    s32 glob;

    glob = lbl_80303448;
    mgr = lbl_80303148;
    var_r9 = 0x15;
    if (arg1 != 0) {
        var_r9 = 0x1D;
    }
    if (arg2 != 0) {
        var_r9 |= 0x20;
    }
    arg0->unk0x8 = fn_80136FA0(glob, 0, (s32)lbl_802AFDE8, 0x14, 0x141E, 0, var_r9);
    fn_802195C4(arg0, 0);
    if (arg0->unk0x8 != 0) {
        fn_8000A578(mgr + 8, arg0->unk0xD8);
        fn_80139510(arg0->unk0x8 + 4, 3, (s32)fn_80223FA0, 3, (s32)arg0, 0);
        fn_80139510(arg0->unk0x8 + 4, 0x90, (s32)fn_80226F54, 0, (s32)arg0, 0xFF);
        fn_80139510(arg0->unk0x8 + 4, 0x50, (s32)fn_802241F0, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x11, (s32)fn_80223C68, 3, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0xB, (s32)fn_802245A4, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x4A, (s32)fn_80224438, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x26, (s32)fn_80223C14, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x54, (s32)fn_80223448, 0, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x57, (s32)fn_80224E28, 0, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x59, (s32)fn_80227024, 0, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x60, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x61, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x62, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x63, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x64, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x65, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x66, (s32)fn_8022527C, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x67, (s32)fn_802273FC, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x6B, (s32)fn_802261D8, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x6E, (s32)fn_80227794, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x6F, (s32)fn_80227D64, 2, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x6C, (s32)fn_802263BC, 0, (s32)arg0, 0xFF);
        fn_80139510(arg0->unk0x8 + 4, 0x88, (s32)fn_8022640C, 0, (s32)arg0, 0xFF);
        fn_80139510(arg0->unk0x8 + 4, 0x7D, (s32)fn_802281C4, 0, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x81, (s32)fn_802282B8, 0, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x8B, (s32)fn_802281CC, 0, (s32)arg0, 0x80);
        fn_80139510(arg0->unk0x8 + 4, 0x8A, (s32)fn_802281CC, 0, (s32)arg0, 0x80);
        arg0->unk0x1B8 = 0;
        arg0->unk0x1E0 = 0;
        fn_8021EB8C(arg0);
        arg0->unk0x108 = 0;
    }
    return arg0->unk0x8;
}
