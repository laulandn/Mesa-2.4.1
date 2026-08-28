
/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#include <GL/glut.h>
#include "glutint.h"

/* CENTRY */
int
glutGet(GLenum param)
{
#ifdef unix
  Window win, root;
  int x, y, value;
  unsigned int width, height, border, depth;
#elif defined( WIN32 )
  int value;
  RECT rect;
#endif

  switch (param) {
#ifdef FULL_SCREEN
  case GLUT_INIT_WINDOW_X:
  case GLUT_INIT_WINDOW_Y:
    return 0;
#else
  case GLUT_INIT_WINDOW_X:
    return __glutInitX;
  case GLUT_INIT_WINDOW_Y:
    return __glutInitY;
#endif
  case GLUT_INIT_WINDOW_WIDTH:
    return __glutInitWidth;
  case GLUT_INIT_WINDOW_HEIGHT:
    return __glutInitHeight;
  case GLUT_INIT_DISPLAY_MODE:
    return __glutDisplayMode;
  case GLUT_WINDOW_X:
#ifdef FULL_SCREEN
	return 0;
#else
#ifdef unix
    XTranslateCoordinates(__glutDisplay, __glutCurrentWindow->win,
      __glutRoot, 0, 0, &x, &y, &win);
    return x;
#elif defined( WIN32 )
    GetWindowRect( __glutCurrentWindow->win, &rect );
    return rect.left;
#endif
#endif
  case GLUT_WINDOW_Y:
#ifdef FULL_SCREEN
	return 0;
#else
#ifdef unix
    XTranslateCoordinates(__glutDisplay, __glutCurrentWindow->win,
      __glutRoot, 0, 0, &x, &y, &win);
    return y;
#elif defined( WIN32 )
    GetWindowRect( __glutCurrentWindow->win, &rect );
    return rect.top;
#endif
#endif
  case GLUT_WINDOW_WIDTH:
#ifdef FULL_SCREEN
	if (!__glutCurrentWindow->reshape) {
#ifdef unix
      XGetGeometry(__glutDisplay, __glutCurrentWindow->win,
        &root, &x, &y,
        &width, &height, &border, &depth);
      return height;
#elif defined( WIN32 )
    	GetWindowRect( __glutCurrentWindow->win, &rect );
    	return rect.top - rect.bottom;
#endif
    }
#endif
    return __glutCurrentWindow->width;
  case GLUT_WINDOW_HEIGHT:
#ifdef FULL_SCREEN
    if (!__glutCurrentWindow->reshape) {
#ifdef unix
      XGetGeometry(__glutDisplay, __glutCurrentWindow->win,
        &root, &x, &y,
        &width, &height, &border, &depth);
      return height;
#elif defined( WIN32 )
    	GetWindowRect( __glutCurrentWindow->win, &rect );
    	return rect.top - rect.bottom;
#endif
    }
#endif
    return __glutCurrentWindow->height;

#ifdef unix
#define GET_CONFIG(attrib) { \
  if (__glutCurrentWindow->renderWin == __glutCurrentWindow->win) { \
    glXGetConfig(__glutDisplay, __glutCurrentWindow->vis, \
      attrib, &value); \
  } else { \
    glXGetConfig(__glutDisplay, __glutCurrentWindow->overlay->vis, \
      attrib, &value); \
  } \
}

  case GLUT_WINDOW_BUFFER_SIZE:
    GET_CONFIG(GLX_BUFFER_SIZE);
    return value;
  case GLUT_WINDOW_STENCIL_SIZE:
    GET_CONFIG(GLX_STENCIL_SIZE);
    return value;
  case GLUT_WINDOW_DEPTH_SIZE:
    GET_CONFIG(GLX_DEPTH_SIZE);
    return value;
  case GLUT_WINDOW_RED_SIZE:
    GET_CONFIG(GLX_RED_SIZE);
    return value;
  case GLUT_WINDOW_GREEN_SIZE:
    GET_CONFIG(GLX_GREEN_SIZE);
    return value;
  case GLUT_WINDOW_BLUE_SIZE:
    GET_CONFIG(GLX_BLUE_SIZE);
    return value;
  case GLUT_WINDOW_ALPHA_SIZE:
    GET_CONFIG(GLX_ALPHA_SIZE);
    return value;
  case GLUT_WINDOW_ACCUM_RED_SIZE:
    GET_CONFIG(GLX_ACCUM_RED_SIZE);
    return value;
  case GLUT_WINDOW_ACCUM_GREEN_SIZE:
    GET_CONFIG(GLX_ACCUM_GREEN_SIZE);
    return value;
  case GLUT_WINDOW_ACCUM_BLUE_SIZE:
    GET_CONFIG(GLX_ACCUM_BLUE_SIZE);
    return value;
  case GLUT_WINDOW_ACCUM_ALPHA_SIZE:
    GET_CONFIG(GLX_ACCUM_ALPHA_SIZE);
    return value;
  case GLUT_WINDOW_DOUBLEBUFFER:
    GET_CONFIG(GLX_DOUBLEBUFFER);
    return value;
  case GLUT_WINDOW_RGBA:
    GET_CONFIG(GLX_RGBA);
    return value;
  case GLUT_WINDOW_COLORMAP_SIZE:
    GET_CONFIG(GLX_RGBA);
    if (value) {
      return 0;
    } else {
      return __glutCurrentWindow->vis->visual->map_entries;
    }
#elif defined( WIN32 )

#define GET_CONFIG(attrib) { \
  PIXELFORMATDESCRIPTOR pfd; \
  if (__glutCurrentWindow->renderWin == __glutCurrentWindow->win) { \
    DescribePixelFormat( __glutCurrentWindow->dc, __glutCurrentWindow->ipfd, \
		sizeof( PIXELFORMATDESCRIPTOR ), &pfd ); \
	value = pfd.attrib; \
  } else { \
    DescribePixelFormat( __glutCurrentWindow->overlay->dc, \
		__glutCurrentWindow->overlay->ipfd, sizeof( PIXELFORMATDESCRIPTOR ), &pfd ); \
	value = pfd.attrib; \
  } \
}
  case GLUT_WINDOW_BUFFER_SIZE:
    GET_CONFIG( cColorBits );
	return value;
  case GLUT_WINDOW_STENCIL_SIZE:
    GET_CONFIG( cStencilBits );
	return value;
  case GLUT_WINDOW_DEPTH_SIZE:
    GET_CONFIG( cDepthBits );
	return value;
  case GLUT_WINDOW_RED_SIZE:
    GET_CONFIG( cRedBits );
	return value;
  case GLUT_WINDOW_GREEN_SIZE:
    GET_CONFIG( cGreenBits );
	return value;
  case GLUT_WINDOW_BLUE_SIZE:
    GET_CONFIG( cBlueBits );
	return value;
  case GLUT_WINDOW_ALPHA_SIZE:
    GET_CONFIG( cAlphaBits );
	return value;
  case GLUT_WINDOW_ACCUM_RED_SIZE:
    GET_CONFIG( cAccumRedBits );
	return value;
  case GLUT_WINDOW_ACCUM_GREEN_SIZE:
    GET_CONFIG( cAccumGreenBits );
	return value;
  case GLUT_WINDOW_ACCUM_BLUE_SIZE:
    GET_CONFIG( cAccumBlueBits );
	return value;
  case GLUT_WINDOW_ACCUM_ALPHA_SIZE:
    GET_CONFIG( cAccumAlphaBits );
	return value;
  case GLUT_WINDOW_DOUBLEBUFFER:
    GET_CONFIG( dwFlags );
	return ( value & PFD_DOUBLEBUFFER ) != 0;
  case GLUT_WINDOW_RGBA:
    GET_CONFIG( iPixelType );
	return value == PFD_TYPE_RGBA;
  case GLUT_WINDOW_COLORMAP_SIZE:
    GET_CONFIG( iPixelType ); 
	return value == PFD_TYPE_RGBA ? 0 : glutGet(GLUT_WINDOW_BUFFER_SIZE);
#endif
  case GLUT_WINDOW_PARENT:
    return __glutCurrentWindow->parent ?
      __glutCurrentWindow->parent->num + 1 : 0;
  case GLUT_WINDOW_NUM_CHILDREN:
    {
      int num = 0;
      GLUTwindow *children = __glutCurrentWindow->children;

      while (children) {
        num++;
        children = children->siblings;
      }
      return num;
    }
  case GLUT_WINDOW_NUM_SAMPLES:
#if defined(GLX_VERSION_1_1) && defined(GLX_SGIS_multisample)
    if (__glutIsSupportedByGLX("GLX_SGIS_multisample")) {
      GET_CONFIG(GLX_SAMPLES_SGIS);
      return value;
    } else {
      return 0;
    }
#else
    /* Independent of GLX server support, multisampling not
       supported by GLX client-side. */
    return 0;
#endif
  case GLUT_WINDOW_STEREO:
#ifdef unix
    GET_CONFIG(GLX_STEREO);
    return value;
#elif defined( WIN32 )
    GET_CONFIG( dwFlags );
    return value  | PFD_STEREO;
#endif
  case GLUT_WINDOW_CURSOR:
    return __glutCurrentWindow->cursor;
  case GLUT_SCREEN_WIDTH:
    return DisplayWidth(__glutDisplay, __glutScreen);
  case GLUT_SCREEN_HEIGHT:
    return DisplayHeight(__glutDisplay, __glutScreen);
  case GLUT_SCREEN_WIDTH_MM:
#ifdef unix
    return DisplayWidthMM(__glutDisplay, __glutScreen);
#elif defined( WIN32 )
      __glutWarning("SCREEN_WIDTH_MM unimplemented in Win32 implementation of GLUT");
      return 0;
#endif
  case GLUT_SCREEN_HEIGHT_MM:
#ifdef unix
    return DisplayHeightMM(__glutDisplay, __glutScreen);
#elif defined( WIN32 )
      __glutWarning("SCREEN_HEIGHT_MM unimplemented in Win32 implementation of GLUT");
      return 0;
#endif
  case GLUT_MENU_NUM_ITEMS:
    return __glutCurrentMenu->num;
  case GLUT_DISPLAY_MODE_POSSIBLE:
    {
      XVisualInfo *vi;
      Bool dummy;

      vi = __glutDetermineVisual(__glutDisplayMode, &dummy, __glutGetVisualInfo);
      if (vi) {
        XFree(vi);
        return 1;
      }
      return 0;
    }
  case GLUT_ELAPSED_TIME:
    {
      struct timeval elapsed, beginning, now;

      __glutInitTime(&beginning);
      GETTIMEOFDAY(&now);
      TIMEDELTA(elapsed, now, beginning);
      /* Return elapsed milliseconds. */
#if defined(__vms)
      return (int) (elapsed.val / TICKS_PER_MILLISECOND);
#else
      return (int) ((elapsed.tv_sec * 1000) + (elapsed.tv_usec / 1000));
#endif
    }
  default:
    __glutWarning("invalid glutGet parameter: %d", param);
    return -1;
  }
}
/* ENDCENTRY */
