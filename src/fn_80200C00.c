// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80200C00-0x80200C5C (92B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_80200C00(CScript *arg0) {
    {
        void *vt = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *))*((u32 *)&((Unk_89391A04 *)vt)->unk0x34))((char *)arg0 + (s32)((Unk_89391A04 *)vt)->unk0x30);
    }
    {
        void *vt = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *))*((u32 *)&((Unk_89391A04 *)vt)->unk0x24))((char *)arg0 + (s32)((Unk_89391A04 *)vt)->unk0x20);
    }
    return true;
}
