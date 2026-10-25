// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B120C-0x800B14C0 (692B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

extern char lbl_802987F8[];
extern s32 lbl_80301A38;
extern void *lbl_80301B0C;

typedef struct N_s N_t;

typedef struct {
    char pad0x0[4];
    N_t *head;   /* 0x04 */
    s32 f8;      /* 0x08 */
    s32 fC;      /* 0x0C */
} Grp_t;

struct N_s {
    char pad0x0[4];
    s32 f4;       /* 0x04 */
    __ps_t b8;    /* 0x08 (8B: the psq_l source of the block copy) */
    __ps_t b10;   /* 0x10 (8B) */
    char pad0x18[0x40];
    s32 f58;      /* 0x58 */
    s32 f5C;      /* 0x5C */
    s32 f60;      /* 0x60 */
    s32 f64;      /* 0x64 */
    s32 f68;      /* 0x68 */
    s32 f6C;      /* 0x6C */
    char pad0x70[0x34];
    s32 fA4;      /* 0xA4 */
    N_t *next;    /* 0xA8 */
};

/* script context: only +0x18 (a bit index) is read by this function */
typedef struct { char pad[0x18]; s32 idx; } Scr_t;

/* vtable layouts: s16 `this` offset followed by the method pointer */
typedef struct { char p[0x48]; s16 off; void *fn; } VtA_t;
typedef struct { char p[0x38]; s16 off; void *fn; } VtB_t;

s32 fn_800A1A84(s32);
s32 fn_800A398C(s32, s32);
void fn_8009E1F0(s32, s32);
s32 fn_8009F204(s32, s32, s32);
void fn_8009F310(s32, s32, s32, s32, s32, s32);
void fn_8009FC60(s32, s32, s32);
s32 fn_80125A08(s32, s32);
s32 fn_800B250C(s32, s32);
s32 fn_800B24F4(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(s32, s32);
s32 AddChecksum(s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);

void fn_800B120C(u32 arg0, Scr_t *arg1, s32 arg2, s32 arg3) {
    Grp_t *g;
    N_t *p;
    s32 r;
    u32 m;

    g = (Grp_t *)lbl_80301B0C;
    if (g != NULL) {
        for (p = g->head; p != NULL; p = p->next) {
            if (p->f58 != 0 && p->f6C == arg3) {
                s32 f5c;
                r = fn_800B250C((s32)p, arg2);
                m = p->f68;
                if (arg0 & m) {
                    if (r != 0) {
                        f5c = p->f5C;
                        p->f68 = m & ~arg0;
                        if (f5c == 0) {
                            g->f8 = 1;
                            g->fC = 1;
                            if (arg1 != 0) {
                                fn_8009F310((s32)arg1, p->fA4, p->f4, 0, 0, 0);
                                p->f64 |= 1 << arg1->idx;
                            } else {
                                Script_RunScript(p->fA4, 0, 0, 0, 0);
                            }
                            g->fC = 0;
                        } else if (arg1 != 0) {
                            volatile s32 s8[2];
                            volatile s32 s10[2];
                            register s32 pf __asm__("r4");
                            s32 obj;

                            obj = fn_800A1A84(lbl_80301A38);
                            pf = p->f5C;
                            fn_8009E1F0(obj, pf + arg1->idx);
                            *(__ps_t *)((char *)obj + 0x58) = *(__ps_t *)((char *)p + 8);
                            *(__ps_t *)((char *)obj + 0x60) = *(__ps_t *)((char *)p + 0x10);
                            p->f60 |= 1 << arg1->idx;
                            CStruct_ctor(s8);
                            if (fn_800B24F4((s32)p) != 0) {
                                AddChecksum(s8, 0x08470F2E, p->f4);
                            }
                            fn_8009FC60(obj, fn_80125A08((s32)lbl_802987F8, 0), s8);
                            {
                                VtA_t *vt = *(VtA_t **)((char *)obj + 8);
                                ((void (*)(void *))vt->fn)((void *)((char *)obj + vt->off));
                            }
                            CStruct_ctor(s10);
                            fn_8009F204(obj, p->fA4, s10);
                            CStruct_delete(s10, 2);
                            CStruct_delete(s8, 2);
                        }
                    }
                } else if (r == 0) {
                    f5c = p->f5C;
                    p->f68 = m | arg0;
                    if (f5c == 0) {
                        g->f8 = 0;
                        g->fC = 1;
                        if (arg1 != 0) {
                            fn_8009F310((s32)arg1, p->fA4, p->f4, 0, 0, 0);
                            p->f64 &= ~(1 << arg1->idx);
                        } else {
                            Script_RunScript(p->fA4, 0, 0, 0, 0);
                        }
                        g->fC = 0;
                    } else if (arg1 != 0) {
                        s32 obj = fn_800A398C(lbl_80301A38, p->f5C + arg1->idx);
                        if (obj != NULL) {
                            VtB_t *vt = *(VtB_t **)((char *)obj + 8);
                            ((void (*)(void *))vt->fn)((void *)((char *)obj + vt->off));
                        }
                        p->f60 &= ~(1 << arg1->idx);
                    }
                }
            }
        }
    }
}
