// PARKED: 408B, 8 callees (0x801fa66c..0x8023b364 skater-state cluster) - deep callee-signature harvest required first
// family=m2c range=0x80235FA8-0x80236144 size=412B
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 21.3% ([0]rev->21.3%).
// UPDATED 2026-09-15 (e): 21.7% -> 22.6%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address (fn_8006A8C0 recipe). tools/raw_sym_scan.py automated the A/B; keep the best body.
#include "types.h"
extern char lbl_802B0C5C[];
#include "qb_constants.h"
#include "structs.h"
s32 fn_8022D4C4(s32);
void fn_80235FA8(Unk_9DBD21F4 *arg0, s32 arg1) {
    Unk_638CF717 sp8;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 var_ctr;
    s32 var_r11;
    s32 var_r28;
    s32 var_r9;
    Unk_897A0ACF *var_r26;

    var_r28 = arg1;
    fn_8023C0EC();
    temp_r5 = arg0->unk0x1772C & 5;
    if ((temp_r5 == 0) && ((s32) arg0->unk0x8 != 0)) {
        fn_8023B364(arg0, temp_r5);
    }
    fn_802373AC(arg0, 0);
    fn_80240614();
    if ((var_r28 == QB_CLEAR) || (temp_r5_2 = arg0->unk0x1772C & 2, ((temp_r5_2 == 0) != 0))) {
        var_r26 = (char *)arg0 + 0x3524;
        var_r11 = 0;
        do {
            var_r9 = var_r11 * 0x10;
            var_ctr = 0x3A;
            var_r11 += 1;
loop_7:
            *((s32 *)((char *)arg0 + (s32)0x3530 + (s32)var_r9)) = 0;
            *((s32 *)((char *)arg0 + (s32)0x3534 + (s32)var_r9)) = 0;
            *((s32 *)((char *)arg0 + (s32)0x3538 + (s32)var_r9)) = 0;
            *((s32 *)((char *)arg0 + (s32)0x353C + (s32)var_r9)) = 0;
            var_r9 += 0x3A0;
            var_ctr -= 1;
            if (var_ctr != 0) {
                goto loop_7;
            }
        } while (var_r11 <= 0x39);
        fn_8023B364(arg0);
        var_r28 = QB_CLEAR;
        fn_80235D1C(arg0,(s32)lbl_802B0C5C);
        arg0->unk0x1772C = (s32) (arg0->unk0x1772C & QB_UNKNOWN_0xFFFFFFF7);
    } else {
        fn_8023B830(arg0, temp_r5_2);
        var_r26 = (char *)arg0 + 0x3524;
    }
    *((s32 *)&sp8) = arg0->unk0x3524;
    *(s32 *)0x80305FF4 = 0;
    sp8.unk0x4 = (u16) var_r26->unk0x4;
    fn_802366E4(arg0, &sp8);
    fn_80239FAC(arg0, 0, 0);
    *(s32 *)0x80305FF4 = 1;
    fn_8022D4C4(arg0->unk0x0);
    arg0->unk0x8 = 1;
    if (var_r28 == QB_CLEAR) {
        arg0->unk0x1772C = (s32) (arg0->unk0x1772C | 1);
    }
    *(s32 *)0x80305FF4 = 0;
    fn_801FC0E0();
    fn_801FA66C();
    *(s32 *)0x80305FF4 = 1;
    fn_8022D4C4(arg0->unk0x0);
}
