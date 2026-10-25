// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C694-0x8006C780 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 fn_8006F19C(s32);
extern s32 fn_8006F1B0(s32, s32);
extern void fn_80086B84(s32);
extern char lbl_80301434[];

typedef struct Unk_8006C694_node {
    f32 x;
    f32 y;
    f32 z;
    f32 pad0xC;
    f32 pad0x10;
    s32 unk14;
    s32 pad0x18;
    s32 pad0x1C;
} Unk_8006C694_node;

typedef struct Unk_8006C694_box {
    f32 min_x;
    f32 min_y;
    f32 min_z;
    f32 pad0xC;
    f32 max_x;
    f32 max_y;
    f32 max_z;
    f32 pad0x1C;
} Unk_8006C694_box;

void fn_8006C694(void *arg0) {
    Unk_8006C694_node *var_r3;
    Unk_8006C694_box *box = arg0;
    s32 var_r0;

    fn_8006F19C(*(s32 *)lbl_80301434);
    var_r3 = fn_8006F1B0(*(s32 *)lbl_80301434, 0);
    if (var_r3 != NULL) {
        do {
            var_r0 = 0;
            if (var_r3->x >= box->min_x) {
                if (var_r3->y >= box->min_y) {
                    if (var_r3->z >= box->min_z) {
                        if (var_r3->x <= box->max_x) {
                            if (var_r3->y <= box->max_y) {
                                if (var_r3->z <= box->max_z) {
                                    var_r0 = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (var_r0 != 0) {
                var_r3->unk14 = 0;
            }
            var_r3 = fn_8006F1B0(*(s32 *)lbl_80301434, 0);
        } while (var_r3 != NULL);
    }
    fn_80086B84(arg0);
}
