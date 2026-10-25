// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017DC0C-0x8017DD34 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* script/struct message block; layout read from fn_80137CB4's field stores */
typedef struct {
    s8   b00;        /* 0x00  stb  */
    s8   b01;        /* 0x01  stb  */
    u16  h02;        /* 0x02  sth  */
    s32  w04;        /* 0x04  stw  */
    s32  w08;        /* 0x08  stw  */
    s32  w0C;        /* 0x0C  stw  */
    s8   b10;        /* 0x10  stb  */
    s32  w14;        /* 0x14  stw  */
    s32  w18;        /* 0x18  stw  */
    s32  w1C;        /* 0x1C  stw  */
    s8   b20;        /* 0x20  stb  */
    char pad21[0x7]; /* -> 0x28 total; see note (3) for why 0x28 not 0x2C */
} Msg_t;

void fn_8013DE78(void *, void *);
void fn_8021D928(void *);
void fn_8021B37C(void *);
void fn_80009C00(void *);
void fn_8013CC84(void *, void *, void *);
void fn_80137CB4(void *);
void fn_8013E184(void *, s32);
void fn_8021B508(void *);
void *fn_8021B554(void *);
void *fn_8021B55C(void *, s32);
void fn_8012E970(void);
void Script_RunScript(s32, s32, s32, s32, s32);
extern char lbl_80305F9C[];
s32 fn_80219638(Unk_C7387A53 *o);
s32 fn_80219698(CStruct *o);
void fn_8017DC0C(CScript *arg0) {
    Msg_t msg;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = *(s32 *)&lbl_80305F9C;
    Script_RunScript(QB_PATCHCLEANUP, 0, 0, 0, 0);
    fn_8012E970();
    if (fn_80219698(temp_r31) != 0) {
        fn_80137CB4(&msg);
        temp_r30 = fn_8021B554(temp_r31);
        if (fn_80219638(temp_r31) == 1) {
            fn_8021B508(temp_r31);
        }
        msg.b00 = 0x32;
        msg.w08 = 0xFF;
        fn_8013CC84(temp_r30, 0xFF, &msg);
        fn_8013E184(temp_r30, 0);
        fn_8021B37C(temp_r31);
        fn_80009C00(arg0->unk0x1C);
        fn_80009C00(arg0->unk0x20);
    } else {
        temp_r3 = fn_8021B55C(temp_r31, 0);
        if (temp_r3 != 0) {
            fn_80137CB4(&msg);
            msg.b00 = 0xB;
            msg.w0C = 2;
            msg.b10 = 8;
            fn_8013DE78(temp_r3, &msg);
            fn_8013E184(temp_r3, 0);
        }
    }
    fn_8021D928(temp_r31);
}
