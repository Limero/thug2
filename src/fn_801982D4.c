// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801982D4-0x80198344 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
extern char lbl_802AA7D8[];
extern char lbl_802AA7F0[];
void CStruct_ctor(s32);
void fn_80199120(void *);
typedef struct { char pad[4]; s32 unk0x4; s32 unk0x8; s32 unk0xC; s32 unk0x10; s32 unk0x14; } Node81982;
void *fn_801982D4(Unk_C7387A53 *arg0) {
    Node81982 *n;
    arg0->unk0x24 = (s32)lbl_802AA7D8;
    CStruct_ctor((s32)arg0 + 4);
    n = (Node81982 *)((char *)arg0 + 0xC);
    n->unk0x14 = (s32)lbl_802AA7F0;
    n->unk0x4 = -1;
    n->unk0x8 = 0;
    n->unk0x10 = (s32)n;
    n->unk0xC = (s32)n;
    fn_80199120(arg0);
    return arg0;
}
