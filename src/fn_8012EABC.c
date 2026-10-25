// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EABC-0x8012EBC4 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 strlen(const char *);
s32 strcasecmp(const char *, const char *);
char *fn_8000B58C(void);
void fn_8000F2F8(void *, s32);
s32 fn_800127E4(void *, s32, s32, s32, s32);
void fn_8000F320(void *);
void fn_8012E604(s32, s32, s32);
void fn_8012E228(s32, s32, s32, s32, s32);
void fn_80126468(void *);
void fn_80012A10(s32);
void fn_8012EA18(void);
extern char lbl_802FFE98[];

/* File-local: the corpus-merged classes type 0x118 as pad and 0x12C as s32, but
 * the same object is read at BOTH offsets (0x12C in the `.ext` arm, 0x118 in
 * the other), and the merged class has no member at 0x118, so m2c fell back
 * to a raw `*(s32 *)` word read.  Every gap is an explicit char pad (§6dy/§6de). */
typedef struct {
    char pad0x0[0x118];
    s32 unk0x118;
    char pad0x11C[0x10];
    s32 unk0x12C;
} EABC_t;

void fn_8012EABC(void * arg0, s32 arg1, s32 arg2) {
    s32 len;
    s32 ext;
    char *end;
    register s32 ret __asm__("r29");
    EABC_t *obj;

    len = strlen((const char *)arg0);
    ext = (s32)fn_8000B58C();
    end = (char *)len + (s32)arg0;
    if (*(u8 *)(end - 4) == 0x2E && strcasecmp(end - 3, (const char *)ext) == 0) {
        obj = (EABC_t *)(*(void **)lbl_802FFE98);
        fn_8000F2F8(obj, obj->unk0x12C);
        ret = fn_800127E4(arg0, 0, 0, 0, 0);
        fn_8000F320(*(void **)lbl_802FFE98);
        fn_8012E604(arg0, ret, arg1);
        fn_80126468(arg0);
    } else {
        obj = (EABC_t *)(*(void **)lbl_802FFE98);
        fn_8000F2F8(obj, obj->unk0x118);
        ret = fn_800127E4(arg0, 0, 0, 0, 0);
        fn_8000F320(*(void **)lbl_802FFE98);
        fn_8012E228(arg0, ret, arg1, 0, arg2);
        fn_80012A10(arg0);
    }
    fn_8012EA18();
}
