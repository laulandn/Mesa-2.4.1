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
	SIZE=25  => 2480.6 Tri/sec
	SIZE=50  => 845 Tri/sec
	SIZE=100 => 269.2 Tri/sec
	SIZE=250 => 48.26 Tri/sec
	SIZE=480 => 13.7 Tri/sec

   Mesa 2.3beta2
	SIZE=25  => 10869 Tri/sec
	SIZE=50  => 3521 Tri/sec
	SIZE=100 => 952.3 Tri/sec
	SIZE=250 => 159.7 Tri/sec
	SIZE=480 => 43.8 Tri/sec
*/

/*
Indy 4600SC@133MHz+SGI OpenGL 24bit:

	SIZE=25  => 42613 Tri/sec
	SIZE=50  => 28037 Tri/sec
	SIZE=100 => 13274 Tri/sec
	SIZE=250 => 3369 Tri/sec
	SIZE=480 => 1293 Tri/sec
*/

/*
Pentium@133Mhz+Win95+Mesa+Monster 3D:

	driver v0.1
	SIZE=25  => 42520 Tri/sec (my pentium is too slow for the M3D)
	SIZE=50  => 40760 Tri/sec
	SIZE=100 => 21668 Tri/sec
	SIZE=250 => 3870 Tri/sec
	SIZE=480 => 1286 Tri/sec

	driver v0.13
	SIZE=25  => 47021 Tri/sec (my pentium is too slow for the M3D)
	SIZE=50  => 45560 Tri/sec
	SIZE=100 => 19642 Tri/sec
	SIZE=250 => 3194 Tri/sec
	SIZE=480 => 865 Tri/sec

	driver v0.15
	SIZE=25  => 51840 Tri/sec
	SIZE=50  => 54521 Tri/sec
	SIZE=100 => 22222 Tri/sec
	SIZE=250 => 3561 Tri/sec
	SIZE=480 => 981 Tri/sec

	driver v0.16
	SIZE=25  => 66489 Tri/sec
	SIZE=50  => 64432 Tri/sec
	SIZE=100 => 22172 Tri/sec
	SIZE=250 => 3606 Tri/sec
	SIZE=480 => 981 Tri/sec

   driver v0.17
   the some v0.16 performance

  	driver v0.18
	SIZE=25  => 77054 Tri/sec
	SIZE=50  => 76660 Tri/sec
	SIZE=100 => 22113 Tri/sec
	SIZE=250 => 3588 Tri/sec
	SIZE=480 => 981 Tri/sec
*/

#define SIZE 25
#define NUM 10500

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

  if (tkInitWindow("Smooth Triangle Bench") == GL_FALSE) {
    tkQuit();
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-0.5, 639.5, 0.0, 479.5);
  glMatrixMode(GL_MODELVIEW);

  glShadeModel(GL_SMOOTH);

#ifdef FX
  glDrawBuffer(GL_FRONT);
#else
  glDrawBuffer(GL_BACK);
#endif

  glClearColor(0.0, 0.1, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  st=clock();
  glBegin(GL_TRIANGLES);
  for(y=0;y<NUM;y++)
    for(x=0;x<SIZE;x++) {
      glColor3f(0.0,1.0,0.0);
      glVertex2i(0,x);
      glColor3f(1.0,0.0,x/(float)SIZE);
      glVertex2i(SIZE-1-x,0);
      glColor3f(1.0,x/(float)SIZE,0.0);
      glVertex2i(x,SIZE-1-x);
    }
  glEnd();
  glFinish();

  et=clock();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Smooth Triangles/sec (%d/%f): %f\n",SIZE*NUM,t,(SIZE*NUM)/t);

  tkQuit();

  return 0;
}

