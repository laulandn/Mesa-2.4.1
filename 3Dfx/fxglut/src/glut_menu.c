/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>


#include <GL/glut.h>
#include "glutint.h"

GLUTmenu *__glutCurrentMenu = NULL;
GLUTmenu *__glutMappedMenu;
GLUTwindow *__glutMenuWindow;
GLUTmenuItem *__glutItemSelected;

static GLUTmenu **menuList = NULL;

/* DEPRICATED, use glutMenuStatusFunc instead. */
void
glutMenuStateFunc(GLUTmenuStateCB menuStateFunc)
{
  __glutWarning("glutMenuStateFunc unsupported in full screen implementation of GLUT");
}

void
glutMenuStatusFunc(GLUTmenuStatusCB menuStatusFunc)
{
  __glutWarning("glutMenuStatusFunc unsupported in full screen implementation of GLUT");
}

int
glutCreateMenu(GLUTselectCB selectFunc)
{
  __glutWarning("glutCreateMenu unsupported in full screen implementation of GLUT");
  return 0;
}

/* CENTRY */
void
glutDestroyMenu(int menunum)
{
  __glutWarning("glutDestroyMenu unsupported in full screen implementation of GLUT");
}

int
glutGetMenu(void)
{
  if (__glutCurrentMenu) {
    return __glutCurrentMenu->id + 1;
  } else {
    return 0;
  }
}

void
glutSetMenu(int menuid)
{
  __glutWarning("glutSetMenu unsupported in full screen implementation of GLUT");
}
/* ENDCENTRY */

/* CENTRY */
void
glutAddMenuEntry(char *label, int value)
{
  __glutWarning("glutAddMenuEntry unsupported in full screen implementation of GLUT");
}

void
glutAddSubMenu(char *label, int menu)
{
  __glutWarning("glutAddSubMenu unsupported in full screen implementation of GLUT");
}

void
glutChangeToMenuEntry(int num, char *label, int value)
{
  __glutWarning("glutChangeToMenuEntry unsupported in full screen implementation of GLUT");
}

void
glutChangeToSubMenu(int num, char *label, int menu)
{
  __glutWarning("glutChangeToSubMenu unsupported in full screen implementation of GLUT");
}

void
glutRemoveMenuItem(int num)
{
  __glutWarning("glutRemoveMenuItem unsupported in full screen implementation of GLUT");
}

void
glutAttachMenu(int button)
{
  __glutWarning("glutAttachMenu unsupported in full screen implementation of GLUT");
}

void
glutDetachMenu(int button)
{
  __glutWarning("glutDetachMenu unsupported in full screen implementation of GLUT");
}
/* ENDCENTRY */

