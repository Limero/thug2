// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041E54-0x80041F08 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_801293FC(CStruct *, s32);

bool CScreenElement_resolve_rgba(s32 self, CStruct *ctx, s32 color_id, s32 *out) {
    CStruct *arr;

    if (GetArray(ctx, color_id, &arr, 0)) {
        u32 acc = 0;
        s32 i = 0;
        s32 count = arr->unk0x4;

        if ((s32)acc < count) {
            s32 shift = 0;
            do {
                acc |= (fn_801293FC(arr, i++) & 0xFF) << shift;
                shift += 8;
            } while (i < count);
        }
        acc = (acc >> 24) | ((acc >> 8) & 0xFF00) | ((acc << 8) & 0xFF0000) | (acc << 24);
        *out = acc;
        return true;
    }
    return false;
}
