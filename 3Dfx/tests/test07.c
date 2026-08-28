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
#include "gltk.h"

#ifdef WIN32
#include <windows.h>
#endif

/*
Pentium@133Mhz+Win95+Monster 3D:

    v0.16 (Glide 2.2+Mesa 2.2)
    SIZE=10  => 5.37 MPixel/sec
    SIZE=100 => 8.71 MPixel/sec

    v0.16 (Glide 2.3beta1+Mesa 2.3)
    SIZE=10  => 3.3 MPixel/sec
    SIZE=100 => 7.5 MPixel/sec

    v0.17
    SIZE=10  => 4.9 MPixel/sec
    SIZE=100 => 12.5 MPixel/sec

*/

/*
Pentium@133Mhz+Linux+Mesa+X11 8bit (Diamond Stealth 64 2MB VRAM,
MESA_BACK_BUFFER="X", MESA_RGB_VISUAL="PseudoColor 8"):

    Mesa 2.3beta2
    SIZE=10  => 1.8 MPixel/sec (!?!?)
    SIZE=100 => 2.1 MPixel/sec (!?!?)
*/

/*
Indy 4600SC@133MHz+SGI OpenGL 24bit:
*/

/*must not be a power of 2 */
#define SIZE 100
#define NUM 10000

int main(int ac, char **av)
{
  int x,y;
  GLubyte bitmap[(SIZE/8+1)*SIZE];
  clock_t st,et,dt;
  float t;

  for(y=0;y<SIZE;y++)
    for(x=0;x<SIZE/8+1;x++)
      bitmap[y*(SIZE/8+1)+x]=(y % 2)*0xff;
  
  tkInitPosition(0, 0, 640, 480);

#ifdef FX
   tkInitDisplayMode(TK_RGB|TK_DIRECT|TK_SINGLE);
#else
   tkInitDisplayMode(TK_RGB|TK_DIRECT|TK_DOUBLE);
#endif

  if (tkInitWindow("Bitmap Bench") == GL_FALSE) {
    tkQuit();
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5, 639.5, -0.5, 479.5, -1.0, 1.0);

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

  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glColor3f(1.0,0.5,0.1);

  st=clock();
  glRasterPos2i(10,20);
  for(x=0;x<NUM;x++)
    glBitmap(SIZE,SIZE,0,0,0,0,&bitmap[0]);
  glFinish();
  et=clock();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Bitmap MPixel/sec (%d/1000000*%f): %f\n",NUM*SIZE*SIZE,t,(NUM*SIZE*SIZE)/(1000000*t));

  tkQuit();

  return 0;
}

