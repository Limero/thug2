// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131008-0x80131154 (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* fn_80125480() result: opcode byte at +2, fn/handler pointer at +0xC
   (matches Unk_ECD1B899's u8 unk0x2 in src/fn_801316D8.c / fn_8013465C.c). */
typedef struct ScriptOp {
    char pad0x0[0x2];
    u8 opcode;
    char pad0x3[0x9];
    void *unk_C;
} ScriptOp;

/* arg2's callee table (loaded with lwz r9, 8(arg2)). */
typedef struct ScriptBytecode {
    char pad0x0[0x18];
    s16 base_off;
    void (*unk_1C)(void *, s32, s32, s32);
} ScriptBytecode;

typedef struct ScriptRunCtx {
    char pad0x0[0x8];
    ScriptBytecode *unk_8;
} ScriptRunCtx;

/* lbl_802FFE98's pointee (lwz r4, 0x12c(r3)). */
typedef struct ScriptVM {
    char pad0x0[0x12C];
    s32 unk_12C;
} ScriptVM;

extern s32 lbl_802FFE98;
extern void *fn_80125480(s32);
extern void fn_80130F40(s32, s32, void *);
extern void fn_8012FAFC(void *, s32, void *, s32);
extern void fn_8000F2F8(void *, s32);
extern s32 fn_80032088(s32);
extern void *fn_8012ED98(s32 *);
extern void fn_8012F260(void *, void *, void *, void *);
extern void fn_8000F320(void *);
extern s32 fn_801309EC(void *);
extern void fn_8012EE64(void *, s32);

void Script_RunScript(s32 arg0, s32 arg1, ScriptRunCtx *arg2, s32 arg3) {
    ScriptOp *op;
    ScriptBytecode *bc;
    void *scratch;

    op = fn_80125480(arg0);
    if ((op != NULL) && ((u32) (op->opcode - 7) <= 2U)) {
        if (arg3 != 0) {
            fn_80130F40(arg0, arg1, arg2);
        }
        switch (op->opcode) {
        case 8:
            ((void (*)(s32, s32))op->unk_C)(arg1, 0);
            break;
        case 9:
            if (op->unk_C != NULL) {
                fn_8012FAFC(op->unk_C, arg1, arg2, 0);
                break;
            }
            bc = arg2->unk_8;
            ((void (*)(void *, s32, s32, s32))bc->unk_1C)((void *)((char *)arg2 + bc->base_off), arg0, arg1, 0);
            break;
        case 7:
            fn_8000F2F8((void *)lbl_802FFE98, ((ScriptVM *)lbl_802FFE98)->unk_12C);
            scratch = fn_8012ED98(fn_80032088(0xF8));
            fn_8012F260(scratch, arg0, arg1, arg2);
            fn_8000F320((void *)lbl_802FFE98);
            while (fn_801309EC(scratch) != 0) {
            }
            if (scratch != 0) {
                fn_8012EE64(scratch, 3);
            }
            break;
        }
    }
}
