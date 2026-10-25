// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F1A8-0x8012F260 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-strength-reduce
#include "types.h"
#include "structs.h"
// FLAG: -fno-strength-reduce
extern void *lbl_802FFE98;
extern u8 *fn_8012D0D8(u8 *);
extern void fn_8000F2F8(void *arg0, s32 arg1);
extern void *Mem_Alloc_3(s32);
extern void fn_8000F320(void *arg0);
extern void fn_8012F064(Unk_C7387A53 *arg0, s32 arg1, void *arg2, Unk_C8FEE62D *arg3, CStruct *arg4);
typedef struct {
    s32 unk0x0;
    u8 *unk0x4;
} ScriptStr;

void fn_8012F1A8(Unk_C7387A53 *arg0, ScriptStr *arg1, Unk_C8FEE62D *arg2, CStruct *arg3) {
    void *buf;
    u32 size;
    u32 i;
    u8 *src;
    u8 *dst;

    size = fn_8012D0D8(arg1->unk0x4) - arg1->unk0x4;
    fn_8000F2F8(lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x12C);
    buf = Mem_Alloc_3(size);
    fn_8000F320(lbl_802FFE98);
    i = 0;
    src = arg1->unk0x4;
    dst = (u8 *)buf;
    while (i < size) {
        *dst = *src;
        dst = dst + 1;
        src = src + 1;
        i = i + 1;
    }
    fn_8012F064(arg0, arg1->unk0x0, buf, arg2, arg3);
    arg0->unk0xC = (s32)buf;
}
