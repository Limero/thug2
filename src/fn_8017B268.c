// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017B268-0x8017B390 (296B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern void *fn_8021D358(void *, s32);
extern void *CStruct_new(s32);
extern void *CStruct_ctor(void *);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_801279A0(CStruct *, s32, CStruct *);
extern void AddChecksum(CStruct *, s32, s32);
extern void Script_RunScript(s32, void *, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);

s32 fn_8017B268(void **arg0) {
    __ps_t sp8[2];
    CStruct *in;
    CScript *res;
    s32 count;
    register s32 var_r28 __asm__("r28");
    register __ps_t *out __asm__("r27");
    __ps_t *w;

    in = *arg0;
    res = fn_8021D358((void *)lbl_80305F9C, (u16)(s8)*(u8 *)in);
    if (res == NULL) {
        return 4;
    }
    count = in->unk0x4;
    var_r28 = 0;
    res->unk0x38 = count;
    if (var_r28 < count) {
        w = (__ps_t *)((char *)in + 8);
        out = sp8;
        do {
            void *obj = CStruct_ctor(CStruct_new(8));

            AddInteger(obj, QB_INDEX, var_r28);
            AddInteger(obj, QB_OBJID, *(s32 *)(res->unk0x18 + 0x18));
            sp8[0] = w[0];
            out[1] = w[1];
            fn_801279A0(obj, QB_POS, out);
            AddChecksum(obj, QB_SHOW_NOW, QB_SHOW_NOW);
            Script_RunScript(QB_DROPSHOBJECT, obj, res->unk0x18, 0, 0);
            if (obj != NULL) {
                CStruct_delete(obj, 3);
            }
            var_r28++;
            w += 2;
        } while (var_r28 < res->unk0x38);
    }
    return 1;
}
