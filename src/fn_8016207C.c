// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016207C-0x80162174 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void* lbl_80305EAC;
extern Unk_9994C3F5 * lbl_80366474;
extern void memset(void *, s32, u32);
extern void GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_80174A58(void *, CStruct *);
extern s32 fn_8003AE20(Unk_31DE137E *);
extern s32 fn_8005CF80(Unk_9994C3F5 *, s32);
extern void fn_8005C54C(s32, void *);
extern s32 fn_8005C4E4(s32);
extern s32 fn_8005C68C(s32);
extern void fn_8005C518(s32, void *, s32);
extern s32 fn_8005C448(s32);
extern s32 fn_8005C47C(s32);
extern void fn_8003E9B8(s32, void *, s32);

bool ScriptSetFaceTextureFromVideoCapture(CStruct *pParams, CScript *pScript) {
    char buf[0x4420];
    s32 sp4428;
    char *dst;
    s32 tex;
    s32 width;
    s32 pixels;
    s32 size;
    s32 mat;

    dst = &buf[0x20];
    GetChecksum_2(pParams, QB_CAPTURED_TEXTURE, &sp4428, 1);
    mat = fn_8003AE20(fn_80174A58(lbl_80305EAC, 0) + 4);
    tex = fn_8005CF80(lbl_80366474, sp4428);
    memset(&buf[0], 0, 0x4420);
    fn_8005C54C(tex, buf);
    width = fn_8005C4E4(tex);
    fn_8005C518(tex, dst, width / (s32)(u8)(fn_8005C68C(tex) >> 3U));
    dst += width;
    pixels = fn_8005C448(tex);
    size = fn_8005C47C(tex);
    memcpy(dst, pixels, size);
    size += 0x20;
    fn_8003E9B8(mat, buf, width + size);
    return true;
}
