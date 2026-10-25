// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B0E4-0x8021B1CC (232B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303148[];
extern char lbl_80303448[];
void fn_80137CB4(Unk_9F066EC1 * arg0);
s32 fn_802195BC(Unk_C7387A53 * arg0);
s32 fn_80137AD4(Unk_F386DC9F * arg0);
void fn_8013DE78(void * arg0, Unk_C71E6DE1 * arg1);
void fn_8013E184(s32 *arg0, s32 arg1);
s32 fn_800145AC(void);
void fn_8000A578(void *arg0, s32 arg1);
void fn_8022019C(CScript * arg0, s32 arg1);

/* frame template: r1+8..r1+0x47 (locals region 0x40 => frame 0x68 w/ stmw r25) */
struct fr_B0E4 {
    s32 hash;      /* r1+0x08 */
    u8 c;          /* r1+0x0C */
    u8 d;          /* r1+0x0D */
    u8 e;          /* r1+0x0E */
    u8 _p0[9];     /* r1+0x0F..0x17 */
    u8 flag;       /* r1+0x18 */
    u8 _p1[7];     /* r1+0x19..0x1F */
    u8 cmd_b;      /* r1+0x20 */
    u8 _p2;
    s16 cmd_w;     /* r1+0x22 */
    void *cmd_q;   /* r1+0x24 */
    u8 _tail[0x20];
};

// StartNetworkLobby @ 0x8021B0E4
void StartNetworkLobby(Unk_BF863306 *arg0, void *arg1) {
    struct fr_B0E4 fr;
    register void *pv __asm__("r29");
    s32 g148;
    s32 g3448;
    s32 a2;
    s32 t137;

    pv = &fr.cmd_b;
    fn_80137CB4(pv);
    g148 = *(s32 *)&lbl_80303148;
    g3448 = *(s32 *)&lbl_80303448;
    fr.c = (fn_802195BC(arg0) == 1);
    fr.hash = 0x4000B;
    fr.d = 1;
    fr.e = 0;
    t137 = fn_80137AD4(g3448);
    a2 = (s32)pv;
    __asm__("" : "+r"(a2));
    if (t137 == 1) {
        fr.flag = 0;
    } else {
        fr.flag = 1;
    }
    fr.cmd_q = &fr.hash;
    fr.cmd_w = 0x14;
    fr.cmd_b = 3;
    fn_8013DE78(arg1, a2);
    fn_8013E184(arg1, 0);
    arg0->unk0x1D4 = fn_800145AC();
    fn_8000A578((char *)g148 + 8, arg0->unk0xE8);
    fn_8022019C(arg0, 2);
}
