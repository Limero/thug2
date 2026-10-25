// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3930-0x800F39BC (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct F3930_vt {
    char pad0x0[0x8];
    s16 off;                 /* s16: want `lha r3,8(r9)` */
    char pad0xA[0x2];
    void (*fn)(void *, s32);
} F3930_vt;

typedef struct F3930_node {
    char pad0x0[0x4];
    s32 id;                  /* -1 == end-of-list sentinel */
    char pad0x8[0x4];
    struct F3930_node *next;
    char pad0x10[0x4];
    F3930_vt *vt;
} F3930_node;

typedef struct F3930_root {
    char pad0x0[0x44];
    F3930_node *head;
} F3930_root;

void fn_800F3930(F3930_root *arg0, s32 arg1) {
    F3930_node *node;
    F3930_node *next;
    F3930_vt *vt;

    {
        F3930_node *raw = arg0->head;
        if (raw->id == -1) {
            node = NULL;
        } else {
            node = raw;
        }
    }
    if (node != NULL) {
        do {
            next = node->next;
            if (next->id == -1) {
                next = NULL;
            }
            if (node->id == arg1) {
                if (node != NULL) {
                    vt = node->vt;
                    vt->fn((char *)node + vt->off, 3);
                }
                break;
            }
            node = next;
        } while (node != NULL);
    }
}
