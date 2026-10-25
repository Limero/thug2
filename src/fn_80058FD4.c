// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058FD4-0x80058FE8 (20B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// IDENTIFIED (2026-09-01): float field compare — returns
// farg0 < obj->0x1C via fcmpu cr7 + extrwi (cr7.LT). m2c inferred `==`
// from the flag extract; the actual source is `<` (only `<` reproduces
// the extrwi 1,28 word). Part of the 0x80058xxx float/object helper
// cluster. Suggested rename: CmpFloatField1C.
#include "types.h"
#include "structs.h"
s32 fn_80058FD4(Unk_31DE137E *arg0, f32 farg0) {
    return farg0 < *((f32 *)&arg0->unk0x1C);
}
