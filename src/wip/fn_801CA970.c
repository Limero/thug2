// WIP DRAFT (non-matching) — hand-written from disasm.
// PARKED 63.5%: hash-switch dispatcher, semantically complete incl. audited
// arities (fn_80181DA0/fn_80181C78 5-arg, GetChecksum_2/280E0/28228 4-arg,
// AddInteger 3-arg void, Script_GenerateCRC s32(s32)). Remaining diffs are doc-15
// class: (a) want keeps case 0x5589B902's branchy bool INLINE while ngccc
// crossjumps its [beq][li r3,1][blr] tail into the big-arm judge block
// (barriers, "+r" wedges, case reordering all resist); (b) judge granularity:
// want shares only [beq][li r3,1] across the two big-arm sites leaving
// [cmpwi][li r3,0] per-site, got merges differently; (c) one arg-move order
// swap in case 0xBE3E5463 (mr r3,r31 two slots early).
// family=m2c range=0x801CA970-0x801CAEF4 size=1412B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 72.5%.
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *);
s32 GetString(CStruct *, s32 *, s32 *, s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_801813F0(CStruct *);
void fn_80181300(Unk_F515CE8D *, s32);
s32 fn_801820E8(Unk_FFAD6788 *);
void fn_801801CC(Unk_FFAD6788 *);
void fn_8017FB44(Unk_F515CE8D *, s32);
s32 fn_80181DA0(Unk_FFAD6788 *, s32, s32, s32, s32);
s32 fn_80181C78(Unk_FFAD6788 *, s32, s32, s32, s32);
s32 Script_GenerateCRC(s32);
s32 fn_801CA970(void *arg0, u32 arg1, s32 arg2, CScript *arg3) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 var_r3;
    s32 temp_r3;
    void *temp_r30;
    register s32 a0 __asm__("r30");
    register s32 a2 __asm__("r31");
    register s32 t29 __asm__("r29");
    a0 = (s32)arg0;
    a2 = arg2;
    switch (arg1) {
    case QB_LASTSCORELANDEDGREATERTHAN:
        GetInteger(a2, 0, &sp8, 1);
        return *(s32 *)(((Unk_31DE137E *)a0)->unk0x1C + 0x24) > sp8;
    case QB_LASTSCORELANDEDLESSTHAN:
        GetInteger(a2, 0, &spC, 1);
        return *(s32 *)(((Unk_31DE137E *)a0)->unk0x1C + 0x24) < spC;
    case QB_INCREMENTSCORE:
        a0 = ((Unk_31DE137E *)a0)->unk0x1C;
        fn_80181300((void *)a0, fn_801813F0(a0) + 1);
        goto ret1;
    case QB_TOTALSCOREGREATERTHAN:
        GetInteger(a2, 0, &sp10, 1);
        return fn_801813F0(((Unk_31DE137E *)a0)->unk0x1C) > sp10;
    case QB_TOTALSCORELESSTHAN:
        GetInteger(a2, 0, &sp14, 1);
        return fn_801813F0(((Unk_31DE137E *)a0)->unk0x1C) < sp14;
    case QB_CURRENTSCOREPOTGREATERTHAN:
        GetInteger(a2, 0, &sp18, 1);
        {
            register s32 ob __asm__("r8");
            ob = ((Unk_31DE137E *)a0)->unk0x1C;
            return (s32)((f32)((Unk_C8FEE62D *)ob)->unk0x18 *
                         *((f32 *)&((Unk_C8FEE62D *)ob)->unk0x6C)) > sp18;
        }
    case QB_GETTOTALSCORE:
        temp_r3 = ((Unk_31DE137E *)a0)->unk0x1C;
        a0 = arg3->unk0x18;
        AddInteger((void *)a0, QB_TOTALSCORE, fn_801813F0(temp_r3));
        goto ret1;
    case QB_CURRENTSCOREPOTLESSTHAN:
        GetInteger(a2, 0, &sp1C, 1);
        {
            register s32 ob __asm__("r8");
            ob = ((Unk_31DE137E *)a0)->unk0x1C;
            return (s32)((f32)((Unk_C8FEE62D *)ob)->unk0x18 *
                         *((f32 *)&((Unk_C8FEE62D *)ob)->unk0x6C)) < sp1C;
        }
    case QB_GETNUMBEROFNONGAPTRICKS:
        temp_r3 = ((Unk_31DE137E *)a0)->unk0x1C;
        a0 = arg3->unk0x18;
        AddInteger((void *)a0, QB_NUMBEROFNONGAPTRICKS, fn_801820E8(temp_r3));
        goto ret1;
    case QB_GOTSPECIAL: {
        register s32 v3 __asm__("r3");
        v3 = 0;
        if (*(s32 *)(((Unk_31DE137E *)a0)->unk0x1C + 0x80) != 0) {
            __asm__("" : "+r"(v3));
            v3 = 1;
        }
        return v3;
    }
    case QB_FORCESPECIAL:
        fn_801801CC(*((void * *)&((Unk_31DE137E *)a0)->unk0x1C));
        goto ret1;
    case QB_GETSPECIALVALUE:
        temp_r30 = *((void * *)&arg3->unk0x18);
        AddInteger(temp_r30, QB_VALUE,
                    *(s32 *)(((Unk_31DE137E *)a0)->unk0x1C + 0x7C));
        goto ret1;
    case QB_SETSPECIALVALUE:
        GetInteger(a2, QB_VALUE, &sp20, 0);
        *(s32 *)(((Unk_31DE137E *)a0)->unk0x1C + 0x7C) = sp20;
        goto ret1;
    case QB_TWEAKTRICK:
        sp24 = 0;
        GetInteger(a2, 0, &sp24, 0);
        fn_8017FB44(*((void * *)&((Unk_31DE137E *)a0)->unk0x1C), sp24);
        goto ret1;
    case QB_ISLATESTTRICK:
        t29 = GetChecksum_2(a2, QB_KEYCOMBO, &sp28);
        if (t29 != 0) {
            sp2C = 0;
            if (GetInteger(a2, QB_SPIN, &sp2C, 0) != 0) {
                sp2C /= 0xB4;
            }
            sp30 = 1;
            GetInteger(a2, QB_NUMTAPS, &sp30, 0);
            {
                register s32 v3 __asm__("r3");
                v3 = 0;
                if (fn_80181DA0(*((void * *)&((Unk_31DE137E *)a0)->unk0x1C), sp28, sp2C, 0,
                                sp30) != 0) {
                    __asm__("" : "+r"(v3));
                    v3 = 1;
                }
                return v3;
            }
        }
        __asm__("" : "+r"(t29));
        if (GetString(a2, QB_TRICKTEXT, &sp34, 0) == 0) {
            return 2;
        }
        sp38 = t29;
        if (GetInteger(a2, QB_SPIN, &sp38, 0) != 0) {
            sp38 /= 0xB4;
        }
        sp3C = 1;
        GetInteger(a2, QB_NUMTAPS, &sp3C, 0);
        a0 = ((Unk_31DE137E *)a0)->unk0x1C;
        {
            register s32 v3 __asm__("r3");
            v3 = 0;
            if (fn_80181C78((void *)a0, Script_GenerateCRC(sp34), sp38, 0, sp3C) != 0) {
                __asm__("" : "+r"(v3));
                v3 = 1;
            }
            return v3;
        }
    default:
        return 2;
    }
ret1:
    return 1;
}
