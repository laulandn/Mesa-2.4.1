
/* This is a tiny fake implementation AGL, attempting to be compatible with Apple's */
/* It uses either Mesa or TinyGL's offscreen rendering */

#include <stdio.h>
#include <stdlib.h>

// NOTE: You can, and should, use a real Apple agl.h
#include <GL/agl.h>


// Define SDL_MACOSCLASSIC_TINYGL to use TinyGL, otherwise we will assume Mesa


#ifdef SDL_MACOSCLASSIC_TINYGL
#include "GL/ostinygl.h"
#else
#include <GL/osmesa.h>
#endif


typedef struct __AGLPixelFormatRec
{
  int fake;
} __AGLPixelFormatRec;

#ifdef SDL_MACOSCLASSIC_TINYGL
typedef ostgl_context_t * OSGLContext;
#else
typedef OSMesaContext OSGLContext;
#endif

typedef struct __AGLContextRec
{
  int fake;
} __AGLContextRec;


struct __AGLPixelFormatRec aglThePixelFormat;
AGLPixelFormat aglThePixelFormatPtr=(AGLPixelFormat)&aglThePixelFormat;

char *osBuffer=NULL;
OSGLContext osContext=NULL;
int aglTheError=0;

// NOTE: TinyGL doesn't seem to like 32 bit pixels...
int aglTheScreenDepth=16;  // TODO: This should be current depth
int aglWinSizeX=640,aglWinSizeY=480;  // TODO: This should be current size


#ifndef USING_SDL1
#ifndef USING_SDL2
void *theOnlyLonelyWindow=NULL;
#endif
#endif


GLenum aglGetError()
{
  return aglTheError;
}


struct __GLpixelfmtRec *aglChoosePixelFormat(struct __AGLDevice * const *gdevs, GLint ndev, GLint *v)
{
  fprintf(stderr,"fake aglChoosePixelFormat!\n"); fflush(stderr);
  return (struct __AGLPixelFormatRec *)aglThePixelFormatPtr;
}


void aglDestroyPixelFormat(AGLPixelFormat pix)
{
  // We ignore...we only support a single static pixel format...
}


GLboolean aglSetDrawable(AGLContext ctx, AGLDrawable draw)
{
  // If using SDL we ignore...we either already have SDL's drawable, or none...
#ifndef USING_SDL2
#ifndef USING_SDL2
  if(!draw) {
    fprintf(stderr,"draw was NULL!\n"); fflush(stderr); return false;
  }
  theOnlyLonelyWindow=(void *)draw;
  fprintf(stderr,"FYI theOnlyLonelyWindow is now %x\n",theOnlyLonelyWindow); fflush(stderr);
#endif
#endif
  return true;
}


GLboolean aglSetCurrentContext(AGLContext ctx)
{
  // We ignore...we only support a single static context...
  return true;
}


GLboolean aglDestroyContext(AGLContext ctx)
{
#ifdef SDL_MACOSCLASSIC_TINYGL
  ostgl_delete_context((ostgl_context_t *)ctx);
#else
  // TODO: Destroy mesa os context here
#endif
  return true;
}


AGLContext aglGetCurrentContext(void)
{
  // We ignore...we only support a single static context...
  return NULL;
}


GLboolean aglUpdateContext(AGLContext ctx)
{
  // We ignore...we only support a single static context...
  // ...but maybe we should do something here if win size changed?
  return true;
}


GLboolean aglSetInteger(AGLContext ctx, GLenum pname,const GLint *params)
{
  fprintf(stderr,"fake aglSetInteger %d to %d!\n",pname,*params); fflush(stderr);
  return true;
}


const GLubyte * aglErrorString(GLenum code)
{
  if(aglTheError==1) return (GLubyte *)"Problem getting something!";
  else return (GLubyte *)"Who knows";
}


// TODO: This should be moved to and used from static pixel format
GLboolean aglDescribePixelFormat(struct __GLpixelfmtRec *fmt,GLint what,GLint *value)
{
  switch(what) {
    case AGL_RGBA:
      *value=1;
      return true;
      break;
    case AGL_ACCELERATED:
      *value=true;
      return true;
      break;
    case AGL_RENDERER_ID:
      *value=1;
      return true;
      break;
    case AGL_DEPTH_SIZE:
      *value=20;
      return true;
      break;
    case AGL_STENCIL_SIZE:
      *value=20;
      return true;
      break;
    case AGL_DOUBLEBUFFER:
      *value=true;
      return true;
      break;
    case AGL_PIXEL_SIZE:
      *value=aglTheScreenDepth;
      return true;
      break;
    default:
      fprintf(stderr,"aglDescribePixelFormat...what=%d implemented\n",what); fflush(stderr);
      return false;
      break;
  }
  return false;
}


AGLRendererInfo aglQueryRendererInfo(const AGLDevice *gdevs, GLint ndev)
{
  fprintf(stderr,"aglQueryRendererInfo...not implemented\n"); fflush(stderr);
  return (AGLRendererInfo)NULL;
}


void aglDestroyRendererInfo(AGLRendererInfo rend)
{
  fprintf(stderr,"aglDestroyRendererInfo...not implemented\n"); fflush(stderr);
}


AGLRendererInfo aglNextRendererInfo(AGLRendererInfo rend)
{
  fprintf(stderr,"aglNextRendererInfo...not implemented\n"); fflush(stderr);
  return (AGLRendererInfo)NULL;
}


GLboolean aglDescribeRenderer(AGLRendererInfo rend, GLint prop, GLint *value)
{
  fprintf(stderr,"aglDescribeRenderer...not implemented\n"); fflush(stderr);
  return false;
}


GLboolean aglConfigure(GLint whats, GLint value)
{
  fprintf(stderr,"aglConfigure %d...not implemented\n",whats); fflush(stderr);
  return false;
}


GLboolean aglDisable(AGLContext ctx, GLenum pname)
{
  fprintf(stderr,"aglDisable %d...not implemented\n",pname); fflush(stderr);
  return true;
}


GLboolean aglSetOffScreen(AGLContext ctx, int w, int h, int rowbytes, void *baseaddr)
{
  fprintf(stderr,"aglSetOffScreen %d x %d rowbytes=%d...not implemented\n",w,h,rowbytes); fflush(stderr);
  //return __aglMakeCurrent(ctx->drawable,ctx);
  return true;
}


GLboolean aglSetFullScreen(AGLContext ctx, int w, int h, int freq, int dev)
{
  fprintf(stderr,"aglSetFullScreen %d x %d and %d and %d...not implemented\n",w,h,freq,dev); fflush(stderr);
  //return __aglMakeCurrent(ctx->drawable,ctx);
  return true;
}
