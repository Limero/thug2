// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126BF0-0x80126E28 (568B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

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

void *CreateString(char *arg0);
void *fn_80128EF4(s32 arg0);
void *fn_80125000(void *arg0);
void *fn_80128F44(s32 arg0);
void *fn_80124FDC(void *arg0);
void *CStruct_new(s32 arg0);
void *CStruct_ctor(void *arg0);
void fn_80126E28(void *arg0, void *arg1);
s32 fn_80126F40(void *arg0, void *arg1);
void *fn_8003E7CC(s32 arg0);
void *fn_80128F94(void *arg0);

void fn_80126BF0(void **arg0, void **arg1, u32 arg2, s32 arg3) {
    u32 n = arg2;

    switch (arg3) {
    case 1:
    case 2:
    case 13: {
        u32 i = 0;
        if (i < n) {
            do {
                void *t = *arg1;
                arg1++;
                *arg0 = t;
                arg0++;
                i++;
            } while (i < n);
        }
        break;
    }
    case 3:
    case 4: {
        u32 i = 0;
        void **s = arg1;
        void **d = arg0;
        if (i < n) {
            do {
                char *e = *s;
                if (e != NULL) {
                    *d = CreateString(e);
                }
                i++;
                s++;
                d++;
            } while (i < n);
        }
        break;
    }
    case 5: {
        u32 i = 0;
        void **s = arg1;
        void **d = arg0;
        if (i < n) {
            do {
                A5Obj *e = *s;
                if (e != NULL) {
                    A5Obj *o = fn_80125000(fn_80128EF4(0xC));
                    o->f4 = e->f4;
                    o->f8 = e->f8;
                    *d = o;
                }
                i++;
                s++;
                d++;
            } while (i < n);
        }
        break;
    }
    case 6: {
        u32 i = 0;
        void **s = arg1;
        void **d = arg0;
        if (i < n) {
            do {
                A6Obj *e = *s;
                if (e != NULL) {
                    A6Obj *o = fn_80124FDC(fn_80128F44(0x10));
                    o->f4 = e->f4;
                    o->f8 = e->f8;
                    o->fC = e->fC;
                    *d = o;
                }
                i++;
                s++;
                d++;
            } while (i < n);
        }
        break;
    }
    case 10: {
        u32 i = 0;
        void **s = arg1;
        void **d = arg0;
        if (i < n) {
            do {
                void *e = *s;
                if (e != NULL) {
                    void *o = CStruct_ctor(CStruct_new(8));
                    fn_80126F40(o, e);
                    *d = o;
                }
                i++;
                s++;
                d++;
            } while (i < n);
        }
        break;
    }
    case 12: {
        u32 i = 0;
        void **s = arg1;
        void **d = arg0;
        if (i < n) {
            do {
                void *e = *s;
                if (e != NULL) {
                    void *o = fn_80128F94(fn_8003E7CC(0xC));
                    fn_80126E28(o, e);
                    *d = o;
                }
                i++;
                s++;
                d++;
            } while (i < n);
        }
        break;
    }
    }
}
