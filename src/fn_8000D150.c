// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000D150-0x8000D33C (492B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    s32 pad0x0;
    struct CStruct *unk0x4;
    struct CStruct *unk0x8;
    struct CStruct *unk0xC;
    s32 unk0x10;
    struct CStruct *unk0x14;
} D150Object;

struct CStruct *fn_8000CCF4(struct CStruct *, s8 *);
s32 fn_8000CE8C(struct CStruct *, struct CStruct *);
void fn_8000EB24(struct CStruct *);
struct CStruct *fn_8000EB38(struct CStruct *, s32);
u32 strlen(s8 *);
extern s32 lbl_802FFE48;

struct CStruct *fn_8000D150(D150Object *arg0, s8 *arg1) {
    s8 sp8[0x80];
    s8 *dst = sp8;
    s8 *src = arg1;
    s32 len = 0;
    struct CStruct *entry;
    struct CStruct *res;

    sp8[0] = src[0];
    if (src[0] != 0) {
        do {
            if (dst[0] == '/') {
                dst[0] = '\\';
            }
            len++;
            *++dst = *++src;
        } while (src[0] != 0);
    }
    if (strlen(sp8) > 0xB) {
        if (sp8[len - 1] == 'e' &&
            sp8[len - 2] == 'r' &&
            sp8[len - 3] == 'p' &&
            sp8[len - 4] == '.' &&
            sp8[len - 5] == 's' &&
            sp8[len - 6] == 't' &&
            sp8[len - 7] == 'p' &&
            sp8[len - 8] == 'i' &&
            sp8[len - 9] == 'r' &&
            sp8[len - 10] == 'c' &&
            sp8[len - 11] == 's') {
            s8 c_i = sp8[len - 8];
            s8 c_s = sp8[len - 11];
            switch (lbl_802FFE48) {
            case 3:
                sp8[len - 1] = 'f';
                break;
            case 4:
                sp8[len - 1] = c_s;
                break;
            case 5:
                sp8[len - 1] = 'd';
                break;
            case 6:
                sp8[len - 1] = c_i;
                break;
            default:
                sp8[len - 1] = 'e';
                break;
            }
        }
    }
    fn_8000EB24(arg0->unk0x14);
    for (;;) {
        entry = fn_8000EB38(arg0->unk0x14, 0);
        if (entry == 0) {
            break;
        }
        res = fn_8000CCF4(entry, sp8);
        if (res == 0) {
            continue;
        }
        arg0->unk0x4 = entry;
        arg0->unk0x8 = res;
        arg0->unk0xC = fn_8000CE8C(entry, res);
        return res;
    }
    return 0;
}
