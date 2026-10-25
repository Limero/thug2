// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800791A4-0x80079300 (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void *Mem_Alloc(s32);
void Mem_Free2(void *);
void fn_8000F2F8(Unk_9F352E7C *arg0, s32 arg1);
void fn_8000F320(Unk_F12C5E01 *self);
void fn_80078FFC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4);
typedef struct { char _0[0x158]; s16 m_off; void *(*m_fn)(void *); } VT_t;
typedef struct { char _0[6]; u8 n6; u8 n7; } Sz_t;
typedef struct { char _0[8]; VT_t *vt; Sz_t *sz; } Obj_t;
bool fn_800791A4(Obj_t *arg0) {
    s32 alloc;
    char *v29;
    char *v30;
    char *t1;
    char *t2;
    s32 one = 1;
    void *mgr;

    mgr = *(void **)&lbl_802FFE98;
    fn_8000F2F8((Unk_9F352E7C *)mgr, *(s32 *)((char *)mgr + 0x118));
    alloc = (s32)Mem_Alloc(((one << arg0->sz->n7) << 2) & 0x3FFFC);
    fn_8000F320(*(void **)&lbl_802FFE98);
    v29 = (char *)arg0->vt->m_fn((char *)arg0 + arg0->vt->m_off);
    v30 = (char *)arg0->vt->m_fn((char *)arg0 + arg0->vt->m_off)
        + ((((one << arg0->sz->n6) << 2) & 0x3FFFC) - 4);
    if (v29 < v30) {
        do {
            fn_80078FFC((s32 *)alloc, 1, (s32 *)v29, (u16)(1 << arg0->sz->n6), (u16)(1 << arg0->sz->n7));
            t1 = v29;
            v29 += 4;
            fn_80078FFC((s32 *)t1, (u16)(1 << arg0->sz->n6), (s32 *)v30, (u16)(1 << arg0->sz->n6), (u16)(1 << arg0->sz->n7));
            t2 = v30;
            v30 -= 4;
            fn_80078FFC((s32 *)t2, (u16)(1 << arg0->sz->n6), (s32 *)alloc, 1, (u16)(1 << arg0->sz->n7));
        } while (v29 < v30);
    }
    if (alloc != 0) {
        Mem_Free2((void *)alloc);
    }
    return true;
}
