#ifndef __XLIBTOWIN32_H__
#define __XLIBTOWIN32_H__

#include <windows.h>

typedef HWND Window;
typedef unsigned long Colormap;
typedef unsigned long Atom;
typedef HGLRC GLXContext;
typedef PIXELFORMATDESCRIPTOR XVisualInfo;
typedef void Display;
typedef HCURSOR Cursor;
typedef void XDevice;

#define XFree(a) free((a))

/*
 *	Excerpts from various X11 include files
 */

#define Bool int
#define Status int
#define True 1
#define False 0
#define None                 0L     /* universal null resource or null atom */

/* definitions for initial window state */
#define WithdrawnState 0	/* for windows that are not mapped */
#define NormalState 1	/* most applications want to start this way */
#define IconicState 3	/* application wants to start as an icon */

/* ConfigureWindow structure */

#define CWX			(1<<0)
#define CWY			(1<<1)
#define CWWidth			(1<<2)
#define CWHeight		(1<<3)
#define CWBorderWidth		(1<<4)
#define CWSibling		(1<<5)
#define CWStackMode		(1<<6)

/* Window stacking method (in configureWindow) */

#define Above                   0
#define Below                   1
#define TopIf                   2
#define BottomIf                3
#define Opposite                4

/* 
 * Bitmask returned by XParseGeometry().  Each bit tells if the corresponding
 * value (x, y, width, height) was found in the parsed string.
 */
#define NoValue		0x0000
#define XValue  	0x0001
#define YValue		0x0002
#define WidthValue  	0x0004
#define HeightValue  	0x0008
#define AllValues 	0x000F
#define XNegative 	0x0010
#define YNegative 	0x0020

/*
 * The next block of definitions are for window manager properties that
 * clients and applications use for communication.
 */

/* flags argument in size hints */
#define USPosition	(1L << 0) /* user specified x, y */
#define USSize		(1L << 1) /* user specified width, height */

#define NoEventMask			0L
#define KeyPressMask			(1L<<0)  
#define KeyReleaseMask			(1L<<1)  
#define ButtonPressMask			(1L<<2)  
#define ButtonReleaseMask		(1L<<3)  
#define EnterWindowMask			(1L<<4)  
#define LeaveWindowMask			(1L<<5)  
#define PointerMotionMask		(1L<<6)  
#define PointerMotionHintMask		(1L<<7)  
#define Button1MotionMask		(1L<<8)  
#define Button2MotionMask		(1L<<9)  
#define Button3MotionMask		(1L<<10) 
#define Button4MotionMask		(1L<<11) 
#define Button5MotionMask		(1L<<12) 
#define ButtonMotionMask		(1L<<13) 
#define KeymapStateMask			(1L<<14)
#define ExposureMask			(1L<<15) 
#define VisibilityChangeMask		(1L<<16) 
#define StructureNotifyMask		(1L<<17) 
#define ResizeRedirectMask		(1L<<18) 
#define SubstructureNotifyMask		(1L<<19) 
#define SubstructureRedirectMask	(1L<<20) 
#define FocusChangeMask			(1L<<21) 
#define PropertyChangeMask		(1L<<22) 
#define ColormapChangeMask		(1L<<23) 
#define OwnerGrabButtonMask		(1L<<24) 

#define DisplayWidth( a, b ) GetSystemMetrics( SM_CXSCREEN )
#define DisplayHeight( a, b ) GetSystemMetrics( SM_CYSCREEN )

#define ShiftMask               (1<<0)
#define LockMask                (1<<1)
#define ControlMask             (1<<2)
#define Mod1Mask                (1<<3)
#define AltMask                (1<<3)

typedef struct {
    long flags;	/* marks which fields in this structure are defined */
	int x, y;		/* obsolete for new window mgrs, but clients */
	int width, height;	/* should set so old wm's don't mess up */
} XSizeHints;

#define XC_arrow				IDC_SIZEALL		/* GLUT_CURSOR_RIGHT_ARROW */
#define XC_top_left_arrow		IDC_ARROW		/* GLUT_CURSOR_LEFT_ARROW */
#define XC_hand1				IDC_SIZEALL		/* GLUT_CURSOR_INFO */
#define XC_pirate				IDC_NO			/* GLUT_CURSOR_DESTROY */
#define XC_question_arrow		IDC_SIZEALL		/* GLUT_CURSOR_HELP */
#define XC_exchange				IDC_NO			/* GLUT_CURSOR_CYCLE */
#define XC_spraycan				IDC_SIZEALL		/* GLUT_CURSOR_SPRAY */
#define XC_watch				IDC_WAIT		/* GLUT_CURSOR_WAIT */
#define XC_xterm				IDC_IBEAM		/* GLUT_CURSOR_TEXT */
#define XC_crosshair			IDC_CROSS		/* GLUT_CURSOR_CROSSHAIR */
#define XC_sb_v_double_arrow	IDC_SIZENS		/* GLUT_CURSOR_UP_DOWN */
#define XC_sb_h_double_arrow	IDC_SIZEWE		/* GLUT_CURSOR_LEFT_RIGHT */
#define XC_top_side				IDC_UPARROW		/* GLUT_CURSOR_TOP_SIDE */
#define XC_bottom_side			IDC_SIZENS		/* GLUT_CURSOR_BOTTOM_SIDE */
#define XC_left_side			IDC_SIZEWE		/* GLUT_CURSOR_LEFT_SIDE */
#define XC_right_side			IDC_SIZEWE		/* GLUT_CURSOR_RIGHT_SIDE */
#define XC_top_left_corner		IDC_SIZENWSE	/* GLUT_CURSOR_TOP_LEFT_CORNER */
#define XC_top_right_corner		IDC_SIZENESW	/* GLUT_CURSOR_TOP_RIGHT_CORNER */
#define XC_bottom_right_corner	IDC_SIZENWSE	/* GLUT_CURSOR_BOTTOM_RIGHT_CORNER */
#define XC_bottom_left_corner	IDC_SIZENESW	/* GLUT_CURSOR_BOTTOM_LEFT_CORNER */

void gettimeofday( struct timeval *);
#endif /* !__XLIBTOWIN32_H__! */

