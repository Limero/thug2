// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801266EC-0x80126808 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    union {
        struct { u16 a; u16 b; } ab;                                  /* +0, +2 */
        struct { u32 h9 : 9; u32 k : 7; u32 m9 : 9; u32 t7 : 7; } bits;
    } w;
    u32 pad;                                                         /* +4 */
    void *p;                                                         /* +8 */
} T266EC;

void DeleteString(void *);
void fn_80117CC0(void *);
void fn_80117D74(void *);
void CStruct_delete(void *, s32);
void fn_80126A30(void *);
void fn_80128FB4(void *, s32);
void Mem_Free_3(void *);

void fn_801266EC(T266EC *arg0) {
    s32 t = arg0->w.ab.a & 0x7F;
    switch (t) {
    case 3 ... 4:
        if (arg0->p) { DeleteString(arg0->p); }
        break;
    case 5:
        if (arg0->p) { fn_80117CC0(arg0->p); }
        break;
    case 6:
        if (arg0->p) { fn_80117D74(arg0->p); }
        break;
    case 10:
        if (arg0->p) { CStruct_delete(arg0->p, 3); }
        break;
    case 12:
        if (arg0->p) { fn_80126A30(arg0->p); }
        if (arg0->p) { fn_80128FB4(arg0->p, 3); }
        break;
    case 7:
        if (arg0->p) { Mem_Free_3(arg0->p); }
        arg0->w.ab.b = 0;
        break;
    }
    arg0->p = 0;
    arg0->w.bits.k = 0;
}
