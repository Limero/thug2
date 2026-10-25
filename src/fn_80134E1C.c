// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134E1C-0x80135170 (852B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// family=m2c range=0x80134E1C-0x80135170 size=852B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// TECHNIQUE: switch needs explicit empty cases {0,1,2,13} to reproduce WANT's
// dispatch tree; cases 5/6 use nested if inside plain else (size assigned
// before the inner n==1 test); the two identical tails are pinned after the
// empty loops with an empty "+r" asm barrier so cross-jump merges them into
// the single shared `add r27,r27,r8`. No special flags.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *fn_801352A8(CStruct * arg0, s32 arg1);
extern s32 strlen(const char *);

void *fn_80134E1C(Unk_F8A5095F *arg0, s32 arg1) {
    void *temp_r3;
    u32 var_k;
    s32 var_off;
    u32 var_bp;
    u32 var_acc;
    u32 var_i;
    u32 var_c;
    u32 var_e;
    u32 var_size;
    void *var_wp;
    void *arr;
    void *result;
    void *p;
    u32 count;

    result = (char *)arg0 + (s32)0xC;
    count = arg0->unk0x4;
    if (count > 1U) {
        p = *((void * *)&arg0->unk0x8);
        if (p != NULL) {
            *((void * *)&arg0->unk0x8) = (char *)p + arg1;
        }
        arr = *((void * *)&arg0->unk0x8);
        result = (char *)result + (count << 2);
    } else {
        arr = (char *)arg0 + (s32)0x8;
    }

    switch (((Unk_ECD1B899 *)arg0)->unk0x2) {
    case 0xC:
        {
            u32 n = arg0->unk0x4;
            if (n > 1U) {
                var_k = 0U;
                if (var_k < n) {
                    var_off = 0;
                    do {
                        var_bp = arg0->unk0x8;
                        *(u32 *)(var_off + var_bp) = *(u32 *)(var_off + var_bp) + arg1;
                        var_k += 1;
                        var_off += 4;
                    } while (var_k < arg0->unk0x4);
                }
            } else if (n == 1U) {
                arg0->unk0x8 = arg0->unk0x8 + arg1;
            }
        }
        var_c = 0U;
        if (var_c < count) {
            var_wp = arr;
            do {
                temp_r3 = *(void **)var_wp;
                var_c += 1;
                var_wp = (char *)var_wp + 4;
                result = fn_80134E1C(temp_r3, arg1);
            } while (var_c < count);
        }
        break;
    case 0xA:
        {
            u32 n = arg0->unk0x4;
            if (n > 1U) {
                var_k = 0U;
                if (var_k < n) {
                    var_off = 0;
                    do {
                        var_bp = arg0->unk0x8;
                        *(u32 *)(var_off + var_bp) = *(u32 *)(var_off + var_bp) + arg1;
                        var_k += 1;
                        var_off += 4;
                    } while (var_k < arg0->unk0x4);
                }
            } else if (n == 1U) {
                arg0->unk0x8 = arg0->unk0x8 + arg1;
            }
        }
        var_c = 0U;
        if (var_c < count) {
            var_wp = arr;
            do {
                temp_r3 = *(void **)var_wp;
                var_c += 1;
                var_wp = (char *)var_wp + 4;
                result = fn_801352A8(temp_r3, arg1);
            } while (var_c < count);
        }
        break;
    case 3:
    case 4:
        {
            u32 n = arg0->unk0x4;
            if (n > 1U) {
                var_k = 0U;
                if (var_k < n) {
                    var_off = 0;
                    do {
                        var_bp = arg0->unk0x8;
                        *(u32 *)(var_off + var_bp) = *(u32 *)(var_off + var_bp) + arg1;
                        var_k += 1;
                        var_off += 4;
                    } while (var_k < arg0->unk0x4);
                }
            } else if (n == 1U) {
                arg0->unk0x8 = arg0->unk0x8 + arg1;
            }
        }
        var_acc = 0U;
        var_i = 0U;
        if (var_acc < count) {
            var_wp = arr;
            do {
                temp_r3 = *(void **)var_wp;
                var_acc += 1;
                var_i += 1;
                var_wp = (char *)var_wp + 4;
                var_acc += strlen(temp_r3);
            } while (var_i < count);
        }
        var_acc = (var_acc + 3) & QB_UNKNOWN_0xFFFFFFFC;
        result = (char *)result + var_acc;
        break;
    case 6:
        {
            u32 n = arg0->unk0x4;
            if (n > 1U) {
                var_k = 0U;
                var_size = count * 16;
                if (var_k < n) {
                    var_off = 0;
                    do {
                        var_bp = arg0->unk0x8;
                        *(u32 *)(var_off + var_bp) = *(u32 *)(var_off + var_bp) + arg1;
                        var_k += 1;
                        var_off += 4;
                    } while (var_k < arg0->unk0x4);
                }
            } else {
                var_size = count * 16;
                if (n == 1U) {
                    arg0->unk0x8 = arg0->unk0x8 + arg1;
                }
            }
        }
        __asm__ volatile("" : "+r"(result), "+r"(var_size));
        var_e = 0U;
        if (var_e < count) {
            do {
                var_e += 1;
            } while (var_e < count);
        }
        result = (char *)result + var_size;
        break;
    case 5:
        {
            u32 n = arg0->unk0x4;
            if (n > 1U) {
                var_k = 0U;
                var_size = count * 12;
                if (var_k < n) {
                    var_off = 0;
                    do {
                        var_bp = arg0->unk0x8;
                        *(u32 *)(var_off + var_bp) = *(u32 *)(var_off + var_bp) + arg1;
                        var_k += 1;
                        var_off += 4;
                    } while (var_k < arg0->unk0x4);
                }
            } else {
                var_size = count * 12;
                if (n == 1U) {
                    arg0->unk0x8 = arg0->unk0x8 + arg1;
                }
            }
        }
        __asm__ volatile("" : "+r"(result), "+r"(var_size));
        var_e = 0U;
        if (var_e < count) {
            do {
                var_e += 1;
            } while (var_e < count);
        }
        result = (char *)result + var_size;
        break;
    case 0:
    case 1:
    case 2:
    case 13:
        break;
    }
    return result;
}
