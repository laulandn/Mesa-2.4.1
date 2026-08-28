/*
 * This program is in the public domain.
 * Use at your own risk.
 *
 * written by David Bucciarelli (tech.hmw@plus.it)
 *            Humanware s.r.l.
 */

#include <stdio.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gltk.h"

#ifdef WIN32
#include <windows.h>
#endif

/*
Pentium@133Mhz+Linux+Mesa+X11 8bit (Diamond Stealth 64 2MB VRAM,
MESA_BACK_BUFFER="X", MESA_RGB_VISUAL="PseudoColor 8"):

   Mesa 2.2 (You can get better results under X11 using the doublebuffer)
	167441 Pnts/sec

	Mesa 2.3beta2
	220183 Pnts/sec
*/

/*
Indy 4600SC@133MHz+SGI OpenGL 24bit:

    657534.2 Pnts/sec
*/

/*
Pentium@133Mhz+Win95+Mesa+Monster 3D:

	(my pentium is too slow for the M3D)
	driver v0.1
	218000 Pnts/sec

	driver v0.11
	244000 Pnts/sec

	driver v0.13
	273000 Pnts/sec

	driver v0.15
	245000 Pnts/sec

	driver v0.16
	320213 Pnts/sec (Booom !!!)

   driver v0.17
   the some v0.16 performance

  	driver v0.18
	422205 Pnts/sec (Booom !!!)
*/

#define NUM 6000

int main(int ac, char **av)
{
  int x,y;
  clock_t st,et,dt;
  float t;

#ifdef WIN32
  if(!SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS)) {
		fprintf(stderr,"Error setting the process class.\n");
    return 0;
  }

  if(!SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL)) {
		fprintf(stderr,"Error setting the process priority.\n");
    return 0;
  }
#endif

   tkInitPosition(0, 0, 640, 480);

#ifdef FX
   tkInitDisplayMode(TK_RGB|TK_DIRECT|TK_SINGLE);
#else
   tkInitDisplayMode(TK_RGB|TK_DIRECT|TK_DOUBLE);
#endif

   if (tkInitWindow("Point Bench") == GL_FALSE) {
      tkQuit();
   }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-0.5, 639.5, 0.0, 479.5);
  glMatrixMode(GL_MODELVIEW);

  glShadeModel(GL_FLAT);

#ifdef FX
  glDrawBuffer(GL_FRONT);
#else
  glDrawBuffer(GL_BACK);
#endif

  glDisable(GL_DEPTH_TEST);

  glClearColor(0.0, 0.1, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);

  st=clock();
  glBegin(GL_POINTS);
  for(y=0;y<NUM;y++)
    for(x=0;x<480;x++)
      glVertex2i(x,x);
  glEnd();
  glFinish();

  et=clock();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Points/sec (%d/%f): %f\n",480*NUM,t,(480*NUM)/t);

  tkQuit();

  return 0;
}
