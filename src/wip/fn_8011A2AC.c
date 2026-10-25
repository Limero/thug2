// WIP DRAFT — best attempt, compiles clean (positional DIFF 19.0%, aligned-structural 80/105)
// 2026-10-08: reload_pin_sweep WIN — retype `u32 var_r9` ->
// `register u32 var_r9 __asm__("r11")` => official 70.5% (sweep base 19.42,
// +51.1). The redundant-addi wall described below was NOT the binding
// constraint; the register pin was. Re-measure the rest of the note against
// the pinned body before trusting it.
// PARKED (2026-09-20) at 19.0% — best match; park reason: three mini-walls. (a) Loop keeps a
// redundant `addi r0,r11,1; mr r9,r0` that CSE always merges into the pre-branch `addi r9,r11,1`
// (-fno-cse-follow-jumps/-fno-gcse inert); single-reg loop emitted instead of the r11-IV/r9-next
// pair. (b) FPR 3-cycle (farg0/1/2 land f30/f29/f31, want f31/f30/f29); invasive probes risk the
// now-exact GPR map. (c) Call#2 cold-inline block order (`bne`+inline `li r3,0` unreachable — GCC
// always lays hot-success fallthrough with `beq`; both polarities + goto forms probed). Solved en
// route: 0x58 frame via 3rd volatile double, exact GPR homes, tail rotate-right order, all protos
// (19470 0-arg, 19B24 2-arg, 26EAC(19D08(8)) chain, 277E4 hidden-arg0), lbl addi-forms, s8/s16/f32
// widths, head li/bne. Retry only with a new CSE-defeat or block-order lever.
// family=m2c range=0x8011A2AC-0x8011A450 size=420B
// h1 changes: real callee protos (kill crclr), fn_80119470() 0-arg bare,
// fn_80119B24 2-arg, byte loop via s8 base, lbl_ externs (addi form),
// typed tail stores (f32/s16/s8), clean if/else-early-return layout.
#include "types.h"
#include "structs.h"

s32 fn_80119470(void);
s32 strlen(const char *s);
s32 Script_GenerateCRC(s32 hash);
s32 fn_80119B24(void *arg0, s32 hash);
s32 fn_8011EF14(void *str, s32 hash, void *entry, s32 a3, s32 a4);

extern bool lbl_80302C48;
extern s32 lbl_80302C44;
extern char lbl_80385A44[];
extern char lbl_80383644[];

s32 fn_8011A2AC(void *arg0, s32 arg1, s16 arg2, s8 arg3, s8 arg4, f32 farg0, f32 farg1, f32 farg2) {
    volatile double _dummy;
    volatile double _dummy2;
    volatile double _dummy3;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r3;
    s32 temp_r3_2;
    register u32 var_r9 __asm__("r11");
    s32 var_r11;
    s32 var_r30;
    s32 var_r3;
    s8 temp_r0;
    s32 var_r31;

    var_r3 = 0;
    if (fn_80119470() != 0) {
        return var_r3;
    }
        var_r30 = arg1;
        temp_r3 = strlen((const char *)arg1);
        var_r11 = 0;
        if (var_r11 < temp_r3) {
            do {
                temp_r0 = ((s8 *)arg1)[var_r11];
                var_r9 = var_r11 + 1;
                if ((temp_r0 == 0x5C) || (temp_r0 == 0x2F)) {
                    temp_r0_2 = var_r11 + 1;
                    var_r9 = temp_r0_2;
                    var_r30 = arg1 + temp_r0_2;
                }
                var_r11 = var_r9;
            } while (var_r11 < temp_r3);
        }
        temp_r3_2 = Script_GenerateCRC(var_r30);
        if (fn_80119B24(arg0, temp_r3_2) == 0) {
            if (arg3 == 0) {
                temp_r0_3 = lbl_80302C48;
                if (temp_r0_3 > 0xFF) {
                    return 0;
                }
                var_r31 = (temp_r0_3 * 0x24) + (s32)lbl_80385A44;
                if (fn_8011EF14((void *)arg1, temp_r3_2, (void *)(var_r31 + 0x14), 0, arg4) == 0) {
                    return 0;
                }
                lbl_80302C48 += 1;
            } else {
                temp_r0_4 = lbl_80302C44;
                if (temp_r0_4 > 0xFF) {
                    return 0;
                }
                var_r31 = (temp_r0_4 * 0x24) + (s32)lbl_80383644;
                if (fn_8011EF14((void *)arg1, temp_r3_2, (void *)(var_r31 + 0x14), arg3, arg4) != 0) {
                    goto success2;
                }
                return 0;
success2:
                lbl_80302C44 += 1;
            }
            *(f32 *)((char *)var_r31 + 0x10) = farg0;
            *(f32 *)((char *)var_r31 + 8) = farg1;
            *(f32 *)((char *)var_r31 + 0xC) = farg2;
            *(s32 *)var_r31 = temp_r3_2;
            *(s16 *)((char *)var_r31 + 4) = arg2;
            *(s8 *)((char *)var_r31 + 6) = arg3;
            var_r3 = 1;
            *(s8 *)((char *)var_r31 + 7) = arg4;
            return var_r3;
        }
        return 0;
}
