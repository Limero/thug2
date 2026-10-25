// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B3104-0x801B31A8 (164B). Byte-identical.
#include "types.h"
#include "structs.h"

typedef struct { s32 w0; s32 w1; } fn801B3104_ent;

void fn_801B3104(CScript *arg0, Unk_F5317C5D *arg1, s32 arg2, s32 arg3) {
    s16 t = arg1->unk0xA;
    if (t != 0) {
        s32 (*fn)(void *, s32, s32);
        s32 off;
        s16 t4;
        fn801B3104_ent e;

        if (t >= 0) {
            s16 idx = *((s16 *)&arg1->unk0xC);
            void *tbl = *(void **)((char *)arg0 + idx);
            e = ((fn801B3104_ent *)((char *)tbl + t * 8))[-1];
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
