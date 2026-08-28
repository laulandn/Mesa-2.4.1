/* Copyright (c) Mark J. Kilgard, 1994.  */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#ifdef unix
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>  /* for XA_STRING atom */
#endif

#include <GL/glut.h>
#include "glutint.h"

/* CENTRY */
void
glutSetWindowTitle(char *title)
{
	SetWindowText( __glutCurrentWindow->win, title );
}

void
glutSetIconTitle(char *title)
{
	SetWindowText( __glutCurrentWindow->win, title );
}

void
glutPositionWindow(int x, int y)
{
  __glutWarning("glutPositionWindow unsupported in full screen implementation of GLUT");
}

void
glutReshapeWindow(int w, int h)
{
  __glutWarning("glutReshapeWindow unsupported in full screen implementation of GLUT");
}

void
glutPopWindow(void)
{
  __glutWarning("glutPopWindow unsupported in full screen implementation of GLUT");
}

void
glutPushWindow(void)
{
  __glutWarning("glutPushWindow unsupported in full screen implementation of GLUT");
}

void
glutIconifyWindow(void)
{
  __glutWarning("glutIconifyWindow unsupported in full screen implementation of GLUT");
}

void
glutShowWindow(void)
{
  __glutWarning("glutShowWindow unsupported in full screen implementation of GLUT");
}

void
glutHideWindow(void)
{
  __glutWarning("glutHideWindow unsupported in full screen implementation of GLUT");
}

/* ENDCENTRY */
