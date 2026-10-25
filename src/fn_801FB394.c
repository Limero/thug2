// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB394-0x801FB50C (376B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80129528(CStruct *, s32);
extern void fn_8012788C(CStruct *, s32, f32, f32, f32);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 Script_GenerateCRC(s32);
extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);
extern void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
extern void fn_80129260(CStruct *, s32, s32);
extern void AddArrayPointer(CStruct *, s32, s32);

void fn_801FB394(Unk_C7387A53 *arg0, CStruct *arg1, s32 *arg2, s32 arg3) {
    s32 sp8[14];
    CStruct *outer;
    Unk_DB0E2BAB *inner;
    s32 entry;
    s32 handle;
    s32 idx;
    s32 i;
    register char *anchor __asm__("r22");

    outer = arg0->unk0x24;
    idx = *arg2;
    i = 0;
    if (outer != NULL) {
        do {
            inner = outer->unk0xC;
            if (inner != NULL) {
                anchor = (char *)0x802B0000;
                do {
                    entry = fn_80129528(arg1, idx);
                    idx += 1;
                    fn_8012788C(entry, QB_POS,
                                *((f32 *)&inner->unk0x8),
                                *((f32 *)&inner->unk0xC),
                                *((f32 *)&inner->unk0x10));
                    AddChecksum(entry, QB_NAME, arg3);
                    arg3 += 1;
                    AddChecksum(entry, 0, QB_NCOMP_RAILNODE_PARK);
                    AddChecksum(entry, 0, QB_TRICKOBJECT);
                    sprintf(sp8, (s32)(anchor - 0x1A4C), i);
                    AddChecksum(entry, QB_CLUSTER, Script_GenerateCRC(sp8));
                    AddChecksum(entry, QB_TERRAINTYPE, QB_TERRAIN_METALSMOOTH);
                    if (inner->unk0x24 != NULL) {
                        handle = fn_80128F94(fn_8003E7CC(0xC));
                        fn_80129068(handle, 1, 1);
                        fn_80129260(handle, 0, idx);
                        AddArrayPointer(entry, QB_LINKS, handle);
                    }
                    inner = inner->unk0x24;
                } while (inner != NULL);
            }
            outer = outer->unk0x4;
            i += 1;
        } while (outer != NULL);
    }
    *arg2 = idx;
}
