/* -*- mode: C; tab-width:8;  -*-

             fxmesa.c - 3Dfx VooDoo/Mesa interface
*/

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * V0.18 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         the Mesa-2.4beta3 is finally using the driver quads support (the previous Mesa versions have never taken any advantage from the quads support !)
 *         tested with the Glide 2.4 for Win
 *         ported all asm code to Linux
 *         ported the v0.18 to Linux (without asm code)
 *         back to Linux !!!
 *         optimized the SETUP macro (no more vertex snap for points and lines)
 *         optimized the SETUP macro (added one argument)
 *         the Mesa/Voodoo is now 20/30% for points, lines and small triangles !
 *         performance improvement setting VBSIZE to 72 
 *         the GrVertex texture code is now written in asm
 *         the GrVertex zbuffer code is now written in asm
 *         the GrVertex wbuffer code is now written in asm
 *         the GrVertex gouraud code is now written in asm
 *         the GrVertex snap code is now written in asm
 *         changed the 8bit compressed texture maps in 8bit palette texture maps support (it has the some advantage of compressed texture maps without the problem of a fixed NCC table for all mipmap levels)
 *         written the support for 8bit compressed texture maps (but texture maps with more than one mipmap level aren't working fine)
 *         finnaly everthing is working fine in MesaQuake !
 *         fixed a bug in the computation of texture mapping coordinates (I have found the bug thanks to MesaQuake !)
 *         written the GL_REPLACE support (mainly for MesaQuake)
 *         written the support for textures with not all mipmap levels defined
 *         rewritten all the Texture memory stuff
 *         written the MesaQuake support (define MESAQUAKE)
 *         working with a ZBuffer if glOrtho or not int the default glDepthRange, otherwise working with the WBuffer
 *         written the glDepthRange support
 *
 *         Diego Picciani (d.picciani@novacomp.it) Nova Computer s.r.l.
 *         written the fxCloseHardware() and the fxQuaryHardware() (mainly for the VoodooWGL emulator)
 *
 *         Brian Paul (brianp@elastic.avid.com) Avid Technology
 *         implemented read/write_color_span() so glRead/DrawPixels() works
 *         now needs Glide 2.3 or later.  Removed GLIDE_FULL_SCREEN and call to grSstOpen().
 *
 * V0.17 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         optimized the bitmap support (66% faster)
 *         tested with the Mesa 2.3beta2
 *
 *         Diego Picciani (d.picciani@novacomp.it) Nova Computer s.r.l.
 *         solved a problem with the drawbitmap() and the Voodoo Rush (GR_ORIGIN_LOWER_LEFT did not work with the Stingray)
 *
 *         Brian Paul (brianp@elastic.avid.com) Avid Technology
 *         linux stuff
 *         general code clean-up
 *         added attribList parameter to fxMesaCreateContext()
 *         single buffering works now
 *         VB colors are now GLubytes, removed ColorShift stuff
 *
 *         Paul Metzger
 *         linux stuff
 *
 * V0.16 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         written the quadfunc support (no performance improvement)
 *         written the support for the new Mesa 2.3beta1 driver interface (Wow ! It is faaaster)
 *         rewritten the glBitmap support for the Glide 2.3 (~35% slower !)
 *         written the glBitmap support for the most common case (fonts)
 *
 *         Jack Palevich
 *         Glide 2.3 porting
 *
 *         Diego Picciani (d.picciani@novacomp.it) Nova Computer s.r.l.
 *         extended the fxMesaCreateContext() and fxMesaCreateBestContext() functions in order to support also the Voodoo Rush
 *         tested with the Hercules Stingray 128/3D (The rendering in a window works !)
 *
 * V0.15 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         written the GL_LUMINANCE_ALPHA support
 *         written the GL_ALPHA support
 *         written the GL_LUMINANCE support
 *         now SETUP correctly set color for mono color sequences
 *         written the 9x1,10x1,...,1x9,1x10,... texture map ratio support
 *         written the no square texture map support
 *         the fog table is no more rebuilt inside setup_fx_units() each time
 *
 *         Henri Fousse (arnaud@pobox.oleane.com) Thomson Training & Simulation
 *         written (not yet finished: no texture mapping) support for glOrtho
 *         some change to setup functions
 *         the fog support is now fully compatible with the standard OpenGL
 *         rewritten several parts of the driver in order to take advantage of meshes (40% faster !!!)
 *
 * V0.14 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         now glAlphaFunc() works
 *         now glDepthMask() works
 *         solved a mipmap problem when using more than one texture
 *         moved ti, texid and wscale inside the fxMesaContext (now we can easy support more ctx and more boards)
 *         the management of the fxMesaContext was completly broken !
 *         solved several problems about Alpha and texture Alpha
 *         4 (RGBA) texture channels supported
 *         setting the default color to white
 *
 *         Henri Fousse (arnaud@pobox.oleane.com) Thomson Training & Simulation
 *         small change to fxMesaCreateContext() and fxMesaMakeCurrent()
 *         written the fog support
 *         setting the default clear color to black
 *         written cleangraphics() for the onexit() function
 *         written fxMesaCreateBestContext()
 *
 * V0.13 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         now glBlendFunc() works for all glBlendFunc without DST_ALPHA (because the alpha buffer is not yet implemented) 
 *         now fxMesaCreateContext() accept resolution and refresh rate
 *         fixed a bug for texture mapping: the w (alias z) must be set also without depth buffer
 *         fixed a bug for texture image with width!=256
 *         written texparam()
 *         written all point, line and triangle functions for all possible supported contexts and
 *         the driver is slight faster with points, lines and small triangles
 *         fixed a small bug in fx/fxmesa.h (glOrtho)
 *
 * V0.12 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         glDepthFunc supported
 *         introduced a trick to discover the far plane distance (see fxMesaSetFar and fx/fxmesa.h)
 *         now the wbuffer works with homogeneous coordinate (and it doesn't work with a glOrtho projection :)
 *         solved several problems with homogeneous coordinate and texture mapping
 *         fixed a bug in all line functions
 *         fixed a clear framebuffer bug
 *         solved a display list/teximg problem (but use glBindTexture: it is several times faster)
 *
 * V0.11 - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         introduced texture mapping support (not yet finished !)
 *         tested with Mesa2.2b6
 *         the driver is faster 
 *         written glFlush/glFinish
 *         the driver print a lot of info about the Glide lib
 *
 * v0.1  - David Bucciarelli (tech.hmw@plus.it) Humanware s.r.l.
 *         Initial revision
 *
 */

#if defined(FX)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "context.h"
#include "macros.h"
#include "matrix.h"
#include "texture.h"
#include "types.h"
#include "vb.h"
#include "xform.h"
#include "GL/fxmesa.h"
#include <texus.h>

#ifdef MESAQUAKE
#define MAXNUM_TEX	512
#else
#define MAXNUM_TEX	256
#endif

#define FXCOLOR(r,g,b,a) (( ((unsigned int)(a))<<24 )|( ((unsigned int)(b))<<16 )|( ((unsigned int)(g))<<8 )|(r))

#define FUNC_DEPTH	0x01
#define FUNC_SMOOTH	0x02
#define FUNC_TEX_DECAL	0x04
#define FUNC_TEX_MOD	0x08

typedef struct {
  GLboolean valid;
  FxU32 address;
  GrTexInfo info;

  GrTextureFilterMode_t minfilt;
  GrTextureFilterMode_t maxfilt;

  GrTextureClampMode_t sclamp;
  GrTextureClampMode_t tclamp;

  GrMipMapMode_t mmmode;

  GLfloat sscale,tscale;
  GLint levelsdefined;

  GLboolean fixedpalette;
  GuTexPalette palette;
} texinfo;

struct fx_mesa_context {
  GLcontext *gl_ctx;             /* the core Mesa context */
  GLvisual *gl_vis;              /* describes the color buffer */
  GLframebuffer *gl_buffer;      /* the ancillary buffers */

  GLint width, height;           /* size of color buffer */
  GLboolean double_buffer;
  GLboolean fixedpalette_texture;
  GLboolean wbuffer;

  GrBuffer_t currentfb;

  GrColor_t color;
  GrColor_t clearc;
  GrAlpha_t cleara;

  FxU32 mintexmem;
  texinfo ti[MAXNUM_TEX];
  int currenttex;

  float wscale,nearval,farval;

  GLenum fogtablemode;
  GLfloat fogdensity;
  GrFog_t fogtable[64];

  GrVertex gwin[VB_SIZE];
};

fxMesaContext CurrentfxMesaCtx=NULL;

/*
 * Status of 3Dfx hardware initialization
 */

static int glideInitialized = 0;
static int _3dfxPresent = 0;
static GrHwConfiguration hwconfig;


/**********************************************************************/
/*****                 Miscellaneous functions                    *****/
/**********************************************************************/

/* return buffer size information */
static void buffer_size(GLcontext *ctx, GLuint *width, GLuint *height)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: buffer_size(...)\n");
#endif

  *width=fxMesa->width;
  *height=fxMesa->height;
}


/* Set current drawing color */
static void set_color(GLcontext *ctx, GLubyte red, GLubyte green,
		      GLubyte blue, GLubyte alpha )
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: set_color(%d,%d,%d,%d)\n",red,green,blue,alpha);
#endif

  fxMesa->color=FXCOLOR(red,green,blue,alpha);
}


/* implements glClearColor() */
static void clear_color(GLcontext *ctx, GLubyte red, GLubyte green,
			GLubyte blue, GLubyte alpha )
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: clear_color(%d,%d,%d,%d)\n",red,green,blue,alpha);
#endif
 
  fxMesa->clearc=FXCOLOR(red,green,blue,255);
  fxMesa->cleara=alpha;
}


/* clear the frame buffer */
static void clear(GLcontext *ctx, GLboolean all,
		  GLint x, GLint y, GLint width, GLint height )
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: clear(%d,%d,%d,%d)\n",x,y,width,height);
#endif

  grDepthMask(FXFALSE);

  grBufferClear(fxMesa->clearc,fxMesa->cleara,0);

  if(ctx->Depth.Test && ctx->Depth.Mask)
    grDepthMask(FXTRUE);
}


/*  set the buffer used in double buffering */
static GLboolean set_buffer(GLcontext *ctx, GLenum mode )
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: set_buffer(%d)\n",mode);
#endif

  if (fxMesa->double_buffer) {
    if(mode==GL_FRONT)
      fxMesa->currentfb = GR_BUFFER_FRONTBUFFER;
    else if(mode==GL_BACK)
      fxMesa->currentfb = GR_BUFFER_BACKBUFFER;
    else
      return GL_FALSE;
  } else {
    if(mode==GL_FRONT)
      fxMesa->currentfb = GR_BUFFER_FRONTBUFFER;
    else
      return GL_FALSE;
  }

  grRenderBuffer(fxMesa->currentfb);
  return GL_TRUE;
}


static GLboolean drawbitmap(GLcontext *ctx, GLsizei width, GLsizei height,
                            GLfloat xorig, GLfloat yorig,
                            GLfloat xmove, GLfloat ymove,
                            const struct gl_image *bitmap)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
  FxU16 *p;
  GrLfbInfo_t info;
  GLubyte *pb;
  int x,y;
  GLint r,g,b,a,px,py,scrwidth,scrheight,stride;
  FxU16 color;

#define ISCLIPPED(rx) ( ((rx)<0) || ((rx)>=scrwidth) )
#define DRAWBIT(i) {	   \
  if(!ISCLIPPED(x+px))	   \
    if( (*pb) & (1<<(i)) ) \
      (*p)=color;	   \
  p++;                     \
  x++;			   \
  if(x>=width) {           \
    pb++;                  \
    break;                 \
  }                        \
}

  scrwidth=fxMesa->width;
  scrheight=fxMesa->height;

  px=(GLint)((ctx->Current.RasterPos[0]-xorig)+0.0F);
  py=(GLint)((ctx->Current.RasterPos[1]-yorig)+0.0F);

  if((px>=scrwidth) || (px+width<=0) || (py>=scrheight) || (py+height<=0))
    return GL_TRUE;

  pb=(GLubyte *)bitmap->Data;

  if(py<0) {
    pb+=(bitmap->Height*(-py)) >> (3+1);
    height+=py;
    py=0;
  }

  if(py+height>=scrheight)
    height-=(py+height)-scrheight;

  info.size=sizeof(info);
  if(!grLfbLock(GR_LFB_WRITE_ONLY,
		fxMesa->currentfb,
		GR_LFBWRITEMODE_565,
		GR_ORIGIN_UPPER_LEFT,
		FXFALSE,
		&info)) {
#ifndef FX_SILENT
    fprintf(stderr,"fx Driver: error locking the linear frame buffer\n");
#endif
    return GL_TRUE;
  }

  r=(GLint)(ctx->Current.RasterColor[0]*ctx->Visual->RedScale);
  g=(GLint)(ctx->Current.RasterColor[1]*ctx->Visual->GreenScale);
  b=(GLint)(ctx->Current.RasterColor[2]*ctx->Visual->BlueScale);
  a=(GLint)(ctx->Current.RasterColor[3]*ctx->Visual->AlphaScale);
  color=(FxU16)
    ( ((FxU16)0xf8 & r) <<(11-3))  |
    ( ((FxU16)0xfc & g) <<(5-3+1)) |
    ( ((FxU16)0xf8 & b) >> 3);

  stride=info.strideInBytes>>1;

  /* This code is a bit slow... */

  for(y=0;y<height;y++) {
    p=((FxU16 *)info.lfbPtr)+px+((scrheight-(y+py))*stride);

    for(x=0;;) {
      DRAWBIT(7);	DRAWBIT(6);	DRAWBIT(5);	DRAWBIT(4);
      DRAWBIT(3);	DRAWBIT(2);	DRAWBIT(1);	DRAWBIT(0);
      pb++;
    }
  }

  grLfbUnlock(GR_LFB_WRITE_ONLY,fxMesa->currentfb);

#undef ISCLIPPED
#undef DRAWBIT

  return GL_TRUE;
}


/************************************************************************/
/************************************************************************/
/************************************************************************/

#define GOURAUD_ENABLED 0x1
#define TEXTURE_ENABLED 0x2
#define FOG_ENABLED		0x4
#define WBUFFER_ENABLED 0x8
#define ZBUFFER_ENABLED 0x10

#ifdef __WIN32__

/************************************************************************/
/********* The Win32 Version of the asm GrVertex Setup code *************/
/************************************************************************/

#define RDTSC	__asm _emit 0x0f __asm _emit 0x31

#if 0
#define DATA_PROFILING char *format="Number of Cycles for the GrVertex setup: %u (%u number of GrVertex)\n"; unsigned long numcycl

#define START_PROFILING __asm { \
  RDTSC                         \							
  _asm mov numcycl,eax	        \
}

#define STOP_PROFILING __asm { \
  RDTSC		               \
  __asm mov ebx,vend	       \
  __asm sub ebx,vstart	       \
  __asm push ebx	       \
  __asm sub eax,numcycl	       \
  __asm push eax	       \
  __asm mov ecx,format	       \
  __asm push ecx	       \
  __asm call printf	       \
  __asm add esp,12             \
}
#else
#define DATA_PROFILING
#define START_PROFILING
#define STOP_PROFILING
#endif

#define NOSNAP(v) __asm {                       \
  __asm mov eax,dword ptr [edx]	                \
  __asm mov ebx,dword ptr [edx+4]               \
  __asm mov dword ptr [ecx]GrVertex.x,eax       \
  __asm mov dword ptr [ecx]GrVertex.y,ebx       \
}

#define SNAP(v) __asm {                         \
  /* Snap verticies */	                        \
  __asm fld dword ptr [edx]			\
  __asm fadd snapconst				\
  __asm fld dword ptr [edx+4]			\
  __asm fadd snapconst				\
  __asm fxch					\
  __asm fstp dword ptr [ecx]GrVertex.x		\
  __asm fstp dword ptr [ecx]GrVertex.y		\
}

#define GOURAUD(v) __asm {              \
  __asm mov ebx,vcol			\
  __asm mov eax,dword ptr [ebx]		\
  __asm mov vwin,edx			\
  __asm add ebx,4			\
  __asm mov vcol,ebx			\
                                        \
  __asm sub edx,edx			\
  __asm sub ebx,ebx			\
  __asm mov dl,ah			\
  __asm mov bl,al			\
  __asm mov stmp2,dx			\
  __asm shr eax,16			\
  __asm mov stmp1,bx			\
  __asm	fild stmp2			\
  __asm	fild stmp1			\
  __asm mov bl,al			\
  __asm mov dl,ah			\
  __asm mov stmp1,bx			\
  __asm mov stmp2,dx			\
  __asm	fild stmp1			\
  __asm fild stmp2			\
  __asm fstp dword ptr [ecx]GrVertex.a	\
  __asm fstp dword ptr [ecx]GrVertex.b	\
  __asm fstp dword ptr [ecx]GrVertex.r	\
  __asm fstp dword ptr [ecx]GrVertex.g	\
  __asm mov edx,vwin                    \
}

#define TEXTURE(v) __asm {              \
  __asm mov eax,vtex		        \
  __asm fld sscale			\
  __asm fmul dword ptr [eax]				\
  __asm fmul dword ptr [ecx]GrVertex.oow		\
  __asm fstp dword ptr [ecx]GrVertex.tmuvtx[0].sow	\
  __asm fld tscale			\
  __asm fmul dword ptr [eax+4]	        \
  __asm add eax,16			\
  __asm fmul dword ptr [ecx]GrVertex.oow		\
  __asm fstp dword ptr [ecx]GrVertex.tmuvtx[0].tow	\
  __asm mov vtex,eax		        \
}

#define WBUFFER(v) __asm {      \
  __asm mov ebx,vclip		\
  __asm fld wscale		\
  __asm fdiv dword ptr [ebx]	\
  __asm add ebx,16		\
  __asm mov vclip,ebx		\
  __asm fstp dword ptr [ecx]GrVertex.oow	\
}

#define ZBUFFER(v) __asm {                      \
  __asm	mov eax,dword ptr [edx+8]		\
  __asm mov dword ptr [ecx]GrVertex.ooz,eax	\
}

#define NOP(v) 

#define SETUP(label, snap, gouraud, texture, wdepth, zdepth) {	\
  struct vertex_buffer *VB = ctx->VB;				\
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;		\
  GrVertex *GVB = &fxMesa->gwin[vstart];			\
  GrVertex *GVBlast = &fxMesa->gwin[vend];			\
  float wscale = fxMesa->wscale; 				\
  float sscale = fxMesa->ti[fxMesa->currenttex].sscale;	        \
  float tscale = fxMesa->ti[fxMesa->currenttex].tscale;	        \
  float snapconst=(float)(3L<<18);				\
  float *vwin=VB->Win[vstart];					\
  short stmp1,stmp2;						\
  unsigned char *vcol=VB->Color[vstart];		        \
  float *vclip=&VB->Clip[vstart][3];			        \
  float *vtex=VB->TexCoord[vstart];			        \
  DATA_PROFILING;						\
								\
  __asm	{							\
    START_PROFILING			\
    /* eax: tmp */			\
    /* ebx: tmp */			\
    /* ecx: GVB */			\
    /* edx: vwin */			\
    __asm mov ecx,GVB			\
    __asm mov edx,vwin		        \
    			                \
    __asm align 16			\
    __asm label :			\
    snap(GVB)				\
    gouraud(GVB)			\
    wdepth(GVB)				\
    zdepth(GVB)				\
    texture(GVB)			\
    				        \
    __asm add ecx,SIZE GrVertex		\
    __asm add edx,12			\
    __asm cmp ecx,GVBlast	        \
    __asm jne label			\
    				        \
    STOP_PROFILING			\
  }					\
}


#else /******************************************************************/


#ifdef __linux__


/************************************************************************/
/*********** The Linux Version of the asm GrVertex Setup code ***********/
/************************************************************************/


#define NOSNAP(v) "      \
  movl (%%edx),%%eax;    \
  movl 4(%%edx),%%ebx;   \
  movl %%eax,(%%ecx);    \
  movl %%ebx,4(%%ecx);"

#define SNAP(v) "               \
  flds (%%edx);	        	\
  fadds %0;			\
  flds 4(%%edx);		\
  fadds %0;			\
  fxch;				\
  fstps (%%ecx);	        \
  fstps 4(%%ecx);" 

#define GOURAUD(v) "            \
  movl %2,%%ebx;                \
  movl (%%ebx),%%eax;		\
  movl %%edx,%1; 		\
  addl $4,%%ebx;  		\
  movl %%ebx,%2;                \
                                \
  subl %%edx,%%edx;		\
  subl %%ebx,%%ebx;		\
  movb %%ah,%%dl;        	\
  movb %%al,%%bl;		\
  movw %%dx,%4;                 \
         			\
  shrl $16,%%eax;  		\
  movw %%bx,%3;			\
  fildw %4;			\
  fildw %3;			\
  movb %%al,%%bl;		\
  movb %%ah,%%dl;		\
  movw %%bx,%3;			\
  movw %%dx,%4;			\
  fildw %3;			\
  fildw %4;			\
  fstps 28(%%ecx);         	\
  fstps 20(%%ecx);         	\
  fstps 12(%%ecx);         	\
  fstps 16(%%ecx);         	\
  movl %1,%%edx;"

#define TEXTURE(v) "            \
  movl %5,%%eax;	        \
  flds %6;			\
  fmuls (%%eax);		\
  fmuls 32(%%ecx);		\
  fstps 36(%%ecx);       	\
  flds %7;			\
  fmuls 4(%%eax);	        \
  addl $16,%%eax;		\
  fmuls 32(%%ecx);		\
  fstps 40(%%ecx);       	\
  mov %%eax,%5;"

#define WBUFFER(v) "            \
  movl %9,%%ebx;		\
  flds %8;		        \
  fdivs (%%ebx);                \
  addl $16,%%ebx;		\
  movl %%ebx,%9;		\
  fstps 32(%%ecx);"

#define ZBUFFER(v) "            \
  movl 8(%%edx),%%eax;		\
  movl %%eax,24(%%ecx);"

#define NOP(v) ""

#define SETUP_ASMLOOP(c)               \
  __asm__ volatile (c                  \
  : /* not correctly filled */         \
  : "m" (GVB), "m" (GVBlast), "m" (vwin), "i" (sizeof(GrVertex)) \
  : "eax", "ebx", "ecx", "edx", "cc", "memory")

#define SETUP_ASM(c)                   \
  __asm__ volatile (c                  \
  : /* not correctly filled */         \
  : "m" (snapconst), "m" (vwin),       \
    "m" (vcol), "m" (stmp1), "m" (stmp2), "m" (vtex), "m" (sscale), "m" (tscale),  \
    "m" (wscale), "m" (vclip)                                                      \
  : "eax", "ebx", "ecx", "edx", "cc", "memory")

#define SETUP(label, snap, gouraud, texture, wdepth, zdepth) {  \
  struct vertex_buffer *VB = ctx->VB;				\
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;		\
  GrVertex *GVB = &fxMesa->gwin[vstart];			\
  GrVertex *GVBlast = &fxMesa->gwin[vend];			\
  float wscale = fxMesa->wscale; 				\
  float sscale = fxMesa->ti[fxMesa->currenttex].sscale;	        \
  float tscale = fxMesa->ti[fxMesa->currenttex].tscale;	        \
  float snapconst=(float)(3L<<18);				\
  float *vwin=VB->Win[vstart];					\
  short stmp1,stmp2;						\
  unsigned char *vcol=VB->Color[vstart];		        \
  float *vclip=&VB->Clip[vstart][3];			        \
  float *vtex=VB->TexCoord[vstart];			        \
  								\
  /* eax: tmp */			\
  /* ebx: tmp */			\
  /* ecx: GVB */			\
  /* edx: vwin */			\
  SETUP_ASMLOOP("                       \
    movl %0,%%ecx;			\
    movl %2,%%edx;		        \
                                        \
    .align 16;		                \
    ."#label":;");	                \
                                        \
  SETUP_ASM(snap(GVB));			\
  SETUP_ASM(gouraud(GVB));		\
  SETUP_ASM(wdepth(GVB));		\
  SETUP_ASM(zdepth(GVB));		\
  SETUP_ASM(texture(GVB));		\
                                        \
  SETUP_ASMLOOP("                       \
    addl %3,%%ecx;                      \
    addl $12,%%edx;                     \
    cmpl %1,%%ecx;                      \
    jne ."#label";                      \
  ");                                   \
}


#else /******************************************************************/


/************************************************************************/
/********* The generic Version of the asm GrVertex Setup code ***********/
/************************************************************************/

#define NOSNAP(v) { \
  (v)->x = VB->Win[i][0];	         \
  (v)->y = VB->Win[i][1];	         \
}

#define SNAP(v) { \
  /* trunc (x,y) to multiple of 1/16 */		        \
  (v)->x = ((int)(VB->Win[i][0]*16.0f))*(1.0f/16.0f);	\
  (v)->y = ((int)(VB->Win[i][1]*16.0f))*(1.0f/16.0f);	\
}


#define GOURAUD(v) { \
  (v)->r = (float) (VB->Color[i][0]); \
  (v)->g = (float) (VB->Color[i][1]); \
  (v)->b = (float) (VB->Color[i][2]); \
  (v)->a = (float) (VB->Color[i][3]); \
}

#define TEXTURE(v)  { \
  (v)->tmuvtx[0].sow = sscale*VB->TexCoord[i][0]*(v)->oow; \
  (v)->tmuvtx[0].tow = tscale*VB->TexCoord[i][1]*(v)->oow; \
}

#define WBUFFER(v) { (v)->oow = wscale/VB->Clip[i][3]; }

#define ZBUFFER(v) { (v)->ooz = VB->Win[i][2]; }

#define NOP(v) 

#define SETUP(label, snap, gouraud, texture, wdepth, zdepth) { \
  register unsigned int i;					        \
  register struct vertex_buffer *VB = ctx->VB;			        \
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx; 		\
  register GrVertex *GVB = &fxMesa->gwin[vstart];			\
  register float wscale = fxMesa->wscale; 			        \
  register float sscale = fxMesa->ti[fxMesa->currenttex].sscale;	\
  register float tscale = fxMesa->ti[fxMesa->currenttex].tscale;	\
  								        \
  for(i=vstart;i<vend;i++,GVB++) {                              \
    snap(GVB);                                                  \
    gouraud(GVB);                                               \
    wdepth(GVB);                                                \
    zdepth(GVB);                                                \
    texture(GVB);                                               \
  }                                                             \
}


#endif /********************************************************/
#endif


static void setup(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:           Lines need vertex snap ?!?!
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l1, NOSNAP, NOP, NOP, NOP, NOP);
    break;
  default:
    SETUP(l2, SNAP, NOP, NOP, NOP, NOP);
    break;
  }
}
        
static void setupG(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l3, NOSNAP, GOURAUD, NOP, NOP, NOP);
    break;
  default:
    SETUP(l4, SNAP, GOURAUD, NOP, NOP, NOP);
    break;
  }
}

static void setupT(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l5, NOSNAP, NOP, TEXTURE, WBUFFER, NOP);
    break;
  default:
    SETUP(l6, SNAP, NOP, TEXTURE, WBUFFER, NOP);
    break;
  }
}

static void setupGT(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l7, NOSNAP, GOURAUD, TEXTURE, WBUFFER, NOP);
    break;
  default:
    SETUP(l8, SNAP, GOURAUD, TEXTURE, WBUFFER, NOP);
    break;
  }
}
        
static void setupW(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l9, NOSNAP, NOP, NOP, WBUFFER, NOP);
    break;
  default:
    SETUP(l10, SNAP, NOP, NOP, WBUFFER, NOP);
    break;
  }
}
        
static void setupGW(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l11, NOSNAP, GOURAUD, NOP, WBUFFER, NOP);
    break;
  default:
    SETUP(l12, SNAP, GOURAUD, NOP, WBUFFER, NOP);
    break;
  }
}

static void setupZ(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l13, NOSNAP, NOP, NOP, NOP, ZBUFFER);
    break;
  default:
    SETUP(l14, SNAP, NOP, NOP, NOP, ZBUFFER);
    break;
  }
}
        
static void setupGZ(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l15, NOSNAP, GOURAUD, NOP, NOP, ZBUFFER);
    break;
  default:
    SETUP(l16, SNAP, GOURAUD, NOP, NOP, ZBUFFER);
    break;
  }
}

static void setupTZ(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l17, NOSNAP, NOP, TEXTURE, WBUFFER, ZBUFFER);
    break;
  default:
    SETUP(l18, SNAP, NOP, TEXTURE, WBUFFER, ZBUFFER);
    break;
  }
}
        
static void setupGTZ(GLcontext *ctx, GLuint vstart, GLuint vend)
{
  switch (ctx->Primitive) {
  case GL_POINTS:
/*  case GL_LINES:
  case GL_LINE_STRIP:
  case GL_LINE_LOOP:*/
    SETUP(l19, NOSNAP, GOURAUD, TEXTURE, WBUFFER, ZBUFFER);
    break;
  default:
    SETUP(l20, SNAP, GOURAUD, TEXTURE, WBUFFER, ZBUFFER);
    break;
  }
}
        
typedef void (*setup_func)(GLcontext *, GLuint, GLuint);

setup_func fxSetupFuncs[] = {
  setup,
  setupG,
  setupT,
  setupGT,
  setupW,
  setupGW,
  setupT,
  setupGT,
  setupW,
  setupGW,
  setupT,
  setupGT,
  setupW,
  setupGW,
  setupT,
  setupGT,
  setupZ,
  setupGZ,
  setupTZ,
  setupGTZ,
  setupZ,
  setupGZ,
  setupTZ,
  setupGTZ
};

setup_func 
choose_setup_function(GLcontext *ctx)
{
  unsigned int setupIndex = 0;

  if (ctx->Light.ShadeModel == GL_SMOOTH && !ctx->Light.Model.TwoSide)
    setupIndex |= GOURAUD_ENABLED;
  if (ctx->Texture.Enabled)
    setupIndex |= TEXTURE_ENABLED;
  if (ctx->Fog.Enabled)
    setupIndex |= FOG_ENABLED;
  if (ctx->Depth.Test) {
    if((ctx->ProjectionMatrix[15]==0.0f) &&
       (ctx->Viewport.Near==0.0) && (ctx->Viewport.Far==1.0))
      setupIndex |= WBUFFER_ENABLED;
    else
      setupIndex |= ZBUFFER_ENABLED;
  }

  return fxSetupFuncs[setupIndex];
}

#undef GOURAUD
#define GOURAUD(v) { \
  fxMesa->gwin[(v)].r = (float) VB->Color[(v)][0]; \
  fxMesa->gwin[(v)].g = (float) VB->Color[(v)][1]; \
  fxMesa->gwin[(v)].b = (float) VB->Color[(v)][2]; \
  fxMesa->gwin[(v)].a = (float) VB->Color[(v)][3]; \
}

static void 
fxPoint(GLcontext *ctx, GLuint first, GLuint last)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  unsigned int i;

  if(ctx->MonoPixels)
    grConstantColorValue(fxMesa->color);

  for (i = first; i < last ; i++)
    grDrawPoint(&fxMesa->gwin[i]);
}


points_func 
choose_points_function(GLcontext *ctx)
{
  return fxPoint;
}

static void 
fxLineSmooth(GLcontext *ctx, GLuint v1, GLuint v2, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  grDrawLine(&fxMesa->gwin[v1], &fxMesa->gwin[v2]);
}

static void 
fxLineSmoothTwoSide(GLcontext *ctx, GLuint v1, GLuint v2, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  struct vertex_buffer *VB = ctx->VB;
  GOURAUD(v1); 
  GOURAUD(v2); 
  grDrawLine(&fxMesa->gwin[v1], &fxMesa->gwin[v2]);
}

static void 
fxLineFlat(GLcontext *ctx, GLuint v1, GLuint v2, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  GLubyte *Color = ctx->VB->Color[pv];

  grConstantColorValue(FXCOLOR(Color[0], Color[1], Color[2], Color[3]));
  grDrawLine(&fxMesa->gwin[v1], &fxMesa->gwin[v2]);
}

line_func 
choose_line_function(GLcontext *ctx)
{
  if (ctx->Light.ShadeModel == GL_SMOOTH)
    if (ctx->Light.Model.TwoSide)
      return fxLineSmoothTwoSide;
    else
      return fxLineSmooth;
  else
    return fxLineFlat;
}

/************************************************************************/
/*********************** Triangle functions *****************************/
/************************************************************************/

static void 
fxTriangleSmooth(GLcontext *ctx, GLuint v1, GLuint v2, GLuint v3, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  grDrawTriangle(&fxMesa->gwin[v1], &fxMesa->gwin[v2], &fxMesa->gwin[v3]);
}

static void 
fxTriangleSmoothTwoSide(GLcontext *ctx, GLuint v1, GLuint v2, GLuint v3, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  struct vertex_buffer *VB = ctx->VB;
  GOURAUD(v1); 
  GOURAUD(v2); 
  GOURAUD(v3); 
  grDrawTriangle(&fxMesa->gwin[v1], &fxMesa->gwin[v2], &fxMesa->gwin[v3]);
}

static void 
fxTriangleFlat(GLcontext *ctx, GLuint v1, GLuint v2, GLuint v3, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  GLubyte *Color = ctx->VB->Color[pv];
  grConstantColorValue(FXCOLOR(Color[0], Color[1], Color[2], Color[3]));
  grDrawTriangle(&fxMesa->gwin[v1], &fxMesa->gwin[v2], &fxMesa->gwin[v3]);
}

triangle_func 
choose_triangle_function(GLcontext *ctx)
{
  if (ctx->Light.ShadeModel == GL_SMOOTH)
    if (ctx->Light.Model.TwoSide)
      return fxTriangleSmoothTwoSide;
    else
      return fxTriangleSmooth;
  else
    return fxTriangleFlat;
}

/************************************************************************/
/************************* Quads functions ******************************/
/************************************************************************/

static void 
fxQuadSmooth(GLcontext *ctx, GLuint v1, GLuint v2, GLuint v3, GLuint v4, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  GrVertex *grv2,*grv4;
  grv2=&fxMesa->gwin[v2];
  grv4=&fxMesa->gwin[v4];
  grDrawTriangle(&fxMesa->gwin[v1], grv2, grv4);
  grDrawTriangle(grv2, &fxMesa->gwin[v3], grv4);
}

static void 
fxQuadSmoothTwoSide(GLcontext *ctx, GLuint v1, GLuint v2, GLuint v3, GLuint v4, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  struct vertex_buffer *VB = ctx->VB;
  GrVertex *grv2,*grv4;

  GOURAUD(v1); 
  GOURAUD(v2); 
  GOURAUD(v3); 
  GOURAUD(v4); 

  grv2=&fxMesa->gwin[v2];
  grv4=&fxMesa->gwin[v4];

  grDrawTriangle(&fxMesa->gwin[v1], grv2, grv4);
  grDrawTriangle(grv2, &fxMesa->gwin[v3], grv4);
}

static void 
fxQuadFlat(GLcontext *ctx, GLuint v1, GLuint v2, GLuint v3,GLuint v4, GLuint pv)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;
  GLubyte *Color = ctx->VB->Color[pv];
  GrVertex *grv2,*grv4;

  grConstantColorValue(FXCOLOR(Color[0], Color[1], Color[2], Color[3]));

  grv2=&fxMesa->gwin[v2];
  grv4=&fxMesa->gwin[v4];

  grDrawTriangle(&fxMesa->gwin[v1], grv2, grv4);
  grDrawTriangle(grv2, &fxMesa->gwin[v3], grv4);
}

quad_func 
choose_quad_function(GLcontext *ctx)
{
  if(ctx->Light.ShadeModel == GL_SMOOTH)
    if(ctx->Light.Model.TwoSide)
      return fxQuadSmoothTwoSide;
    else
      return fxQuadSmooth;
  else
    return fxQuadFlat;
}

/************************************************************************/
/**************** 3D depth buffer functions *****************************/
/************************************************************************/

/* this is a no-op, since the z-buffer is in hardware */
static void alloc_depth_buffer(GLcontext *ctx)
{
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: alloc_depth_buffer()\n");
#endif
}

static void clear_depth_buffer(GLcontext *ctx)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: clear_depth_buffer()\n");
#endif

  if(ctx->Depth.Test && ctx->Depth.Mask) {
    grDepthMask(FXTRUE);
    grColorMask(FXFALSE,FXFALSE);

    if(fxMesa->wbuffer)
      /* I don't know how to convert ctx->Depth.Clear */
      grBufferClear(fxMesa->clearc,fxMesa->cleara,GR_WDEPTHVALUE_FARTHEST);
    else
      grBufferClear(fxMesa->clearc,fxMesa->cleara,(FxU16)(ctx->Depth.Clear*0xffff));

    grColorMask(FXTRUE,FXFALSE);
  }
}

/************************************************************************/
/*****                Span functions                                *****/
/************************************************************************/

static void write_color_span( GLcontext *ctx, 
                              GLuint n, GLint x, GLint y,
                              const GLubyte red[], const GLubyte green[],
                              const GLubyte blue[], const GLubyte alpha[],
                              const GLubyte mask[] )
{
   fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
   GLubyte data[MAX_WIDTH][4];
   GLint i;
   GLint bottom = fxMesa->height-1;
   for (i=0;i<n;i++) {
      data[i][0] = red[i];
      data[i][1] = green[i];
      data[i][2] = blue[i];
      data[i][3] = alpha[i];
   }
   grLfbWriteColorFormat(GR_COLORFORMAT_ABGR);
   grLfbWriteRegion( GR_BUFFER_FRONTBUFFER, x, bottom-y, GR_LFB_SRC_FMT_8888,
                     n, 1, 0, data );
}


static void read_color_span( GLcontext *ctx, 
                             GLuint n, GLint x, GLint y,
                             GLubyte red[], GLubyte green[],
                             GLubyte blue[], GLubyte alpha[] )
{
   fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
   GLushort data[MAX_WIDTH];
   GLint i;
   GLint bottom = fxMesa->height-1;

   assert(n < MAX_WIDTH);
   grLfbReadRegion( GR_BUFFER_FRONTBUFFER, x, bottom-y, n, 1, 0, data);
   for (i=0;i<n;i++) {
      red[i]   = (data[i] & 0x001f) << 3;
      green[i] = (data[i] & 0x07e0) >> 3;
      blue[i]  = (data[i] & 0xf800) >> 8;
      alpha[i] = 255;
   }
}

/************************************************************************/
/************************************************************************/
/************************************************************************/

static void finish(GLcontext *ctx)
{
  grSstIdle();
}

static void flush(GLcontext *ctx)
{
  grSstIdle();
}

/************************************************************************/
/*************************** Texture Mapping ****************************/
/************************************************************************/

static void texbind(GLcontext *ctx, GLenum target, GLuint texObject)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
  texinfo *ti=fxMesa->ti;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: texbind(%d)\n",texObject);
#endif

  if(texObject>=MAXNUM_TEX) {
    fprintf(stderr,"fx Driver: too many texture objects\n");
    fxCloseHardware();
    exit(-1);
  }

  if(!ti[texObject].valid)
    return;

  if(ti[texObject].fixedpalette)
    grTexDownloadTable(GR_TMU0,GR_TEXTABLE_PALETTE,&ti[texObject].palette); 

  fxMesa->currenttex=texObject;
  grTexClampMode(GR_TMU0,ti[texObject].sclamp,ti[texObject].tclamp);
  grTexFilterMode(GR_TMU0,ti[texObject].minfilt,ti[texObject].maxfilt);
  grTexMipMapMode(GR_TMU0,ti[texObject].mmmode,FXFALSE);
  grTexSource(GR_TMU0,ti[texObject].address,GR_MIPMAPLEVELMASK_BOTH,&ti[texObject].info);
}

static void texenv(GLcontext *ctx, GLenum pname, const GLfloat *param)
{
  /* ;) */
}

static void texparam(GLcontext *ctx, GLenum target, GLuint texObject,
                     GLenum pname, const GLfloat *params)
{
  GLenum param=(GLenum)(GLint)params[0];
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
  texinfo *ti=fxMesa->ti;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: texparam(%d)\n",texObject);
#endif

  if(target!=GL_TEXTURE_2D) {
#ifndef FX_SILENT
    fprintf(stderr,"fx Driver: unsupported texture in texparam()\n");
#endif
    return;
  }

  if(!ti[texObject].valid)
    return;

  switch(pname) {

  case GL_TEXTURE_MIN_FILTER:
    switch(param) {
    case GL_NEAREST:
      ti[texObject].mmmode=GR_MIPMAP_DISABLE;
      ti[texObject].minfilt=GR_TEXTUREFILTER_POINT_SAMPLED;
      break;
    case GL_LINEAR:
      ti[texObject].mmmode=GR_MIPMAP_DISABLE;
      ti[texObject].minfilt=GR_TEXTUREFILTER_BILINEAR;
      break;
    case GL_NEAREST_MIPMAP_NEAREST:
      ti[texObject].mmmode=GR_MIPMAP_NEAREST;
      ti[texObject].minfilt=GR_TEXTUREFILTER_POINT_SAMPLED;
      break;
    case GL_NEAREST_MIPMAP_LINEAR:
      ti[texObject].mmmode=GR_MIPMAP_NEAREST;
      ti[texObject].minfilt=GR_TEXTUREFILTER_BILINEAR;
      break;
    case GL_LINEAR_MIPMAP_LINEAR:
      ti[texObject].mmmode=GR_MIPMAP_NEAREST_DITHER;
      ti[texObject].minfilt=GR_TEXTUREFILTER_BILINEAR;
      break;
    default:
      break;
    }
    break;

  case GL_TEXTURE_MAG_FILTER:
    switch(param) {
    case GL_NEAREST:
      ti[texObject].maxfilt=GR_TEXTUREFILTER_POINT_SAMPLED;
      break;
    case GL_LINEAR:
      ti[texObject].maxfilt=GR_TEXTUREFILTER_BILINEAR;
      break;
    default:
      break;
    }
    break;

  case GL_TEXTURE_WRAP_S:
    switch(param) {
    case GL_CLAMP:
      ti[texObject].sclamp=GR_TEXTURECLAMP_CLAMP;
      break;
    case GL_REPEAT:
      ti[texObject].sclamp=GR_TEXTURECLAMP_WRAP;
      break;
    default:
      break;
    }
    break;

  case GL_TEXTURE_WRAP_T:
    switch(param) {
    case GL_CLAMP:
      ti[texObject].tclamp=GR_TEXTURECLAMP_CLAMP;
      break;
    case GL_REPEAT:
      ti[texObject].tclamp=GR_TEXTURECLAMP_WRAP;
      break;
    default:
      break;
    }
    break;

  case GL_TEXTURE_BORDER_COLOR:
    /* TO DO */
    break;
  default:
    break;
  }

  fxMesa->currenttex=texObject;
  texbind(ctx,target,texObject);
}

static void texdel(GLcontext *ctx, GLuint texObject)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: texdel(%d)\n",texObject);
#endif

  fxMesa->ti[texObject].valid=0;

  /* TO DO: Free the texture memory */
}

static int logbase2(int n)
{
  GLint i = 1;
  GLint log2 = 0;

  if (n<0) {
    return -1;
  }

  while (n > i) {
    i *= 2;
    log2++;
  }
  if (i != n) {
    return -1;
  }
  else {
    return log2;
  }
}

static int texgetinfo(int w, int h, GrLOD_t *lodlevel, GrAspectRatio_t *ar,
                      float *sscale, float *tscale,
                      int *wscale, int *hscale)
{
  static GrLOD_t lod[9]={GR_LOD_256,GR_LOD_128,GR_LOD_64,GR_LOD_32,
                         GR_LOD_16,GR_LOD_8,GR_LOD_4,GR_LOD_2,GR_LOD_1};
  int logw,logh,ws,hs;
  GrLOD_t l;
  GrAspectRatio_t aspectratio;
  float s,t;

  logw=logbase2(w);
  logh=logbase2(h);

  switch(logw-logh) {
  case 0:
    aspectratio=GR_ASPECT_1x1;
    l=lod[8-logw];
    s=t=256;
    ws=hs=1;
    break;
  case 1:
    aspectratio=GR_ASPECT_2x1;
    l=lod[8-logw];
    s=256;
    t=128;
    ws=1;
    hs=1;
    break;
  case 2:
    aspectratio=GR_ASPECT_4x1;
    l=lod[8-logw];
    s=256;
    t=64;
    ws=1;
    hs=1;
    break;
  case 3:
    aspectratio=GR_ASPECT_8x1;
    l=lod[8-logw];
    s=256;
    t=32;
    ws=1;
    hs=1;
    break;
  case 4:
    aspectratio=GR_ASPECT_8x1;
    l=lod[8-logw];
    s=256;
    t=32;
    ws=1;
    hs=2;
    break;
  case 5:
    aspectratio=GR_ASPECT_8x1;
    l=lod[8-logw];
    s=256;
    t=32;
    ws=1;
    hs=4;
    break;
  case 6:
    aspectratio=GR_ASPECT_8x1;
    l=lod[8-logw];
    s=256;
    t=32;
    ws=1;
    hs=8;
    break;
  case 7:
    aspectratio=GR_ASPECT_8x1;
    l=lod[8-logw];
    s=256;
    t=32;
    ws=1;
    hs=16;
    break;
  case 8:
    aspectratio=GR_ASPECT_8x1;
    l=lod[8-logw];
    s=256;
    t=32;
    ws=1;
    hs=32;
    break;
  case -1:
    aspectratio=GR_ASPECT_1x2;
    l=lod[8-logh];
    s=128;
    t=256;
    ws=1;
    hs=1;
    break;
  case -2:
    aspectratio=GR_ASPECT_1x4;
    l=lod[8-logh];
    s=64;
    t=256;
    ws=1;
    hs=1;
    break;
  case -3:
    aspectratio=GR_ASPECT_1x8;
    l=lod[8-logh];
    s=32;
    t=256;
    ws=1;
    hs=1;
    break;
  case -4:
    aspectratio=GR_ASPECT_1x8;
    l=lod[8-logh];
    s=32;
    t=256;
    ws=2;
    hs=1;
    break;
  case -5:
    aspectratio=GR_ASPECT_1x8;
    l=lod[8-logh];
    s=32;
    t=256;
    ws=4;
    hs=1;
    break;
  case -6:
    aspectratio=GR_ASPECT_1x8;
    l=lod[8-logh];
    s=32;
    t=256;
    ws=8;
    hs=1;
    break;
  case -7:
    aspectratio=GR_ASPECT_1x8;
    l=lod[8-logh];
    s=32;
    t=256;
    ws=16;
    hs=1;
    break;
  case -8:
    aspectratio=GR_ASPECT_1x8;
    l=lod[8-logh];
    s=32;
    t=256;
    ws=32;
    hs=1;
    break;
  default:
    return 0;
    break;
  }

  if(lodlevel)
    (*lodlevel)=l;

  if(ar)
    (*ar)=aspectratio;

  if(sscale)
    (*sscale)=s;

  if(tscale)
    (*tscale)=t;

  if(wscale)
    (*wscale)=ws;

  if(hscale)
    (*hscale)=hs;

  return 1;
}

static GrTextureFormat_t texgetformat(GLcontext *ctx, GLenum glformat)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
  GrTextureFormat_t format;

  switch(glformat) {
  case GL_LUMINANCE:
  case GL_LUMINANCE8:
  case 1:
    format=GR_TEXFMT_INTENSITY_8;
    break;
  case GL_LUMINANCE_ALPHA:
  case GL_LUMINANCE8_ALPHA8:
  case 2:
    format=GR_TEXFMT_ALPHA_INTENSITY_88;
    break;
  case GL_ALPHA8:
  case GL_ALPHA:
    format=GR_TEXFMT_ALPHA_8;
    break;
  case GL_RGB:
  case GL_RGB8:
  case 3:
    if(fxMesa->fixedpalette_texture)
      format=GR_TEXFMT_P_8;
    else
      format=GR_TEXFMT_RGB_565;
    break;
  case GL_RGBA:
  case GL_RGBA8:
  case 4:
    format=GR_TEXFMT_ARGB_4444;
    break;
  default:
    fprintf(stderr,"fx Driver: wrong internalFormat in texgetformat()\n");
    fxCloseHardware();
    exit(-1);
    break;
  }

  return format;
}

static void texalloc(GLcontext *ctx, GLuint texObject, GLenum glformat, int w, int h)
{
  GrTextureFormat_t format;
  GrLOD_t l;
  GrAspectRatio_t aspectratio;
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
  texinfo *ti=fxMesa->ti;
  int wscale,hscale,texmemsize;

  texgetinfo(w,h,&l,&aspectratio,&(ti[texObject].sscale),&(ti[texObject].tscale),&wscale,&hscale);

  format=texgetformat(ctx,glformat);

  ti[texObject].info.smallLod=GR_LOD_1;
  ti[texObject].info.largeLod=l;
  ti[texObject].info.aspectRatio=aspectratio;
  ti[texObject].info.format=format;
  ti[texObject].info.data=NULL;

  ti[texObject].address=fxMesa->mintexmem;
  texmemsize=grTexTextureMemRequired(GR_MIPMAPLEVELMASK_BOTH,&ti[texObject].info);

  if(ti[texObject].address+texmemsize>grTexMaxAddress(GR_TMU0)) {
    fprintf(stderr,"fx Driver: out of texture memory !\n");
    fxCloseHardware();
    exit(-1);
  }

  fxMesa->mintexmem+=texmemsize;
        
  ti[texObject].fixedpalette=fxMesa->fixedpalette_texture;

  ti[texObject].info.smallLod=l;

  ti[texObject].minfilt=GR_TEXTUREFILTER_BILINEAR;
  ti[texObject].maxfilt=GR_TEXTUREFILTER_BILINEAR;

  ti[texObject].sclamp=GR_TEXTURECLAMP_WRAP;
  ti[texObject].tclamp=GR_TEXTURECLAMP_WRAP;

  ti[texObject].mmmode=GR_MIPMAP_NEAREST;

  ti[texObject].levelsdefined=0;
}

static int istexsupported(GLenum target, GLint internalFormat,
                          const struct gl_texture_image *image)
{
  if(target!=GL_TEXTURE_2D)
    return GL_FALSE;

  switch(internalFormat) {
  case GL_LUMINANCE:
  case GL_LUMINANCE8:
  case 1:
  case GL_LUMINANCE_ALPHA:
  case GL_LUMINANCE8_ALPHA8:
  case 2:
  case GL_ALPHA8:
  case GL_ALPHA:
  case GL_RGB:
  case GL_RGB8:
  case 3:
  case GL_RGBA:
  case GL_RGBA8:
  case 4:
    break;
  default:
    return GL_FALSE;
  }

  if(image->Width>256)
    return GL_FALSE;

  if(image->Height>256)
    return GL_FALSE;

  if(!texgetinfo(image->Width,image->Height,NULL,NULL,NULL,NULL,NULL,NULL))
    return GL_FALSE;

  return GL_TRUE;
}

static unsigned short *texbuildimagemap(const struct gl_texture_image *image, GLint internalFormat, GuTexPalette *palette, GLint levelsdefined)
{
  unsigned short *src,*srccpy;
  unsigned char r,g,b,a,l,*data,*srcb;
  int x,y,w,h,wscale,hscale,idx;

  texgetinfo(image->Width,image->Height,NULL,NULL,NULL,NULL,&wscale,&hscale);
  w=image->Width*wscale;
  h=image->Height*hscale;

  if(!(srccpy=src=(unsigned short *)malloc(sizeof(unsigned short)*w*h))) {
    fprintf(stderr,"fx Driver: out of memory !\n");
    fxCloseHardware();
    exit(-1);
  }

  data=image->Data;
  switch(internalFormat) {
  case GL_ALPHA:
  case GL_ALPHA8:
  case GL_LUMINANCE:
  case GL_LUMINANCE8:
  case 1:
    srcb=(unsigned char *)src;
    for(y=0;y<h;y++)
      for(x=0;x<w;x++) {
        idx=(x/wscale+(y/hscale)*(w/wscale));
        srcb[x+y*w]=data[idx];
      }
    break;
  case GL_LUMINANCE_ALPHA:
  case GL_LUMINANCE8_ALPHA8:
  case 2:
    for(y=0;y<h;y++)
      for(x=0;x<w;x++) {
        idx=(x/wscale+(y/hscale)*(w/wscale))*2;
        l=data[idx];
        a=data[idx+1];

        src[x+y*w]=(unsigned short)
          (((unsigned short) a) << 8) |
          (((unsigned short) l));
      }
    break;
  case GL_RGB:
  case GL_RGB8:
  case 3:
    if(palette) {
      Gu3dfInfo info;
      int memreq;
      unsigned char *expdata;

      if(!(expdata=malloc(w*h*3))) {
        fprintf(stderr,"fx Driver: out of memory\n");
        grGlideShutdown();
        exit(-1);
      }

      for(y=0;y<h;y++)
        for(x=0;x<w;x++) {
          idx=(x/wscale+(y/hscale)*(w/wscale))*3;
          r=data[idx];
          g=data[idx+1];
          b=data[idx+2];

          expdata[(x+y*w)*3]=r;
          expdata[(x+y*w)*3+1]=g;
          expdata[(x+y*w)*3+2]=b;
        }

      memreq=txInit3dfInfo(&info,GR_TEXFMT_P_8,&w,&h,1,TX_AUTORESIZE_DISABLE);

      if(!(info.data=malloc(memreq))) {
        fprintf(stderr,"fx Driver: out of memory\n");
        grGlideShutdown();
        exit(-1);
      }

      if(!levelsdefined) {
        txConvert(&info,GR_TEXFMT_RGB_888,w,h,expdata,TX_DITHER_ERR,NULL);
        memcpy(palette,&info.table.palette,sizeof(GuTexPalette));
      } else
        txConvert(&info,GR_TEXFMT_RGB_888,w,h,expdata,TX_TARGET_PALNCC_SOURCE|TX_DITHER_ERR,palette);

      memcpy(src,info.data,memreq);

      free(info.data);
      free(expdata);
    } else {
      for(y=0;y<h;y++)
        for(x=0;x<w;x++) {
          idx=(x/wscale+(y/hscale)*(w/wscale))*3;
          r=data[idx];
          g=data[idx+1];
          b=data[idx+2];

          src[x+y*w]=(unsigned short)
            (((unsigned short)0xf8 & r) <<(11-3))  |
            (((unsigned short)0xfc & g) <<(5-3+1)) |
            (((unsigned short)0xf8 & b) >> 3); 
        }
    }
    break;
  case GL_RGBA:
  case GL_RGBA8:
  case 4:
    for(y=0;y<h;y++)
      for(x=0;x<w;x++) {
        idx=(x/wscale+(y/hscale)*(w/wscale))*4;
        r=data[idx];
        g=data[idx+1];
        b=data[idx+2];
        a=data[idx+3];

        src[x+y*w]=(unsigned short)
          (((unsigned short)0xf0 & a) << 8) |
          (((unsigned short)0xf0 & r) << 4) |
          ((unsigned short)0xf0 & g)       |
          (((unsigned short)0xf0 & b) >> 4); 
      }
    break;
  default:
    fprintf(stderr,"fx Driver: wrong internalFormat in texbuildimagemap()\n");
    grGlideShutdown();
    exit(-1);
    break;
  }

  return srccpy;
}

static void teximg(GLcontext *ctx, GLenum target,
                   GLuint texObject, GLint level, GLint internalFormat,
                   const struct gl_texture_image *image)
{
  unsigned short *src,*srccpy;
  GrLOD_t lodlev;
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;
  texinfo *ti=fxMesa->ti;

#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: teximg(...,%d,%d,%d,%d...)\n",target,internalFormat,image->Width,image->Height);
#endif

  if(istexsupported(target,internalFormat,image)) {
    /* The following line isn't really right ... */

    if((!ti[texObject].valid) || (ti[texObject].info.format!=texgetformat(ctx,internalFormat)))
      texalloc(ctx,texObject,image->Format,image->Width,image->Height);

    if(ti[texObject].fixedpalette)
      srccpy=src=texbuildimagemap(image,internalFormat,&ti[texObject].palette,ti[texObject].levelsdefined);
    else
      srccpy=src=texbuildimagemap(image,internalFormat,NULL,0);
                
    texgetinfo(image->Width,image->Height,&lodlev,NULL,NULL,NULL,NULL,NULL);

    if(lodlev>ti[texObject].info.smallLod)
      ti[texObject].info.smallLod=lodlev;

    if(lodlev>=ti[texObject].info.largeLod) {
      grTexDownloadMipMapLevel(GR_TMU0,ti[texObject].address,lodlev,
                               ti[texObject].info.largeLod,ti[texObject].info.aspectRatio,
                               ti[texObject].info.format,GR_MIPMAPLEVELMASK_BOTH,src);

      free(srccpy);

      ti[texObject].levelsdefined|=(1<<level);
      ti[texObject].valid=1;
    }

    fxMesa->currenttex=texObject;
    texbind(ctx,target,texObject);
  }
#ifndef FX_SILENT
  else
    fprintf(stderr,"fx Driver: unsupported texture in teximg()\n");
#endif
}

/************************************************************************/
/************************************************************************/
/************************************************************************/

static void SetNearFar(GLcontext *ctx, GLfloat n, GLfloat f)
{
  fxMesaContext fxMesa = (fxMesaContext)ctx->DriverCtx;

  if(fxMesa) {
    fxMesa->nearval=fabs(n);
    fxMesa->farval=fabs(f);
    fxMesa->wscale=fxMesa->farval/65535.0;

    /*
     * We need to update fog table because it depends on w 
     * and w is adjusted to the maximum range.
     */
    if(ctx->Fog.Enabled && ctx->Hint.Fog==GL_NICEST) {
      switch(ctx->Fog.Mode)     {
      case GL_LINEAR:
        guFogGenerateLinear(fxMesa->fogtable,
                            ctx->Fog.Start/fxMesa->wscale,
                            ctx->Fog.End /fxMesa->wscale); /* works ? */
        break;
      case GL_EXP:
        guFogGenerateExp(fxMesa->fogtable,
                         ctx->Fog.Density*fxMesa->wscale);
        break;
      case GL_EXP2:
        guFogGenerateExp2(fxMesa->fogtable,
                          ctx->Fog.Density*fxMesa->wscale);
        break;
      default: /* That should never happen */
        break; 
      }
    }
  }
}

void fxMesaSetNearFar(GLfloat n, GLfloat f)
{
  if(CurrentfxMesaCtx)
    SetNearFar(CurrentfxMesaCtx->gl_ctx, n, f);
}


static void setup_fx_units(GLcontext *ctx)
{
  fxMesaContext fxMesa=(fxMesaContext)ctx->DriverCtx;

  if(ctx->Color.BlendEnabled) {
    GrAlphaBlendFnc_t sfact,dfact;

    if(ctx->Light.ShadeModel==GL_SMOOTH)
      guAlphaSource(GR_ALPHASOURCE_ITERATED_ALPHA);
    else
      guAlphaSource(GR_ALPHASOURCE_CC_ALPHA);

    switch(ctx->Color.BlendSrc) {
    case GL_ZERO:
      sfact=GR_BLEND_ZERO;
      break;
    case GL_ONE:
      sfact=GR_BLEND_ONE;
      break;
    case GL_DST_COLOR:
      sfact=GR_BLEND_DST_COLOR;
      break;
    case GL_ONE_MINUS_DST_COLOR:
      sfact=GR_BLEND_ONE_MINUS_DST_COLOR;
      break;
    case GL_SRC_ALPHA:
      sfact=GR_BLEND_SRC_ALPHA;
      break;
    case GL_ONE_MINUS_SRC_ALPHA:
      sfact=GR_BLEND_ONE_MINUS_SRC_ALPHA;
      break;
    case GL_SRC_ALPHA_SATURATE:
    case GL_SRC_COLOR:
    case GL_ONE_MINUS_SRC_COLOR:
    case GL_DST_ALPHA:
    case GL_ONE_MINUS_DST_ALPHA:
      /* USELESS or TO DO */
      sfact=GR_BLEND_ONE;
      break;
    default:
      break;
    }

    switch(ctx->Color.BlendDst) {
    case GL_ZERO:
      dfact=GR_BLEND_ZERO;
      break;
    case GL_ONE:
      dfact=GR_BLEND_ONE;
      break;
    case GL_SRC_COLOR:
      dfact=GR_BLEND_SRC_COLOR;
      break;
    case GL_ONE_MINUS_SRC_COLOR:
      dfact=GR_BLEND_ONE_MINUS_SRC_COLOR;
      break;
    case GL_SRC_ALPHA:
      dfact=GR_BLEND_SRC_ALPHA;
      break;
    case GL_ONE_MINUS_SRC_ALPHA:
      dfact=GR_BLEND_ONE_MINUS_SRC_ALPHA;
      break;
    case GL_SRC_ALPHA_SATURATE:
    case GL_DST_COLOR:
    case GL_ONE_MINUS_DST_COLOR:
    case GL_DST_ALPHA:
    case GL_ONE_MINUS_DST_ALPHA:
      /* USELESS or TO DO */
      sfact=GR_BLEND_ZERO;
      break;
    default:
      break;
    }

    grAlphaBlendFunction(sfact,dfact,GR_BLEND_ONE,GR_BLEND_ZERO);

    grColorMask(FXTRUE,FXFALSE);
  } else {
    grAlphaBlendFunction(GR_BLEND_ONE,GR_BLEND_ZERO,GR_BLEND_ONE,GR_BLEND_ZERO);
    grColorMask(FXTRUE,FXFALSE);
  }

  if(ctx->Color.AlphaEnabled) {
    switch(ctx->Color.AlphaFunc) {
    case GL_NEVER:
      grAlphaTestFunction(GR_CMP_NEVER);
      break;
    case GL_LESS:
      grAlphaTestFunction(GR_CMP_LESS);
      break;
    case GL_EQUAL:
      grAlphaTestFunction(GR_CMP_EQUAL);
      break;
    case GL_LEQUAL:
      grAlphaTestFunction(GR_CMP_LEQUAL);
      break;
    case GL_GREATER:
      grAlphaTestFunction(GR_CMP_GREATER);
      break;
    case GL_NOTEQUAL:
      grAlphaTestFunction(GR_CMP_NOTEQUAL);
      break;
    case GL_GEQUAL:
      grAlphaTestFunction(GR_CMP_GEQUAL);
      break;
    case GL_ALWAYS:
      grAlphaTestFunction(GR_CMP_ALWAYS);
      break;
    default:
      break;
    }
    grAlphaTestReferenceValue(ctx->Color.AlphaRefUbyte);
  } else
    grAlphaTestFunction(GR_CMP_ALWAYS);

  if(ctx->Texture.Enabled) {
    switch(ctx->Texture.EnvMode) {
    case GL_DECAL:
      guColorCombineFunction(GR_COLORCOMBINE_DECAL_TEXTURE);
      guTexCombineFunction(GR_TMU0,GR_TEXTURECOMBINE_DECAL);
      break;
    case GL_MODULATE:
      if(ctx->Color.BlendEnabled || ctx->Color.AlphaEnabled)
        guAlphaSource(GR_ALPHASOURCE_TEXTURE_ALPHA);

      if(ctx->Light.ShadeModel==GL_SMOOTH)
        guColorCombineFunction(GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB);
      else
        guColorCombineFunction(GR_COLORCOMBINE_TEXTURE_TIMES_CCRGB);

      guTexCombineFunction(GR_TMU0,GR_TEXTURECOMBINE_DECAL);
      break;
    case GL_BLEND:
#ifndef FX_SILENT
      fprintf(stderr,"fx Driver: GL_BLEND not yet supported\n");
#endif
      /* TO DO */
      break;
    case GL_REPLACE:
      if(ctx->Color.BlendEnabled || ctx->Color.AlphaEnabled)
        guAlphaSource(GR_ALPHASOURCE_TEXTURE_ALPHA);

      guColorCombineFunction(GR_COLORCOMBINE_DECAL_TEXTURE);
      guTexCombineFunction(GR_TMU0,GR_TEXTURECOMBINE_DECAL);
      break;
    default:
#ifndef FX_SILENT
      fprintf(stderr,"fx Driver: %x Texture.EnvMode not yet supported\n",ctx->Texture.EnvMode);
#endif
      break;
    }
  } else {
    if(ctx->Light.ShadeModel==GL_SMOOTH)
      guColorCombineFunction(GR_COLORCOMBINE_ITRGB);
    else
      guColorCombineFunction(GR_COLORCOMBINE_CCRGB);
      
    grTexCombineFunction(GR_TMU0,GR_TEXTURECOMBINE_ZERO);
  }

  if(ctx->Depth.Test) {
    if((ctx->ProjectionMatrix[15]==0.0f) &&
       (ctx->Viewport.Near==0.0) && (ctx->Viewport.Far==1.0)) {
      grDepthBufferMode(GR_DEPTHBUFFER_WBUFFER);
      fxMesa->wbuffer=1;
    } else {
      grDepthBufferMode(GR_DEPTHBUFFER_ZBUFFER); 
      fxMesa->wbuffer=0;
    }

    switch(ctx->Depth.Func) {
    case GL_NEVER:
      grDepthBufferFunction(GR_CMP_NEVER);
      break;
    case GL_LESS:
      grDepthBufferFunction(GR_CMP_LESS);
      break;
    case GL_GEQUAL:
      grDepthBufferFunction(GR_CMP_GEQUAL);
      break;
    case GL_LEQUAL:
      grDepthBufferFunction(GR_CMP_LEQUAL);
      break;
    case GL_GREATER:
      grDepthBufferFunction(GR_CMP_GREATER);
      break;
    case GL_NOTEQUAL:
      grDepthBufferFunction(GR_CMP_NOTEQUAL);
      break;
    case GL_EQUAL:
      grDepthBufferFunction(GR_CMP_EQUAL);
      break;
    case GL_ALWAYS:
      grDepthBufferFunction(GR_CMP_ALWAYS);
      break;
    default:
      break;
    }

    if(ctx->Depth.Mask)
      grDepthMask(FXTRUE);
    else
      grDepthMask(FXFALSE);
  } else {
    grDepthBufferFunction(GR_CMP_ALWAYS);
    grDepthMask(FXFALSE);
  }

  if(ctx->Fog.Enabled && ctx->Hint.Fog==GL_NICEST) {
    grFogMode(GR_FOG_WITH_TABLE);
    grFogColorValue FXCOLOR((unsigned int)(255*ctx->Fog.Color[0]), 
                            (unsigned int)(255*ctx->Fog.Color[1]),
                            (unsigned int)(255*ctx->Fog.Color[2]), 
                            (unsigned int)(255*ctx->Fog.Color[3]));

    if((fxMesa->fogtablemode!=ctx->Fog.Mode) ||
       (fxMesa->fogdensity!=ctx->Fog.Density)) {
      float wscale = ((fxMesaContext)ctx->DriverCtx)->wscale;
      switch(ctx->Fog.Mode)     {
      case GL_LINEAR:
        guFogGenerateLinear(fxMesa->fogtable,
                            ctx->Fog.Start/wscale,
                            ctx->Fog.End/wscale);
        break;
      case GL_EXP:
        guFogGenerateExp(fxMesa->fogtable,ctx->Fog.Density*wscale);
        break;
      case GL_EXP2:
        guFogGenerateExp2(fxMesa->fogtable,ctx->Fog.Density*wscale);
        break;
      default: /* That should never happen */
        break; 
      }
         
      fxMesa->fogtablemode=ctx->Fog.Mode;
      fxMesa->fogdensity=ctx->Fog.Density;
    }
      
    grFogTable(fxMesa->fogtable);
  } else
    grFogMode(GR_FOG_DISABLE);
}


static const char *renderer_string(void)
{
  return "Glide";
}


static void setup_dd_pointers(GLcontext *ctx)
{
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: fx_mesa_setup_dd_pointers()\n");
#endif

  ctx->Driver.UpdateState=setup_dd_pointers;
         
  ctx->Driver.RendererString=renderer_string;

  ctx->Driver.NearFar=SetNearFar;

  ctx->Driver.ClearIndex=NULL;
  ctx->Driver.ClearColor=clear_color;
  ctx->Driver.Clear=clear;

  ctx->Driver.Index=NULL;
  ctx->Driver.Color=set_color;

  ctx->Driver.SetBuffer=set_buffer;
  ctx->Driver.GetBufferSize=buffer_size;

  ctx->Driver.AllocDepthBuffer=alloc_depth_buffer;
  ctx->Driver.ClearDepthBuffer=clear_depth_buffer;

  /* acc. functions*/

  setup_fx_units(ctx);

  ctx->Driver.PointsFunc=choose_points_function(ctx);
  ctx->Driver.LineFunc=choose_line_function(ctx);
  ctx->Driver.TriangleFunc=choose_triangle_function(ctx);
  ctx->Driver.QuadFunc=choose_quad_function(ctx);
  ctx->Driver.RectFunc=NULL;

  ctx->Driver.Bitmap=drawbitmap;
  ctx->Driver.DrawPixels=NULL;

  ctx->Driver.RasterSetup=choose_setup_function(ctx);
  ctx->Driver.RenderVB=NULL;

  ctx->Driver.Finish=flush;
  ctx->Driver.Flush=finish;

  ctx->Driver.TexEnv=texenv;
  ctx->Driver.TexImage=teximg;
  ctx->Driver.TexParameter=texparam;
  ctx->Driver.BindTexture=texbind;
  ctx->Driver.DeleteTexture=texdel;

  ctx->Driver.WriteColorSpan      =write_color_span;
  ctx->Driver.WriteMonocolorSpan  =NULL;
  ctx->Driver.WriteColorPixels    =NULL;
  ctx->Driver.WriteMonocolorPixels=NULL;
  ctx->Driver.WriteIndexSpan      =NULL;
  ctx->Driver.WriteMonoindexSpan  =NULL;
  ctx->Driver.WriteIndexPixels    =NULL;
  ctx->Driver.WriteMonoindexPixels=NULL;

  ctx->Driver.ReadIndexSpan=NULL;
  ctx->Driver.ReadColorSpan=read_color_span;
  ctx->Driver.ReadIndexPixels=NULL;
  ctx->Driver.ReadColorPixels=NULL;
}


#define NUM_RESOLUTIONS 3

static resolutions[NUM_RESOLUTIONS][3]={ 
  /*    { 320, 200, GR_RESOLUTION_320x200 },*
        { 320, 240, GR_RESOLUTION_320x240 },
        { 400, 256, GR_RESOLUTION_400x256 },
        { 512, 256, GR_RESOLUTION_512x256 },*/
  { 512, 384, GR_RESOLUTION_512x384 },
  /*    { 640, 200, GR_RESOLUTION_640x200 },
        { 640, 350, GR_RESOLUTION_640x350 },*/
  { 640, 400, GR_RESOLUTION_640x400 },
  { 640, 480, GR_RESOLUTION_640x480 } /*,
                                        { 800, 600, GR_RESOLUTION_800x600 },
                                        { 856, 480, GR_RESOLUTION_856x480 },
                                        { 960, 720, GR_RESOLUTION_960x720 }*/ };

GrScreenResolution_t bestResolution(int width, int height)
{
  int i;

  for(i=0;i<NUM_RESOLUTIONS;i++)
    if((width<=resolutions[i][0]) && (height<=resolutions[i][1]))
      return resolutions[i][2];
        
  return GR_RESOLUTION_640x480;
}


fxMesaContext fxMesaCreateBestContext(GLuint win,GLint width, GLint height,
                                      const GLint attribList[])
{
  return fxMesaCreateContext(win, bestResolution(width,height),
                             GR_REFRESH_75Hz, attribList);
}

/*
 * Create a new FX/Mesa context and return a handle to it.
 */
fxMesaContext fxMesaCreateContext(GLuint win,GrScreenResolution_t res,
                                  GrScreenRefresh_t ref,
                                  const GLint attribList[])
{
  fxMesaContext ctx;
  int i,type;
  GLboolean doubleBuffer=GL_FALSE;
  GLboolean alphaBuffer=GL_FALSE;
  GLint depthSize=0;
  GLint stencilSize=0;
  GLint accumSize=0;

  i=0;
  while (attribList[i]!=FXMESA_NONE) {
    switch (attribList[i]) {
    case FXMESA_DOUBLEBUFFER:
      doubleBuffer = GL_TRUE;
      break;
    case FXMESA_ALPHA_SIZE:
      i++;
      alphaBuffer = attribList[i] > 0;
      break;
    case FXMESA_DEPTH_SIZE:
      i++;
      depthSize = attribList[i];
      break;
    case FXMESA_STENCIL_SIZE:
      i++;
      stencilSize = attribList[i];
      break;
    case FXMESA_ACCUM_SIZE:
      i++;
      accumSize = attribList[i];
      break;
    default:
      return NULL;
    }
    i++;
  }


#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: fxMesaCreateContext()\n");
#endif

#ifndef FX_SILENT
  fprintf(stderr,"Mesa fx Voodoo Device Driver v0.18\nWritten by David Bucciarelli (tech.hmw@plus.it)\n");
#endif

  if((type=fxQueryHardware()) >= 0) {
    if(type==GR_SSTTYPE_VOODOO)
      win=0;

#if USE_GLIDE_FULLSCREEN
    if(!grSstOpen(res,                  /* resolution */
                  ref,                  /* refresh */
                  GR_COLORFORMAT_ABGR,  /* pixel format */
                  GR_ORIGIN_LOWER_LEFT, /* origin */
                  GR_SMOOTHING_ENABLE,  /* smoothing mode */
                  2))                   /* num buffers */
      return NULL;
#else   /* Glide in a window */
    if(!grSstWinOpen((FxU32)win,res,ref,
                     GR_COLORFORMAT_ABGR,GR_ORIGIN_LOWER_LEFT,2,1))
      return NULL;
#endif

#ifndef FX_SILENT
    fprintf(stderr,"Glide screen size: %dx%d\n",
	    (int)grSstScreenWidth(),(int)grSstScreenHeight());
#endif
  } else {
    fprintf(stderr,"ERROR: no Voodoo Graphics or Voodoo Rush !\n");
    return NULL;
  }

  ctx=(fxMesaContext)malloc(sizeof(struct fx_mesa_context));
  if(!ctx)
    return NULL;

  ctx->width=grSstScreenWidth();
  ctx->height=grSstScreenHeight();
  ctx->double_buffer = doubleBuffer;
  ctx->fixedpalette_texture=0;
  ctx->color=FXCOLOR(255,255,255,255);
  ctx->clearc=0;
  ctx->cleara=0;
  ctx->mintexmem=grTexMinAddress(GR_TMU0);
  ctx->currenttex=0;
  ctx->currentfb=GR_BUFFER_BACKBUFFER;

  grColorMask(FXTRUE,FXFALSE);
  if (doubleBuffer)
    grRenderBuffer(GR_BUFFER_BACKBUFFER);
  else
    grRenderBuffer(GR_BUFFER_FRONTBUFFER);


  for(i=0;i<MAXNUM_TEX;i++)
    ctx->ti[i].valid=0;

  ctx->gl_vis = gl_create_visual(GL_TRUE,     /* RGB mode */
                                 alphaBuffer,
                                 doubleBuffer,
                                 depthSize,   /* depth_size */
                                 stencilSize, /* stencil_size */
                                 accumSize,   /* accum_size */
                                 0,           /* index bits */
                                 255.0,       /* color scales */
                                 255.0,
                                 255.0,
                                 255.0,
                                 8, 8, 8, 0);

  ctx->gl_ctx = gl_create_context(ctx->gl_vis,
                                  NULL,  /* share list context */
                                  (void *) ctx);

  ctx->gl_buffer = gl_create_framebuffer(ctx->gl_vis);

  setup_dd_pointers(ctx->gl_ctx);

  SetNearFar(ctx->gl_ctx,1.0,100.0);

  return ctx;
}


/*
 * Destroy the given FX/Mesa context.
 */
void fxMesaDestroyContext(fxMesaContext ctx)
{
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: fxMesaDestroyContext()\n");
#endif

  if(ctx) {
    gl_destroy_visual(ctx->gl_vis);
    gl_destroy_context(ctx->gl_ctx);
    gl_destroy_framebuffer(ctx->gl_buffer);

#ifndef FX_SILENT
    fprintf(stderr,"Free texture memory: %u bytes\n",
	    (unsigned)(grTexMaxAddress(GR_TMU0)-ctx->mintexmem));
#endif

    fxCloseHardware();

    free(ctx);
  }

  if(ctx==CurrentfxMesaCtx)
    CurrentfxMesaCtx=NULL;
}

/*
 * Make the specified FX/Mesa context the current one.
 */
void fxMesaMakeCurrent(fxMesaContext ctx)
{
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: fxMesaMakeCurrent()\n");
#endif

  if(!ctx) {
    gl_make_current(NULL,NULL);
    CurrentfxMesaCtx=NULL;

    return;
  }

  CurrentfxMesaCtx=ctx;

  gl_make_current(ctx->gl_ctx,ctx->gl_buffer);

  setup_dd_pointers(ctx->gl_ctx);


  /* The first time we call MakeCurrent we set the initial viewport size */
  if (ctx->gl_ctx->Viewport.Width==0)
    gl_Viewport(ctx->gl_ctx,0,0,ctx->width,ctx->height);
}


/*
 * Swap front/back buffers for current context if double buffered.
 */
void fxMesaSwapBuffers(void)
{
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: fxMesaSwapBuffers()\n");
#endif

  if(CurrentfxMesaCtx)
    if(CurrentfxMesaCtx->double_buffer)
      grBufferSwap(1);
}


/*
 * Activate/Deactivate Texture Palette
 */
void fxMesaTextureUsePalette(GLboolean v)
{
#if defined(DEBUG_FXMESA)
  fprintf(stderr,"fxmesa: fxMesaTextureUsePalette()\n");
#endif

  if(CurrentfxMesaCtx)
    CurrentfxMesaCtx->fixedpalette_texture=v;
}


#if defined(__WIN32__)
static int cleangraphics(void)
{
  fxMesaDestroyContext(CurrentfxMesaCtx);

  return 0;
}
#elif defined(__linux__)
static void cleangraphics(void)
{
  fxMesaDestroyContext(CurrentfxMesaCtx);
}
#endif


/*
 * Query 3Dfx hardware presence/kind
 */
int fxQueryHardware(void)
{
  if(!glideInitialized)
    {
      grGlideInit();
      if(grSstQueryHardware(&hwconfig))
	{
#ifndef FX_SILENT
	  char		buf[80];
			
	  grGlideGetVersion(buf);
#endif
	  grSstSelect(0);
	  _3dfxPresent = 1;
#ifndef FX_SILENT
	  fprintf(stderr,"Using Glide V%s\nNumber of boards: %d\n",buf,hwconfig.num_sst);
#endif
	} else
	  _3dfxPresent = 0;

      glideInitialized = 1;

#if defined(__WIN32__)
      onexit((_onexit_t)cleangraphics);
#elif defined(__linux__)
      atexit(cleangraphics);
#endif
    }

  if(!_3dfxPresent)
    return(-1);
  else
    return(hwconfig.SSTs[0].type);
}


/*
 * Shutdown Glide library
 */
int fxCloseHardware(void)
{
  if(glideInitialized)
    {
#ifndef FX_SILENT
      GrSstPerfStats_t		st;

      grSstPerfStats(&st);
      fprintf(stderr,"# pixels processed (minus buffer clears): %u\n",(unsigned)st.pixelsIn);
      fprintf(stderr,"# pixels not drawn due to chroma key test failure: %u\n",(unsigned)st.chromaFail);
      fprintf(stderr,"# pixels not drawn due to depth test failure: %u\n",(unsigned)st.zFuncFail);
      fprintf(stderr,"# pixels not drawn due to alpha test failure: %u\n",(unsigned)st.aFuncFail);
      fprintf(stderr,"# pixels drawn (including buffer clears and LFB writes): %u\n",(unsigned)st.pixelsOut);
#endif

      grGlideShutdown();
      glideInitialized = 0;
    }

  return 0;
}


#else


/*
 * Need this to provide at least one external definition.
 */

int gl_fx_dummy_function(void)
{
  return 0;
}

#endif  /* FX */
