/*
 * Copyright (c) 2017 Vladimir Lin, Foxman
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library in the file COPYING;
 * if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __VGDEFS_H
#define __VGDEFS_H

/* Standard headers */

#if defined(WIN32)
#  include <windows.h>
#endif

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#ifndef __APPLE__
#  include <malloc.h>
#endif

/* Disable VGHandle-pointer conversion warnings since we
   do deal with it by defining VGHandle properly */

#if defined(_MSC_VER)
#  pragma warning(disable:4311)
#  pragma warning(disable:4312)
#endif

/* Type definitions */

#if defined(HAVE_CONFIG_H)
#include "../config.h"
#
#  if HAVE_INTTYPES_H
#  include <inttypes.h>
#  endif
#
#else
#
#  define int8_t    char
#  define uint8_t   unsigned char
#  define int16_t   short
#  define uint16_t  unsigned short
#  define int32_t   int
#  define uint32_t  unsigned int
#  define int64_t   long long
#  define uint64_t  unsigned long long
#
#endif

typedef int8_t      vgint8    ;
typedef uint8_t     vguint8   ;
typedef int16_t     vgint16   ;
typedef uint16_t    vguint16  ;
typedef int32_t     vgint32   ;
typedef uint32_t    vguint32  ;
typedef float       vgfloat32 ;

#define vgint       vgint32
#define vguint      vguint32
#define vgfloat     vgfloat32

/* Maximum / minimum values */

#define VG_MAX_INT  (0x7fffffff)
#define VG_MIN_INT (-0x7fffffff-1)

#define VG_MANTISSA_BITS   23
#define VG_EXPONENT_BITS   8

/* all 1s in exponent yields NaN in IEEE 754 so we take
   1 less then maximum representable with exponent bits */
#define VG_MAX_EXPONENT ((1 << SH_EXPONENT_BITS) - 2)
/* maximum representable with mantissa bits */
#define VG_MAX_MANTISSA ((1 << SH_MANTISSA_BITS) - 1)
/* compose into IEEE754 floating point bit value */
#define VG_MAX_FLOAT_BITS (SH_MAX_EXPONENT << SH_MANTISSA_BITS) | SH_MAX_MANTISSA

typedef union    {
  float        f ;
  unsigned int i ;
} vgfloatint     ;

vgfloat getMaxFloat();

/* Portable function definitions */

#define VG_SQRT   (float) sqrt
#define VG_COS    (float) cos
#define VG_SIN    (float) sin
#define VG_ACOS   (float) acos
#define VG_ASIN   (float) asin
#define VG_ATAN   (float) atan
#define VG_FLOOR  (float) floor
#define VG_CEIL   (float) ceil
#define VG_ASSERT         assert

#if defined(__isnan) || (defined(__APPLE__) && (__GNUC__ == 3))
#  define VG_ISNAN __isnan
#elif defined(_isnan) || defined(WIN32)
#  define VG_ISNAN  _isnan
#else
#  define VG_ISNAN   isnan
#endif

/* Helper macros */

#define PI                               M_PI
#define VG_DEG2RAD(a)                    (a * PI / 180.0f)
#define VG_RAD2DEG(a)                    (a * 180.0f / PI)
#define VG_ABS(a)                        ((a < 0.0f) ? -a : a)
#define VG_MAX(a,b)                      ((a > b) ? a : b)
#define VG_MIN(a,b)                      ((a < b) ? a : b)
#define VG_NEARZERO(a)                   (a >= -0.0001 && a < 0.0001)
#define VG_SWAP(a,b)                     {vgfloat t=a; a=b; b=t;}
#define VG_CLAMP(a,min,max)              {if (a<min) a=min; if (a>max) a=max; }

#define VG_NEWOBJ(type,obj)              { obj = (type*)malloc(sizeof(type)); if(obj) type ## _ctor(obj); }
#define VG_INITOBJ(type,obj)             { type ## _ctor(&obj); }
#define VG_DEINITOBJ(type,obj)           { type ## _dtor(&obj); }
#define VG_DELETEOBJ(type,obj)           { if(obj) type ## _dtor(obj); free(obj); }

/* Implementation limits */

#define VG_MAX_SCISSOR_RECTS             1
#define VG_MAX_DASH_COUNT                VG_MAXINT
#define VG_MAX_IMAGE_WIDTH               VG_MAXINT
#define VG_MAX_IMAGE_HEIGHT              VG_MAXINT
#define VG_MAX_IMAGE_PIXELS              VG_MAXINT
#define VG_MAX_IMAGE_BYTES               VG_MAXINT
#define VG_MAX_COLOR_RAMP_STOPS          256

#define VG_MAX_VERTICES                  999999999
#define VG_MAX_RECURSE_DEPTH             16

#define VG_GRADIENT_TEX_SIZE             1024
#define VG_GRADIENT_TEX_COORDSIZE        4096 /* 1024 * RGBA */

/* OpenGL headers */

#if defined(__APPLE__)
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#elif defined(_WIN32)
#  include <GL/gl.h>
#  include <GL/glu.h>
#else
#  define GL_GLEXT_LEGACY /* don't include glext.h */
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glx.h>
#endif

#include "vgExtensions.h"

#endif /* __SHDEFS_H */
