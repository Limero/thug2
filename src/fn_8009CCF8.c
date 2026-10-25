// range 0x8009CCF8-0x8009CD1C (0x24). Byte-identical.
// Identification: doubly-linked-list insert — inserts the successor
// (node->0x10) after self+8: n->0xc = s; n->0x10 = s->0x10;
// s->0x10->0xc = n; s->0x10 = n.
//
// Matching key: s->0x10 must be loaded TWICE in source (the want has two
// separate lwz of s->0x10 — one for n->0x10's value, one for the
// s->0x10->0xc address); a single temp collapses the reload (9/9).
#include "types.h"
#include "structs.h"
void fn_8009CCF8(void *self, CStruct *node) {
    void *s = (char *)self + 8;
    void *n = *((void * *)&node->unk0x10);
    void *next = *((void * *)&((CStruct *)s)->unk0x10);
    *((void * *)&((CStruct *)n)->unk0xC) = s;
    *((void * *)&((CStruct *)n)->unk0x10) = next;
    *(void **)((char *)*((void * *)&((CStruct *)s)->unk0x10) + 0xc) = n;
    *((void * *)&((CStruct *)s)->unk0x10) = n;
}
