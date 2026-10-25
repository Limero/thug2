// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062B28-0x80062BA8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
/* S62 = the 6 non-NUL bytes of the ".loc." constant, written as the retail
   4+2 store split.  A local typedef (not a shared Unk_ class) is right here:
   this is a string patch, not an object field layout. */
typedef struct { s32 unk0x0; u16 unk0x4; } S62;
extern char lbl_80293FC4[];     /* "." */
extern u32 lbl_80293FC8[];      /* ".loc." + 2 pad bytes (src/r2d_80293FC8.c) */
void strcpy(s32, s32);
s32 strstr(s32, s32);
s32 strcat(s32, s32);
s32 fn_8005570C(void);
void sGenerateCollisionFilename(s32 arg0, s32 arg1) {
    S62 *p;
    s32 v0;
    u16 v4;
    strcpy(arg0, arg1);
    p = (S62 *)strstr(arg0, (s32)lbl_80293FC4);
    if (p != NULL) {
        v0 = *(s32 *)&lbl_80293FC8;
        v4 = *(u16 *)((char *)&lbl_80293FC8 + 4);
        p->unk0x0 = v0;
        p->unk0x4 = v4;
    } else {
        strcat(arg0, (s32)&lbl_80293FC8);
    }
    strcat(arg0, fn_8005570C());
}
