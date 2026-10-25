// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034994-0x80034A28 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad0x0[0x1C]; f32 unk0x1C; } T34994_anim;
typedef struct { char pad0x0[0x20C]; s32 unk0x20C; s32 unk0x210; } T34994_state;
typedef struct {
    char pad0x0[0x18];
    T34994_anim *unk0x18;
    T34994_state *unk0x1C;
    Unk_DB0E2BAB *unk0x20;
} T34994_obj;
s32 fn_8006FB50(T34994_state *, s32);
void fn_8002A3E0(Unk_DB0E2BAB *, void *, void *, s32, f32, s32, T34994_state *);
Unk_DB0E2BAB *fn_80033604(T34994_obj *);
bool fn_80034994(T34994_obj *arg0, void *arg1) {
    s32 temp_r9;
    s32 var_r0;
    T34994_anim *temp_r9_2;
    f32 farg0;

    temp_r9 = fn_80033604(arg0)->unk0x8;
    __asm__ volatile("" : "+r"(temp_r9));
    var_r0 = (temp_r9 != 0) ? temp_r9 + 0x408 : 0;
    arg0->unk0x1C->unk0x20C = var_r0;
    arg0->unk0x1C->unk0x210 = fn_80033604(arg0)->unk0xC;
    temp_r9_2 = arg0->unk0x18;
    farg0 = temp_r9_2->unk0x1C;
    __asm__("" : "+f"(farg0));
    fn_8002A3E0(arg0->unk0x20, arg1, arg1 + 0x400, arg1 + 0x800, farg0, -1, arg0->unk0x1C);
    fn_8006FB50(arg0->unk0x1C, 1);
    return true;
}
