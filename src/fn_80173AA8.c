// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173AA8-0x80173B98 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct node_s {
    s32 unk0;
    s32 cursor;
    char pad8[4];
    struct node_s *next;
} node_t;

typedef struct {
    s32 unk0;
    s32 cursor;
    char pad8[4];
    node_t *first;
} search_t;

typedef struct {
    char pad0[0x2C];
    search_t hdr;
    char pad[0x374 - 0x3C];
    s32 *unk374;
} arg0_t;

typedef struct {
    char pad0[0x18];
    s32 unk18;
    char pad1C[0xC8 - 0x1C];
    s32 unkC8;
} obj_t;

s32 fn_801EF978(void *, void *);
s32 IsTrue(s32 arg0, s32 arg1);
s32 fn_8019B834(void *);
obj_t *fn_801746A4(s32, s32);
extern s32 lbl_80305EC0;
void *GetChecksum_3(void *, s32);
s32 fn_801EFA84(void *);

s32 fn_80173AA8(arg0_t *arg0) {
    s32 var_r27;
    u32 var_r29;
    u32 cnt;
    node_t *node;
    search_t *hdr;
    obj_t *temp_r30;
    void *temp_r31;

    var_r27 = 1;
    var_r29 = 0U;
    hdr = &arg0->hdr;
    for (;;) {
        node = hdr->first;
        cnt = 0U;
        for (;;) {
            if (node->cursor == -1) {
                node = NULL;
            }
            if (node == NULL) {
                break;
            }
            node = node->next;
            cnt += 1U;
        }
        if (var_r29 >= cnt) {
            break;
        }
        temp_r30 = fn_801746A4((s32)arg0, var_r29);
        if ((IsTrue(lbl_80305EC0, QB_IS_HORSE) == 0) ||
            (fn_8019B834(arg0->unk374) == temp_r30->unk18)) {
            temp_r31 = GetChecksum_3(temp_r30, QB_SKATERENDRUN);
            if (fn_801EFA84(temp_r31) == 0) {
                var_r27 = 0;
                if (temp_r30->unkC8 != 0) {
                    fn_801EF978(temp_r31, 0);
                }
            }
        }
        var_r29 += 1U;
    }
    return var_r27;
}
