/* These are functions that were new for later versions of AGL */
/* this is a massive hack */

#include <stdio.h>

#include <agl.h>

#include "aglPixelFormat.h"
#include "aglPixelFormat.h"
#include "aglContext.h"


/*
typedef struct AGLPixelFormat
{
} AGLPixelFormat;
*/


extern AGLPixelFmt DDChoosePixelFmt(TAGLPixelFmtReq *req);
extern void AGLSetAGLError(void *a,int b,char *c);
extern GLboolean __aglMakeCurrent(AGLDrawable drawable, AGLContext ctx);

extern void glGetIntegerv_old( GLenum pname, GLint *params );
const GLubyte * glGetString_old( GLenum name );


#define AGLPixelFormat int
#define AGLDevice int


AGLContext myContext=NULL;
int pixelSizeTheyAskedFor=16;
int depthSizeTheyAskedFor=16;
int stencilSizeTheyAskedFor=16;  /* Is this sane? */
int swapIntervalTheyAskedFor=16;  /* Is this sane? */


AGLPixelFmt __aglChoosePixelFmt2026(GDHandle *dev,int ndev,int *attribs)
{
	int 			parseCmd,currentCmd;
	int 			*parseList = attribs;
	
	TAGLPixelFmtReq 	pixFmtReq;
	AGLPixelFmt 		pixFmt;
	
	/*
	 * Set the default values:
	 */
	 
	pixFmtReq.bufferSize = -1;
	
	pixFmtReq.overlayLevel = 0;
	
	pixFmtReq.rgba = GL_FALSE;
	
	pixFmtReq.depthSize = -1;
	
	pixFmtReq.stencilSize = -1;
	
	
	pixFmtReq.doubleBuffer = GL_FALSE;
	
	pixFmtReq.stereo = GL_FALSE;
	
	pixFmtReq.auxBuffers = -1;
	
	pixFmtReq.redSize = -1;
	pixFmtReq.greenSize = -1;
	pixFmtReq.blueSize = -1;
	pixFmtReq.alphaSize = -1;
	
	pixFmtReq.accumRedSize = -1;
	pixFmtReq.accumGreenSize = -1;
	pixFmtReq.accumBlueSize = -1;
	pixFmtReq.accumAlphaSize = -1;

	pixFmtReq.dev = dev;
	pixFmtReq.ndev = ndev;
  
  	/*
  	 * Fill out the pixel-format from the attribs
  	 */
  	 
  	while(*parseList)
  	{
  		
    	parseCmd = (*parseList);
    	parseList++;
    	switch(parseCmd) 
    	{
      		case AGL_USE_GL: 
        		break;
      		
      		case AGL_BUFFER_SIZE:
        		currentCmd = *parseList++;
        		pixFmtReq.bufferSize = currentCmd;
        		break;
      		
      		case AGL_LEVEL:
      			currentCmd = *parseList++;
      			pixFmtReq.overlayLevel = currentCmd; 
        		break; 
      		
      		case AGL_RGBA:
        		pixFmtReq.rgba = GL_TRUE;
        		break;
        		
      		case AGL_DOUBLEBUFFER:
        		pixFmtReq.doubleBuffer = GL_TRUE;
        		break;
        		
      		case AGL_STEREO:
        		pixFmtReq.stereo = GL_TRUE;
        		break;
        		
      		case AGL_AUX_BUFFERS:
      			currentCmd = *parseList++;
        		pixFmtReq.auxBuffers = currentCmd;
       		 	break;
       		 	
      		case AGL_RED_SIZE:
      			currentCmd = *parseList++;
      			pixFmtReq.redSize = currentCmd;
      			break;
      			
      		case AGL_GREEN_SIZE:
      			currentCmd = *parseList++;
      			pixFmtReq.greenSize = currentCmd;      
      			break;
      			
      		case AGL_BLUE_SIZE:
      			currentCmd = *parseList++;
      			pixFmtReq.blueSize = currentCmd;        
      			break;
      			
      		case AGL_ALPHA_SIZE:
      			currentCmd = *parseList++;
      			pixFmtReq.alphaSize = currentCmd;    
        		break;
      
      		case AGL_DEPTH_SIZE:
        		currentCmd = *parseList++;
				pixFmtReq.depthSize = currentCmd;
        		break;
        		
      		case AGL_STENCIL_SIZE:
        		currentCmd = *parseList++;
        		pixFmtReq.stencilSize = currentCmd;
        		break;
        		
      		case AGL_ACCUM_RED_SIZE:
        		currentCmd = *parseList++;
        		pixFmtReq.accumRedSize = currentCmd;
        		break;
        		
      		case AGL_ACCUM_GREEN_SIZE:
        		currentCmd = *parseList++;
        		pixFmtReq.accumGreenSize = currentCmd;
      			break;
      			
      		case AGL_ACCUM_BLUE_SIZE:
        		currentCmd = *parseList++;
        		pixFmtReq.accumBlueSize = currentCmd;
        		break;
        		
      		case AGL_ACCUM_ALPHA_SIZE:
      			currentCmd = *parseList++;
        		pixFmtReq.accumAlphaSize = currentCmd;
        		break;

          case AGL_PIXEL_SIZE:
      			currentCmd = *parseList++;
            /* TODO check if current screen depth matches, if not, give error */
            pixelSizeTheyAskedFor=currentCmd;
            break;
       
          case AGL_SAMPLE_BUFFERS_ARB:
      			currentCmd = *parseList++;  /* Is this right? */
            /* TODO */
            break;
            
          case AGL_SAMPLES_ARB:
      			currentCmd = *parseList++;  /* Is this right? */
            /* TODO */
            break;
            
          case AGL_RENDERER_ID:
      			currentCmd = *parseList++;  /* Is this right? */
            /* TODO */
            break;
            
          case AGL_NO_RECOVERY:
            /* Fine with us, ignoring */
            break;
            
          case AGL_ACCELERATED:
            /* Sure!  We're accelerated...sure, sure... */
            break;
            
          case AGL_CLOSEST_POLICY:
            /* Fine with us, ignoring */
            break;
            
          case AGL_SWAP_INTERVAL:
      			currentCmd = *parseList++;  /* Is this right? */
            swapIntervalTheyAskedFor=currentCmd;
            break;
                       
       		default:
        		AGLSetAGLError(NULL,AGL_BAD_ATTRIBUTE,"Unknown attribute to set!");
        		return 0;
    	}
  }
  
  /*
   * Get the Pixel-Format from the driver manager.
   */
  pixFmt = (AGLPixelFmt)DDChoosePixelFmt(&pixFmtReq);
  
  return pixFmt;
}


GLboolean aglSetDrawable(AGLContext ctx, AGLDrawable draw)
{
  //fprintf(stderr,"aglSetDrawable...not implemented\n"); fflush(stderr);
  return __aglMakeCurrent(draw,ctx);
  //return true;
}


GLboolean aglSetCurrentContext(AGLContext ctx)
{
  //fprintf(stderr,"aglSetCurrentContext...not implemented\n"); fflush(stderr);
  return __aglMakeCurrent(ctx->drawable,ctx);
  //return true;
}


GLboolean aglUpdateContext(AGLContext ctx)
{
  fprintf(stderr,"aglUpdateContext...not implemented\n"); fflush(stderr);
  return true;
}


GLboolean aglSetInteger(AGLContext ctx, GLenum pname,
                               const GLint *params)
{
  switch(pname) {
    case AGL_SWAP_INTERVAL:
      swapIntervalTheyAskedFor=(int)*params;  /* Is this right? */
      break;
    default:
      fprintf(stderr,"aglSetInteger pname=%d...not implemented\n",(int)pname); fflush(stderr);
      break;
  }
  return true;
}


void glGetIntegerv( GLenum pname, GLint *params )
{
  /* TODO: Handle ones old Mesa can't or won't */
  //fprintf(stderr,"FYI glGetIntegerv %d 0x%x\n",pname,pname); fflush(stderr);
  glGetIntegerv_old(pname,params);
  //fprintf(stderr,"FYI glGetIntegerv_old said %d 0x%x\n",*params,*params); fflush(stderr);
  switch(pname) {
    case 3410:
      fprintf(stderr,"FYI glGetIntegerv is lying and we are saying SDL_GL_RED_SIZE 5\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetIntegerv_old said %d 0x%x\n",*params,*params); fflush(stderr);
      *params=5;
      break;
    case 3411:
      fprintf(stderr,"FYI glGetIntegerv is lying and we are saying SDL_GL_BLUE_SIZE 5\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetIntegerv_old said %d 0x%x\n",*params,*params); fflush(stderr);
      *params=5;
      break;
    case 3412:
      fprintf(stderr,"FYI glGetIntegerv is lying and we are saying SDL_GL_GREEN_SIZE 5\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetIntegerv_old said %d 0x%x\n",*params,*params); fflush(stderr);
      *params=5;
      break;
    case 3414:
      fprintf(stderr,"FYI glGetIntegerv is lying and we are saying SDL_GL_DEPTH 16\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetIntegerv_old said %d 0x%x\n",*params,*params); fflush(stderr);
      *params=16;
      break;
    default:
      /* Assume old Mesa answered correctly... */
      break;
  }
}


const GLubyte * glGetString( GLenum name )
{
  /* TODO: Handle ones old Mesa can't or won't */
  char *ret=NULL;
  /*fprintf(stderr,"FYI glGetString %d 0x%x\n",name,name); fflush(stderr);*/
  ret=(char *)glGetString_old(name);
  /*fprintf(stderr,"FYI glGetString_old said %s\n",ret); fflush(stderr);*/
  switch(name) {
    case GL_VENDOR:
      fprintf(stderr,"FYI glGetString is lying and we are saying GL_VENDOR unknown\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetString_old said %s\n",ret); fflush(stderr);
      ret="Unknown";
      break;
    case GL_RENDERER:
      fprintf(stderr,"FYI glGetString is lying and we are saying GL_RENDERER unknown\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetString_old said %s\n",ret); fflush(stderr);
      ret="Unknown";
      break;
    case GL_VERSION:
      fprintf(stderr,"FYI glGetString is lying and we are saying  GL_VERSION unknown\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetString_old said %s\n",ret); fflush(stderr);
      ret="Unknown";
      break;
    case GL_EXTENSIONS:
      fprintf(stderr,"FYI glGetString is lying and we are saying GL_EXTENSIONS unknown\n"); fflush(stderr);
      fprintf(stderr,"FYI glGetString_old said %s\n",ret); fflush(stderr);
      ret="Unknown";
      break;
    default:
      /* Assume old Mesa answered correctly... */
      break;
  }
  return (const GLubyte *)ret;
}


void aglDestroyPixelFormat(AGLPixelFormat pix)
{
  //fprintf(stderr,"aglDestroyPixelFormat...not implemented\n"); fflush(stderr);
  AGLDisposePixelFormat((AGLPixelFmt)pix);
}


GLboolean aglDescribePixelFormat(AGLPixelFormat pix, GLint attrib,
                                        GLint *value)
{
  GLboolean ret=false;
  switch(attrib) {
    case AGL_ACCELERATED:
      /* Of COURSE we are accelerated..right? */
      fprintf(stderr,"aglDescribePixelFormat asked about AGL_ACCELERATED, we are lying...\n"); fflush(stderr);
      *value=true;
      ret=true;
      break;
    case AGL_RENDERER_ID:
      /* Um...1? */
      fprintf(stderr,"aglDescribePixelFormat asked about AGL_RENDERER_ID, we are making one up...\n"); fflush(stderr);
      *value=1;
      ret=true;
      break;
    case AGL_DEPTH_SIZE:
      /* We return what they asked for, possibly lying.  If they didn't ask, 16 */
      fprintf(stderr,"aglDescribePixelFormat asked about AGL_DEPTH_SIZE, we are lying...\n"); fflush(stderr);
      *value=depthSizeTheyAskedFor;
      ret=true;
      break;
    case AGL_PIXEL_SIZE:
      /* We return what they asked for, possibly lying.  If they didn't ask, 16 */
      fprintf(stderr,"aglDescribePixelFormat asked about AGL_PIXEL_SIZE, we are lying...\n"); fflush(stderr);
      *value=pixelSizeTheyAskedFor;
      ret=true;
      break;
    case AGL_STENCIL_SIZE:
      /* We return what they asked for, possibly lying.  If they didn't ask, 16 */
      fprintf(stderr,"aglDescribePixelFormat asked about AGL_STENCIL_SIZE, we are lying...\n"); fflush(stderr);
      *value=stencilSizeTheyAskedFor;
      ret=true;
      break;
    case AGL_DOUBLEBUFFER:
      /* Of COURSE we are double buffered...right? */
      fprintf(stderr,"aglDescribePixelFormat asked about AGL_DOUBLEBUFFER, are we lying?\n"); fflush(stderr);
      *value=true;
      ret=true;
      break;
    default:
      fprintf(stderr,"aglDescribePixelFormat %d %d ...not implemented\n",(int)pix,(int)attrib); fflush(stderr);
      break;
  }
  return ret;
}


AGLPixelFormat aglChoosePixelFormat(const AGLDevice *gdevs, GLint ndev,
                                           /*const*/ GLint *attribs)
{
  //fprintf(stderr,"aglChoosePixelFormat...not implemented\n"); fflush(stderr);
  int count=0;
  while(attribs[count]!=AGL_NONE) {
    	switch(attribs[count]) 
    	{
      		case AGL_USE_GL: 
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_USE_GL\n"); fflush(stderr);
        		break;
      		case AGL_BUFFER_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_BUFFER_SIZE\n"); fflush(stderr);
        		break;
      		case AGL_LEVEL:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_LEVEL\n"); fflush(stderr);
        		break; 
      		case AGL_RGBA:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_RGBA\n"); fflush(stderr);
        		break;
      		case AGL_DOUBLEBUFFER:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_DOUBLEBUFFER\n"); fflush(stderr);
        		break;
      		case AGL_STEREO:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_STEREO\n"); fflush(stderr);
        		break;      		case AGL_AUX_BUFFERS:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_AUX_BUFFERS\n"); fflush(stderr);
       		 	break;
      		case AGL_RED_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_RED_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
         		break;
      		case AGL_GREEN_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_GREEN_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_BLUE_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_BLUE_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
         		break;
      		case AGL_ALPHA_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_ALPHA_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_DEPTH_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_DEPTH_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            depthSizeTheyAskedFor=attribs[count+1];
            count++;
       		  break;
      		case AGL_STENCIL_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_STENCIL_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            stencilSizeTheyAskedFor=attribs[count+1];
            count++;
       		  break;
      		case AGL_ACCUM_RED_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_ACCUM_RED_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_ACCUM_GREEN_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_ACCUM_GREEN_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_ACCUM_BLUE_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_ACCUM_BLUE_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_ACCUM_ALPHA_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_ACCUM_ALPHA_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_PIXEL_SIZE:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_PIXEL_SIZE is %d\n",attribs[count+1]); fflush(stderr);
            pixelSizeTheyAskedFor=attribs[count+1];
            count++;
        		break;
      		case AGL_SAMPLE_BUFFERS_ARB:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_SAMPLE_BUFFERS_ARB is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_SAMPLES_ARB:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_SAMPLES_ARB is %d\n",attribs[count+1]); fflush(stderr);
            count++;
        		break;
      		case AGL_NO_RECOVERY:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_NO_RECOVERY\n"); fflush(stderr);
        		break;
      		case AGL_ACCELERATED:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_ACCELERATED\n"); fflush(stderr);
        		break;
      		case AGL_CLOSEST_POLICY:
            fprintf(stderr,"aglChoosePixelFormat: attrib=AGL_CLOSEST_POLICY\n"); fflush(stderr);
        		break;
       		default:
            fprintf(stderr,"aglChoosePixelFormat: attrib=%d?\n",attribs[count]); fflush(stderr);
        		break;
    	}
    count++;
  }
  /* NOTE: gdevs may not be correct! */
  return (AGLPixelFormat)__aglChoosePixelFmt2026((GDHandle *)gdevs,ndev,attribs);
}


void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
  fprintf(stderr,"glBlendFuncSeparate...not implemented\n"); fflush(stderr);
}


void glBlendEquation(GLenum mode)
{
  fprintf(stderr,"glBlendEquation...not implemented\n"); fflush(stderr);
}


const GLubyte *aglErrorString(GLenum code)
{
  //fprintf(stderr,"aglErrorString...not implemented\n"); fflush(stderr);
  if (code)
    switch (code)
    {
      case AGL_BAD_ATTRIBUTE:
        return (const GLubyte *)"AGL_BAD_ATTRIBUTE";
        break;
      case AGL_BAD_PIXELFMT:
        return (const GLubyte *)"AGL_BAD_PIXELFMT";
        break;
     /* case AGL_INVALID_OPT:
        return (const GLubyte *)"AGL_INVALID_OPT";
        break; */
      case AGL_BAD_CONTEXT:
        return (const GLubyte *)"AGL_BAD_CONTEXT";
        break;
      case AGL_BAD_DRAWABLE:
        return (const GLubyte *)"AGL_BAD_DRAWABLE";
        break;
      /* case AGL_NOT_RENDERING:
        return (const GLubyte *)"AGL_NOT_RENDERING";
        break; */
      /* case AGL_DO_ALREADY:
        return (const GLubyte *)"AGL_DO_ALREADY";
        break; */
      /* case AGL_ATTRIB_UNAVAIL:
        return (const GLubyte *)"AGL_ATTRIB_UNAVAIL";
        break; */
      case AGL_INVALID_GDEV:
        return (const GLubyte *)"AGL_INVALID_GDEV";
        break;
      case AGL_GL_ERROR:
        return (const GLubyte *)"AGL_GL_ERROR";
        break;
      default:
        return (const GLubyte *)"Unknown error.";
        break;
    }
  return "Who knows?!?";
}
