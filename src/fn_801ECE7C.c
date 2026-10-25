// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ECE7C-0x801ED044 (456B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80032088(s32 arg0);
extern s32 fn_8012ED98(s32 * arg0);
extern void fn_8012F260(Unk_15EF4A35 * arg0, s32 arg1, Unk_C8FEE62D * arg2, CStruct * arg3);
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_8012954C(CStruct * arg0, s32 arg1);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
extern void fn_801F0E84(CScript * arg0);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);
extern void fn_801309EC(Unk_DB0E2BAB * arg0);

extern s32 fn_80032088(s32 arg0);
extern s32 fn_8012ED98(s32 * arg0);
extern void fn_8012F260(Unk_15EF4A35 * arg0, s32 arg1, Unk_C8FEE62D * arg2, CStruct * arg3);
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_8012954C(CStruct * arg0, s32 arg1);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
extern void fn_801F0E84(CScript * arg0);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);
extern void fn_801309EC(Unk_DB0E2BAB * arg0);

void fn_801ECE7C(void *arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    register void *a0 __asm__("r29");
    s32 var_r31;
    s32 flags;
    Unk_C8FEE62D *obj;

    a0 = arg0;
    obj = *((void * *)&((Unk_8BDA5B95 *)a0)->unk0xC);
    if (obj->unk0x14 == 0) {
        obj->unk0x14 = fn_8012ED98(fn_80032088(0xF8));
    }
    if (((Unk_8BDA5B95 *)a0)->unk0x35C != 0) {
        fn_8012F260(*(s32 *)((char *)(((Unk_8BDA5B95 *)a0)->unk0xC) + 0x14), 0xF7CA3F78u, 0,
                    ((Unk_8BDA5B95 *)a0)->unk0xC);
    } else {
        var_r31 = 0;
        switch (arg1) {
        case 0:
            break;
        case 1:
            var_r31 = 1;
            break;
        case 2:
            var_r31 = 2;
            break;
        case 3:
            var_r31 = 3;
            break;
        case 4:
            var_r31 = 4;
            break;
        case 5:
            var_r31 = 5;
            break;
        case 6:
            var_r31 = 6;
            break;
        case 7:
            var_r31 = 7;
            break;
        case 8:
            var_r31 = 8;
            break;
        }
        var_r31 = fn_8012954C(fn_801259C8(0x2AB3341Du, 0), var_r31);
        flags = 0;
        if (arg2 != 0) {
            flags = 1;
        }
        if (arg3 != 0) {
            flags |= 2;
        }
        if (arg4 != 0) {
            flags |= 4;
        }
        if (arg5 != 0) {
            flags |= 8;
        }
        ((Unk_8BDA5B95 *)a0)->unk0x428 = 0;
        fn_801F0E84(GetChecksum_3(((Unk_8BDA5B95 *)a0)->unk0xC, 0x488AF07Au));
        fn_8012F260(*(s32 *)((char *)(((Unk_8BDA5B95 *)a0)->unk0xC) + 0x14),
                    GetChecksum(var_r31, flags), 0,
                    ((Unk_8BDA5B95 *)a0)->unk0xC);
    }
    fn_801309EC(*(s32 *)((char *)(((Unk_8BDA5B95 *)a0)->unk0xC) + 0x14));
    *(s32 *)(((Unk_8BDA5B95 *)a0)->unk0x15BC + 0x144) = 1;
}
