// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800163A0-0x80016448 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *memset(void *, s32, s32);
s32 CARDWrite(s32, s32, s32, s32);
void Mem_Free_3(s32);
bool fn_800163A0(CStruct *arg0) {
    s32 rem;
    if (arg0->unk0x68 == 0) {
        return true;
    }
    rem = arg0->unk0x6C % ((Unk_9994C3F5 *)arg0->unk0x80)->unk0x8;
    memset((void *)(arg0->unk0x70 + rem), 0,
           ((Unk_9994C3F5 *)arg0->unk0x80)->unk0x8 - rem);
    if (CARDWrite((s32)arg0 + 0x50, arg0->unk0x70,
                  ((Unk_9994C3F5 *)arg0->unk0x80)->unk0x8,
                  arg0->unk0x6C - rem) != 0) {
        return false;
    }
    arg0->unk0x68 = 0;
    arg0->unk0x6C = 0;
    if (arg0->unk0x70 != 0) {
        Mem_Free_3(arg0->unk0x70);
        arg0->unk0x70 = 0;
    }
    return true;
}
