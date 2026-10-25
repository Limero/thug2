// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044960-0x80044ADC (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-sched-interblock
#include "types.h"

// Line-wrapping state (CText-ish object).  Offsets are all that matter.
typedef struct TextObj {
    char pad0x0[0x178];
    f32 maxWidth;  /* 0x178: wrap when line width passes this           */
    char pad0x17C[0x14];
    void *font;    /* 0x190                                          */
    char **lines;  /* 0x194: per-line buffers                         */
    s32 linesUsed; /* 0x198                                           */
    s32 lineIdx;   /* 0x19C: index into lines[]                       */
    s32 linePos;   /* 0x1A0: write cursor inside lines[lineIdx]        */
    f32 lineWidth; /* 0x1A4: width already used on the current line    */
    s32 maxLines;  /* 0x1A8                                           */
    char pad0x1AC[0x8];
    f32 scale;     /* 0x1B4: width multiplier                         */
} TextObj;

// The four loop locals of the original, as one object so ngccc lays them out
// at +0x68/+0x6C/+0x70 and leaves the (unused) 8 bytes at +0x74.
typedef struct Loc {
    char word[0x60]; /* +0x08: word filled by fn_80009818 */
    char *cursor;    /* +0x68: scan cursor (fn_80009818 in/out) */
    f32 width;       /* +0x6C: measured word width         */
    s32 height;      /* +0x70: measured word height        */
    char pad[8];     /* +0x74: unused in the want          */
} Loc;

s32 fn_80053790(void *);
s32 fn_80009818(char *, char **);
void fn_800586CC(void *, char *, f32 *, s32 *);
u32 strlen(const char *);
char *strcpy(char *, const char *);

extern f32 lbl_8029251C;

void fn_80044960(TextObj *arg0, char *arg1) {
    Loc loc;
    s32 state;
    s32 prev;
    s32 fontCtx;
    f32 x;
    f32 w;
    f32 zero;
    char *tail;
    u8 last;

    fontCtx = fn_80053790(arg0->font);
    state = 0;
    loc.cursor = arg1;
    zero = lbl_8029251C;
    do {
        prev = fn_80009818(loc.word, &loc.cursor);
        fn_800586CC(fontCtx, loc.word, &loc.width, &loc.height);
        x = arg0->lineWidth;
        w = loc.width * arg0->scale;
        loc.width = w;
        if (((x > zero) && ((x + w) > arg0->maxWidth)) || (state == 1) ||
            ((u32)(arg0->linePos + strlen(loc.word)) > 0x5FU)) {
            /* line overflows: trim the trailing space of the finished line
               and advance to the next one. */
            tail = arg0->linePos + (s32)arg0->lines[arg0->lineIdx];
            last = *(u8 *)(tail - 1);
            if (last == 0x20) {
                *(u8 *)(tail - 1) = 0;
            }
            arg0->linesUsed = arg0->linesUsed + 1;
            arg0->lineIdx = arg0->lineIdx + 1;
            if (arg0->lineIdx >= arg0->maxLines) {
                arg0->lineIdx = 0;
            }
            arg0->linePos = 0;
            arg0->lineWidth = zero;
        }
        state = prev;
        strcpy(arg0->lines[arg0->lineIdx] + arg0->linePos, loc.word);
        arg0->linePos = arg0->linePos + strlen(loc.word);
        arg0->lineWidth = arg0->lineWidth + loc.width;
    } while (state != 2);
}
