// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF938-0x800AF9C4 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    u8 pad0[0x14];
    void *unk14;
    u8 pad1[0x24];
    s32 unk3c;
    s32 unk40;
    u8 pad2[0xc];
    s32 unk50;
    u8 pad3[0xc];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6c;
    s32 unk70;
    s32 unk74;
} Unk_AF938;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk_AF938_Src;

extern char lbl_802986B0[];
void *fn_800AB0F0(Unk_AF938 *);
void *CStruct_new(s32);
s32 CStruct_ctor(void *);

Unk_AF938 *fn_800AF938(Unk_AF938 *arg0, CStruct *arg1) {
    fn_800AB0F0(arg0);
    arg0->unk3c = 0;
    arg0->unk40 = 0;
    arg0->unk14 = lbl_802986B0;
    arg0->unk50 = CStruct_ctor(CStruct_new(8));
    *(Unk_AF938_Src *)((char *)arg0 + 0x60) = *(Unk_AF938_Src *)arg1;
    arg0->unk70 = 0;
    arg0->unk74 = -1;
    arg0->unk6c = arg0->unk68;
    return arg0;
}
