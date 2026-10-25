// PARKED: 3508B (~20-arm QB hash-switch, particle-emitter setter). First
// hand-rewritten want-derived body (below). Compile-clean, NEAR 60.7% with
// per-object -mps-float (pad12 after env pins frame 0x198 and arm slots).
// Frame/local map decoded from want: vec@0x08 (12B GetVector temp), env@0x18
// (0xB0, __ps_t[4] pair block with ref-count slot at env+0xA8), per-arm
// scalars 0xD8-0x160 in arm order (SETPOS xyz 0xD8/DC/E0, SPEEDRANGE
// 0xE4/E8, EMITRANGE 0xEC/F0/F4, SPREAD 0xF8, LOD 0xFC/100/104, RANDOM
// 0x108, CIRCULAR 0x10C, FORCE 0x110/114/118, SIZE 0x11C/120/124/128,
// SCALE 0x12C, LIFE 0x130/134, TARGET 0x138/13C/140, ANGLE 0x144/148/14C,
// COLOR corner 0x150/col 0x154, EMIT 0x158, SETEMITTERINDEPENDENT 0x15C,
// EMITRATE 0x160). APPLYENV uses -mps-float __ps_t psq pair copies +
// lbl_802940A8 (+/- lbl_802940B4) fixups on env pairs.
// WIP DRAFT (non-matching) — previous m2c body removed (compile FAIL:
// 4-arg callee arities, junk QB_UNKNOWN constants, raw address literals).
// family=m2c range=0x80065220-0x80065FD4 size=3508B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float

#include "qb_constants.h"
#include "structs.h"
#include "types.h"

extern f32 lbl_802940A4;
extern f32 lbl_802940A8;
extern f32 lbl_802940AC;
extern f32 lbl_802940B0;
extern f32 lbl_802940B4;

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetVector(CStruct *, s32, void *, s32);
s32 fn_80128C80(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8010794C(void *);
s32 fn_80107B20(void *, s32, void *);
f32 fn_80107D7C(void *);
void fn_800639E8(void *, s32);
void CObject_RemoveRefLink(void *, void *);

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec_t;

typedef struct {
    char pad[0x20];
    s16 off;
    s32 fn;
} Vt_t;

typedef struct {
    __ps_t o[4];
    char pad[0x88];
    s32 ptr;
} Env_t;

bool fn_80065220(Unk_9994C3F5 *arg0, u32 arg1, CStruct *arg2) {
    Vec_t vec;

    switch (arg1) {
    case QB_SETPOS: {
        f32 x = lbl_802940A4;
        f32 y = lbl_802940A4;
        f32 z = lbl_802940A4;

        if (GetVector(arg2, QB_POS, &vec, 0) != 0) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        } else {
            GetFloat(arg2, QB_X, &x, 0);
            GetFloat(arg2, QB_Y, &y, 0);
            GetFloat(arg2, QB_Z, &z, 0);
        }

        *(f32 *)&arg0->unk0x28 = x;
        *(f32 *)&arg0->unk0x2C = y;
        *(f32 *)&arg0->unk0x30 = z;
        break;
    }
    case QB_SETSPEEDRANGE: {
        f32 min = lbl_802940A4;
        f32 max;

        GetFloat(arg2, QB_MIN, &min, 0);
        max = min;
        GetFloat(arg2, QB_MAX, &max, 0);

        *(f32 *)&arg0->unk0x98 = min;
        *(f32 *)&arg0->unk0x9C = max;
        break;
    }
    case QB_SETEMITRANGE: {
        f32 zero = lbl_802940A4;
        f32 width = zero;
        f32 height;
        f32 depth;

        GetFloat(arg2, QB_WIDTH, &width, 0);
        height = width;
        GetFloat(arg2, QB_HEIGHT, &height, 0);
        depth = zero;
        GetFloat(arg2, QB_DEPTH, &depth, 0);

        *(f32 *)&arg0->unk0xA0 = width;
        *(f32 *)&arg0->unk0xA4 = height;
        *(f32 *)&arg0->unk0xA8 = depth;
        break;
    }
    case QB_SETANGLESPREAD: {
        f32 spread = lbl_802940A4;

        GetFloat(arg2, QB_SPREAD, &spread, 0);
        *(f32 *)&arg0->unk0xAC = spread;
        break;
    }
    case QB_SETLODPARAMS: {
        s32 minParticles = 0;
        f32 lodDist1;
        f32 lodDist2;

        GetVector(arg2, QB_MIN_PARTICLES, &minParticles, 0);
        lodDist1 = lbl_802940A4;
        lodDist2 = lbl_802940A4;
        GetFloat(arg2, QB_LOD_DIST1, &lodDist1, 0);
        GetFloat(arg2, QB_LOD_DIST2, &lodDist2, 0);

        arg0->unk0x88 = minParticles;
        *(f32 *)&arg0->unk0x8C = lodDist1 * lodDist1;
        *(f32 *)&arg0->unk0x90 = lodDist2 * lodDist2;
        break;
    }
    case QB_SETRANDOMANGLE: {
        s32 random = 0;
        s32 cond;

        GetInteger(arg2, QB_RANDOM, &random, 0);
        cond = random > 0;
        if (cond != 0) {
            arg0->unk0x128 |= 0x10;
        } else {
            arg0->unk0x128 &= ~0x10;
        }
        arg0->unk0x13C = (random > 0);
        break;
    }
    case QB_SETCIRCULAREMIT: {
        s32 random = 0;
        s32 cond;

        GetInteger(arg2, QB_CIRCULAR, &random, 0);
        cond = random > 0;
        if (cond != 0) {
            arg0->unk0x128 |= 0x100;
        } else {
            arg0->unk0x128 &= ~0x100;
        }
        arg0->unk0x140 = (random > 0);
        break;
    }
    case QB_SETFORCE: {
        f32 fx = lbl_802940A4;
        f32 fy = lbl_802940A4;
        f32 fz = lbl_802940A4;

        if (GetVector(arg2, QB_FORCE, &vec, 0) != 0) {
            fx = vec.x;
            fy = vec.y;
            fz = vec.z;
        } else {
            GetFloat(arg2, QB_X, &fx, 0);
            GetFloat(arg2, QB_Y, &fy, 0);
            GetFloat(arg2, QB_Z, &fz, 0);
        }

        *(f32 *)&arg0->unk0xB0 = fx;
        *(f32 *)&arg0->unk0xB4 = fy;
        *(f32 *)&arg0->unk0xB8 = fz;
        break;
    }
    case QB_SETPARTICLESIZE: {
        f32 sw = lbl_802940A4;
        f32 sh;
        f32 ew;
        f32 eh;
        s32 ret;

        GetFloat(arg2, QB_SW, &sw, 0);
        sh = sw;
        GetFloat(arg2, QB_SH, &sh, 0);
        *(f32 *)&arg0->unk0xBC = sw;
        *(f32 *)&arg0->unk0xC0 = sh;
        ew = sw;
        ret = GetFloat(arg2, QB_EW, &ew, 0);
        if (ret != 0) {
            eh = ew;
        } else {
            eh = sh;
        }
        GetFloat(arg2, QB_EH, &eh, 0);

        *(f32 *)&arg0->unk0xC4 = ew;
        *(f32 *)&arg0->unk0xC8 = eh;
        break;
    }
    case QB_SETPARTICLESIZESCALE: {
        f32 scale = lbl_802940A8;

        GetFloat(arg2, QB_SCALESIZE, &scale, 0);
        *(f32 *)&arg0->unk0xCC = scale;
        break;
    }
    case QB_SETLIFE: {
        f32 min = lbl_802940A4;
        f32 max;

        GetFloat(arg2, QB_MIN, &min, 0);
        max = min;
        GetFloat(arg2, QB_MAX, &max, 0);

        *(f32 *)&arg0->unk0xD0 = min;
        *(f32 *)&arg0->unk0xD4 = max;
        arg0->unk0x14C = 1;
        break;
    }
    case QB_SETEMITTARGET: {
        f32 x = lbl_802940A4;
        f32 y = lbl_802940A4;
        f32 z = lbl_802940A4;

        if (GetVector(arg2, QB_TARGET, &vec, 0) != 0) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        } else {
            GetFloat(arg2, QB_X, &x, 0);
            GetFloat(arg2, QB_Y, &y, 0);
            GetFloat(arg2, QB_Z, &z, 0);
        }

        if (x != lbl_802940A4 || z != lbl_802940A4 || y != lbl_802940A8) {
            *(f32 *)&arg0->unk0xE0 = z;
            *(f32 *)&arg0->unk0xDC = y;
            *(f32 *)&arg0->unk0xD8 = x;
        }
        break;
    }
    case QB_SETEMITANGLE: {
        f32 zero = lbl_802940A4;
        f32 x = zero;
        f32 y = zero;
        f32 z = zero;

        if (GetVector(arg2, QB_ANGLE, &vec, 0) != 0) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        } else {
            GetFloat(arg2, QB_X, &x, 0);
            GetFloat(arg2, QB_Y, &y, 0);
            GetFloat(arg2, QB_Z, &z, 0);
        }

        y = y * lbl_802940AC / lbl_802940B0;
        z = z * lbl_802940AC / lbl_802940B0;
        x = x * lbl_802940AC / lbl_802940B0;
        *(f32 *)&arg0->unk0xE8 = x;
        *(f32 *)&arg0->unk0xEC = y;
        *(f32 *)&arg0->unk0xF0 = z;
        break;
    }
    case QB_SETCOLOR: {
        s32 corner;
        s32 corner2;
        s32 col;
        s32 i;
        s32 end;

        corner2 = GetInteger(arg2, QB_CORNER, &corner, 0);
        if (corner2 != 0) {
            corner2 = corner;
        } else {
            corner = 0;
            corner2 = (((s32 (*)(void *))((Vt_t *)arg0->unk0x8)->fn)((char *)arg0 + ((Vt_t *)arg0->unk0x8)->off) - 1);
        }
        if (corner < (((s32 (*)(void *))((Vt_t *)arg0->unk0x8)->fn)((char *)arg0 + ((Vt_t *)arg0->unk0x8)->off))) {
            if (corner2 < (((s32 (*)(void *))((Vt_t *)arg0->unk0x8)->fn)((char *)arg0 + ((Vt_t *)arg0->unk0x8)->off))) {
                end = corner2 + 1;
                for (i = corner; i < end; i++) {
                    if (i < (((s32 (*)(void *))((Vt_t *)arg0->unk0x8)->fn)((char *)arg0 + ((Vt_t *)arg0->unk0x8)->off))) {
                        if (GetInteger(arg2, QB_ER, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x11C)[i * 4] = ((u8 *)(&col))[3];
                            arg0->unk0x150 = 1;
                        }
                        if (GetInteger(arg2, QB_EG, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x11C)[i * 4 + 1] = ((u8 *)(&col))[3];
                            arg0->unk0x150 = 1;
                        }
                        if (GetInteger(arg2, QB_EB, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x11C)[i * 4 + 2] = ((u8 *)(&col))[3];
                            arg0->unk0x150 = 1;
                        }
                        if (GetInteger(arg2, QB_EA, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x11C)[i * 4 + 3] = ((u8 *)(&col))[3] >> 1;
                            arg0->unk0x150 = 1;
                        }
                        if (GetInteger(arg2, QB_MR, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x118)[i * 4] = ((u8 *)(&col))[3];
                        }
                        if (GetInteger(arg2, QB_MG, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x118)[i * 4 + 1] = ((u8 *)(&col))[3];
                        }
                        if (GetInteger(arg2, QB_MB, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x118)[i * 4 + 2] = ((u8 *)(&col))[3];
                        }
                        if (GetInteger(arg2, QB_MA, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x118)[i * 4 + 3] = ((u8 *)(&col))[3] >> 1;
                        }
                        if (GetInteger(arg2, QB_SR, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x114)[i * 4] = ((u8 *)(&col))[3];
                            if ((s32)arg0->unk0x150 == 0) {
                                ((u8 *)arg0->unk0x11C)[i * 4] = ((u8 *)(&col))[3];
                            }
                        }
                        if (GetInteger(arg2, QB_SG, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x114)[i * 4 + 1] = ((u8 *)(&col))[3];
                            if ((s32)arg0->unk0x150 == 0) {
                                ((u8 *)arg0->unk0x11C)[i * 4 + 1] = ((u8 *)(&col))[3];
                            }
                        }
                        if (GetInteger(arg2, QB_SB, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x114)[i * 4 + 2] = ((u8 *)(&col))[3];
                            if ((s32)arg0->unk0x150 == 0) {
                                ((u8 *)arg0->unk0x11C)[i * 4 + 2] = ((u8 *)(&col))[3];
                            }
                        }
                        if (GetInteger(arg2, QB_SA, &col, 0) != 0) {
                            ((u8 *)arg0->unk0x114)[i * 4 + 3] = ((u8 *)(&col))[3] >> 1;
                            if ((s32)arg0->unk0x150 == 0) {
                                ((u8 *)arg0->unk0x11C)[i * 4 + 3] = ((u8 *)(&col))[3] >> 1;
                            }
                        }
                    }
                }
            }
        }
        GetFloat(arg2, QB_MIDTIME, (char *)arg0 + 0x110, 0);
        break;
    }
    case QB_EMIT: {
        s32 num = 1;

        GetInteger(arg2, QB_NUM, &num, 0);
        fn_800639E8(arg0, num);
        break;
    }
    case QB_SETEMITTERINDEPENDENT: {
        s32 out = 0;

        GetInteger(arg2, 0, &out, 0);
        arg0->unk0x134 = ((out ^ 1) == 0);
        break;
    }
    case QB_EMITRATE: {
        f32 rate = lbl_802940A8;

        GetFloat(arg2, QB_RATE, &rate, 0);
        *(f32 *)&arg0->unk0x78 = rate;
        break;
    }
    case QB_APPLYENVBRIGHTNESS: {
        Env_t env;
        f32 dist;
        u8 fr[0x10];
        s32 envP;

        envP = ContainsFlag(arg2, QB_ALWAYS_UPDATE);
        if (envP != 0) {
            arg0->unk0x164 = 1;
            break;
        }
        arg0->unk0x164 = envP;

        fn_8010794C(&env);
        env.o[0] = *(__ps_t *)&arg0->unk0x28;
        env.o[2] = *(__ps_t *)&arg0->unk0x28;
        env.o[1] = *(__ps_t *)&arg0->unk0x30;
        env.o[3] = *(__ps_t *)&arg0->unk0x30;
        ((f32 *)&env)[1] = ((f32 *)&env)[1] + lbl_802940A8;
        ((f32 *)&env)[5] = ((f32 *)&env)[5] - lbl_802940B4;
        if (fn_80107B20(&env, 1, 0) != 0) {
            dist = fn_80107D7C(&env);
            *(f32 *)&arg0->unk0xF4 = dist + dist;
        }
        if (env.ptr != 0) {
            CObject_RemoveRefLink((void *)env.ptr, &env.ptr);
            env.ptr = 0;
        }
        break;
    }
    case QB_EMPTYSYSTEM: {
        arg0->unk0x94 = 0;
        break;
    }
    default:
        break;
    }

    return true;
}
