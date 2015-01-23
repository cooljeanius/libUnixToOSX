/* portable_endian.h
 * "License": Public Domain
 * I, Mathias Panzenböck, place this file hereby into the public domain.
 * Use it at your own risk for whatever you like.
 */

#ifndef PORTABLE_ENDIAN_H__
#define PORTABLE_ENDIAN_H__ 1

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
# define __WINDOWS__
#endif /* __WINDOWS__ */

#if defined(__linux__) || defined(__CYGWIN__) || defined(HAVE_ENDIAN_H)
# include <endian.h>
#elif defined(__APPLE__) || defined(HAVE_LIBKERN_OSBYTEORDER_H)
# include <libkern/OSByteOrder.h>
/* 16-bit ones: */
# define htobe16(x) OSSwapHostToBigInt16(x)
# define htole16(x) OSSwapHostToLittleInt16(x)
# define be16toh(x) OSSwapBigToHostInt16(x)
# define le16toh(x) OSSwapLittleToHostInt16(x)
/* 32-bit ones: */
# define htobe32(x) OSSwapHostToBigInt32(x)
# define htole32(x) OSSwapHostToLittleInt32(x)
# define be32toh(x) OSSwapBigToHostInt32(x)
# define le32toh(x) OSSwapLittleToHostInt32(x)
/* 64-bit ones: */
# define htobe64(x) OSSwapHostToBigInt64(x)
# define htole64(x) OSSwapHostToLittleInt64(x)
# define be64toh(x) OSSwapBigToHostInt64(x)
# define le64toh(x) OSSwapLittleToHostInt64(x)
/* other decls: */
# define __BYTE_ORDER    BYTE_ORDER
# define __BIG_ENDIAN    BIG_ENDIAN
# define __LITTLE_ENDIAN LITTLE_ENDIAN
# define __PDP_ENDIAN    PDP_ENDIAN
#elif defined(__OpenBSD__)
# include <sys/endian.h>
#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)
# include <sys/endian.h>
/* 16-bit ones: */
# define be16toh(x) betoh16(x)
# define le16toh(x) letoh16(x)
/* 32-bit ones: */
# define be32toh(x) betoh32(x)
# define le32toh(x) letoh32(x)
/* 64-bit ones: */
# define be64toh(x) betoh64(x)
# define le64toh(x) letoh64(x)
#elif defined(__WINDOWS__)
# include <winsock2.h>
# include <sys/param.h>
# if (BYTE_ORDER == LITTLE_ENDIAN)
/* 16-bit ones: */
#  define htobe16(x) htons(x)
#  define htole16(x) (x)
#  define be16toh(x) ntohs(x)
#  define le16toh(x) (x)
/* 32-bit ones: */
#  define htobe32(x) htonl(x)
#  define htole32(x) (x)
#  define be32toh(x) ntohl(x)
#  define le32toh(x) (x)
/* 64-bit ones: */
#  define htobe64(x) htonll(x)
#  define htole64(x) (x)
#  define be64toh(x) ntohll(x)
#  define le64toh(x) (x)
# elif (BYTE_ORDER == BIG_ENDIAN)
/* (that would be xbox 360) */
/* 16-bit ones: */
#  define htobe16(x) (x)
#  define htole16(x) __builtin_bswap16(x)
#  define be16toh(x) (x)
#  define le16toh(x) __builtin_bswap16(x)
/* 32-bit ones: */
#  define htobe32(x) (x)
#  define htole32(x) __builtin_bswap32(x)
#  define be32toh(x) (x)
#  define le32toh(x) __builtin_bswap32(x)
/* 64-bit ones: */
#  define htobe64(x) (x)
#  define htole64(x) __builtin_bswap64(x)
#  define be64toh(x) (x)
#  define le64toh(x) __builtin_bswap64(x)
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   warning "byte order not supported for Windows, some endianness functions may be missing."
#  else
#   error "byte order not supported for Windows"
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* BYTE_ORDER == [LITTLE|BIG]_ENDIAN */
/* other decls: */
# define __BYTE_ORDER    BYTE_ORDER
# define __BIG_ENDIAN    BIG_ENDIAN
# define __LITTLE_ENDIAN LITTLE_ENDIAN
# define __PDP_ENDIAN    PDP_ENDIAN
#else
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "platform not supported, some endianness functions may be missing."
# else
#  error "platform not supported"
# endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* platform check */

#endif /* PORTABLE_ENDIAN_H__ */

/* EOF */
