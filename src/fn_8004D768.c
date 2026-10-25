// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D768-0x8004DA9C (820B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80300434[];
extern CStruct * lbl_80297F18;
extern f32 lbl_80292958;

typedef struct {
    void *f0;
    void *f4;
    void *f8;
    void *fC;
} Ref;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, void *, s32);
s32 GetString(CStruct *, s32, void *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void *fn_8012935C(CStruct *, s32);
s32 fn_80053790(s32);
s32 fn_80009818(s8 *, void **);
void fn_800586CC(void *, s8 *, void *, void *);
CStruct *CStruct_new(s32);
CStruct *CStruct_ctor(CStruct *);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void AddString(CStruct *, s32, void *);
void fn_8004A800(CStruct *, Unk_C7387A53 *, s32, s32, CStruct *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CStruct_delete(CStruct *, s32);
u32 strlen(const char *);
char *strcpy(char *, const char *);

bool ScriptCreateMultipleTextElements(CStruct *pScript) {
    char word[0x60];
    char line[0x200];
    Ref handle;
    struct {
        s32 id;
        CStruct *arr;
        void *index;
        s32 fontId;
        f32 maxWidth;
        void *cursor;
        f32 textWidth;
        s32 textHeight;
        s32 pad[2];
    } sc;

    s32 prevTok;
    s32 tok;
    s32 lineLen;
    s32 wrapped;
    register u32 wordIdx __asm__("r25");
    CStruct *mgr;
    CStruct *font;
    register CStruct *elem __asm__("r30");
    f32 startY;

    prevTok = 0;
    sc.id = 0;
    GetChecksum_2(pScript, QB_ID, &sc.id, 0);
    sc.arr = 0;
    wordIdx = 0;
    sc.index = 0;
    mgr = *(s32 *)&lbl_80300434;
    if (GetArray(pScript, QB_TEXT, &sc.arr, 0) != 0) {
        sc.index = fn_8012935C(sc.arr, 0);
    } else {
        GetString(pScript, QB_TEXT, &sc.index, 1);
    }
    prevTok = 0;
    GetChecksum_2(pScript, QB_FONT, &sc.fontId, 1);
    lineLen = 0;
    GetFloat(pScript, QB_WIDTH, &sc.maxWidth, 1);
    font = fn_80053790(sc.fontId);
    sc.cursor = sc.index;
    startY = lbl_80292958;
    do {
        tok = fn_80009818(word, &sc.cursor);
        if ((sc.arr != 0) && (tok == 2) && (wordIdx < (u32)sc.arr->unk0x4 - 1)) {
            void *next;
            wordIdx += 1;
            next = fn_8012935C(sc.arr, wordIdx);
            sc.index = next;
            sc.cursor = next;
            if (prevTok != 1) {
                u32 n = strlen(word);
                word[n] = 0x20;
                word[n + 1] = 0;
            }
            tok = 0;
        }
        fn_800586CC(font, word, &sc.textWidth, &sc.textHeight);
        wrapped = 0;
        if (((startY > lbl_80292958) && ((startY + sc.textWidth) > sc.maxWidth)) || (prevTok == 1) ||
            ((u32)(lineLen + strlen(word)) > 0x5FU)) {
            wrapped = 1;
            if (line[lineLen - 1] == 0x20) {
                line[lineLen - 1] = 0;
            }
            startY = lbl_80292958;
            lineLen = 0;
            elem = CStruct_ctor(CStruct_new(8));
            fn_80126FF4(elem, pScript);
            AddString(elem, QB_TEXT, line);
            fn_8004A800(&handle, mgr, QB_TEXTELEMENT, lbl_80297F18, elem);
            if (handle.f0 != 0) {
                CObject_RemoveRefLink(handle.f0, &handle);
                handle.f0 = 0;
            }
            if (elem != 0) {
                CStruct_delete(elem, 3);
            }
        }
        strcpy(line + lineLen, word);
        lineLen += strlen(word);
        startY += sc.textWidth;
        if ((tok == 2) && (wrapped == 0)) {
            elem = CStruct_ctor(CStruct_new(8));
            fn_80126FF4(elem, pScript);
            AddString(elem, QB_TEXT, line);
            fn_8004A800(&handle, mgr, QB_TEXTELEMENT, lbl_80297F18, elem);
            if (handle.f0 != 0) {
                CObject_RemoveRefLink(handle.f0, &handle);
                handle.f0 = 0;
            }
            if (elem != 0) {
                CStruct_delete(elem, 3);
            }
        }
        prevTok = tok;
    } while (prevTok != 2);
    return true;
}
