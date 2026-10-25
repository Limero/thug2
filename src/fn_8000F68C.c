// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000F68C-0x8000F95C (720B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80010400(s32, s32, s32);
s32 *fn_800103C4(void *);
s32 fn_8000F68C(Unk_B0F19D72 *arg0, u32 arg1) {
    s32 *temp_r3;

    temp_r3 = fn_800103C4(arg0);
    if (temp_r3 != NULL) {
        return temp_r3[1];
    }
    switch (arg1) {
    case 0xC7800B0:
        return arg0->unk0x11C;
    case QB_TOPDOWNHEAP:
        return arg0->unk0x118;
    case QB_FRONTENDHEAP:
        return arg0->unk0x124;
    case QB_NETWORKHEAP:
        return arg0->unk0x134;
    case QB_NETMISCHEAP:
        return arg0->unk0x13C;
    case QB_INTERNETTOPDOWNHEAP:
        return arg0->unk0x144;
    case QB_INTERNETBOTTOMUPHEAP:
        return arg0->unk0x148;
    case QB_SCRIPTHEAP:
        return arg0->unk0x12C;
    case QB_DEBUGHEAP:
        return arg0->unk0x178;
    case QB_UNKNOWN_0xC3909393:
        return arg0->unk0x1A4;
    case QB_UNKNOWN_0xB497A305:
        return arg0->unk0x1A8;
    case QB_UNKNOWN_0x2D9EF2BF:
        return arg0->unk0x1AC;
    case QB_UNKNOWN_0x5A99C229:
        return arg0->unk0x1B0;
    case QB_UNKNOWN_0x572A9F4C:
        return arg0->unk0x1E4;
    case QB_UNKNOWN_0x202DAFDA:
        return arg0->unk0x1E8;
    case QB_UNKNOWN_0xB924FE60:
        return arg0->unk0x1EC;
    case QB_UNKNOWN_0xCE23CEF6:
        return arg0->unk0x1F0;
    case 0x08682D24:
        return arg0->unk0x5F8;
    case QB_THEMEHEAP:
        return arg0->unk0x600;
    case QB_UNKNOWN_0x7ED56B49:
        return arg0->unk0x154;
    case QB_UNKNOWN_0x25D71469:
        return arg0->unk0x150;
    case QB_VMHEAPBOTTOMUP:
        return arg0->unk0x164;
    case QB_VMHEAPTOPDOWN:
        return arg0->unk0x168;
    default:
        return fn_80010400(arg0, arg1, 0);
    }
}
