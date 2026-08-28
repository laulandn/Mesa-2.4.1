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
Pentium@133Mhz+Linux+Mesa+X11 (XFree 3.2) 8bit (Diamond Stealth 64 2MB VRAM):
*/

/*
Indy 4600SC@133MHz+SGI OpenGL 24bit:

  SIZE=25  =>  370.3 Tri/sec
  SIZE=50  =>  102 Tri/sec
  SIZE=100 =>  26.2 Tri/sec
  SIZE=250 =>  4.4 Tri/sec
  SIZE=400 =>  1.8 Tri/sec
*/

/*
Pentium@133Mhz+Win95+Monster 3D:

  driver v0.15
  SIZE=2   => 105540 Tri/sec 0.21 MPixel/sec
  SIZE=25  => 103896 Tri/sec 32.4 MPixel/sec
  SIZE=50  => 31331 Tri/sec 39.1 MPixel/sec
  SIZE=100 => 8571 Tri/sec 42.8 MPixel/sec
  SIZE=250 => 1209 Tri/sec 44.19 MPixel/sec
  SIZE=400 => 564.2 Tri/sec 45.19 MPixel/sec

  driver v0.16
  SIZE=2   => 121457 Tri/sec 0.24 MPixel/sec
  SIZE=25  => 106006 Tri/sec 33.12 MPixel/sec
  SIZE=50  => 31396 Tri/sec 39.24 MPixel/sec
  SIZE=100 => 8648 Tri/sec 43.24 MPixel/sec
  SIZE=250 => 1449 Tri/sec 45.28 MPixel/sec
  SIZE=400 => 564.5 Tri/sec 45.16 MPixel/sec

  driver v0.17
  the some v0.16 performance

  driver v0.18
  SIZE=2   => 133332 Tri/sec 0.26 MPixel/sec
  SIZE=25  => 103895 Tri/sec 32.46 MPixel/sec
  SIZE=50  => 31682 Tri/sec 39.60 MPixel/sec
  SIZE=100 => 8676 Tri/sec 43.38 MPixel/sec
  SIZE=250 => 1441 Tri/sec 45.03 MPixel/sec
  SIZE=400 => 560 Tri/sec 44.85 MPixel/sec
*/

#define SIZE 2.0
#define NUM 150000

#define TEXSIZE 128

int main(int ac, char **av)
{
  int x,y,z;
  clock_t st,et,dt;
  float t;
  GLubyte tex[TEXSIZE][TEXSIZE][3];
  GLenum gluerr;
  float v0[3]={320-SIZE/2,240-SIZE/2,0.0};
  float v1[3]={320+SIZE/2,240-SIZE/2,0.0};
  float v2[3]={320-SIZE/2,240+SIZE/2,0.0};
  float v3[3]={320+SIZE/2,240+SIZE/2,0.0};
  float cv0[3]={1.0,0.0,0.0};
  float cv1[3]={1.0,1.0,0.0};
  float cv2[3]={1.0,0.0,1.0};
  float cv3[3]={1.0,1.0,1.0};
  float tv0[3]={0.0,0.0};
  float tv1[3]={1.0,0.0};
  float tv2[3]={0.0,1.0};
  float tv3[3]={1.0,1.0};

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
  tkInitDisplayMode(TK_RGB|TK_DIRECT|TK_SINGLE|TK_DEPTH);

  if (tkInitWindow("Z Tex Smooth Tmesh Bench") == GL_FALSE) {
    tkQuit();
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5, 639.5, -0.5, 479.5, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);

  glShadeModel(GL_SMOOTH);
  glDrawBuffer(GL_FRONT);
  glEnable(GL_DEPTH_TEST);

  for(y=0;y<TEXSIZE;y++)
    for(x=0;x<TEXSIZE;x++) {
	  tex[x][y][0]=((x % (TEXSIZE/4)) < (TEXSIZE/8)) ? 255 : 0;
	  tex[x][y][1]=((y % (TEXSIZE/4)) < (TEXSIZE/8)) ? 255 : 0;
	  tex[x][y][2]=x;
	}

  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  if((gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TEXSIZE, TEXSIZE, GL_RGB,
	  GL_UNSIGNED_BYTE, (GLvoid *)(&tex[0][0][0])))) {
	  fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
	  exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glEnable(GL_TEXTURE_2D);

  glDepthFunc(GL_ALWAYS);

  glClearColor(0.0, 0.1, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  st=clock();
  glBegin(GL_TRIANGLE_STRIP);
  for(y=0;y<NUM;y++) {
    glColor3fv(cv0);
    glTexCoord2fv(tv0);
    glVertex3fv(v0);

    glColor3fv(cv1);
    glTexCoord2fv(tv1);
    glVertex3fv(v1);

    glColor3fv(cv2);
    glTexCoord2fv(tv2);
    glVertex3fv(v2);

    glColor3fv(cv3);
    glTexCoord2fv(tv3);
    glVertex3fv(v3);
  }
  glEnd();
  glFinish();

  et=clock();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Z Smooth Tex Tmesh/sec (%d/%f): %f\n",4*NUM-2,t,(4*NUM-2)/t);
  printf("Z Smooth Tex Tmesh MPixel Fill/sec: %f\n",((4*NUM-2)*(SIZE*SIZE/2)/(1000000.0))/t);

  tkQuit();

  return 0;
}

