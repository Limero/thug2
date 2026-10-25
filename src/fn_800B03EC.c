// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B03EC-0x800B0564 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8037BC68[];
extern char lbl_8037BCB8[];
extern char lbl_8037BD08[];
extern const f32 lbl_80298748;
extern const f32 lbl_8029874C;
extern const f32 lbl_80298750;
extern const f32 lbl_80298754;
extern const f32 lbl_80298758;
extern const f32 lbl_8029875C;
extern const f32 lbl_80298760;
extern const f32 lbl_80298764;
extern const f32 lbl_80298768;
extern const f32 lbl_8029876C;
extern const f32 lbl_80298770;
extern const f32 lbl_80298774;

typedef struct { f32 v0; f32 v1; f32 v2; f32 v3; } E;

void fn_800B03EC(s32 arg0, s32 arg1) {
    E *p;
    E *q;
    E *r;
    u32 i;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        p = (E *)lbl_8037BC68;
        p->v0 = lbl_80298748; p->v1 = lbl_80298748; p->v2 = lbl_80298748; p->v3 = lbl_8029874C; p++;
        p->v0 = lbl_80298750; p->v1 = lbl_80298754; p->v2 = lbl_80298758; p->v3 = lbl_8029874C; p++;
        p->v0 = lbl_80298750; p->v1 = lbl_8029875C; p->v2 = lbl_80298760; p->v3 = lbl_8029874C; p++;
        p->v0 = lbl_80298764; p->v1 = lbl_80298768; p->v2 = lbl_8029876C; p->v3 = lbl_8029874C; p++;
        p->v0 = lbl_80298764; p->v1 = lbl_80298770; p->v2 = lbl_80298774; p->v3 = lbl_8029874C;
        q = (E *)lbl_8037BCB8;
        q->v0 = lbl_8029874C; q->v1 = lbl_8029874C; q->v2 = lbl_8029874C; q->v3 = lbl_8029874C; q++;
        q->v0 = lbl_8029874C; q->v1 = lbl_8029874C; q->v2 = lbl_8029874C; q->v3 = lbl_8029874C; q++;
        q->v0 = lbl_8029874C; q->v1 = lbl_8029874C; q->v2 = lbl_8029874C; q->v3 = lbl_8029874C; q++;
        q->v0 = lbl_8029874C; q->v1 = lbl_8029874C; q->v2 = lbl_8029874C; q->v3 = lbl_8029874C; q++;
        q->v0 = lbl_8029874C; q->v1 = lbl_8029874C; q->v2 = lbl_8029874C; q->v3 = lbl_8029874C;
        r = (E *)lbl_8037BD08;
        i = 0x80;
        do {
            r->v0 = lbl_80298748; r->v1 = lbl_80298748; r->v2 = lbl_80298748; r->v3 = lbl_8029874C; r++;
        } while (--i != 0);
        i = 0x80;
        do {
        } while (--i != 0);
    }
}
