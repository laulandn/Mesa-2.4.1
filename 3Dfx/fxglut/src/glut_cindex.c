/* Copyright (c) Mark J. Kilgard, 1994, 1996. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <GL/glut.h>
#include "glutint.h"

GLUTcolormap *__glutColormapList = NULL;

#define CLAMP(i) ((i) > 1.0 ? 1.0 : ((i) < 0.0 ? 0.0 : (i)))

/* CENTRY */
void
glutSetColor(int ndx, GLfloat red, GLfloat green, GLfloat blue)
{
  __glutWarning("glutSetColor unsupported in full screen implementation of GLUT");
}

GLfloat
glutGetColor(int ndx, int comp)
{
  __glutWarning("glutSetColor unsupported in full screen implementation of GLUT");
}
/* ENDCENTRY */

void
__glutFreeColormap(GLUTcolormap * cmap)
{
}

/* CENTRY */
void
glutCopyColormap(int winnum)
{
  __glutWarning("glutCopyColormap unsupported in full screen implementation of GLUT");
}
/* ENDCENTRY */
