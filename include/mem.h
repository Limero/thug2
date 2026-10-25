/* Game heap alloc/free wrappers (Neversoft engine, NOT libc malloc/free).
 *
 *   Mem_Alloc @ 0x80009A78 — allocates `size` bytes via the heap manager at
 *     lbl_802FFE98 (fn_8000F10C(mgr, size, 1, 0)), result in r3.
 *     Byte-identical twin: Mem_Alloc2 @ 0x80009A44.
 *   Mem_Free @ 0x80009AAC — frees `p` via fn_8000F2D0(mgr, p); null-safe
 *     (fn_8000F2D0 skips the vtable dispatch when p == NULL).
 *     Byte-identical twin: Mem_Free2 @ 0x80009AD8.
 *
 * Callers that allocate arrays of structs then construct each element
 * (e.g. fn_8000E978: Mem_Alloc(n*0xC) + per-element init loop) are the
 * `new T[n]` lowering shape, so the NEW_ARRAY/DELETE_ARRAY macros document
 * that intent while compiling to the same plain-C calls (no .cpp needed).
 */
#ifndef MEM_H
#define MEM_H

#include "types.h"

void *Mem_Alloc(s32 size);
void Mem_Free(void *p);

/* Byte-identical twins of the above (duplicate wrappers the game links
 * separately — the new/new[] + delete/delete[] duplication shape).
 * Same per-symbol rules as Mem_Alloc/Mem_Free: 1-arg prototyped calls
 * include this header; zero-arg/implicit-decl (crclr-preserving) sites
 * keep their local form and are NOT migrated.
 */
void *Mem_Alloc2(s32 size);
void Mem_Free2(void *p);

#define NEW_ARRAY(T, n) ((T *)Mem_Alloc((s32)(sizeof(T) * (n))))
#define DELETE_ARRAY(p) Mem_Free((void *)(p))

#endif
