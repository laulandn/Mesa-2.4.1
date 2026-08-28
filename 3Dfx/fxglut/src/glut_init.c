/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <GL/glut.h>
#include "glutint.h"

/* GLUT inter-file variables */
/* *INDENT-OFF* */
char *__glutProgramName = NULL;
int __glutArgc = 0;
char **__glutArgv = NULL;
char *__glutGeometry = NULL;
Display *__glutDisplay = NULL;
int __glutScreen;
Window __glutRoot;
int __glutScreenHeight;
int __glutScreenWidth;
GLboolean __glutIconic = GL_FALSE;
GLboolean __glutDebug = GL_FALSE;
unsigned int __glutDisplayMode =
  GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH;
int __glutConnectionFD;
XSizeHints __glutSizeHints = {0};
int __glutInitWidth = 640, __glutInitHeight = 480;
int __glutInitX = -1, __glutInitY = -1;
GLboolean __glutForceDirect = GL_FALSE,
  __glutTryDirect = GL_TRUE;
Atom __glutWMDeleteWindow;
/* *INDENT-ON* */

static Bool synchronize = False;

#if defined(__vms)
char *
strdup(const char *string)
{
  char *new;

  new = malloc(strlen(string) + 1);
  if (new == NULL)
    return NULL;
  strcpy(new, string);
  return new;
}
#endif

#ifdef WIN32
#define NeedFunctionPrototypes 1
/*
 *    XParseGeometry parses strings of the form
 *   "=<width>x<height>{+-}<xoffset>{+-}<yoffset>", where
 *   width, height, xoffset, and yoffset are unsigned integers.
 *   Example:  "=80x24+300-49"
 *   The equal sign is optional.
 *   It returns a bitmask that indicates which of the four values
 *   were actually found in the string.  For each value found,
 *   the corresponding argument is updated;  for each value
 *   not found, the corresponding argument is left unchanged. 
 */

int
ReadInteger(string, NextString)
register char *string;
char **NextString;
{
    register int Result = 0;
    int Sign = 1;
    
    if (*string == '+')
	string++;
    else if (*string == '-')
    {
	string++;
	Sign = -1;
    }
    for (; (*string >= '0') && (*string <= '9'); string++)
    {
	Result = (Result * 10) + (*string - '0');
    }
    *NextString = string;
    if (Sign >= 0)
	return (Result);
    else
	return (-Result);
}

#if NeedFunctionPrototypes
int XParseGeometry (
const char *string,
int *x,
int *y,
unsigned int *width,    /* RETURN */
unsigned int *height)    /* RETURN */
#else
int XParseGeometry (string, x, y, width, height)
char *string;
int *x, *y;
unsigned int *width, *height;    /* RETURN */
#endif
{
	int mask = NoValue;
	register char *strind;
	unsigned int tempWidth, tempHeight;
	int tempX, tempY;
	char *nextCharacter;

	if ( (string == NULL) || (*string == '\0')) return(mask);
	if (*string == '=')
		string++;  /* ignore possible '=' at beg of geometry spec */

	strind = (char *)string;
	if (*strind != '+' && *strind != '-' && *strind != 'x') {
		tempWidth = ReadInteger(strind, &nextCharacter);
		if (strind == nextCharacter) 
		    return (0);
		strind = nextCharacter;
		mask |= WidthValue;
	}

	if (*strind == 'x') {	
		strind++;
		tempHeight = ReadInteger(strind, &nextCharacter);
		if (strind == nextCharacter)
		    return (0);
		strind = nextCharacter;
		mask |= HeightValue;
	}

	if ((*strind == '+') || (*strind == '-')) {
		if (*strind == '-') {
  			strind++;
			tempX = -ReadInteger(strind, &nextCharacter);
			if (strind == nextCharacter)
			    return (0);
			strind = nextCharacter;
			mask |= XNegative;

		}
		else
		{	strind++;
			tempX = ReadInteger(strind, &nextCharacter);
			if (strind == nextCharacter)
			    return(0);
			strind = nextCharacter;
		}
		mask |= XValue;
		if ((*strind == '+') || (*strind == '-')) {
			if (*strind == '-') {
				strind++;
				tempY = -ReadInteger(strind, &nextCharacter);
				if (strind == nextCharacter)
			    	    return(0);
				strind = nextCharacter;
				mask |= YNegative;

			}
			else
			{
				strind++;
				tempY = ReadInteger(strind, &nextCharacter);
				if (strind == nextCharacter)
			    	    return(0);
				strind = nextCharacter;
			}
			mask |= YValue;
		}
	}
	
	/* If strind isn't at the end of the string the it's an invalid
		geometry specification. */

	if (*strind != '\0') return (0);

	if (mask & XValue)
	    *x = tempX;
 	if (mask & YValue)
	    *y = tempY;
	if (mask & WidthValue)
            *width = tempWidth;
	if (mask & HeightValue)
            *height = tempHeight;
	return (mask);
}
#endif

void
__glutOpenXConnection(char *display)
{
  __glutDisplay = (void *)"GLUTapp";
  __glutRoot = GetDesktopWindow();
  __glutScreenWidth = GetSystemMetrics(SM_CXSCREEN);
  __glutScreenHeight = GetSystemMetrics(SM_CXSCREEN);
}

#ifdef WIN32
static LARGE_INTEGER counterResolution;

void 
gettimeofday( struct timeval *time )
{
	LARGE_INTEGER counter;

	QueryPerformanceCounter( &counter );

	counter.QuadPart = counter.QuadPart / counterResolution.QuadPart;
	
	time->tv_sec = counter.QuadPart / 1000000;
	time->tv_usec = counter.QuadPart % 1000000;
}
#endif

void
__glutInitTime(struct timeval *beginning)
{
  static int beenhere = 0;
  static struct timeval genesis;

  if (!beenhere) {
#ifdef WIN32
	QueryPerformanceFrequency(&counterResolution);
	counterResolution.QuadPart /= 1000000;
#endif
    GETTIMEOFDAY(&genesis);
    beenhere = 1;
  }
  *beginning = genesis;
}

static void
removeArgs(int *argcp, char **argv, int numToRemove)
{
  int i, j;

  for (i = 0, j = numToRemove; argv[j]; i++, j++) {
    argv[i] = argv[j];
  }
  argv[i] = NULL;
  *argcp -= numToRemove;
}

void
glutInit(int *argcp, char **argv)
{
  char *display = NULL;
  char *str;
  struct timeval unused;
  int i;

  if (__glutDisplay) {
    __glutWarning("glutInit being called a second time.");
    return;
  }
  /* Determine temporary program name. */
  str = strrchr(argv[0], '/');
  if (str == NULL) {
    __glutProgramName = argv[0];
  } else {
    __glutProgramName = str + 1;
  }

  /* Make private copy of command line arguments. */
  __glutArgc = *argcp;
  __glutArgv = (char **) malloc(__glutArgc * sizeof(char *));
  if (!__glutArgv)
    __glutFatalError("out of memory.");
  for (i = 0; i < __glutArgc; i++) {
    __glutArgv[i] = strdup(argv[i]);
    if (!__glutArgv[i])
      __glutFatalError("out of memory.");
  }

  /* determine permanent program name */
  str = strrchr(__glutArgv[0], '/');
  if (str == NULL) {
    __glutProgramName = __glutArgv[0];
  } else {
    __glutProgramName = str + 1;
  }

  /* parse arguments for standard options */
  for (i = 1; i < __glutArgc; i++) {
    if (!strcmp(__glutArgv[i], "-display")) {
      if (++i >= __glutArgc) {
        __glutFatalError(
          "follow -display option with X display name.");
      }
#ifdef WIN32
      __glutWarning("-display option unsupported in Win32 implementation of GLUT");
#endif
      display = __glutArgv[i];
      removeArgs(argcp, &argv[1], 2);
    } else if (!strcmp(__glutArgv[i], "-geometry")) {
      int flags, x, y, width, height;

      if (++i >= __glutArgc) {
        __glutFatalError(
          "follow -geometry option with geometry parameter.");
      }
      /* Fix bogus "{width|height} may be used before set"
         warning */
      width = 0;
      height = 0;

      flags = XParseGeometry(__glutArgv[i], &x, &y,
        (unsigned int *) &width, (unsigned int *) &height);
      if (WidthValue & flags) {
        /* Careful because X does not allow zero or negative
           width windows */
        if (width > 0)
          __glutInitWidth = width;
      }
      if (HeightValue & flags) {
        /* Careful because X does not allow zero or negative
           height windows */
        if (height > 0)
          __glutInitHeight = height;
      }
      glutInitWindowSize(__glutInitWidth, __glutInitHeight);
      if (XValue & flags) {
        if (XNegative & flags)
          x = DisplayWidth(__glutDisplay, __glutScreen) +
            x - __glutSizeHints.width;
        /* Play safe: reject negative X locations */
        if (x >= 0)
          __glutInitX = x;
      }
      if (YValue & flags) {
        if (YNegative & flags)
          y = DisplayHeight(__glutDisplay, __glutScreen) +
            y - __glutSizeHints.height;
        /* Play safe: reject negative Y locations */
        if (y >= 0)
          __glutInitY = y;
      }
      glutInitWindowPosition(__glutInitX, __glutInitY);
      removeArgs(argcp, &argv[1], 2);
    } else if (!strcmp(__glutArgv[i], "-direct")) {
#ifdef WIN32
	  __glutWarning("-direct option unsupported in Win32 implementation of GLUT");
#else
      if (!__glutTryDirect)
        __glutFatalError(
          "cannot force both direct and indirect rendering.");
      __glutForceDirect = GL_TRUE;
#endif
      removeArgs(argcp, &argv[1], 1);
    } else if (!strcmp(__glutArgv[i], "-indirect")) {
#ifdef WIN32
	  __glutWarning("-indirect option unsupported in Win32 implementation of GLUT");
#else
      if (__glutForceDirect)
        __glutFatalError(
          "cannot force both direct and indirect rendering.");
      __glutTryDirect = GL_FALSE;
#endif
      removeArgs(argcp, &argv[1], 1);
    } else if (!strcmp(__glutArgv[i], "-iconic")) {
#ifdef FULL_SCREEN
	  __glutWarning("-iconic option unsupported in full screen implementation of GLUT");
#else
      __glutIconic = GL_TRUE;
#endif
      removeArgs(argcp, &argv[1], 1);
    } else if (!strcmp(__glutArgv[i], "-gldebug")) {
      __glutDebug = GL_TRUE;
      removeArgs(argcp, &argv[1], 1);
    } else if (!strcmp(__glutArgv[i], "-sync")) {
#ifdef WIN32
	__glutWarning("-sync option unsupported in Win32 implementation of GLUT");
#else
      synchronize = GL_TRUE;
#endif
      removeArgs(argcp, &argv[1], 1);
    } else {
      /* Once unknown option encountered, stop command line
         processing. */
      break;
    }
  }
  __glutOpenXConnection(display);
  __glutInitTime(&unused);

}

/* CENTRY */
void
glutInitWindowPosition(int x, int y)
{
  __glutInitX = x;
  __glutInitY = y;
  if (x >= 0 && y >= 0) {
    __glutSizeHints.x = x;
    __glutSizeHints.y = y;
    __glutSizeHints.flags |= USPosition;
  } else {
    __glutSizeHints.flags &= ~USPosition;
  }
}

void
glutInitWindowSize(int width, int height)
{
  __glutInitWidth = width;
  __glutInitHeight = height;
  if (width > 0 && height > 0) {
    __glutSizeHints.width = width;
    __glutSizeHints.height = height;
    __glutSizeHints.flags |= USSize;
  } else {
    __glutSizeHints.flags &= ~USSize;
  }
}

void
glutInitDisplayMode(unsigned int mask)
{
  __glutDisplayMode = mask;
}

/* ENDCENTRY */
