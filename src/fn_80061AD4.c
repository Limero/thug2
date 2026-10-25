// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80061AD4-0x80061DE8 (788B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8005F8E0(CStruct *);
void fn_8005F0CC(void *);
s32 fn_8005F148(void *, s32, s32, s32 *);
s32 fn_801293FC(CStruct *, s32);
s32 fn_80129528(CStruct *, s32);

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Rgba;

/* The list node is re-read from the stack slot at every use in the original,
   so it is spelled as an expression rather than kept in a variable. */
#define NODE ((CStruct *)((CStruct *)slots.slot10)->unk0x0)

s32 fn_80061AD4(CStruct *arg0, CStruct *arg1) {
    struct {
        void *slot8;
        s32 padc;
        void *slot10;
    } slots;
    CStruct *head;
    CStruct *cur;
    CStruct *cur_tmp;
    void *head_tmp;
    void *temp_r0;
    CStruct *item;
    CStruct *array;
    CStruct *array2;
    s32 ret;
    s32 checksum;
    s32 checksum2;
    s32 val;
    volatile s32 out;
    s32 res;
    s32 all_flag;
    u32 i;
    u32 j;
    Rgba color;
    Rgba color2;
    register CStruct *t10 __asm__("r11");

    GetChecksum_2(arg1, QB_PART, &checksum, 1);
    ret = 0;
    head = (CStruct *)arg0->unk0x10;
    slots.slot8 = (void *)head;
    all_flag = checksum == QB_ALL;
    cur = head ? (CStruct *)head->unk0x4 : NULL;
    slots.slot10 = (void *)cur;
    if (cur != head) {
        do {
            val = 0;
            t10 = (CStruct *)slots.slot10;
            if (fn_8005F8E0((CStruct *)((CStruct *)t10->unk0x0)->unk0x0) == 0) {
                if ((checksum == NODE->unk0x8) || (all_flag != 0)) {
                    ret = 1;
                    fn_8005F0CC((void *)NODE->unk0x0);
                }
            } else if (GetArray(arg1, QB_MATERIALS, (s32 *)&array, 0) != 0) {
                color.r = 0x80;
                i = 0;
                color.g = 0x80;
                color.b = 0x80;
                color.a = 0x80;
                if (i < (u32)array->unk0x4) {
                    do {
                        item = (CStruct *)fn_80129528(array, i);
                        GetChecksum_2(item, 0, &checksum2, 1);
                        GetInteger(item, 0, &val, 1);
                        *(s32 *)&out = *(s32 *)&color;
                        res = fn_8005F148((void *)NODE->unk0x0, checksum2, val, (s32 *)&out);
                        ret = (ret != 0) | (res != 0);
                        i += 1;
                    } while (i < (u32)array->unk0x4);
                }
            } else if (GetChecksum_2(arg1, QB_MATERIAL, &checksum2, 0) != 0) {
                color2.r = 0x80;
                color2.g = 0x80;
                color2.b = 0x80;
                color2.a = 0x80;
                if (GetArray(arg1, QB_PASS, (s32 *)&array2, 0) != 0) {
                    j = 0;
                    if (j < (u32)array2->unk0x4) {
                        do {
                            *(s32 *)&out = *(s32 *)&color2;
                            res = fn_8005F148((void *)NODE->unk0x0, checksum2,
                                              fn_801293FC(array2, j), (s32 *)&out);
                            ret = (ret != 0) | (res != 0);
                            j += 1;
                        } while (j < (u32)array2->unk0x4);
                    }
                } else if (GetInteger(arg1, QB_PASS, &val, 1) != 0) {
                    *(s32 *)&out = *(s32 *)&color2;
                    res = fn_8005F148((void *)NODE->unk0x0, checksum2, val, (s32 *)&out);
                    ret = (ret != 0) | (res != 0);
                }
            }
            cur_tmp = (CStruct *)slots.slot10;
            head_tmp = (void *)slots.slot8;
            temp_r0 = (void *)cur_tmp->unk0x4;
            slots.slot10 = temp_r0;
        } while (temp_r0 != head_tmp);
    }
    return ret;
}
