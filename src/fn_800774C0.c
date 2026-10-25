// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800774C0-0x80077590 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void *fn_80024660(void *);
void *fn_800246AC(void *);
void *fn_8001D440(void *, f32, f32, f32);
void fn_800967B8(void *, void *, void *);

typedef struct { f32 x, y, z; } Vec3;

typedef struct { char pad0x20[0x20]; f32 x, y, z; } Row2;

typedef struct { char pad0x0[0xC]; void *unk0xc; } Unk_C7387A53;

void fn_800774C0(Unk_C7387A53 *arg0, void *arg1) {
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;

    fn_8001D440(&v1, ((f32 *)fn_80024660(arg1))[0],
                     ((f32 *)fn_80024660(arg1))[1],
                     ((f32 *)fn_80024660(arg1))[2]);
    fn_8001D440(&v2, v1.x + ((Row2 *)fn_800246AC(arg1))->x,
                     v1.y + ((Row2 *)fn_800246AC(arg1))->y,
                     v1.z + ((Row2 *)fn_800246AC(arg1))->z);
    fn_800967B8(arg0->unk0xc, &v1, &v2);
}
