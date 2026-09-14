
/* This is a tiny fake implementation AGL, attempting to be compatible with Apple's */
/* It uses either Mesa or TinyGL's offscreen rendering */

#include <stdio.h>
#include <stdlib.h>

// NOTE: You can, and should, use a real Apple agl.h
#include <GL/agl.h>


// This should be kept in sync with macosgl.c in SDL2 as much as possible...


// Define SDL_MACOSCLASSIC_TINYGL to use TinyGL, otherwise we will assume Mesa

// Define USING_SDL2 to use SDL2, USING_SDL1 for SDL1, neither for no SDL

// NOTE: If you don't define either, there will be no display!


#ifdef USING_SDL2
#include <SDL2/SDL.h>
#endif
#ifdef USING_SDL1
#include <SDL/SDL.h>
#endif


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


extern char *osBuffer;
extern OSGLContext osContext;
extern int aglTheError;

// These may or may not match actual screen...
extern int aglTheScreenDepth;
extern int aglWinSizeX,aglWinSizeY;


#ifdef USING_SDL2
static SDL_Texture *texture = NULL;
static SDL_Renderer *renderer = NULL;
#endif

// This is needed, so we'll have to get it somehow...
#ifdef USING_SDL2
extern SDL_Window *theOnlyLonelyWindow;
#endif


AGLContext aglCreateContext(AGLPixelFormat pix, AGLContext share)
{
    fprintf(stderr,"aglCreateContext....\n"); fflush(stderr);
#ifdef SDL_MACOSCLASSIC_TINYGL
    fprintf(stderr,"Using TingGL....\n"); fflush(stderr);
#else
    fprintf(stderr,"Using Mesa....\n"); fflush(stderr);
#endif
#ifdef USING_SDL1
    fprintf(stderr,"Using SDL1....\n"); fflush(stderr);
#endif
#ifdef USING_SDL2
    fprintf(stderr,"Using SDL2....\n"); fflush(stderr);
#endif
    fprintf(stderr,"aglTheScreenDepth is %d\n",aglTheScreenDepth); fflush(stderr);
    //int winSizeX,winSizeY;
    //SDL_GetWindowSize(theOnlyLonelyWindow,&winSizeX,&winSizeY);
#ifdef USING_SDL2
    if(!theOnlyLonelyWindow) {
      fprintf(stderr,"theOnlyLonelyWindow failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }  
    SDL_GetWindowSize(theOnlyLonelyWindow,&aglWinSizeX,&aglWinSizeY);
#endif
#ifdef SDL_MACOSCLASSIC_TINYGL
    int tDepth=aglTheScreenDepth;
    if(aglTheScreenDepth==32) {
      // NOTE: This doesn't work in aglSwapBuffers...can't fool SDL...
      fprintf(stderr,"NOTE: Requested 32 bit, switching to 16!\n"); fflush(stderr);
      tDepth=16;
    }
  	osContext = ostgl_create_context(aglWinSizeX,aglWinSizeY,tDepth);
	  ostgl_make_current(osContext);
	  osBuffer=osContext->pixels;
#else
    int format=OSMESA_BGR;
    if(aglTheScreenDepth==32) format=OSMESA_ARGB;  // Not sure this is right...
    int factor=2;
    if(aglTheScreenDepth==32) factor=4;
    //fprintf(stderr,"aglTheScreenDepth is %d\n",aglTheScreenDepth); fflush(stderr);
    // TODO: The context is obviously not QUITE right...
  	osContext=OSMesaCreateContext(format,NULL);
  	osBuffer=(char *)malloc(aglWinSizeX*aglWinSizeY*factor);
    if(!osBuffer) {
      fprintf(stderr,"osBuffer failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got osBuffer\n"); fflush(stderr); } 
    GLboolean res=OSMesaMakeCurrent((OSMesaContext)osContext,osBuffer,GL_UNSIGNED_BYTE,aglWinSizeX,aglWinSizeY);
    if(!res) {
      fprintf(stderr,"OSMesaMakeCurrent failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got OSMesaMakeCurrent\n"); fflush(stderr); } 
    OSMesaPixelStore(OSMESA_Y_UP, 0);
glDisable(GL_DEPTH_TEST);
glDisable(GL_DITHER);
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
glDisable(GL_TEXTURE_2D);
glDisable(GL_TEXTURE_1D);
OSMesaPixelStore(OSMESA_ROW_LENGTH, aglWinSizeX);
glShadeModel(GL_FLAT);
#endif
    if(!osContext) {
      fprintf(stderr,"osContext failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }
    else { fprintf(stderr,"got osContext\n"); fflush(stderr); } 
#ifdef USING_SDL2
    renderer = SDL_CreateRenderer(theOnlyLonelyWindow, -1, SDL_RENDERER_PRESENTVSYNC);	
    if(!renderer) {
      fprintf(stderr,"SDL_CreateRenderer failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got renderer\n"); fflush(stderr); } 
    texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(theOnlyLonelyWindow), SDL_TEXTUREACCESS_STREAMING, aglWinSizeX,aglWinSizeY);
    if(!texture) {
      fprintf(stderr,"SDL_CreateTexture failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got texture\n"); fflush(stderr); }
#endif
    fprintf(stderr,"aglCreateContext done\n"); fflush(stderr);
    return (AGLContext)osContext;
}


GLboolean aglSwapBuffers(struct __AGLContextRec *ctx)
{
#ifdef USING_SDL2
    SDL_Surface *src=NULL;
    SDL_Surface *dst=NULL;
    int tFormat=SDL_PIXELFORMAT_RGB565;
    if(aglTheScreenDepth==32) tFormat=SDL_PIXELFORMAT_ARGB8888;
    //SDL_GetWindowSize(theOnlyLonelyWindow,&aglWinSizeX,&aglWinSizeY);
    //fprintf(stderr,"aglSwapBuffers FYI window is %d by %d\n",aglWinSizeX,aglWinSizeY);
#endif
    int winSizeX=640,winSizeY=480;  // probably not needed...
    int tDepth=aglTheScreenDepth;
#ifdef SDL_MACOSCLASSIC_TINYGL
    // Note: If doesn't match actual win size, we're wrong for win, right for buffer...
    aglWinSizeX=((ostgl_context_t *)ctx)->width;  // probably not needed...
    aglWinSizeY=((ostgl_context_t *)ctx)->height;  // probably not needed...
    // Same here...
    aglTheScreenDepth=((ostgl_context_t *)ctx)->depth;  // probably not needed...
    if(((ostgl_context_t *)ctx)->depth!=aglTheScreenDepth) {
      fprintf(stderr,"ostgl_context_t depth mismatch!\n"); fflush(stderr);
    }
#else
    // Mesa only?
    //SDL_GetWindowSize(theOnlyLonelyWindow,&winSizeX,&winSizeY);
#endif
#ifdef USING_SDL2
    // Would error checking here slow things down?
  	src = SDL_CreateRGBSurfaceWithFormatFrom(osBuffer, aglWinSizeX, aglWinSizeY, aglTheScreenDepth, (aglWinSizeX * aglTheScreenDepth / 8), tFormat);
  	dst = SDL_CreateRGBSurfaceWithFormatFrom(NULL, aglWinSizeX, aglWinSizeY, 0, 0, SDL_GetWindowPixelFormat(theOnlyLonelyWindow));
  	if (SDL_LockTexture(texture, NULL, &dst->pixels, &dst->pitch) == 0)
  	{
   		if (SDL_BlitSurface(src, NULL, dst, NULL) != 0)
  		{ SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "surface blit failed: %s", SDL_GetError()); }
	  	SDL_UnlockTexture(texture);
	  }
  	else
	  { SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "texture lock failed: %s", SDL_GetError()); }
	  if(dst) SDL_FreeSurface(dst);
	  if(src) SDL_FreeSurface(src);
	  SDL_RenderClear(renderer);
	  SDL_RenderCopy(renderer, texture, NULL, NULL);
	  SDL_RenderPresent(renderer);
#endif
    return true;
}

