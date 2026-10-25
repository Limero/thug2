// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022F5B0-0x8022F840 (656B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_8022CBBC(CStruct * arg0);
extern s32 fn_80129528(s32 arg0);
extern void fn_801279A0(CStruct * arg0, s32 arg1, CStruct * arg2);
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_8003E7CC(s32 arg0);
extern s32 fn_80128F94(Unk_9D4ED6AF * arg0);
extern void fn_80129068(Unk_5AA7B5D7 * arg0, s32 arg1, s32 arg2);
extern void fn_80129260(CStruct * arg0, s32 arg1, s32 arg2);
extern void fn_80127AAC(CStruct * arg0, s32 arg1, Unk_5AA7B5D7 * arg2);
extern void fn_80128FB4(Unk_F8A5095F * arg0, s32 arg1);

void fn_8022F5B0(s32 arg0, CStruct *arg1, s32 *arg2) {
    __ps_t sp8p[2];
    __ps_t *po;
    CStruct *tp;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r22;
    s32 var_r23;
    s32 var_r26;
    Unk_C8FEE62D *var_r27;
    s32 var_r28;
    Unk_AC63D244 *var_r29;
    s32 temp_r30;
    s32 temp_r31_2;
    s32 temp_r9;
    s32 temp_r0;
    register s32 iv __asm__("r4");
    s32 next;

    tp = (char *)arg0 + 0x5C;
    temp_r3 = fn_8022CBBC((s32)tp);
    if (temp_r3 != 0) {
        register s32 t4 __asm__("r4");
        t4 = *arg2;
        var_r27 = *((void * *)&tp->unk0x4);
        var_r26 = 0x1E8481;
        var_r22 = t4 + temp_r3;
        var_r23 = t4;
        __asm__("" : "+r"(t4));
        var_r29 = *((void * *)&var_r27->unk0x10);
        if (t4 < var_r22) {
            po = sp8p;
            do {
                temp_r30 = fn_80129528(arg1);
                if (var_r27->unk0x4 == QB_RAILNODE) {
                    *(__ps_t *)sp8p = var_r29->unk0x10;
                    po[1] = var_r29->unk0x18;
                    fn_801279A0(temp_r30, QB_POS, po);
                    AddChecksum(temp_r30, QB_NAME, var_r26);
                    var_r26 += 1;
                    if (!(*((u32 *)&var_r27->unk0x8) & QB_UNKNOWN_0x40000000)) {
                        AddChecksum(temp_r30, 0, QB_NCOMP_RAILNODE_PARK_NC);
                    } else {
                        AddChecksum(temp_r30, 0, QB_NCOMP_RAILNODE_PARK);
                    }
                    AddChecksum(temp_r30, QB_TERRAINTYPE, *((s32 *)&var_r29->unk0x8));
                    if (*((s32 *)&var_r29->unk0x30) != 0) {
                        AddChecksum(temp_r30, 0, QB_TRICKOBJECT);
                        AddChecksum(temp_r30, QB_CLUSTER, ~*((s32 *)&var_r29->unk0x30));
                    }
                } else {
                    *(__ps_t *)sp8p = var_r29->unk0x10;
                    po[1] = var_r29->unk0x18;
                    fn_801279A0(temp_r30, QB_POS, po);
                    *(__ps_t *)sp8p = var_r29->unk0x20;
                    po[1] = var_r29->unk0x28;
                    fn_801279A0(temp_r30, QB_ANGLES, po);
                    AddChecksum(temp_r30, QB_NAME, var_r26);
                    var_r26 += 1;
                    AddChecksum(temp_r30, 0, QB_NCOMP_CLIMBINGNODE_PARK);
                    AddChecksum(temp_r30, QB_TYPE, *((s32 *)&var_r29->unk0x4));
                }
                next = *((s32 *)&var_r29->unk0x34);
                if ((next != 0) || (var_r27->unk0x8 < 0)) {
                    var_r28 = *arg2 + 1;
                    if ((next == 0) && (var_r27->unk0x8 < 0)) {
                        var_r28 = var_r23;
                    }
                    temp_r31_2 = fn_80128F94(fn_8003E7CC(0xC));
                    fn_80129068(temp_r31_2, 1, 1);
                    fn_80129260(temp_r31_2, 0, var_r28);
                    fn_80127AAC(temp_r30, QB_LINKS, temp_r31_2);
                    if (temp_r31_2 != 0) {
                        fn_80128FB4(temp_r31_2, 3);
                    }
                }
                var_r29 = var_r29->unk0x34;
                temp_r9 = *arg2;
                if (var_r29 == NULL) {
                    var_r27 = *((void * *)&var_r27->unk0x1C);
                    if (var_r27 != NULL) {
                        var_r29 = *((void * *)&var_r27->unk0x10);
                        var_r23 = temp_r9 + 1;
                    }
                }
                temp_r0 = temp_r9 + 1;
                __asm__("mr %0,%1" : "=r"(iv) : "r"(temp_r0));
                *arg2 = temp_r0;
            } while (iv < var_r22);
        }
    }
}
