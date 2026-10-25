// UPDATED 2026-08-29: fn_80137CB4 proto flipped void->s32 (return-live
// arg-setup order; now 74.5%).
// WIP DRAFT (non-matching) — rebuilt from want disasm 2026-08-25
// family=m2c range=0x8021FAB4-0x8021FCF8 size=580B
// PARKED 73.8% DIFF (107/145; baseline was 11.8%). Structure is fully
// correct incl. the 9-arg signature — residual is ONE allocator
// decision cascading: retail SHARES flag's home r26 with msgp
// (path-exclusive liveness: flag dies at the branch in the if-path,
// msgp only exists there; flag's else-path stb reuses r26). ngccc
// gives msgp its OWN reg (r24) instead -> +1 saved reg (stmw r21 vs
// r22, frame 0x2a0 vs 0x298) -> whole register map rotates down one.
// Every attempt to force the share failed: pinning msgp->r26 pushes
// flag out (pins block inter-web reuse); pinning other params made
// mgr/flag lose their homes entirely (brittle-allocator collapse,
// doc-15/32 class). Wedge-copy births (mr %0,%1) for msgp ARE required
// (plain assign coalesces to a direct birth, losing want's mr).
// Retry hints: find a source form where flag's ELSE-path use reads the
// param home slot instead of a dedicated copy; or a sched/regalloc
// lever that enables inter-path home sharing. Also untested: .cpp
// frontend for this object (references may model the sharing).
//
// 9-ARG signature (p5 in r8 is DEAD — body never reads it; p8 arrives
// on the caller's STACK at r1+8, prologue reads it at 0x2a0(r1) after
// the stwu -0x298). Callers store 0x7D0 to r1+8 for arg8.
// Reg map (want): r31=mgr, r26=flag(or.-tested; stb'd in else arm;
// recycled as &msg home in the if arm), r28=p2(recycled as strstr
// result), r27=p3, r25=p4, r29=p6(recycled as &sp70), r24=p7,
// r22=p8(stack), r23=&es(esp), r30=str(recycled as &sp170).
// Frame (rel r1): es@8, pad4, sp18/1C/20 @18/1C/20, sp24[16]@24,
// sp34[20]@34, msg(0x28)@48, sp70[0x100]@70, sp170[0x100]@170.
// PERMUTED 2026-09-13 (<permute script> full-permutation statement search): score now 76.55% ([0]p72->75.9% [3]p1->76.6%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern char lbl_802AFE78[];

s32 fn_80137CB4(Unk_9F066EC1 *);
s32 Script_GenerateCRC(s32);
void strcpy(char *, char *);
char *strstr(char *, char *);
void strcat(char *, char *);
void *fn_8021D454(void *, CStruct *, s32);
void *fn_8021D4E8(void *, CStruct *, s32);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
char *fn_8012591C(s32, s32);
void AddComponent(CStruct *, s32, s32, void *);
void fn_80127E70(s32, s32, s32, s32);
void AddInteger(CStruct *, s32, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
s32 CStruct_delete(CStruct *, s32);

typedef struct { void *iter; void *pad; void *cb; } essfab_t;
typedef struct {
    u8 b0; u8 _1; u16 bh; s32 w4; u8 _8[4]; s32 w8; u8 b10; u8 _11[0x17];
} msgfab_t;

void fn_8021FAB4(Unk_9994C3F5 *mgr, s32 flag, s32 arg2, char *arg3, char *arg4,
                 s32 dead5, s32 arg6, s32 arg7, s32 arg8) {
    struct {
        essfab_t es;        /* r1+0x08 */
        char _p0[4];
        s32 sp18;           /* r1+0x18: Script_GenerateCRC result */
        s32 sp1C;           /* r1+0x1C: p2 */
        s32 sp20;           /* r1+0x20: p8 */
        char sp24[16];      /* r1+0x24 */
        char sp34[20];      /* r1+0x34 */
        msgfab_t msg;       /* r1+0x48 */
        char sp70[0x100];   /* r1+0x70 */
        char sp170[0x100];  /* r1+0x170 */
    } fr;
    register essfab_t *esp;
    register msgfab_t *msgp;
    void *entry;
    s32 obj;
    char *str;
    char *m;
    char *sp70p;

    if (flag != 0) {
        register essfab_t *e11 __asm__("r11");
        register msgfab_t *m3 __asm__("r3");
        __asm__("" : "=r"(e11) : "r"(&fr.es));
        __asm__("" : "=r"(m3) : "r"(&fr.msg));
        __asm__("mr %0,%1" : "=r"(esp) : "r"(e11));
        e11->cb = (void *)lbl_802A83F8;
        __asm__("mr %0,%1" : "=r"(msgp) : "r"(m3));
        e11->pad = NULL;
        fn_80137CB4(m3);
        fr.sp24[0] = 0;
        fr.sp34[0] = 0;
        fr.sp1C = arg2;
        fr.sp20 = arg8;
        fr.sp18 = Script_GenerateCRC(arg6);
        if (arg3 != NULL) {
            strcpy(fr.sp24, arg3);
        }
        if (arg4 != NULL) {
            strcpy(fr.sp34, arg4);
        }
        fr.msg.w4 = (s32)&fr.sp18;
        fr.msg.bh = 0x2C;
        fr.msg.b0 = 0x3F;
        if (arg7 != 0) {
            fr.msg.w8 = 2;
            fr.msg.b10 = 8;
        }
        entry = fn_8021D454(mgr, &fr.es, 1);
        if (entry != NULL) {
            do {
                fn_8013CC84(mgr->unk0x8, fn_8022A9B8(entry), msgp);
                entry = fn_8021D4E8(mgr, &fr.es, 1);
            } while (entry != NULL);
        }
        esp->cb = (void *)lbl_802A83F8;
    } else {
        sp70p = &fr.sp70[0];
        str = fn_8012591C(arg2, 0);
        obj = CStruct_ctor(CStruct_new(8));
        strcpy(sp70p, str);
        m = strstr(sp70p, lbl_802AFE78);
        if (m != NULL) {
            *(u8 *)m = (u8)flag;
            strcpy(&fr.sp170[0], sp70p);
            strcat(&fr.sp170[0], arg3);
            strcat(&fr.sp170[0], m + 3);
            AddComponent(obj, QB_TEXT, 3, &fr.sp170[0]);
        } else {
            AddComponent(obj, QB_TEXT, 3, str);
        }
        fn_80127E70(obj, QB_ID, 0xD, QB_NET_PANEL_MSG);
        AddInteger(obj, (s32)QB_MSG_TIME, arg8);
        Script_RunScript(QB_CREATE_NET_PANEL_MESSAGE, obj, 0, 0, 0);
        if (obj != 0) {
            CStruct_delete(obj, 3);
        }
    }
}
