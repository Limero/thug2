// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012A544-0x8012A8F0 (940B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern void *lbl_802FFE98;

typedef struct {
    char pad0x0[0x12C];
    void *unk0x12C;
} Mgr;

typedef struct {
    s32 unk0x0;
    f32 f4;
    f32 f8;
} A5Obj;

typedef struct {
    s32 unk0x0;
    f32 f4;
    f32 f8;
    f32 fC;
} A6Obj;

void fn_80126A30(void *);
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
void fn_80129068(void *, s32, u8);
void fn_8012CB2C();
s32 CreateString(char *);
u32 strlen(char *);
void *fn_80128EF4(s32);
void *fn_80125000(void *);
void *fn_80128F44(s32);
void *fn_80124FDC(void *);
void *CStruct_new(s32);
void *CStruct_ctor(void);
u8 *fn_80129EA0(void *, u8 *);
void *fn_8003E7CC(s32);
void *fn_80128F94(void *);
void fn_80129260(void *, s32, s32);
void fn_80129284(void *, s32, f32);
void fn_801292A8(void *, s32, s32);
void fn_80129218(void *, s32, s32);
void fn_8012923C(void *, s32, s32);
void fn_801292F0(void *, s32, void *);
void fn_801292CC(void *, s32, void *);
void fn_80129314(void *, s32, void *);
void fn_80129338(void *, s32, void *);

void *fn_8012A544(void *arg0, u8 *arg1) {
    u8 *p = arg1;
    u32 n;
    s32 tag;
    u32 i;
    u32 j;

    fn_80126A30(arg0);
    tag = *p++;
    n = *p++;
    n += *p++ << 8;
    fn_8000F2F8(lbl_802FFE98, ((Mgr *)lbl_802FFE98)->unk0x12C);
    fn_80129068(arg0, n, tag);
    fn_8000F320(lbl_802FFE98);

    if (tag == 4) goto case4;
    if (tag > 4) goto tags_above_4;
    if (tag == 1) goto case1;
    if (tag <= 1) goto done;
    if (tag == 2) goto case2;
    if (tag == 3) goto case3;
    goto done;

tags_above_4:
    if (tag == 10) goto case10;
    if (tag > 10) goto tags_above_10;
    if (tag == 5) goto case5;
    if (tag == 6) goto case6;
    goto done;

tags_above_10:
    if (tag == 12) goto case12;
    if (tag == 13) goto case13;
    goto done;

case1:
    for (i = 0; i < n; i++) {
        s32 v;
        fn_8012CB2C(&v, p);
        p += 4;
        fn_80129260(arg0, i, v);
    }
    goto done;

case2:
    for (i = 0; i < n; i++) {
        f32 v;
        fn_8012CB2C(&v, p);
        p += 4;
        fn_80129284(arg0, i, v);
    }
    goto done;

case13:
    for (i = 0; i < n; i++) {
        s32 v;
        fn_8012CB2C(&v, p);
        p += 4;
        fn_801292A8(arg0, i, v);
    }
    goto done;

case3:
    for (i = 0; i < n; i++) {
        s32 s = CreateString((char *)p);
        fn_80129218(arg0, i, s);
        p += strlen((char *)p) + 1;
    }
    goto done;

case4:
    for (i = 0; i < n; i++) {
        s32 s = CreateString((char *)p);
        fn_8012923C(arg0, i, s);
        p += strlen((char *)p) + 1;
    }
    goto done;

case5:
    for (j = 0; j < n; j++) {
        f32 a;
        f32 b;
        A5Obj *o;
        o = fn_80128EF4(0xC);
        o = fn_80125000(o);
        fn_8012CB2C(&a, p);
        p += 4;
        o->f4 = a;
        fn_8012CB2C(&b, p);
        p += 4;
        o->f8 = b;
        fn_801292F0(arg0, j, o);
    }
    goto done;

case6:
    for (j = 0; j < n; j++) {
        f32 a;
        f32 b;
        f32 c;
        A6Obj *o;
        o = fn_80128F44(0x10);
        o = fn_80124FDC(o);
        fn_8012CB2C(&a, p);
        p += 4;
        o->f4 = a;
        fn_8012CB2C(&b, p);
        p += 4;
        o->f8 = b;
        fn_8012CB2C(&c, p);
        p += 4;
        o->fC = c;
        fn_801292CC(arg0, j, o);
    }
    goto done;

case10:
    for (j = 0; j < n; j++) {
        void *o;
        o = CStruct_new(8);
        o = CStruct_ctor();
        p = fn_80129EA0(o, p);
        fn_80129314(arg0, j, o);
    }
    goto done;

case12:
    for (j = 0; j < n; j++) {
        void *o;
        o = fn_8003E7CC(0xC);
        o = fn_80128F94(o);
        p = fn_8012A544(o, p);
        fn_80129338(arg0, j, o);
    }

done:
    return p;
}
