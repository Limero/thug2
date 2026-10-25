// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CD60-0x8009CE50 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802978A8[];

typedef struct {
    s32 unk0;
    s32 cursor;
    char *name;
    s32 unkC;
} search_t;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    void *vt;
} Node_t;

typedef struct {
    char pad0[0x18];
    s16 off;
    char pad1A[2];
    void (*fn)(void *);
} Vt_t;

void fn_8009CD60(void *arg0) {
    search_t sp8;
    search_t *p = &sp8;
    register search_t *s __asm__("r28");
    Node_t *temp_r3;
    register Node_t *var_r11 __asm__("r11");
    Node_t *var_r11_2;
    Node_t *var_r11_3;
    Node_t *var_r29;
    Node_t *temp_r30;
    s32 temp_r31;
    Vt_t *temp_r9;

    p->cursor = (s32)((char *)arg0 + 8);
    p->name = lbl_802978A8;
    s = p;
    temp_r3 = (Node_t *)((char *)arg0 + 8);

    var_r11 = temp_r3->unkC;
    if (var_r11->unk4 == -1) {
        var_r11 = 0;
    }
    s->cursor = (s32)var_r11;
    if (var_r11 == 0) {
        __asm__("" : "+r"(var_r11));
        var_r11 = 0;
    } else {
        var_r11 = (Node_t *)var_r11->unk4;
    }
    var_r29 = var_r11;
    if (var_r29 != 0) {
        do {
            temp_r30 = var_r29;
            var_r11_3 = (Node_t *)((Node_t *)s->cursor)->unkC;
            if (var_r11_3->unk4 == -1) {
                var_r11_3 = 0;
            }
            s->cursor = (s32)var_r11_3;
            if (var_r11_3 != 0) {
                var_r29 = (Node_t *)var_r11_3->unk4;
            } else {
                __asm__("" : "+r"(var_r11_3));
                var_r29 = 0;
            }
            temp_r31 = temp_r30->unkC;
            if ((temp_r31 == 0) && (temp_r30->unk4 == 1)) {
                temp_r9 = (Vt_t *)temp_r30->vt;
                temp_r9->fn((char *)temp_r30 + temp_r9->off);
                temp_r30->unk8 = temp_r31;
                temp_r30->unk4 = temp_r31;
            }
        } while (var_r29 != 0);
    }
    s->name = lbl_802978A8;
}
