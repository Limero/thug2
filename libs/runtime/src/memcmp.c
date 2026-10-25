// memcmp — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Original SN Systems ProDG newlib source (crashwoc decomp, runtime/libc).
// Compiles byte-exact against the THUG2 DOL (0x8026AD98, 0x90) with the
// game's ngccc (ProDG 3.9.3). The u1/u2/p/l1/l2 variable split pins the
// peeled entry compare to load *l2 first into r0 and *l1 from r3.
#include "types.h"

typedef unsigned int size_t;

#define UNALIGNED(X, Y) ((((long)X) & (sizeof(long) - 1)) | (((long)Y) & (sizeof(long) - 1)))
#define TOO_SMALL(n) ((n) < sizeof(long))
#define LBLOCKSIZE (sizeof(long))

int memcmp(const void *m1, const void *m2, size_t n)
{
  unsigned char *s1 = (unsigned char *) m1;
  unsigned char *s2 = (unsigned char *) m2;
  unsigned long *a1;
  unsigned long *a2;

  if (!TOO_SMALL(n) && !UNALIGNED(s1, s2))
    {
      a1 = (unsigned long*) s1;
      a2 = (unsigned long*) s2;
      while (n >= LBLOCKSIZE)
        {
          if (*a1 != *a2)
            break;
          n -= LBLOCKSIZE;
          a1++;
          a2++;
        }

      s1 = (unsigned char*) a1;
      s2 = (unsigned char*) a2;
    }

  while (n--)
    {
      if (*s1 != *s2)
        return *s1 - *s2;
      s1++;
      s2++;
    }

  return 0;
}
