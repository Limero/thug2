// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED044-0x801ED130 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    s32 pad0x0;
    s32 unk0x4;
    s32 unk0x8;
} ED44Cache;

typedef struct {
    char pad0x0[0x1C];
    s32 *payload;
    char pad0x20[0x50];
    s32 t70;
    s32 t74;
} ED44Node;

typedef struct {
    char pad0x0[0x3CC];
    CStruct *link;
    char pad0x3D0[0x11EC];
    char *p15BC;
    ED44Node *node;
} ED44Obj;

extern s32 lbl_80303150;
s32 Tmr_GetTime(void);
s32 Mem_Free(s32);
void fn_8009F010(CStruct *, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);

void fn_801ED044(ED44Obj *arg0) {
    register ED44Cache *sub __asm__("r31");
    CStruct *link;
    register CStruct *linkAddr __asm__("r28");
    register ED44Node *node __asm__("r31");
    register ED44Obj *base __asm__("r30");
    s32 *pay;
    register s32 zero __asm__("r29");

    base = arg0;
    sub = (ED44Cache *)(base->p15BC + 0xC0);
    if (sub->unk0x4 == 0) {
        return;
    }
    zero = 0;
    linkAddr = (CStruct *)&base->link;
    sub->unk0x4 = zero;
    sub->unk0x8 = lbl_80303150 + Tmr_GetTime();
    link = base->link;
    if (link != NULL) {
        fn_8009F010(link, QB_SKITCHOFF, 0);
        link = base->link;
        if (link != NULL) {
            CObject_RemoveRefLink(link, (CStruct *)linkAddr);
            base->link = (CStruct *)zero;
        }
        base->link = (CStruct *)zero;
    }
    node = base->node;
    pay = node->payload;
    if (pay == NULL) {
        return;
    }
    node->t70 = *pay;
    if (*pay != 0) {
        CObject_RemoveRefLink((CStruct *)*pay, (CStruct *)pay);
        *pay = 0;
    }
    Mem_Free((s32)pay);
    pay = NULL;
    node->payload = pay;
    node->t74 = lbl_80303150 + Tmr_GetTime();
}
