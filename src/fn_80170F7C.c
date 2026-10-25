// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80170F7C-0x80170FB4 (56B). Byte-identical.
#include "types.h"
extern s32 fn_8016F668(void);
typedef struct { char pad[0x15C]; s32 arr[0x100][0x64]; } T;
s32 fn_80170F7C(T *arg0) {
    return arg0->arr[fn_8016F668()][0];
}
