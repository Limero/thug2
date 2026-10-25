// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D63A0-0x800D6444 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { s32 w0; s32 w1; } Ent_t;
void fn_800D63A0(CScript *arg0, Unk_F5317C5D *arg1, s32 arg2, s32 arg3) {
    s16 t = arg1->unk0xA;
    if (t != 0) {
        s32 (*fn)(void *, s32, s32);
        s32 off;
        s16 t4;
        Ent_t e;

        if (t >= 0) {
            s16 idx = *((s16 *)&arg1->unk0xC);
            void *tbl = *(void **)((char *)arg0 + idx);
            e = ((Ent_t *)((char *)tbl + t * 8))[-1];
            fn = (s32 (*)(void *, s32, s32))e.w1;
        } else {
            fn = (s32 (*)(void *, s32, s32))arg1->unk0xC;
        }
        t4 = arg1->unk0x8;
        if (t >= 0) {
            off = (s16)(e.w0 >> 16) + t4;
        } else {
            off = t4;
        }
        fn((char *)arg0 + off, arg2, arg3);
    } else {
        void *vt = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *, s32))(*((void * *)&((Unk_E71E4713 *)vt)->unk0x64)))(
            (char *)arg0 + ((Unk_E71E4713 *)vt)->unk0x60,
            *(s32 *)arg1);
    }
}
