// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B270-0x8021B37C (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    s32 value;
    u8 byte4;
    u8 byte5;
    char text[10];
    u8 flag;
    char pad19[7];
} Local8021B270;

extern char lbl_80303148[];
extern char lbl_80303448[];
void fn_80137CB4(void *);
void *fn_8021E024(void *);
s32 fn_8013FF5C(void *, s32);
void GetText(void *, s32, void *, s32);
s32 fn_802195BC(void *);
s32 fn_80137AD4(void *);
void strcpy(char *, char *);
s32 fn_8013DE78(void *, Unk_C71E6DE1 *);
s32 fn_800145AC(void);
void fn_8000A578(s32, s32);
void fn_8022019C(void *, s32);

typedef struct {
    Unk_C71E6DE1 value;
    u8 pad[4];
} Message8021B270;

typedef struct {
    Local8021B270 local;
    Message8021B270 msg;
    s32 out;
} Frame8021B270;

void fn_8021B270(Unk_BF863306 *arg0, char *arg1) {
    Frame8021B270 frame;
    s32 init_tag;
    s32 network;
    s32 value;
    s32 mgr;

    network = *(s32 *)&lbl_80303148;
    init_tag = *(s32 *)&lbl_80303448;
    fn_80137CB4(&frame.msg.value);
    GetText(fn_8013FF5C(fn_8021E024(arg0), QB_NETWORK_ID), QB_UI_STRING, (s32 *)&frame.out, 1);
    value = fn_802195BC(arg0) ^ 1;
    frame.local.byte4 = value == 0;
    frame.local.value = 0x4000B;
    frame.local.byte5 = 1;
    if (fn_80137AD4(init_tag) == 1) {
        frame.local.flag = 0;
    } else {
        frame.local.flag = 1;
    }
    strcpy(frame.local.text, arg1);
    mgr = arg0->unk0xC;
    frame.msg.value.unk0x4 = (s32)&frame.local;
    frame.msg.value.unk0x2 = 0x14;
    frame.msg.value.unk0x0 = 3;
    fn_8013DE78(mgr, &frame.msg.value);
    arg0->unk0x1D4 = fn_800145AC();
    fn_8000A578((char *)network + 8, arg0->unk0xE8);
    fn_8022019C(arg0, 3);
}
