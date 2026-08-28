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
Pentium@133Mhz+Linux+Mesa+X11 (XFree 3.2) 8bit (Diamond Stealth 64 2MB VRAM):

	SIZE=50 => 5084 Lin/sec
	SIZE=100 => 2631 Lin/sec
	SIZE=250 => 1016 Lin/sec
	SIZE=480 => 536 Lin/sec

	You can get better results under X11 using the doublebuffer.
*/

/*
Indy 4600SC@133MHz+SGI OpenGL 24bit:

	SIZE=50 => 181818 Lin/sec
	SIZE=100 => 179640 Lin/sec
	SIZE=250 => 123915 Lin/sec
	SIZE=480 => 77170 Lin/sec
*/

/*
Pentium@133Mhz+Win95+Mesa+Monster 3D:

	(my pentium is too slow for the M3D)
	driver v0.1
	SIZE=50 => 65900 Lin/sec
	SIZE=100 => 64400 Lin/sec
	SIZE=250 => 65900 Lin/sec
	SIZE=480 => 38570 Lin/sec

	driver v0.13
	SIZE=50 => 73891 Lin/sec
	SIZE=100 => 72463 Lin/sec
	SIZE=250 => 67024 Lin/sec
	SIZE=480 => 34951 Lin/sec

	driver v0.15
	SIZE=50 => 75757 Lin/sec
	SIZE=100 => 78277 Lin/sec
	SIZE=250 => 76870 Lin/sec
	SIZE=480 => 40268 Lin/sec

	driver v0.16
	SIZE=50 => 89126 Lin/sec
	SIZE=100 => 90579 Lin/sec
	SIZE=250 => 75872 Lin/sec
	SIZE=480 => 40100 Lin/sec

  	driver v0.17
	SIZE=50 => 95117 Lin/sec
	SIZE=100 => 97087 Lin/sec
	SIZE=250 => 75757 Lin/sec
	SIZE=480 => 40100 Lin/sec

  	driver v0.18
	SIZE=50 => 109549 Lin/sec
	SIZE=100 => 109717 Lin/sec
	SIZE=250 => 75910 Lin/sec
	SIZE=480 => 40268 Lin/sec
*/

#define SIZE 50
#define NUM 10000

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

  if (tkInitWindow("Smooth Line Bench") == GL_FALSE) {
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
  glDisable(GL_DEPTH_TEST);

  glClearColor(0.0, 0.1, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
    
  st=clock();
  glBegin(GL_LINES);
  for(y=0;y<NUM;y++)
    for(x=0;x<SIZE;x++) {
      glColor3f(0.0,1.0,y/(float)NUM);
      glVertex2i(0,SIZE-1);
      glColor3f(1.0,0.0,x/(float)SIZE);
      glVertex2i(x,x);
    }
  glEnd();
  glFinish();

  et=clock();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Smooth Lines/sec (%d/%f): %f\n",SIZE*NUM,t,(SIZE*NUM)/t);

  tkQuit();

  return 0;
}

