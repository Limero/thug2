// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80220060-0x8022019C (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
void fn_80137CB4(void *);
void *NextItem(void *);
s32 fn_8022989C(void *);
void fn_8013DE78(void *, void *);
void *CStruct_new(s32);
void *CStruct_ctor(void *);
void AddString(void *, s32, char *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(void *, s32);
#include "qb_constants.h"

extern char lbl_802AFE7C[];

/* the 0x11-byte message struct built at r1+0x1A0 and passed to fn_8013DE78 */
typedef struct Msg_s {
    s8    f00;        /* +0x00 = 0x4C, message type   (stb) */
    char  _p01[0x1];
    s16   f02;        /* +0x02 = strlen(name) + 0x12  (sth) */
    void *f04;        /* +0x04 = &fr.sp8 (owner/parent) */
    char  _p08[0x4];
    s32   f0C;        /* +0x0C = 2                   (stw) */
    s8    f10;        /* +0x10 = 8                   (stb) */
    char  _p11[0x7];
} Msg_t;

/* arg0: QB context, +0xC is the script manager handle */
typedef struct Ctx_s {
    char  _00[0xC];
    void *p0C;
} Ctx_t;

/* the NextItem() entry: +0x18 -> ->0x18, +0x3C is the entry name string */
typedef struct Ent_s {
    char  _00[0x18];
    void *p18;
    char  _1C[0x20];
} Ent_t;

/* one frame struct so every local lands on its retail r1 offset
 * (r1+0x08 sp8 .. r1+0x1B0 m.f10, locals region 0x1C4) */
typedef struct Fr_s {
    s8    sp8;         /* r1+0x08 */
    char  sp9[0x10];   /* r1+0x09  strcpy #1 dst */
    char  sp19[0x87];  /* r1+0x19  strcpy #2 dst */
    char  spA0[0x100]; /* r1+0xA0  sprintf buffer */
    Msg_t m;           /* r1+0x1A0 fn_8013DE78 arg */
    char  pad[0x0B];
} Fr_t;

void fn_80220060(Ctx_t *arg0, u8 *arg1) {
    Fr_t   fr;
    Msg_t *m;
    Ent_t *r29;
    void  *r31;
    char  *sp;
    s32    var_r0;

    { register Msg_t *q __asm__("r3"); __asm__("addi %0,1,0x1a0" : "=r"(q)); m = q; fn_80137CB4(q); }
    if ((s32)*arg1 != 0) {
        r29 = NextItem(arg0);
        { register char *d; __asm__ volatile("addi %0,1,9" : "=r"(d)); strcpy(d, (char *)r29 + 0x3C); }
        strcpy(fr.sp19, arg1);
        if (fn_8022989C(r29) != 0) {
            var_r0 = 8;
        } else {
            var_r0 = *(s32 *)((char *)r29->p18 + 0x18);
        }
        fr.sp8 = (s8)var_r0;
        { register char *q; __asm__ volatile("addi %0,1,0xa0" : "=r"(q)); sp = q; }
        { register s32 q; __asm__ volatile("addi %0,%1,0x12" : "=r"(q) : "r"(strlen(arg1))); fr.m.f02 = (s16)q; }
        { register s32 t4 __asm__("r0"); t4 = (s32)&fr.sp8; fr.m.f04 = (void *)t4; }
        fr.m.f00 = 0x4C;
        fr.m.f0C = 2;
        fr.m.f10 = 8;
        fn_8013DE78(arg0->p0C, m);
        r31 = CStruct_ctor(CStruct_new(8));
        sprintf(sp, (s32)lbl_802AFE7C, (char *)r29 + 0x3C, arg1);
        AddString(r31, QB_TEXT, sp);
        Script_RunScript(QB_CREATE_CONSOLE_MESSAGE, r31, 0, 0, 0);
        if (r31 != 0) {
            CStruct_delete(r31, 3);
        }
    }
}
