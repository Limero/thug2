// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FAC10-0x801FAD6C (348B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801FB334(Unk_C7387A53 * arg0);
s32 fn_8003E7CC(s32 arg0);
s32 fn_80128F94(Unk_9D4ED6AF * arg0);
void fn_80129068(Unk_5AA7B5D7 * arg0, s32 arg1, s32 arg2);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 fn_801F9890(Unk_C7387A53 * arg0);
void fn_8012788C(CStruct * arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void fn_80129314(CStruct * arg0, s32 arg1, s32 arg2);
void AddArrayPointer(CStruct * arg0, s32 arg1, s32 arg2);
void fn_801FAC10(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 cnt_outer;
    s32 cnt_inner;
    s32 total;
    s32 sub_total;
    s32 outer_arr;
    s32 sub_arr;
    s32 arr_h;
    s32 item;
    CStruct *walker;
    Unk_DB0E2BAB *iw;

    cnt_outer = 0;
    total = fn_801FB334(arg0);
    fn_80129068((outer_arr = fn_80128F94(fn_8003E7CC(0xC))), total, 0xA);
    walker = arg0->unk0x24;
    if (walker != NULL) {
        do {
            cnt_inner = 0;
            arr_h = CStruct_ctor(CStruct_new(8));
            sub_total = fn_801F9890(walker);
            fn_80129068((sub_arr = fn_80128F94(fn_8003E7CC(0xC))), sub_total, 0xA);
            iw = walker->unk0xC;
            if (iw != NULL) {
                do {
                    item = CStruct_ctor(CStruct_new(8));
                    fn_8012788C(item, QB_POS, *((f32 *)&iw->unk0x8), *((f32 *)&iw->unk0xC), *((f32 *)&iw->unk0x10));
                    if (iw->unk0x30 != 0) {
                        AddChecksum(item, 0, QB_HASPOST);
                    }
                    fn_80129314(sub_arr, cnt_inner++, item);
                    iw = iw->unk0x24;
                } while (iw != NULL);
            }
            AddArrayPointer(arr_h, QB_POINTS, sub_arr);
            fn_80129314(outer_arr, cnt_outer++, arr_h);
            walker = walker->unk0x4;
        } while (walker != NULL);
    }
    AddArrayPointer(arg1, QB_CREATEDRAILS, outer_arr);
}
