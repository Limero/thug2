// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D084-0x8002D108 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef union {
    u32 w;
    struct {
        u32 hi : 13;
        u32 lo : 19;
    } b;
} F_8002D084;
typedef struct {
    char pad0x0[0x2C];
    s32 unk0x2C[79];
    F_8002D084 f;
} Rec_8002D084;
void fn_8002CA64(void *, s32);
void fn_8002CA8C(CScript *);
void fn_8002D084(Rec_8002D084 *arg0, s32 arg1) {
    if ((arg0->f.w & QB_UNKNOWN_0xFFF80000) != 0) {
        if ((arg0->unk0x2C[arg1] != 0) && (arg1 > 0)) {
            fn_8002CA8C((CScript *)arg0->unk0x2C[arg1]);
            if (arg0->unk0x2C[arg1] != 0) {
                fn_8002CA64((void *)arg0->unk0x2C[arg1], 3);
            }
            arg0->unk0x2C[arg1] = 0;
        }
        arg0->f.b.hi--;
    }
}
