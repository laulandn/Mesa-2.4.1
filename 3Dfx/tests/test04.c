/*
 * This program is in the public domain.
 * Use at your own risk.
 *
 * written by David Bucciarelli (tech.hmw@plus.it)
 *            Humanware s.r.l.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <gltk.h>

#ifdef WIN32
#include <windows.h>
#endif

/*
Pentium@133Mhz+Linux+Mesa+X11 8bit (Diamond Stealth 64 2MB VRAM,
MESA_BACK_BUFFER="X", MESA_RGB_VISUAL="PseudoColor 8"):

   Mesa 2.2 (You can get better results under X11 using the doublebuffer)
	SIZE=25  => 2102 Tri/sec
	SIZE=50  => 691.8 Tri/sec
	SIZE=100 => 222 Tri/sec
	SIZE=250 => 44.8 Tri/sec
	SIZE=480 => 12.3 Tri/sec

   Mesa 2.3beta2
	SIZE=25  => 10851 Tri/sec
	SIZE=50  => 3496 Tri/sec
	SIZE=100 => 958 Tri/sec
	SIZE=250 => 159.7 Tri/sec
	SIZE=480 => 43.6 Tri/sec
*/

/*
PentiumPro@200MHz+Linux+Mesa2.2+X11 (XFree 3.2) (Joe Waters):

   Mesa 2.2 (You can get better results under X11 using the doublebuffer)
	SIZE=480 => 45 Tri/sec
*/

/*
Indy 4600SC@133MHz+SGI OpenGL 24bit:

	SIZE=25  => 31531 Tri/sec
	SIZE=50  => 13888 Tri/sec
	SIZE=100 => 4545 Tri/sec
	SIZE=250 => 757 Tri/sec
	SIZE=480 => 186 Tri/sec
*/

/*
Pentium@133Mhz+Win95+Monster 3D:

	driver v0.1
	SIZE=25  => 40200 Tri/sec
	SIZE=50  => 36900 Tri/sec
	SIZE=100 => 16700 Tri/sec
	SIZE=250 => 2990 Tri/sec
	SIZE=480 => 928 Tri/sec

   driver v0.11
	SIZE=25  => 50600 Tri/sec
	SIZE=50  => 48000 Tri/sec
	SIZE=100 => 17094 Tri/sec
	SIZE=250 => 2814 Tri/sec (?)
	SIZE=480 => 771 Tri/sec (?)

   driver v0.13
	SIZE=25  => 48449 Tri/sec
	SIZE=50  => 49549 Tri/sec
	SIZE=100 => 15406 Tri/sec
	SIZE=250 => 2463 Tri/sec
	SIZE=480 => 677 Tri/sec

   driver v0.15
	SIZE=25  => 47348 Tri/sec
	SIZE=50  => 48926 Tri/sec
	SIZE=100 => 17777 Tri/sec
	SIZE=250 => 2840 Tri/sec
	SIZE=480 => 785 Tri/sec

   driver v0.16
	SIZE=25  => 57703 Tri/sec
	SIZE=50  => 59280 Tri/sec
	SIZE=100 => 17796 Tri/sec
	SIZE=250 => 2862 Tri/sec
	SIZE=480 => 784 Tri/sec

   driver v0.17
   SIZE=25  => 63133 Tri/sec
	SIZE=50  => 62893 Tri/sec
	SIZE=100 => 22222 Tri/sec
	SIZE=250 => 3571 Tri/sec
	SIZE=480 => 981 Tri/sec

   driver v0.18
   SIZE=25  => 74349 Tri/sec
	SIZE=50  => 74152 Tri/sec
	SIZE=100 => 22189 Tri/sec
	SIZE=250 => 3558 Tri/sec
	SIZE=480 => 981 Tri/sec
*/

#define SIZE 25
#define NUM 8000

int main(int ac, char **av)
{
  int x,y,z;
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

  if (tkInitWindow("Z Smooth Triangle Bench") == GL_FALSE) {
    tkQuit();
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5, 639.5, 0.0, 479.5, 1.0, -(float)NUM*SIZE);
  glMatrixMode(GL_MODELVIEW);

  glShadeModel(GL_SMOOTH);

#ifdef FX
  glDrawBuffer(GL_FRONT);
#else
  glDrawBuffer(GL_BACK);
#endif

  glEnable(GL_DEPTH_TEST);

  glClearColor(0.0, 0.1, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

/*  glDepthFunc(GL_ALWAYS);*/

  st=clock();
  glBegin(GL_TRIANGLES);
  for(y=0;y<NUM;y++)
    for(x=0;x<SIZE;x++) {
      z=NUM*SIZE-(y*SIZE+x);
      glColor3f(0.0,1.0,0.0);
      glVertex3i(0,x,z);

      glColor3f(1.0,0.0,x/(float)SIZE);
      glVertex3i(SIZE-1-x,0,z);

      glColor3f(1.0,x/(float)SIZE,0.0);
      glVertex3i(x,SIZE-1-x,z);
    }
  glEnd();
  glFinish();

  et=clock();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Z Smooth Triangles/sec (%d/%f): %f\n",SIZE*NUM,t,(SIZE*NUM)/t);

  tkQuit();

  return 0;
}

