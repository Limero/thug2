// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121900-0x80121A78 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

int OSPanic();
extern char lbl_8029DEB4[];
extern char lbl_8029DFD8[];
extern char lbl_8029E004[];
extern char lbl_8029E038[];
extern char lbl_8039BA58[];
s32 fn_80249898(void *);

typedef struct M121900 {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} M121900;

s32 fn_80121900(s32 arg0) {
    char *mgr;
    M121900 msg;
    s32 rc;
    s32 off;
    s32 *m;

    mgr = lbl_8039BA58;
    msg.unk0 = 0x28;
    msg.unk4 = *(u16 *)(mgr + 0x88);
    msg.unk6 = *(u16 *)(mgr + 0x8a);
    msg.unk8 = arg0 != 0;
    msg.unkC = *(s32 *)lbl_8039BA58;
    msg.unk10 = *(s32 *)(mgr + 4);
    msg.unk14 = *(s32 *)(mgr + 8);
    if (*(s32 *)(mgr + 0xa0) == 0x56415544) {
        if (*(s32 *)(mgr + 0x2bc) == 0) {
            OSPanic(lbl_8029DEB4, 0x151, lbl_8029DFD8);
        }
        if (*(s32 *)(mgr + 0xac) == 0) {
            OSPanic(lbl_8029DEB4, 0x152, lbl_8029E004);
        }
        if (*(s32 *)(mgr + 0xb0) == 0) {
            OSPanic(lbl_8029DEB4, 0x153, lbl_8029E038);
        }
        msg.unk8 |= 4;
        off = *(u8 *)(mgr + 0xa9) != 0 ? *(u16 *)(mgr + 0xaa) + 0x10 : 0x24;
        m = (s32 *)lbl_8039BA58;
        msg.unk20 = m[0x2bc / 4] + off;
        msg.unk24 = *(s32 *)(m[0x2bc / 4] + 4) - off;
        msg.unk18 = m[0xac / 4];
        msg.unk1C = m[0xb0 / 4];
    }
    rc = fn_80249898(&msg);
    *(s32 *)(lbl_8039BA58 + 0x398) = rc;
    return rc != 0;
}
