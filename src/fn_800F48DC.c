// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F48DC-0x800F49A0 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
	char _00[0x10];
	s16 off10;
	s16 _12;
	void *(*fn14)(void *);
} VtA;

typedef struct {
	char _00[0x20];
	void *unk20;
	char _24[0x2C];
	VtA *vt50;
	void *p54;
} S;

s32 fn_800F3A6C(void *);
void fn_800F3794(void *, void *, void *);
s32 fn_80013788(void *);
S *fn_800F38B8(S *);
void fn_80056660(void *, void *, s32);
void *fn_80056AD0(void *, s32);

void fn_800F48DC(S *arg0, void *arg1, void *arg2) {
	S *obj;
	void *t;
	register char *e __asm__("r29");
	s16 o;

	obj = fn_800F38B8(arg0);
	t = obj->vt50->fn14((char *)obj + obj->vt50->off10);

	fn_80056660(t, arg1, *(s32 *)((char *)arg0->p54 + 4));

	e = (char *)arg0->vt50;
	o = *(s16 *)(e + 0x58);
	e = e + 0x58;
	((s32 (*)(void *, void *))*(s32 *)(e + 4))((char *)arg0 + (s32)o,
	                                                fn_80056AD0(t, 0));

	fn_800F3A6C(arg0->p54);
	arg0->p54 = 0;
	if (arg0->unk20 != 0) {
		fn_80013788(arg0->unk20);
		arg0->unk20 = 0;
	}
	fn_800F3794(arg0, arg1, arg2);
}
