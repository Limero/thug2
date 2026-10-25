// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112308-0x801123AC (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_8029CFB0[];
extern char lbl_8029CFB4[];
extern char lbl_8029CFB8[];

typedef union {
    u32 word;
    struct {
        u8 c0;
        u8 c1;
        u8 c2;
        u8 c3;
    } byte;
} ScriptColorWord;

typedef union {
    u32 word;
    struct {
        u8 r;
        u8 g;
        u8 b;
        s8 a;
    } byte;
} PackedColor;

typedef struct {
    s32 color;
    ScriptColorWord r;
    ScriptColorWord g;
    ScriptColorWord b;
    PackedColor packed;
    u32 reserved;
} ColorState;

s32 fn_80128294(CStruct *, void *, void *, s32);
void fn_80059258(void *);

void ScriptSetLightAmbientColor(CStruct *arg0) {
    ColorState state;
    ScriptColorWord *r = &state.r;

    fn_80128294(arg0, (void *)lbl_8029CFB0, r, 0);
    fn_80128294(arg0, (void *)lbl_8029CFB4, &state.g, 0);
    fn_80128294(arg0, (void *)lbl_8029CFB8, &state.b, 0);
    {
        PackedColor *packed = &state.packed;
        s32 green;
        s32 blue;

        packed->byte.r = r->byte.c3;
        green = state.g.word;
        blue = state.b.word;
        packed->byte.g = green;
        packed->byte.b = blue;
        packed->byte.a = -0x80;
        state.color = packed->word;
        fn_80059258(&state.color);
    }
}
