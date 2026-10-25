// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000F36C-0x8000F68C (800B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_802903D0[];
extern char lbl_802903E0[];
extern char lbl_802903EC[];
extern char lbl_802903FC[];
extern char lbl_80290408[];
extern char lbl_80290414[];
extern char lbl_80290428[];
extern char lbl_80290440[];
extern char lbl_8029044C[];
extern char lbl_80290458[];
extern char lbl_80290460[];
extern char lbl_80290468[];
extern char lbl_80290470[];
extern char lbl_80290478[];
extern char lbl_80290484[];
extern char lbl_80290490[];
extern char lbl_8029049C[];
extern char lbl_802904A8[];
extern char lbl_802904B4[];
extern char lbl_802904C0[];
extern char lbl_802904D4[];
extern char lbl_802904E4[];
extern char lbl_802904F4[];
extern char lbl_80290504[];
char *fn_800103C4(void *, u32);
char *fn_8000F36C(void *arg0, u32 arg1) {
    char *temp_r3;

    temp_r3 = fn_800103C4(arg0, arg1);
    if (temp_r3 != NULL) {
        return temp_r3 + 0xC;
    }
    switch (arg1) {
    case QB_BOTTOMUPHEAP:
        return lbl_802903D0;
    case QB_TOPDOWNHEAP:
        return lbl_802903E0;
    case QB_FRONTENDHEAP:
        return lbl_802903EC;
    case QB_NETWORKHEAP:
        return lbl_802903FC;
    case QB_NETMISCHEAP:
        return lbl_80290408;
    case QB_INTERNETTOPDOWNHEAP:
        return lbl_80290414;
    case QB_INTERNETBOTTOMUPHEAP:
        return lbl_80290428;
    case QB_SCRIPTHEAP:
        return lbl_80290440;
    case QB_DEBUGHEAP:
        return lbl_8029044C;
    case QB_UNKNOWN_0xC3909393:
        return lbl_80290458;
    case QB_UNKNOWN_0xB497A305:
        return lbl_80290460;
    case QB_UNKNOWN_0x2D9EF2BF:
        return lbl_80290468;
    case QB_UNKNOWN_0x5A99C229:
        return lbl_80290470;
    case QB_UNKNOWN_0x572A9F4C:
        return lbl_80290478;
    case QB_UNKNOWN_0x202DAFDA:
        return lbl_80290484;
    case QB_UNKNOWN_0xB924FE60:
        return lbl_80290490;
    case QB_UNKNOWN_0xCE23CEF6:
        return lbl_8029049C;
    case 0x08682D24:
        return lbl_802904A8;
    case QB_THEMEHEAP:
        return lbl_802904B4;
    case QB_UNKNOWN_0x7ED56B49:
        return lbl_802904C0;
    case QB_UNKNOWN_0x25D71469:
        return lbl_802904D4;
    case QB_VMHEAPBOTTOMUP:
        return lbl_802904E4;
    case QB_VMHEAPTOPDOWN:
        return lbl_802904F4;
    default:
        return lbl_80290504;
    }
}
