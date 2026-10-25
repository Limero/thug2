// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044C64-0x80044D98 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct Elem_t {
    char p00[0x70];
    struct Elem_t *next;
    char p74[0x144];
    s32 unk0x1B8;
    s32 unk0x1BC;
} Elem_t;

typedef struct {
    char p00[0x64];
    Elem_t *first;
    char p68[0x15C];
    s32 unk0x1C4;
    s32 unk0x1C8;
    char p1CC[4];
    f32 unk0x1D0;
    f32 unk0x1D4;
    s32 unk0x1D8;
    s32 unk0x1DC;
} Obj_t;

void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void CTextElement_AttachBlurEffect(void *);
void CTextElement_DetachBlurEffect(void *);
void CTextElement_SetShadowState(void *, s32);
void fn_80042F38(void *, f32, f32);

void fn_80044C64(Obj_t *arg0) {
    s32 *sp8;
    s32 *temp_r31;
    s32 *temp_r3;
    s32 *temp_r0;
    register s32 *entry_copy __asm__("r3");
    register s32 *loop_copy __asm__("r3");
    s32 padA;
    s32 padB;

    ((Unk_59AB5482 *)&sp8)->unk0x4 = 0;
    ((Unk_59AB5482 *)&sp8)->unk0x8 = 0;
    temp_r3 = arg0->first;
    sp8 = temp_r3;
    if (temp_r3 != NULL) {
        CObject_AddRefLink(temp_r3, &sp8);
    }
    temp_r0 = sp8;
    entry_copy = temp_r0;
    __asm__("" : "+r"(entry_copy));
    if (temp_r0 != NULL) {
        do {
            if (arg0->unk0x1C4 != 0) {
                CTextElement_AttachBlurEffect((void *)sp8);
            } else {
                CTextElement_DetachBlurEffect((void *)sp8);
            }
            if (arg0->unk0x1C8 != 0) {
                CTextElement_SetShadowState((void *)sp8, 1);
            } else {
                CTextElement_SetShadowState((void *)sp8, 0);
            }
            fn_80042F38((void *)sp8, arg0->unk0x1D0, arg0->unk0x1D4);
            ((Elem_t *)sp8)->unk0x1B8 = arg0->unk0x1D8;
            ((Elem_t *)sp8)->unk0x1BC = arg0->unk0x1DC;
            temp_r31 = (s32 *)((Elem_t *)sp8)->next;
            if (sp8 != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)&sp8), &sp8);
                sp8 = NULL;
            }
            sp8 = temp_r31;
            if (temp_r31 != NULL) {
                CObject_AddRefLink(temp_r31, &sp8);
            }
            temp_r0 = sp8;
            loop_copy = temp_r0;
            __asm__("" : "+r"(loop_copy));
        } while (temp_r0 != NULL);
    }
    if (loop_copy != NULL) {
        CObject_RemoveRefLink(loop_copy, &sp8);
        sp8 = NULL;
    }
    __asm__("" : : "m"(sp8), "m"(padA), "m"(padB));
}
