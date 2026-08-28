/* Copyright (c) Mark J. Kilgard, 1994.  */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <GL/glut.h>
#include "glutint.h"

#include "GL/fxmesa.h"

GLUTwindow *__glutCurrentWindow = NULL;
GLUTwindow **__glutWindowList = NULL;
int __glutWindowListSize = 0;
GLUTstale *__glutStaleWindowList = NULL;

void (*__glutFreeOverlayFunc) (GLUToverlay *);

static void
cleanWindowWorkList(GLUTwindow * window)
{
  GLUTwindow **pEntry = &__glutWindowWorkList;
  GLUTwindow *entry = __glutWindowWorkList;

  /* Tranverse singly-linked window work list look for the
     window. */
  while (entry) {
    if (entry == window) {
      /* Found it; delete it. */
      *pEntry = entry->prevWorkWin;
      return;
    } else {
      pEntry = &entry->prevWorkWin;
      entry = *pEntry;
    }
  }
}

static void
cleanStaleWindowList(GLUTwindow * window)
{
  GLUTstale **pEntry = &__glutStaleWindowList;
  GLUTstale *entry = __glutStaleWindowList;

  /* Tranverse singly-linked stale window list look for the
     window ID. */
  while (entry) {
    if (entry->window == window) {
      /* Found it; delete it. */
      *pEntry = entry->next;
      free(entry);
      return;
    } else {
      pEntry = &entry->next;
      entry = *pEntry;
    }
  }
}

static GLUTwindow *__glutWindowCache = NULL;

GLUTwindow *
__glutGetWindow(Window win)
{
  GLUTstale *entry;
  int i;

  /* Does win belong to the last window ID looked up? */
  if (__glutWindowCache && (win == __glutWindowCache->win ||
      (__glutWindowCache->overlay && win ==
        __glutWindowCache->overlay->win))) {
    return
      __glutWindowCache;
  }
  /* Otherwise scan the window list looking for the window ID. */
  for (i = 0; i < __glutWindowListSize; i++) {
    if (__glutWindowList[i]) {
      if (win == __glutWindowList[i]->win) {
        __glutWindowCache = __glutWindowList[i];
        return __glutWindowCache;
      }
      if (__glutWindowList[i]->overlay) {
        if (win == __glutWindowList[i]->overlay->win) {
          __glutWindowCache = __glutWindowList[i];
          return __glutWindowCache;
        }
      }
    }
  }
  /* Scan through destroyed overlay window IDs for which no
     DestroyNotify has yet been received. */
  for (entry = __glutStaleWindowList; entry; entry = entry->next) {
    if (entry->win == win)
      return entry->window;
  }
  return NULL;
}

/* CENTRY */
int
glutGetWindow(void)
{
  if (__glutCurrentWindow) {
    return __glutCurrentWindow->num + 1;
  } else {
    return 0;
  }
}
/* ENDCENTRY */

void
__glutSetWindow(GLUTwindow * window)
{
  /* It is tempting to try to short-circuit the call to
     glXMakeCurrent if we "know" we are going to make current
     to a window we are already current to.  In fact, this
     assumption breaks when GLUT is expected to integrated with
     other OpenGL windowing APIs that also make current to
     OpenGL contexts.  Since glXMakeCurrent short-circuits the
     "already bound" case, GLUT avoids the temptation to do so
     too. */
  __glutCurrentWindow = window;
  fxMesaMakeCurrent(__glutCurrentWindow->renderCtx);

  /* We should be careful to force a finish between each
     iteration through the GLUT main loop if indirect OpenGL 
     contexts are in use; indirect contexts tend to have  much
     longer latency because lots of OpenGL extension requests
     can queue up in the X protocol stream.  We accomplish this
     by posting GLUT_FINISH_WORK to be done. */
  if (!__glutCurrentWindow->isDirect)
    __glutPutOnWorkList(__glutCurrentWindow, GLUT_FINISH_WORK);

  /* If debugging is enabled, we'll want to check this window
     for any OpenGL errors every iteration through the GLUT
     main loop.  To accomplish this, we post the
     GLUT_DEBUG_WORK to be done on this window. */
  if (__glutDebug)
    __glutPutOnWorkList(__glutCurrentWindow, GLUT_DEBUG_WORK);
}

/* CENTRY */
void
glutSetWindow(int win)
{
  GLUTwindow *window;

  if (win < 1 || win > __glutWindowListSize) {
    __glutWarning("glutSetWindow attempted on bogus window.");
    return;
  }
  window = __glutWindowList[win - 1];
  if (!window) {
    __glutWarning("glutSetWindow attempted on bogus window.");
    return;
  }
  __glutSetWindow(window);
}
/* ENDCENTRY */

static int
getUnusedWindowSlot(void)
{
  int i;

  /* Look for allocated, unused slot. */
  for (i = 0; i < __glutWindowListSize; i++) {
    if (!__glutWindowList[i]) {
      return i;
    }
  }
  /* Allocate a new slot. */
  __glutWindowListSize++;
  if (__glutWindowList) {
    __glutWindowList = (GLUTwindow **)
      realloc(__glutWindowList,
      __glutWindowListSize * sizeof(GLUTwindow *));
  } else {
    /* XXX Some realloc's do not correctly perform a malloc
       when asked to perform a realloc on a NULL pointer,
       though the ANSI C library spec requires this. */
    __glutWindowList = (GLUTwindow **)
      malloc(sizeof(GLUTwindow *));
  }
  if (!__glutWindowList)
    __glutFatalError("out of memory.");
  __glutWindowList[__glutWindowListSize - 1] = NULL;
  return __glutWindowListSize - 1;
}


XVisualInfo *
__glutGetVisualInfo(unsigned int mode)
{
  /* XXX GLUT_LUMINANCE not implemented for GLUT 3.0. */
  if (GLUT_WIND_IS_LUMINANCE(mode))
    return NULL;

  return 1;
/*
  if (GLUT_WIND_IS_RGB(mode))
    return getVisualInfoRGB(mode);
  else
    return getVisualInfoCI(mode);
*/
}

XVisualInfo *
__glutDetermineVisual(
  unsigned int displayMode,
  Bool * treatAsSingle,
  XVisualInfo * (getVisualInfo) (unsigned int))
{
  XVisualInfo *vis;

  *treatAsSingle = GLUT_WIND_IS_SINGLE(displayMode);
  vis = getVisualInfo(displayMode);
  if (!vis) {
    /* Fallback cases when can't get exactly what was asked
       for... */
    if (GLUT_WIND_IS_SINGLE(displayMode)) {
      /* If we can't find a single buffered visual, try looking
         for a double buffered visual.  We can treat a double
         buffered visual as a single buffer visual by changing
         the draw buffer to GL_FRONT and treating any swap
         buffers as no-ops. */
      displayMode |= GLUT_DOUBLE;
      vis = getVisualInfo(displayMode);
      *treatAsSingle = True;
    }
    if (!vis && GLUT_WIND_IS_MULTISAMPLE(displayMode)) {
      /* If we can't seem to get multisampling (ie, not Reality
         Engine class graphics!), go without multisampling.  It
         is up to the application to query how many multisamples
         were allocated (0 equals no multisampling) if the
         application is going to use multisampling for more than
         just antialiasing. */
      displayMode &= ~GLUT_MULTISAMPLE;
      vis = getVisualInfo(displayMode);
    }
  }
  return vis;
}

void
__glutSetupColormap(XVisualInfo * vi, GLUTcolormap ** colormap, Colormap * cmap)
{
}

void
__glutDefaultDisplay(void)
{
  /* XXX Remove the warning after GLUT 3.0. */
  __glutWarning("The following is a new check for GLUT 3.0; update your code.");
  __glutFatalError(
    "redisplay needed for window %d, but no display callback.",
    __glutCurrentWindow->num + 1);
}

void
__glutDefaultReshape(int width, int height)
{
  GLUToverlay *overlay;

  /* Adjust the viewport of the window (and overlay if one
     exists). */
  fxMesaMakeCurrent(__glutCurrentWindow->ctx);
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  overlay = __glutCurrentWindow->overlay;
  if (overlay) {
  }
  /* Make sure we are current to the current layer (application
     should be able to count on the current layer not changing
     unless the application explicitly calls glutUseLayer). */
  fxMesaMakeCurrent(__glutCurrentWindow->ctx);
}

GLUTwindow *
__glutCreateWindow(GLUTwindow * parent,
  int x, int y, int width, int height)
{
  GLUTwindow *window;
  WNDCLASS wndclass;
  static char     *lpszClassName = "GLUTClass";
  static int been_here = 0;
  long WINAPI __glutProcessEvents(HWND hWnd, UINT message, 
		DWORD wParam, LONG lParam);
  RECT     WinRect;
  int dwStyle;
  int winnum;
  int i;

  if ( been_here && !parent )
  {
	__glutWarning("multiple windows unsupported in full screen implementation of GLUT");
	return NULL;
  }

  if ( !been_here )
  {
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)__glutProcessEvents;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = GetModuleHandle(NULL);
    wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor       = NULL;//No default cursor for the class
    wndclass.hbrBackground = GetStockObject(BLACK_BRUSH);
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = lpszClassName;

  	if ( !RegisterClass(&wndclass) )
     	__glutFatalError("Failed to register window class.");
 	
  }

 if (!__glutDisplay)
    __glutOpenXConnection(NULL);
  winnum = getUnusedWindowSlot();
  window = (GLUTwindow *) malloc(sizeof(GLUTwindow));
  if (!window)
    __glutFatalError("out of memory.");
  window->num = winnum;

  window->vis = __glutDetermineVisual(__glutDisplayMode,
    &window->treatAsSingle, __glutGetVisualInfo);
  if (!window->vis) {
    __glutFatalError(
      "visual with necessary capabilities not found.");
  }
  if ( !been_here )
  {
/* the original Henri's code */
	  WinRect.left   = 100 + GetSystemMetrics(SM_CXFRAME);
	  WinRect.right  = 100 + GetSystemMetrics(SM_CXFRAME) + 200;
	  WinRect.top    = 100 + GetSystemMetrics(SM_CYCAPTION)
					 - GetSystemMetrics(SM_CYBORDER)
					 + GetSystemMetrics(SM_CYFRAME) + 1;
	  WinRect.bottom = 100 + GetSystemMetrics(SM_CYCAPTION)
					 - GetSystemMetrics(SM_CYBORDER)
					 + GetSystemMetrics(SM_CYFRAME) + 200 + 1;

	  AdjustWindowRect( &WinRect, WS_OVERLAPPEDWINDOW, FALSE );
/*

		WinRect.left=0;
		WinRect.right=1280;
		WinRect.top=0;
		WinRect.bottom=1024;
*/
	  if ( parent )
			dwStyle = WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	  else
/* the original Henri's code */
			dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
/*
			dwStyle = WS_MAXIMIZE;
*/
	  window->win = CreateWindow(
  		lpszClassName,
		"",
		dwStyle,
		WinRect.left, WinRect.top,
		WinRect.right - WinRect.left,
		WinRect.bottom - WinRect.top,
		parent == NULL ? NULL : parent->win , NULL,	GetModuleHandle(NULL), NULL);
	 __glutCurrentWindow = window;
	 window->renderDc = window->dc = GetDC( window->win );
  }
  window->renderWin = window->win;

  window->width = width;
  window->height = height;
  window->forceReshape = True;

  window->parent = parent;
  if (parent) {
    window->siblings = parent->children;
    parent->children = window;
  } else {
    window->siblings = NULL;
  }
  window->overlay = NULL;
  window->children = NULL;
  window->display = __glutDefaultDisplay;
  window->reshape = __glutDefaultReshape;
  window->mouse = NULL;
  window->motion = NULL;
  window->windowStatus = NULL;
  window->visibility = NULL;
  window->passive = NULL;
  window->entry = NULL;
  window->special = NULL;
  window->buttonBox = NULL;
  window->dials = NULL;
  window->spaceMotion = NULL;
  window->spaceRotate = NULL;
  window->spaceButton = NULL;
  window->tabletMotion = NULL;
  window->tabletButton = NULL;
  window->tabletPos[0] = -1;
  window->tabletPos[1] = -1;
  window->keyboard = NULL;
  window->shownState = 0;
  window->visState = -1;  /* not VisibilityUnobscured,
                             VisibilityPartiallyObscured, or
                             VisibilityFullyObscured */
  window->entryState = -1;  /* not EnterNotify or LeaveNotify */
  window->workMask = GLUT_MAP_WORK;
  window->desiredMapState = NormalState;
  window->desiredConfMask = 0;
  window->buttonUses = 0;
  window->cursor = GLUT_CURSOR_INHERIT;
  window->prevWorkWin = __glutWindowWorkList;
  __glutWindowWorkList = window;
  for (i = 0; i < GLUT_MAX_MENUS; i++) {
    window->menu[i] = 0;
  }
  __glutWindowList[winnum] = window;
  
  
  if ( !been_here )
  {
          GLint attribList[]={ FXMESA_DOUBLEBUFFER,
                                FXMESA_DEPTH_SIZE,1,
                                FXMESA_ALPHA_SIZE,1,
                                FXMESA_NONE};

	  window->vis = __glutDetermineVisual(__glutDisplayMode,
		&window->treatAsSingle, __glutGetVisualInfo);
	  if (!window->vis) {
		__glutFatalError( 
		  "visual with necessary capabilities not found.");
	  }
	  window->renderCtx = window->ctx = 0;
	  ShowWindow( window->win, __glutIconic ? SW_SHOWMINNOACTIVE : SW_SHOWDEFAULT );

	  window->renderCtx = window->ctx = fxMesaCreateBestContext( window->win,width,height,attribList );
	  __glutSetupColormap(window->vis, &(window->colormap), &(window->cmap));
	  been_here = 1;
  }

  __glutSetWindow(window);

  __glutDetermineMesaSwapHackSupport();

  if (window->treatAsSingle) {
    /* We do this because either the window really is single
       buffered (in which case this is redundant, but harmless,
       because this is the initial single-buffered context
       state); or we are treating a double buffered window as a
       single-buffered window because the system does not
       appear to export any suitable single- buffered visuals
       (in which the following are necessary). */
    glDrawBuffer(GL_FRONT);
    glReadBuffer(GL_FRONT);
  }
  return window;
}


GLUTwindow *
__glutToplevelOf(GLUTwindow * window)
{
  while (window->parent) {
    window = window->parent;
  }
  return window;
}

/* CENTRY */
int
glutCreateWindow(char *title)
{
  static int firstWindow = 1;
  GLUTwindow *window;
#ifdef unix
  XWMHints *wmHints;
#endif
  Window win;
#ifdef unix
  XTextProperty textprop;
#endif

  window = __glutCreateWindow(NULL,
    __glutSizeHints.x, __glutSizeHints.y,
    __glutInitWidth, __glutInitHeight);
  win = window->win;
#ifdef unix
  /* Setup ICCCM properties. */
  textprop.value = (unsigned char *) title;
  textprop.encoding = XA_STRING;
  textprop.format = 8;
  textprop.nitems = strlen(title);
  wmHints = XAllocWMHints();
  wmHints->initial_state =
    __glutIconic ? IconicState : NormalState;
  wmHints->flags = StateHint;
  XSetWMProperties(__glutDisplay, win, &textprop, &textprop,
  /* Only put WM_COMMAND property on first window. */
    firstWindow ? __glutArgv : NULL,
    firstWindow ? __glutArgc : 0,
    &__glutSizeHints, wmHints, NULL);
  firstWindow = 0;
  XFree(wmHints);
  XSetWMProtocols(__glutDisplay, win, &__glutWMDeleteWindow, 1);
#elif defined( WIN32 )
  SetWindowText( win, title );
#endif
  return window->num + 1;
}

int
glutCreateSubWindow(int win, int x, int y, int width, int height)
{
  GLUTwindow *window, *toplevel;

  __glutWarning("glutCreateSubWindow unsupported in full screen implementation of GLUT");
  return 0;

  window = __glutCreateWindow(__glutWindowList[win - 1],
    x, y, width, height);
  toplevel = __glutToplevelOf(window);
  if (toplevel->cmap != window->cmap) {
    __glutPutOnWorkList(toplevel, GLUT_COLORMAP_WORK);
  }
  return window->num + 1;
}
/* ENDCENTRY */

static void
destroyWindow(GLUTwindow * window,
  GLUTwindow * initialWindow)
{
  GLUTwindow **prev, *cur, *parent, *siblings;

  /* Recursively destroy any children. */
  cur = window->children;
  while (cur) {
    siblings = cur->siblings;
    destroyWindow(cur, initialWindow);
    cur = siblings;
  }
  /* Remove from parent's children list (only necessary for
     non-initial windows and subwindows!). */
  parent = window->parent;
  if (parent && parent == initialWindow->parent) {
    prev = &parent->children;
    cur = parent->children;
    while (cur) {
      if (cur == window) {
        *prev = cur->siblings;
        break;
      }
      prev = &(cur->siblings);
      cur = cur->siblings;
    }
  }
  /* Unbind if bound to this window. */
  if (window == __glutCurrentWindow) {
    fxMesaMakeCurrent(NULL);
    __glutCurrentWindow = NULL;
  }
  /* Begin tearing down window itself. */
  if (window->overlay) {
    __glutFreeOverlayFunc(window->overlay);
  }
#ifdef unix
  XDestroyWindow(__glutDisplay, window->win);
  fxMesaDestroyContext(window->ctx);
#elif defined( WIN32 )
  fxMesaDestroyContext( window->ctx );
  ReleaseDC( window->win, window->dc );
  DestroyWindow( window->win );
#endif
  if (window->colormap) {
    /* Only color index windows have colormap data structure. */
    __glutFreeColormap(window->colormap);
  }
  /* NULLing the __glutWindowList helps detect is a window
     instance has been destroyed, given a window number. */
  __glutWindowList[window->num] = NULL;

  /* Cleanup data structures that might contain window. */
  cleanWindowWorkList(window);
  cleanStaleWindowList(window);
  /* Remove window from the "get window cache" if it is there. */
  if (__glutWindowCache == window)
    __glutWindowCache = NULL;

  XFree(window->vis);
  free(window);
}

/* CENTRY */
void
glutDestroyWindow(int win)
{
  GLUTwindow *window = __glutWindowList[win - 1];

  if (__glutMappedMenu && __glutMenuWindow == window) {
    __glutFatalUsage("destroying menu window not allowed while menus in use");
  }
  /* if not a toplevel window... */
  if (window->parent) {
    /* Destroying subwindows may change colormap requirements;
       recalculate toplevel window's WM_COLORMAP_WINDOWS
       property. */
    __glutPutOnWorkList(__glutToplevelOf(window->parent),
      GLUT_COLORMAP_WORK);
  }
  destroyWindow(window, window);
}

void
glutSwapBuffers(void)
{
  GLUTwindow *window = __glutCurrentWindow;

  if (window->renderWin == window->win) {
    if (__glutCurrentWindow->treatAsSingle) {
      /* Pretend the double buffered window is single buffered,
         so treat glutSwapBuffers as a no-op. */
      return;
    }
  } else {
    if (__glutCurrentWindow->overlay->treatAsSingle) {
      /* Pretend the double buffered overlay is single
         buffered, so treat glutSwapBuffers as a no-op. */
      return;
    }
  }

  /* For the MESA_SWAP_HACK. */
  window->usedSwapBuffers = 1;

  fxMesaSwapBuffers();

  /* I considered putting the window being swapped on the
     GLUT_FINISH_WORK work list because you could call
     glutSwapBuffers from an idle callback which doesn't call
     __glutSetWindow which normally adds indirect rendering
     windows to the GLUT_FINISH_WORK work list.  Not being put
     on the list could lead to the buffering up of multiple
     redisplays and buffer swaps and hamper interactivity.  I
     consider this an application bug due to not using
     glutPostRedisplay to trigger redraws.  If
     glutPostRedisplay were used, __glutSetWindow would be
     called and a glFinish to throttle buffering would occur. */
}
/* ENDCENTRY */

void
__glutChangeWindowEventMask(long eventMask, Bool add)
{
  if (add) {
    /* Add eventMask to window's event mask. */
    if ((__glutCurrentWindow->eventMask & eventMask) !=
      eventMask) {
      __glutCurrentWindow->eventMask |= eventMask;
      __glutPutOnWorkList(__glutCurrentWindow,
        GLUT_EVENT_MASK_WORK);
    }
  } else {
    /* Remove eventMask from window's event mask. */
    if (__glutCurrentWindow->eventMask & eventMask) {
      __glutCurrentWindow->eventMask &= ~eventMask;
      __glutPutOnWorkList(__glutCurrentWindow,
        GLUT_EVENT_MASK_WORK);
    }
  }
}

void
glutDisplayFunc(GLUTdisplayCB displayFunc)
{
  /* XXX Remove the warning after GLUT 3.0. */
  if (!displayFunc)
    __glutFatalError("NULL display callback not allowed in GLUT 3.0; update your code.");
  __glutCurrentWindow->display = displayFunc;
}

void
glutKeyboardFunc(GLUTkeyboardCB keyboardFunc)
{
  __glutChangeWindowEventMask(KeyPressMask,
    keyboardFunc != NULL || __glutCurrentWindow->special != NULL);
  __glutCurrentWindow->keyboard = keyboardFunc;
}

void
glutSpecialFunc(GLUTspecialCB specialFunc)
{
  __glutChangeWindowEventMask(KeyPressMask,
    specialFunc != NULL || __glutCurrentWindow->keyboard != NULL);
  __glutCurrentWindow->special = specialFunc;
}

void
glutMouseFunc(GLUTmouseCB mouseFunc)
{
  if (__glutCurrentWindow->mouse) {
    if (!mouseFunc) {
      /* Previous mouseFunc being disabled. */
      __glutCurrentWindow->buttonUses--;
      __glutChangeWindowEventMask(
        ButtonPressMask | ButtonReleaseMask,
        __glutCurrentWindow->buttonUses > 0);
    }
  } else {
    if (mouseFunc) {
      /* Previously no mouseFunc, new one being installed. */
      __glutCurrentWindow->buttonUses++;
      __glutChangeWindowEventMask(
        ButtonPressMask | ButtonReleaseMask, True);
    }
  }
  __glutCurrentWindow->mouse = mouseFunc;
}

void
glutMotionFunc(GLUTmotionCB motionFunc)
{
  /* Hack.  Some window managers (4Dwm by default) will mask
     motion events if the client is not selecting for button
     press and release events. So we select for press and
     release events too (being careful to use reference
     counting).  */
  if (__glutCurrentWindow->motion) {
    if (!motionFunc) {
      /* previous mouseFunc being disabled */
      __glutCurrentWindow->buttonUses--;
      __glutChangeWindowEventMask(
        ButtonPressMask | ButtonReleaseMask,
        __glutCurrentWindow->buttonUses > 0);
    }
  } else {
    if (motionFunc) {
      /* Previously no mouseFunc, new one being installed. */
      __glutCurrentWindow->buttonUses++;
      __glutChangeWindowEventMask(
        ButtonPressMask | ButtonReleaseMask, True);
    }
  }
  /* Real work of selecting for passive mouse motion.  */
  __glutChangeWindowEventMask(
    Button1MotionMask | Button2MotionMask | Button3MotionMask,
    motionFunc != NULL);
  __glutCurrentWindow->motion = motionFunc;
}

void
glutPassiveMotionFunc(GLUTpassiveCB passiveMotionFunc)
{
  __glutChangeWindowEventMask(PointerMotionMask,
    passiveMotionFunc != NULL);

  /* Passive motion also requires watching enters and leaves so
     that a fake passive motion event can be generated on an
     enter. */
  __glutChangeWindowEventMask(EnterWindowMask | LeaveWindowMask,
    __glutCurrentWindow->entry != NULL || passiveMotionFunc != NULL);

  __glutCurrentWindow->passive = passiveMotionFunc;
}

void
glutEntryFunc(GLUTentryCB entryFunc)
{
  __glutChangeWindowEventMask(EnterWindowMask | LeaveWindowMask,
    entryFunc != NULL || __glutCurrentWindow->passive);
  __glutCurrentWindow->entry = entryFunc;
  if (!entryFunc) {
    __glutCurrentWindow->entryState = -1;
  }
}

void
glutWindowStatusFunc(GLUTwindowStatusCB windowStatusFunc)
{
  __glutChangeWindowEventMask(VisibilityChangeMask,
    windowStatusFunc != NULL);
  __glutCurrentWindow->windowStatus = windowStatusFunc;
  if (!windowStatusFunc) {
    /* Make state invalid. */
    __glutCurrentWindow->visState = -1;
  }
}

static void
visibilityHelper(int status)
{
  if (status == GLUT_HIDDEN || status == GLUT_FULLY_COVERED)
    __glutCurrentWindow->visibility(GLUT_NOT_VISIBLE);
  else
    __glutCurrentWindow->visibility(GLUT_VISIBLE);
}

void
glutVisibilityFunc(GLUTvisibilityCB visibilityFunc)
{
  __glutCurrentWindow->visibility = visibilityFunc;
  if (visibilityFunc)
    glutWindowStatusFunc(visibilityHelper);
  else
    glutWindowStatusFunc(NULL);
}

void
glutReshapeFunc(GLUTreshapeCB reshapeFunc)
{
  if (reshapeFunc) {
    __glutCurrentWindow->reshape = reshapeFunc;
  } else {
    __glutCurrentWindow->reshape = __glutDefaultReshape;
  }
}
