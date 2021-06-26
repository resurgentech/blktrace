/*
 * Replaces byteswap.h for windows really only expected to work for x86_64
 */
#define __bswap_16(value) \
((((value) & 0xff) << 8) | ((value) >> 8))

#define __bswap_32(value) \
(((__u32)__bswap_16((__u16)((value) & 0xffff)) << 16) | \
(__u32)__bswap_16((__u16)((value) >> 16)))

#define __bswap_64(value) \
(((__u64)__bswap_32((__u32)((value) & 0xffffffff)) \
<< 32) | \
(__u64)__bswap_32((__u32)((value) >> 32)))

//------------------------------------------------------------------------------------

//
// endian.h
//
// https://gist.github.com/panzi/6856583
//
// I, Mathias Panzenböck, place this file hereby into the public domain. Use
// it at your own risk for whatever you like. In case there are
// jurisdictions that don't support putting things in the public domain you
// can also consider it to be "dual licensed" under the BSD, MIT and Apache
// licenses, if you want to. This code is trivial anyway. Consider it an
// example on how to get the endian conversion functions on different
// platforms.

#ifndef PORTABLE_ENDIAN_H__
#define PORTABLE_ENDIAN_H__

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)

#	define __WINDOWS__

#endif

#if defined(__linux__) || defined(__CYGWIN__)

#	include <endian.h>

#elif defined(__APPLE__)

#	include <libkern/OSByteOrder.h>

#	define htobe16(x) OSSwapHostToBigInt16(x)
#	define htole16(x) OSSwapHostToLittleInt16(x)
#	define be16toh(x) OSSwapBigToHostInt16(x)
#	define le16toh(x) OSSwapLittleToHostInt16(x)

#	define htobe32(x) OSSwapHostToBigInt32(x)
#	define htole32(x) OSSwapHostToLittleInt32(x)
#	define be32toh(x) OSSwapBigToHostInt32(x)
#	define le32toh(x) OSSwapLittleToHostInt32(x)

#	define htobe64(x) OSSwapHostToBigInt64(x)
#	define htole64(x) OSSwapHostToLittleInt64(x)
#	define be64toh(x) OSSwapBigToHostInt64(x)
#	define le64toh(x) OSSwapLittleToHostInt64(x)

#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN

#elif defined(__OpenBSD__)

#	include <sys/endian.h>

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)

#	include <sys/endian.h>

#	define be16toh(x) betoh16(x)
#	define le16toh(x) letoh16(x)

#	define be32toh(x) betoh32(x)
#	define le32toh(x) letoh32(x)

#	define be64toh(x) betoh64(x)
#	define le64toh(x) letoh64(x)

#elif defined(__WINDOWS__)

#	include <winsock2.h>
#	include <sys/param.h>

#	if BYTE_ORDER == LITTLE_ENDIAN

#		define htobe16(x) htons(x)
#		define htole16(x) (x)
#		define be16toh(x) ntohs(x)
#		define le16toh(x) (x)

#		define htobe32(x) htonl(x)
#		define htole32(x) (x)
#		define be32toh(x) ntohl(x)
#		define le32toh(x) (x)

#		define htobe64(x) htonll(x)
#		define htole64(x) (x)
#		define be64toh(x) ntohll(x)
#		define le64toh(x) (x)

#	elif BYTE_ORDER == BIG_ENDIAN

		/* that would be xbox 360 */
#		define htobe16(x) (x)
#		define htole16(x) __builtin_bswap16(x)
#		define be16toh(x) (x)
#		define le16toh(x) __builtin_bswap16(x)

#		define htobe32(x) (x)
#		define htole32(x) __builtin_bswap32(x)
#		define be32toh(x) (x)
#		define le32toh(x) __builtin_bswap32(x)

#		define htobe64(x) (x)
#		define htole64(x) __builtin_bswap64(x)
#		define be64toh(x) (x)
#		define le64toh(x) __builtin_bswap64(x)

#	else

#		error byte order not supported

#	endif

#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN

#else

#	error platform not supported

#endif

#endif

//--------------------------------------------------------------------------------
/*
 * Provide non-functional fcntl for windows
 */
#define F_GETFL 0
#define F_SETFL 0
#define O_NONBLOCK 0
#define SIGHUP SIGINT
static inline int  fcntl(int a, int b, ...)
{
    return 0;
}

//--------------------------------------------------------------------------------

/* Compare strings while treating digits characters numerically.
   Copyright (C) 1997-2019 Free Software Foundation, Inc.
   This file is part of the libiberty library.
   Contributed by Jean-Fran�ois Bignolles <bignolle@ecoledoc.ibp.fr>, 1997.

   Libiberty is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   Libiberty is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301 USA.  */

#ifndef WIN32_STRVERSCMP_H__
#define WIN32_STRVERSCMP_H__

//#include "libiberty.h"
//#include "safe-ctype.h"
#define ISDIGIT isdigit

/* 
@deftypefun int strverscmp (const char *@var{s1}, const char *@var{s2})
The @code{strverscmp} function compares the string @var{s1} against
@var{s2}, considering them as holding indices/version numbers.  Return
value follows the same conventions as found in the @code{strverscmp}
function.  In fact, if @var{s1} and @var{s2} contain no digits,
@code{strverscmp} behaves like @code{strcmp}.

Basically, we compare strings normally (character by character), until
we find a digit in each string - then we enter a special comparison
mode, where each sequence of digits is taken as a whole.  If we reach the
end of these two parts without noticing a difference, we return to the
standard comparison mode.  There are two types of numeric parts:
"integral" and "fractional" (those  begin with a '0'). The types
of the numeric parts affect the way we sort them:

@itemize @bullet
@item
integral/integral: we compare values as you would expect.

@item
fractional/integral: the fractional part is less than the integral one.
Again, no surprise.

@item
fractional/fractional: the things become a bit more complex.
If the common prefix contains only leading zeroes, the longest part is less
than the other one; else the comparison behaves normally.
@end itemize

@smallexample
strverscmp ("no digit", "no digit")
    @result{} 0    // @r{same behavior as strcmp.}
strverscmp ("item#99", "item#100")
    @result{} <0   // @r{same prefix, but 99 < 100.}
strverscmp ("alpha1", "alpha001")
    @result{} >0   // @r{fractional part inferior to integral one.}
strverscmp ("part1_f012", "part1_f01")
    @result{} >0   // @r{two fractional parts.}
strverscmp ("foo.009", "foo.0")
    @result{} <0   // @r{idem, but with leading zeroes only.}
@end smallexample

This function is especially useful when dealing with filename sorting,
because filenames frequently hold indices/version numbers.
@end deftypefun

*/

/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractional parts, S_Z: idem but with leading Zeroes only */
#define  S_N    0x0
#define  S_I    0x4
#define  S_F    0x8
#define  S_Z    0xC

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#define  CMP    2
#define  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the Glibc texinfo doc).  */

static inline int strverscmp (const char *s1, const char *s2)
{
  const unsigned char *p1 = (const unsigned char *) s1;
  const unsigned char *p2 = (const unsigned char *) s2;
  unsigned char c1, c2;
  int state;
  int diff;

  /* Symbol(s)    0       [1-9]   others  (padding)
     Transition   (10) 0  (01) d  (00) x  (11) -   */
  static const unsigned int next_state[] =
    {
      /* state    x    d    0    - */
      /* S_N */  S_N, S_I, S_Z, S_N,
      /* S_I */  S_N, S_I, S_I, S_I,
      /* S_F */  S_N, S_F, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z, S_Z
    };

  static const int result_type[] =
    {
      /* state   x/x  x/d  x/0  x/-  d/x  d/d  d/0  d/-
                 0/x  0/d  0/0  0/-  -/x  -/d  -/0  -/- */

      /* S_N */  CMP, CMP, CMP, CMP, CMP, LEN, CMP, CMP,
                 CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  CMP, +1,  LEN, LEN, CMP,
                 +1,  LEN, LEN, CMP, CMP, CMP, CMP, CMP,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, LEN, CMP, CMP,
                 CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  CMP, -1,  CMP, CMP, CMP,
                 -1,  CMP, CMP, CMP
    };

  if (p1 == p2)
    return 0;

  c1 = *p1++;
  c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  state = S_N | ((c1 == '0') + (ISDIGIT (c1) != 0));

  while ((diff = c1 - c2) == 0 && c1 != '\0')
    {
      state = next_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state |= (c1 == '0') + (ISDIGIT (c1) != 0);
    }

  state = result_type[state << 2 | (((c2 == '0') + (ISDIGIT (c2) != 0)))];

  switch (state)
    {
    case CMP:
      return diff;
      
    case LEN:
      while (ISDIGIT (*p1++))
	if (!ISDIGIT (*p2++))
	  return 1;
      
      return ISDIGIT (*p2) ? -1 : diff;
      
    default:
      return state;
    }
}

#endif /*WIN32_STRVERSCMP_H__*/

