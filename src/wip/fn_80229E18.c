// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-25
// PARKED @67.8% NEAR. Structure/registers/roles fully correct (r25-r31
// pinned to want homes; frame 0x78 via frame-template struct; two-web
// sp8 pointer = addi r11 + volatile "+r" barrier + explicit asm mr r25;
// bufp born as call-arg r3 + mr r28 via r3-pinned carrier; register
// recycling node(r30)=d758-res/mask, obj(r31)=alloc/enum-walker).
// Residues (all scheduler-tie class, ~20 shapes resisted):
// 1. prologue window interleave — want splits mgr-page lis before the
//    param homes and interleaves [lis/addi sym2] around mr r25 and the
//    two pre-call stores; got keeps pairs fused, param homes after.
// 2. pre-call store order: want [+8]=sym THEN [+4]=0 (data-readiness);
//    got emits ascending-offset order regardless of source order,
//    staging, or volatile lvalues.
// 3. loop-entry test: want fused or. r31,r3,r3+beq; every C shape gives
//    mr+cmpwi (assignment-in-condition included).
// 4. mask scratch: want li r0,0x800; got li r28 (bufp recycle).
// family=m2c range=0x80229E18-0x8022A04C size=564B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 68.5% ([0]rev->68.5%).
// RE-MEASURED 2026-10-10: score_wip.py = 69.5% clamped
//   (43/141 diffs, size-exact methodology); test_wip_drafts sweep = 78.7%
//   but that number is LONG-inflated — the object compiles to 572B vs the
//   564B symbol (2 extra words), and the sweep scorer extends want into the
//   next function instead of clamping (AGENTS-recipes §6es hazard). The
//   honest parked score is ~69% until the +8B is removed. The 4 residues
//   above still stand; the 2026-09-23 rename-only edits (fn_80127E38 ->
//   AddComponent) do not change codegen. Do not quote 78.7% as progress.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];
extern char lbl_802B02A4[];
s32 sprintf(s32 ctx, ...);
s32 CStruct_new(s32 size);
s32 CStruct_ctor(s32 obj);
s32 NextItem(s32 mgr);
s32 fn_8022986C(CScript * arg0);
void AddComponent(CStruct * obj, u32 hash, s32 type, void * val);
s32 fn_801258E8(void *buf, s32 flag);
void AddInteger(CStruct * obj, u32 hash, s32 val);
void Script_RunScript(u32 hash, s32 obj, s32 a3, s32 a4, s32 a5);
s32 fn_8022989C(CScript * node);
s32 fn_80229BAC(CScript * node);
void CStruct_delete(CStruct * obj, s32 flag);
void fn_80229C38(CScript * node);
s32 fn_8021D454(s32 mgr, CStruct * out, s32 flag);
s32 fn_8021D4E8(s32 mgr, CStruct * out, s32 flag);

struct frame_s {
    u8 _pad0[4];
    s32 w0;
    s32 w1;
    u8 _pad1[4];
    u8 buf[0x40];
};

void fn_80229E18(void *a0, s32 a1) {
    struct frame_s fr;
    Unk_4C649A8C *spv;
    s32 sym2;
    s32 ztmp;
    register char *sp8p __asm__("r25");
    register char *t3 __asm__("r3");
    register char *bufp __asm__("r28");
    register s32 mgr __asm__("r26");
    register void *self __asm__("r27");
    register s32 arg1v __asm__("r29");
    register s32 node __asm__("r30");
    register s32 obj __asm__("r31");

    spv = (char *)&fr._pad0[0];
    self = a0;
    arg1v = a1;
    __asm__ __volatile__("" : "+r"(spv));
    mgr = lbl_80305F9C;
    t3 = &fr.buf[0];
    ztmp = 0;
    sym2 = (s32)lbl_802B02A4;
    __asm__ __volatile__("mr %0,%1" : "=r"(sp8p) : "r"(spv));
    spv->unk0x8 = (s32)lbl_802A83F8;
    spv->unk0x4 = ztmp;
    bufp = t3;
    sprintf(t3, sym2, arg1v + 1);
    obj = CStruct_ctor(CStruct_new(8));
    node = NextItem(mgr);
    if (fn_8022986C(self) != 0) {
        AddComponent(obj, QB_STRING0, 3, fn_801258E8(bufp, 0));
        Script_RunScript(QB_STOLE_FLAG_YOU, obj, 0, 0, 0);
    } else if (fn_8022989C(node) == 0 && fn_80229BAC(node) == arg1v) {
        AddComponent(obj, QB_STRING0, 3, (s32)((char *)self + 0x3C));
        AddComponent(obj, QB_STRING1, 3, fn_801258E8(bufp, 0));
        Script_RunScript(QB_STOLE_FLAG_FROM_YOU, obj, 0, 0, 0);
    } else {
        AddComponent(obj, QB_STRING0, 3, (s32)((char *)self + 0x3C));
        AddComponent(obj, QB_STRING1, 3, fn_801258E8(bufp, 0));
        Script_RunScript(QB_STOLE_FLAG_OTHER, obj, 0, 0, 0);
    }
    if (obj != 0) {
        CStruct_delete(obj, 3);
    }
    if ((obj = fn_8021D454(mgr, (char *)&fr._pad0[0], 0)) != 0) {
        do {
            node = ~(0x800 << arg1v);
            if (fn_80229BAC(obj) == arg1v) {
                ((CScript *)obj)->unk0x1D8 &= node;
                fn_80229C38(obj);
            }
        } while ((obj = fn_8021D4E8(mgr, (char *)&fr._pad0[0], 0)) != 0);
    }
    ((CScript *)self)->unk0x1D8 |= 0x800 << arg1v;
    ((Unk_1D62F22E_2 *)sp8p)->unk0x8 = (s32)lbl_802A83F8;
}
