/* Copyright (c) Mark J. Kilgard, 1996.  */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <GL/glut.h>
#include "glutint.h"

/* CENTRY */
void
glutEstablishOverlay(void)
{
  __glutWarning("overlays unsupported in full screen implementation of GLUT");
}

void
glutRemoveOverlay(void)
{
  __glutWarning("overlays unsupported in full screen implementation of GLUT");
}

void
glutUseLayer(GLenum layer)
{
  GLUTwindow *window = __glutCurrentWindow;

  switch (layer) {
  case GLUT_NORMAL:
    window->renderWin = window->win;
    window->renderCtx = window->ctx;
    break;
  case GLUT_OVERLAY:
	__glutWarning("overlays unsupported in full screen implementation of GLUT");
    break;
  default:
    __glutWarning("glutUseLayer: unknown layer, %d.", layer);
    break;
  }
  __glutSetWindow(window);
}

void
glutPostOverlayRedisplay(void)
{
  __glutWarning("overlays unsupported in full screen implementation of GLUT");
}

void
glutOverlayDisplayFunc(GLUTdisplayCB displayFunc)
{
  __glutWarning("overlays unsupported in full screen implementation of GLUT");
}

void
glutHideOverlay(void)
{
  __glutWarning("overlays unsupported in full screen implementation of GLUT");
}

void
glutShowOverlay(void)
{
  __glutWarning("overlays unsupported in full screen implementation of GLUT");
}

int
glutLayerGet(GLenum param)
{
  switch (param) {
  case GLUT_OVERLAY_POSSIBLE:
    {
#ifdef unix
		XVisualInfo *vi;
      Bool dummy;

      vi = __glutDetermineVisual(__glutDisplayMode, &dummy, getOverlayVisualInfo);
      if (vi) {
        XFree(vi);
        return 1;
      }
#endif
      return 0;
    }
  case GLUT_LAYER_IN_USE:
    return __glutCurrentWindow->renderWin != __glutCurrentWindow->win;
  case GLUT_HAS_OVERLAY:
    return __glutCurrentWindow->overlay != NULL;
  case GLUT_TRANSPARENT_INDEX:
    if (__glutCurrentWindow->overlay) {
      return __glutCurrentWindow->overlay->transparentPixel;
    } else {
      return -1;
    }
  case GLUT_NORMAL_DAMAGED:
    /* __glutWindowDamaged is used so the damage state within
       the window (or overlay belwo) can be cleared before
       calling a display callback so on return, the state does
       not have to be cleared (since upon return from the
       callback the window could be destroyed (or layer
       removed). */
    return (__glutCurrentWindow->workMask & GLUT_REPAIR_WORK)
      || __glutWindowDamaged;
  case GLUT_OVERLAY_DAMAGED:
    if (__glutCurrentWindow->overlay) {
      return (__glutCurrentWindow->workMask & GLUT_OVERLAY_REPAIR_WORK)
        || __glutWindowDamaged;
    } else {
      return -1;
    }
  default:
    __glutWarning("invalid glutLayerGet param: %d", param);
    return -1;
  }
}
/* ENDCENTRY */
