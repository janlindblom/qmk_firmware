/*
 * Copyright (c) 2009 Andrew Collette <andrew.collette at gmail.com>
 * http://lzfx.googlecode.com
 * AVR adaptation Copyright © 2022 Jan Lindblom (@janlindblom)
 *
 * Implements an LZF-compatible compressor/decompressor based on the liblzf
 * codebase written by Marc Lehmann.  This code is released under the BSD
 * license.  License and original copyright statement follow.
 *
 *
 * Copyright (c) 2000-2008 Marc Alexander Lehmann <schmorp@schmorp.de>
 *
 * Redistribution and use in source and binary forms, with or without modifica-
 * tion, are permitted provided that the following conditions are met:
 *
 *   1.  Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MER-
 * CHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTH-
 * ERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LZFX_H
#define LZFX_H

#ifdef __cplusplus
#    ifndef ARDUINO
#        include <cstdint>
#        include <cstring> /* We need this for memset */
extern "C" {
#    else /* !ARDUINO */
#        include <Arduino.h>
#    endif /* ARDUINO */
#else
#    include <stdint.h>
#    include <string.h> /* We need this for memset */
#endif                  /* __cplusplus */

/*  Documented behavior, including function signatures and error codes,
    is guaranteed to remain unchanged for releases with the same major
    version number.  Releases of the same major version are also able
    to read each other's output, although the output itself is not
    guaranteed to be byte-for-byte identical.
*/
#define LZFX_VERSION_MAJOR 0
#define LZFX_VERSION_MINOR 1
#define LZFX_VERSION_STRING "0.1"

#if defined(__AVR__) && !defined(ARDUINO)
typedef int_fast8_t   int_t;
typedef uint_fast8_t  uint_t;
typedef int_fast16_t  long_t;
typedef uint_fast16_t ulong_t;
typedef int_t         ssize_t;
#else
typedef unsigned char uint8_t;
typedef int           int_t;
typedef unsigned int  uint_t;
typedef long          long_t;
typedef unsigned long ulong_t;
#endif /* __AVR__ && !ARDUINO */

/* Hashtable size (2**LZFX_HLOG entries) */
#ifndef LZFX_HLOG
#    ifdef __AVR__
#        define LZFX_HLOG 8
#        define LZFX_HSIZE 256
#    else
#        define LZFX_HLOG 16
#        define LZFX_HSIZE 65536
#    endif /* __AVR__ */
#endif     /* LZFX_HLOG */

typedef const uint8_t* LZSTATE[LZFX_HSIZE];

/* Predefined errors. */
#define LZFX_ESIZE -1    /* Output buffer too small */
#define LZFX_ECORRUPT -2 /* Invalid data for decompression */
#define LZFX_EARGS -3    /* Arguments invalid (NULL) */

#ifdef LZFX_COMPRESS
/*  Buffer-to buffer compression.

    Supply pre-allocated input and output buffers via ibuf and obuf, and
    their size in bytes via ilen and olen.  Buffers may not overlap.

    On success, the function returns a non-negative value and the argument
    olen contains the compressed size in bytes.  On failure, a negative
    value is returned and olen is not modified.
*/
int_t lzfx_compress(const void* ibuf, uint_t ilen, void* obuf, uint_t* olen);
#endif

#ifdef LZFX_DECOMPRESS
/*  Buffer-to-buffer decompression.

    Supply pre-allocated input and output buffers via ibuf and obuf, and
    their size in bytes via ilen and olen.  Buffers may not overlap.

    On success, the function returns a non-negative value and the argument
    olen contains the uncompressed size in bytes.  On failure, a negative
    value is returned.

    If the failure code is LZFX_ESIZE, olen contains the minimum buffer size
    required to hold the decompressed data.  Otherwise, olen is not modified.

    Supplying a zero *olen is a valid and supported strategy to determine the
    required buffer size.  This does not require decompression of the entire
    stream and is consequently very fast.  Argument obuf may be NULL in
    this case only.
*/
int_t lzfx_decompress(const void* ibuf, uint_t ilen, void* obuf, uint_t* olen);
#endif
#if defined(__cplusplus) && !defined(ARDUINO)
} /* extern "C" */
#endif /* __cplusplus && !ARDUINO */

#if defined(ARDUINO) && defined(__cplusplus)
class LZFX {
   public:
    int compress(const void* ibuf, unsigned int ilen, void* obuf, unsigned int* olen);
    int decompress(const void* ibuf, unsigned int ilen, void* obuf, unsigned int* olen);
};
#endif /* ARDUINO && __cplusplus */
#endif /* LZFX_H */
