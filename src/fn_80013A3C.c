// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013A3C-0x80013AF0 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFF18[];
extern char lbl_802FFF20[];
extern char lbl_803C9C78[];
void fn_8001515C(void);
void fn_8001347C(Unk_C8FEE62D *);

/* 12-byte deferred-call record appended by fn_800139D4. */
typedef struct {
    Unk_C8FEE62D *obj;
    s32 a;
    s32 b;
} Rec13;

void fn_80013A3C(void) {
    s32 idx;
    s32 n;
    s32 cnt;
    s32 off;
    Unk_C8FEE62D *o;
    void (*fp)(Unk_C8FEE62D *, s32, s32, s32, s32);
    Rec13 *rec;
    char *walk;

    fn_8001515C();
    idx = *(s32 *)&lbl_802FFF20 ^ 1;
    n = ((s32 *)lbl_802FFF18)[idx];
    if (n > 0) {
        off = idx * 0xC0;
        rec = (Rec13 *)((char *)lbl_803C9C78 + off);
        walk = (char *)lbl_803C9C78;
        cnt = n;
        do {
            o = *(Unk_C8FEE62D **)((char *)(off + (s32)walk));
            fp = (void (*)(Unk_C8FEE62D *, s32, s32, s32, s32))o->unk0x4;
            walk = walk + 0xC;
            fp(o, rec->a, rec->b, o->unk0x8, o->unk0xC);
            rec = (Rec13 *)((char *)rec + 0xC);
            fn_8001347C(o);
        } while (--cnt != 0);
    }
    ((s32 *)lbl_802FFF18)[idx] = 0;
}
