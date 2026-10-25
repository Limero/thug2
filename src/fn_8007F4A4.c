// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F4A4-0x8007F5F4 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* 0x20-byte material-slot row; the tint writes bytes 0x0C..0x0E. */
typedef struct {
    char pad00[0x0C];
    u8 r;
    u8 g;
    u8 b;
    char pad0F[0x11];
} Row_t;

typedef struct {
    char pad00[0x14];
    void *unk14;          /* 0x14 -> sub-record */
} Elem_t;

typedef struct {
    char pad00[0x04];
    u8 count;             /* 0x04 */
    u8 pad05;
    u8 flags;             /* 0x06, |= 0x10 once a row has been tinted */
    char pad07[0x05];
    u16 idx;              /* 0x0C, row index (stride 0x20) */
} Ent_t;

typedef struct {
    char pad00[0x38];
    Row_t *rows;          /* 0x38 */
    char pad3C[0x1C];
    Elem_t **elems;       /* 0x58 */
    char pad5C[2];
    u16 count;            /* 0x5E */
} Grp_t;

typedef struct {
    s32 flags;            /* 0x00, |= 8 */
    char pad04[0x54];
    void *unk54;          /* 0x54 -> group */
    s32 col;              /* 0x5C */
} M_t;

/* Re-walked from arg0 at every use on purpose: the u8 stores in the body alias
   the whole chain, so the compiler reloads it inside the loops like want does. */
#define MGR (*(M_t **)((char *)arg0 + 0x30))
#define GRP (*(Grp_t **)((char *)MGR + 0x54))
#define CNT (GRP->count)
#define B20 (*(void **)((char *)arg0 + 0x20))
#define N24 (*(u32 *)((char *)arg0 + 0x24))

void fn_8007F4A4(void *arg0, s32 *arg1) {
    s32 col = *arg1;
    M_t *m = MGR;

    if (m != NULL) {
        m->col = col;
        m->flags |= 8;
        if (GRP != NULL) {
            s32 i = 0;
            if (i < CNT) {
                do {
                    Elem_t *e = GRP->elems[i];
                    Ent_t *t = *(Ent_t **)((char *)e->unk14 + 4);
                    if (t != NULL) {
                        Row_t *p = GRP->rows + t->idx;
                        s32 j = 0;
                        if (j < t->count) {
                            u8 *cp = (u8 *)&col;
                            do {
                                j++;
                                p->r = *(u8 *)&col;
                                p->g = cp[1];
                                p->b = cp[2];
                                p++;
                                t->flags |= 0x10;
                            } while (j < t->count);
                        }
                    }
                    i++;
                } while (i < CNT);
            }
        }
    } else if (B20 != NULL) {
        u32 n = N24;
        u32 k = 0;
        s32 off;
        if (k < n) {
            u8 *cp = (u8 *)&col;
            off = 0;
            do {
                void *d;
                k++;
                d = *(void **)((char *)(off + (s32)B20));
                off += 4;
                *(u8 *)((char *)d + 0x18) = *(u8 *)&col;
                *(u8 *)((char *)d + 0x19) = cp[1];
                *(u8 *)((char *)d + 0x1A) = cp[2];
                *(u8 *)((char *)d + 0x1B) = cp[3];
            } while (k < N24);
        }
    }
}
