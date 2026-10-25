// WIP DRAFT (non-matching) — hand semantic reconstruction.
// family=m2c range=0x8011EF98-0x8011F210 size=632B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// 2026-10-06: replaced the m2c body with a struct-typed
// reconstruction of the AX voice setup (acquire + full voice setter chain).
// Semantic/typing fixes made here:
//  * the source object (r31 = arg0->0x4) has u16 fields at
//    0xC/0x3C/0x3E/0x40/0x42/0x44/0x46/0x48 (want `lhz`) and a u32 at 0x4; the
//    m2c body read them through a shared s32 struct (`lwz`) so every load
//    width was wrong;
//  * the AXPBADDR loopFlag is (field != 0), NOT the inverted
//    `((field == 0) == 0) ? 0 : 1` the m2c body emitted;
//  * the AXPBADPCM scratch is 0x28 bytes (AXSetVoiceAdpcm copies 10 u32); the
//    m2c body declared it `s32 sp28` and wrote 0x20 bytes through it — a real
//    overflow of the neighbouring locals;
//  * the copy loop advanced an `s32 *` by 0x18 (=> 0x60 bytes/iteration; want
//    advances 0x18 by bytes) — now byte pointers;
//  * the loop counter is s32 (want `addic. r7,r7,-0x18`), not s16;
//  * all eight AXSetVoice* callees are prototyped (want has no `crclr cr1eq`
//    before the `bl`s);
//  * lbl_8029D6B8 (f32), lbl_8037B778 (s32) and the voice pool lbl_8038EBB8[]
//    are referenced by their registered symbols instead of raw address
//    literals / a fake file-scope static.
// PARKED 2026-10-06: the frame is re-sized by the real AX structs (0x60 bytes
// of locals -> want frame 0x98); the residual is per-store ordering inside the
// AX struct field groups plus the adpcm-copy loop shape. Body compiles
// standalone; no inline asm, no transcribed instructions, no new casts.
#include "types.h"
#include "structs.h"

typedef struct Voice Voice;

typedef struct {
    u32 unk0x0;
    Voice *unk0x4;
    u32 unk0x8;
    f32 unk0xC;
} Sound;

struct Voice {
    char pad0x00[0x04];
    u32 unk0x04;
    char pad0x08[0x04];
    u16 unk0x0C;
    char pad0x0E[0x0E];
    u32 unk0x1C[8];
    u16 unk0x3C;
    u16 unk0x3E;
    u16 unk0x40;
    u16 unk0x42;
    u16 unk0x44;
    u16 unk0x46;
    u16 unk0x48;
};

/* AXPBADDR — lives at r1+0x08 (8 u16). */
typedef struct {
    u16 loopFlag;
    u16 format;
    u16 loopHi;
    u16 loopLo;
    u16 endHi;
    u16 endLo;
    u16 curHi;
    u16 curLo;
} Addr;

/* AXPBSRC — lives at r1+0x18 (8 u16). */
typedef struct {
    u16 unk0x00;
    u16 unk0x02;
    u16 unk0x04;
    u16 unk0x06;
    u16 unk0x08;
    u16 unk0x0A;
    u16 unk0x0C;
    u16 unk0x0E;
} Src;

/* AXPBADPCM — lives at r1+0x28 (0x20 coef bytes + 4 u16). */
typedef struct {
    u16 coef[8][2];
    u16 gain;
    u16 predScale;
    u16 yn1;
    u16 yn2;
} Adpcm;

/* AXPBADPCMLOOP — lives at r1+0x50 (3 u16). */
typedef struct {
    u16 predScale;
    u16 yn1;
    u16 yn2;
} AdpcmLoop;

/* AXPBVE — lives at r1+0x58 (2 u16). */
typedef struct {
    u16 currentVolume;
    u16 currentDelta;
} Ve;

extern s32 lbl_8038EBB8[];
extern f32 lbl_8029D6B8;
extern s32 lbl_8037B778;
void fn_8011E930(s32);
s32 fn_8011E96C(void);
void fn_8011ED64(s32, void *, f32);
s32 AXAcquireVoice(u32, void (*)(s32), u32);
void AXSetVoiceType(s32, s32);
void AXSetVoiceAddr(s32, void *);
void AXSetVoiceAdpcm(s32, void *);
void AXSetVoiceAdpcmLoop(s32, void *);
void AXSetVoiceVe(s32, void *);
void AXSetVoiceSrcType(s32, s32);
void AXSetVoiceSrc(s32, void *);
void AXSetVoiceState(s32, s32);

s32 fn_8011EF98(Sound *arg0, void *arg1, f32 farg0) {
    Addr addr;
    Src src;
    Adpcm adpcm;
    AdpcmLoop loop;
    Ve ve;
    Voice *v;
    char *s;
    char *d;
    s32 handle;
    s32 idx;
    s32 n;
    s32 prio;
    u32 cur;
    u32 end;

    idx = fn_8011E96C();
    if (idx == -1) {
        return -1;
    }
    v = arg0->unk0x4;
    if (v == 0) {
        return -1;
    }
    prio = 1;
    if (v->unk0x0C != 0) {
        prio = 0x1F;
    }
    handle = AXAcquireVoice(prio, fn_8011E930, 0);
    if (handle == 0) {
        return -1;
    }

    addr.loopFlag = (v->unk0x0C != 0);
    addr.format = 0;

    cur = arg0->unk0x0 * 2 + 2;
    end = (arg0->unk0x0 * 2 - 1) + v->unk0x04;

    addr.curHi = cur >> 16;
    addr.endLo = end;
    addr.endHi = end >> 16;
    addr.curLo = cur;

    if (v->unk0x0C != 0) {
        addr.loopHi = cur >> 16;
        addr.loopLo = cur;
    } else {
        u32 g = lbl_8037B778 * 2;
        addr.loopLo = g;
        addr.loopHi = g >> 16;
    }

    s = (char *)v + 0x1C;
    d = (char *)&adpcm;
    n = 0x18;
    do {
        *(u32 *)(d + 0x00) = *(u32 *)(s + 0x00);
        *(u32 *)(d + 0x04) = *(u32 *)(s + 0x04);
        *(u32 *)(d + 0x08) = *(u32 *)(s + 0x08);
        *(u32 *)(d + 0x0C) = *(u32 *)(s + 0x0C);
        *(u32 *)(d + 0x10) = *(u32 *)(s + 0x10);
        *(u32 *)(d + 0x14) = *(u32 *)(s + 0x14);
        d += 0x18;
        s += 0x18;
        n -= 0x18;
    } while (n != 0);
    *(u32 *)(d + 0x00) = *(u32 *)(s + 0x00);
    *(u32 *)(d + 0x04) = *(u32 *)(s + 0x04);

    adpcm.gain = v->unk0x3C;
    adpcm.predScale = v->unk0x3E;
    adpcm.yn1 = v->unk0x40;

    loop.predScale = v->unk0x44;
    loop.yn1 = v->unk0x46;
    loop.yn2 = v->unk0x48;

    src.unk0x00 = 1;
    src.unk0x0C = 0;
    src.unk0x02 = 0;
    src.unk0x04 = 0;
    src.unk0x06 = 0;
    src.unk0x08 = 0;
    src.unk0x0A = 0;

    ve.currentVolume = 0x7FFF;
    adpcm.yn2 = v->unk0x42;
    ve.currentDelta = n;

    AXSetVoiceType(handle, 0);
    AXSetVoiceAddr(handle, &addr);
    AXSetVoiceAdpcm(handle, &adpcm);
    AXSetVoiceAdpcmLoop(handle, &loop);
    AXSetVoiceVe(handle, &ve);
    AXSetVoiceSrcType(handle, 1);
    AXSetVoiceSrc(handle, &src);
    AXSetVoiceState(handle, 1);

    lbl_8038EBB8[idx * 2] = handle;
    lbl_8038EBB8[idx * 2 + 1] = (s32)v;

    fn_8011ED64(idx, arg1, farg0 * arg0->unk0xC * lbl_8029D6B8);
    return idx;
}

// NOTE (2026-10-06): remaining diffs after this rewrite are
//   (a) AXPBADDR field-store order: want stores 0x14,0x12,0x10,0x16
//       (curHi,endLo,endHi,curLo — the body follows that order) but the
//       surrounding `li`/address materialisation is re-scheduled; and
//   (b) the adpcm-copy loop: want keeps a one-trip `do { 6 words } while
//       (n -= 0x18)` followed by a 2-word tail.  With the compile-time
//       `n = 0x18` ngccc may fold that loop into straight-line copies; if it
//       does, all 0x20 bytes are still copied (semantics preserved) but the
//       loop words are lost.  Left un-forced rather than using asm.
// Not promoted; the file stays INERT.
