// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5E8C-0x800A5F38 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct A5E8C_vt {
	s32 f0;
	s32 f4;
	s16 off8;
	s16 p8a;
	void *fnc;
} A5E8C_vt;

typedef struct A5E8C_node {
	s32 f0;
	s32 f4;
	s32 f8;
	struct A5E8C_node *fc;
	struct A5E8C_node *f10;
	A5E8C_vt *vt;
} A5E8C_node;

typedef struct A5E8C_obj {
	s32 f0[4];
	struct A5E8C_node *head;
} A5E8C_obj;

void fn_800A5E8C(A5E8C_obj *arg0, s32 arg1) {
	A5E8C_node *n;
	A5E8C_node *w;
	A5E8C_node *found = NULL;
	A5E8C_vt *vt;

	w = arg0->head;
	found = NULL;
	if (w->f4 == -1) {
		w = NULL;
	}
	n = w;
	while (n != NULL) {
		if (n->f4 == arg1) {
			found = n;
			break;
		}
		n = n->fc;
		if (n->f4 == -1) {
			n = NULL;
		}
	}
	if (found != NULL) {
		found->f10->fc = found->fc;
		found->fc->f10 = found->f10;
		found->fc = found;
		found->f10 = found;
		vt = found->vt;
		((void (*)(void *, s32))vt->fnc)((char *)found + vt->off8, 3);
	}
}
