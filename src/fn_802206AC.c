// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802206AC-0x8022082C (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad00[4];
    s32 f04;
    void *f08;
    s32 f0C;
} search_t;

typedef struct {
    u8 cmd;
    u16 len;
    void *data;
    s32 pad08;
    s32 f0C;
    u8 f10;
    char pad11[0x17];
} msg_t;

typedef struct {
    s32 out40;
    s32 out44;
    u16 pay;
} outs_t;

extern void fn_80137CB4(Unk_9F066EC1 *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_8021D358(s32, u16);
extern s32 fn_8021B554(Unk_9994C3F5 *);
extern s32 fn_8021D454(s32, CStruct *, s32);
extern s32 fn_8021D4E8(s32, CStruct *, s32);
extern s32 fn_8022986C(CScript *);
extern void *fn_8022A9B8(Unk_31DE137E *);
extern void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
extern void fn_8022A04C(CScript *, s32);
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];

bool ScriptPlayerTookFlag(CStruct *arg0) {
    search_t sr;
    msg_t msg;
    outs_t o;
    s32 mgr;
    s32 res;
    s32 walker;
    s32 t;
    u16 *pp;
    char *lblc;
    register search_t *srp __asm__("r26");
    register msg_t *mp __asm__("r24");
    register s32 mgrv __asm__("r29");
    search_t *s0;
    msg_t *m0;
    Unk_85F80354 *p40;
    Unk_1D62F22E *p44;

    lblc = (char *)lbl_802A83F8;
    s0 = &sr;
    s0 = &sr;
    s0->f04 = 0;
    s0->f08 = (void *)lblc;
    srp = s0;
    m0 = &msg;
    mgrv = lbl_80305F9C;
    fn_80137CB4(m0);
    mp = m0;
    p40 = &o.out40;
    GetInteger(arg0, QB_PLAYER, p40, 0);
    p44 = &o.out44;
    GetInteger(arg0, QB_FLAG_TEAM, p44, 0);
    res = fn_8021D358(mgrv, p40->unk0x2);
    if (res != 0)
        goto ok;
    srp->f08 = (void *)lblc;
    return true;
ok:
    o.pay = (*(u8 *)((char *)&o.pay + 1)) | ((((Unk_ECD1B899 *)p40)->unk0x3) << 8);
    pp = &o.pay;
    *(u16 *)pp = o.pay;
    o.pay = (o.pay & 0xFF00) | (p44->unk0x3);
    msg.data = pp;
    msg.len = 2;
    *(u16 *)pp = o.pay;
    msg.cmd = 0x71;
    msg.f0C = 2;
    msg.f10 = 8;
    t = fn_8021B554(mgrv);
    walker = fn_8021D454(mgrv, srp, 1);
    if (walker != 0) {
        do {
            if (fn_8022986C((void *)walker) != 0) {
                fn_8022A04C(res, o.out44);
            } else {
                fn_8013CC84(t, (s32)fn_8022A9B8((void *)walker), (s32)mp);
            }
            walker = fn_8021D4E8(mgrv, &sr, 1);
        } while (walker != 0);
    }
    srp->f08 = (void *)lbl_802A83F8;
    return true;
}
