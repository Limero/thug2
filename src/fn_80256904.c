// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80256904-0x802569D8 (212B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;

extern void fn_80257CC4(void *dst, s32 n);
extern void fn_8024EBD8(void *heap, s32 * ptr);

// MATCHED @ 0x80256904 size=0xD4 (byte-exact, reloc-masked)
void Vtable0x8030804C_m3(Unk_C8FEE62D *arg0) {
    register s32 var_r30 __asm__("r30");
    s32 heap;
    s32 var_r29;

    if (arg0 != NULL) {
        var_r30 = 0;
        if (var_r30 < arg0->unk0x4) {
            var_r29 = 0;
            do {
                s32 arr;
                s32 elem;

                arr = arg0->unk0x14;
                elem = *(s32 *)((char *)(var_r29 + arr));
                if (elem != 0) {
                    heap = lbl_803CA340;
                    fn_8024EBD8((void *)heap, (void *)elem);
                }
                var_r30 += 1;
                var_r29 += 4;
            } while (var_r30 < arg0->unk0x4);
        }
        heap = lbl_803CA340;
        __asm__ volatile("li %0,0" : "=r"(var_r30));
        fn_8024EBD8((void *)heap, ((Unk_C4D756ED *)arg0)->unk0x14);
        if (var_r30 < arg0->unk0x18) {
            var_r29 = 0;
            do {
                s32 arr2;

                arr2 = arg0->unk0x1C;
                var_r30 += 1;
                heap = lbl_803CA340;
                fn_8024EBD8((void *)heap, (void *)(*(s32 *)((char *)(var_r29 + arr2))));
                var_r29 += 4;
            } while (var_r30 < arg0->unk0x18);
        }
        heap = lbl_803CA340;
        fn_8024EBD8((void *)heap, ((Unk_C4D756ED *)arg0)->unk0x1C);
        fn_80257CC4(arg0, 0x2c);
        heap = lbl_803CA340;
        fn_8024EBD8((void *)heap, arg0);
    }
}
