// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80075854-0x80075970 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* The global screen/video setup record initialised here (handle fields
 * 0x14 / 0x1C are resource handles, 0x00/0x04 are the same handle, the
 * 0x10 / 0x08 / 0x24 / 0x28 slots are derived widths and counts). */
typedef struct ScreenSetup {
    s32 unk0x00;
    s32 unk0x04;
    s32 unk0x08;
    char pad0x0C[4];
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    char pad0x20[4];
    s32 unk0x24;
    s32 unk0x28;
} ScreenSetup;

void Script_RunScript(void *, void *, void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_80016DBC(s32, s32, s32);
s32 fn_80016D58(s32, s32, s32);
void fn_800953CC(void);
void fn_8006A1DC(CScript *);
s32 fn_80091440(void *);
s32 fn_800726BC(void *);
extern char lbl_80300450[];
extern s32 lbl_80300454;
extern s32 lbl_80300458;
extern s32 lbl_803016D4;
extern bool lbl_8037B798;
extern char lbl_80296FB8[];
extern ScreenSetup lbl_803016D8;
s32 Mem_Alloc2(s32);
void fn_80075854(void) {
    s32 width, handle, count, desc;
    CScript *obj;
    void *buf;
    void **d50, **d54, **d58;
    ScreenSetup *sp = &lbl_803016D8;
    d50 = (void **)&lbl_80300450;
    fn_800953CC();
    obj = Mem_Alloc2(0x20);
    fn_8006A1DC(obj);
    *d50 = obj;
    desc = (s32)lbl_80296FB8;
    handle = fn_80016DBC(0, 4, (obj->unk0x18 = desc, 1));
    sp->unk0x00 = handle;
    sp->unk0x04 = handle;
    sp->unk0x14 = handle;
    sp->unk0x10 = sp->unk0x14 + fn_80016D58(5, 4, 0);
    width = sp->unk0x10 + fn_80016D58(4, 4, 0);
    count = sp->unk0x00;
    sp->unk0x1C = width;
    sp->unk0x08 = count;
    sp->unk0x24 = count;
    sp->unk0x28 = count;
    lbl_803016D4 = sp->unk0x04;
    if (lbl_8037B798 != 0) {
        Script_RunScript(QB_SCREEN_SETUP_WIDESCREEN, 0, 0, 0, 0);
    }
    d54 = (void **)&lbl_80300454;
    d58 = (void **)&lbl_80300458;
    buf = Mem_Alloc2(0x12B0);
    *d54 = (void *)fn_80091440(buf);
    buf = Mem_Alloc2(8);
    *d58 = (void *)fn_800726BC(buf);
}
