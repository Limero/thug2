// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012ED98-0x8012EE64 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Node_8012ED98 {
    s32 unk0x0;
    s32 unk0x4;
    struct Node_8012ED98 *unk0x8;
} Node_8012ED98;
extern Node_8012ED98 *lbl_803032DC;
extern s32 lbl_803032E0;
extern s32 lbl_803032E4;
void CObject_ctor(void *);
s32 *fn_8012ED98(Unk_9C8EAC3F *arg0) {
    Node_8012ED98 *temp_r9;
    s32 *var_r9;
    s32 temp_r10;
    s32 var_ctr;
    Node_8012ED98 *temp_r9_2;

    temp_r9 = (Node_8012ED98 *)((char *)arg0 + 0xBC);
    temp_r9->unk0x4 = 0;
    temp_r9->unk0x8 = 0;
    arg0->unk0xBC = 0;
    CObject_ctor((char *)arg0 + 0xEC);
    var_ctr = 0x3E;
    var_r9 = (s32 *)arg0;
    do {
        *var_r9 = 0;
        var_r9 += 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    temp_r9_2 = lbl_803032DC;
    arg0->unk0x4 = (s32)temp_r9_2;
    if (temp_r9_2 != 0) {
        temp_r9_2->unk0x8 = (Node_8012ED98 *)arg0;
    }
    temp_r10 = lbl_803032E4;
    lbl_803032DC = (Node_8012ED98 *)arg0;
    lbl_803032E0 += 1;
    arg0->unk0xB0 = temp_r10;
    temp_r10 = temp_r10 + 1;
    lbl_803032E4 = temp_r10;
    arg0->unk0x94 = (s32)((char *)arg0 + 0x3C);
    arg0->unk0x34 = (s32)((char *)arg0 + 0x20);
    arg0->unk0xB8 = 0;
    arg0->unk0xE0 = 0;
    arg0->unk0xE4 = 0;
    arg0->unk0xE8 = 0;
    return (s32 *)arg0;
}
