// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80202464-0x8020249C (56B). Byte-identical.
#include "types.h"
#include "structs.h"

typedef void (*Fn80202464Callback)(void *);

bool fn_80202464(CScript *arg0) {
    void *obj = *((void * *)&arg0->unk0x18);
    s16 offset = ((Unk_64253088 *)obj)->unk0x30;
    Fn80202464Callback callback = (Fn80202464Callback)*((u32 *)&((Unk_64253088 *)obj)->unk0x34);
    callback((char *)arg0 + offset);
    return true;
}
