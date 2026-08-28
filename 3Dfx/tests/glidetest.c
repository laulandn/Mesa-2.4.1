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

#include <glide.h>

/*
Pentium@133Mhz+Win95+Monster 3D:

  Glide v2.3
	SIZE=2   => 439753 Tri/sec 0.8 MPixel/sec
  SIZE=25  => 99750 Tri/sec 31.1 MPixel/sec
  SIZE=50  => 31446 Tri/sec 39.3 MPixel/sec
  SIZE=100 => 8756 Tri/sec 43.7 MPixel/sec
  SIZE=250 => 1445 Tri/sec 45.1 MPixel/sec
  SIZE=400 => 566 Tri/sec 45.2 MPixel/sec

*/

#define SIZE 400.0
#define NUM 2500

#define TEXSIZE 128

int main(int ac, char **av)
{
	int i,x,y;
  clock_t st,et,dt;
  float t;
	unsigned short r,g,b;
  unsigned short tex[TEXSIZE*TEXSIZE],*texcpy;
  float v0[3]={320-SIZE/2,240-SIZE/2,1.0};
  float v1[3]={320+SIZE/2,240-SIZE/2,1.0};
  float v2[3]={320-SIZE/2,240+SIZE/2,1.0};
  float v3[3]={320+SIZE/2,240+SIZE/2,1.0};
  float cv0[3]={1.0,0.0,0.0};
  float cv1[3]={1.0,1.0,0.0};
  float cv2[3]={1.0,0.0,1.0};
  float cv3[3]={1.0,1.0,1.0};
  float tv0[3]={0.0,0.0};
  float tv1[3]={1.0,0.0};
  float tv2[3]={0.0,1.0};
  float tv3[3]={1.0,1.0};
	GrVertex gv0,gv1,gv2,gv3;
	GrMipMapId_t texid;

	grGlideInit();
  grSstSelect(0);
  grSstWinOpen(0,GR_RESOLUTION_640x480,GR_REFRESH_75Hz,GR_COLORFORMAT_ABGR,GR_ORIGIN_LOWER_LEFT,2,1);

	grAlphaBlendFunction(GR_BLEND_ONE,GR_BLEND_ZERO,GR_BLEND_ONE,GR_BLEND_ZERO);
	grAlphaTestFunction(GR_CMP_ALWAYS);
	grColorMask(FXTRUE,FXFALSE);

	guAlphaSource(GR_ALPHASOURCE_TEXTURE_ALPHA);
	guColorCombineFunction(GR_COLORCOMBINE_TEXTURE_TIMES_ITRGB);
	guTexCombineFunction(GR_TMU0,GR_TEXTURECOMBINE_DECAL);

	grDepthBufferMode(GR_DEPTHBUFFER_WBUFFER); 
	grDepthBufferFunction(GR_CMP_ALWAYS);
	grDepthMask(FXTRUE);

	grFogMode(GR_FOG_DISABLE);

	for(y=0;y<TEXSIZE;y++)
		for(x=0;x<TEXSIZE;x++) {
			r=((x % (TEXSIZE/4)) < (TEXSIZE/8)) ? 255 : 0;
	    g=((y % (TEXSIZE/4)) < (TEXSIZE/8)) ? 255 : 0;
	    b=x;

			tex[x+y*TEXSIZE]=(unsigned short)
				( ((unsigned short)0xf8 & r) <<(11-3))  |
				( ((unsigned short)0xfc & g) <<(5-3+1)) |
				( ((unsigned short)0xf8 & b) >> 3); 
		}

	texid=guTexAllocateMemory(GR_TMU0,GR_MIPMAPLEVELMASK_BOTH,TEXSIZE,TEXSIZE,
		GR_TEXFMT_RGB_565,GR_MIPMAP_NEAREST,GR_LOD_128,GR_LOD_128,GR_ASPECT_1x1,
		GR_TEXTURECLAMP_WRAP,GR_TEXTURECLAMP_WRAP,GR_TEXTUREFILTER_BILINEAR,
		GR_TEXTUREFILTER_BILINEAR,0.0,FXFALSE);

	texcpy=tex;
	guTexDownloadMipMapLevel(texid,GR_LOD_128,&texcpy);
	guTexSource(texid);

	grRenderBuffer(GR_BUFFER_FRONTBUFFER);

  grBufferClear(0x00,0,GR_WDEPTHVALUE_FARTHEST);

	gv0.x=v0[0]; gv0.y=v0[1]; gv0.z=v0[2];
	gv0.r=255.0*cv0[0]; gv0.g=255.0*cv0[1]; gv0.b=255.0*cv0[2]; gv0.a=255.0;
	gv0.oow=1.0/gv0.z;
	gv0.tmuvtx[0].sow=255.0*tv0[0]; gv0.tmuvtx[0].tow=255.0*tv0[1];

	gv1.x=v1[0]; gv1.y=v1[1]; gv1.z=v1[2];
	gv1.r=255.0*cv1[0]; gv1.g=255.0*cv1[1]; gv1.b=255.0*cv1[2]; gv1.a=255.0;
	gv1.oow=1.0/gv1.z;
	gv1.tmuvtx[0].sow=255.0*tv1[0]; gv1.tmuvtx[0].tow=255.0*tv1[1];

	gv2.x=v2[0]; gv2.y=v2[1]; gv2.z=v2[2];
	gv2.r=255.0*cv2[0]; gv2.g=255.0*cv2[1]; gv2.b=255.0*cv2[2]; gv2.a=255.0;
	gv2.oow=1.0/gv2.z;
	gv2.tmuvtx[0].sow=255.0*tv2[0]; gv2.tmuvtx[0].tow=255.0*tv2[1];

	gv3.x=v3[0]; gv3.y=v3[1]; gv3.z=v3[2];
	gv3.r=255.0*cv3[0]; gv3.g=255.0*cv3[1]; gv3.b=255.0*cv3[2]; gv3.a=255.0;
	gv3.oow=1.0/gv3.z;
	gv3.tmuvtx[0].sow=255.0*tv3[0]; gv3.tmuvtx[0].tow=255.0*tv3[1];

  st=clock();
  for(i=0;i<NUM;i++) {
		grDrawTriangle(&gv0,&gv1,&gv2);
		grDrawTriangle(&gv1,&gv2,&gv3);
  }
	grSstIdle();
  et=clock();

  grGlideShutdown();

  dt=et-st;
  t=(float)dt/(float)CLOCKS_PER_SEC;

  printf("Glide Z Smooth Tex Tri/sec (%d/%f): %f\n",2*NUM,t,(2*NUM)/t);
  printf("Glide Z Smooth Tex Tri MPixel Fill/sec: %f\n",((2*NUM)*(SIZE*SIZE/2)/(1000000.0))/t);

	return 0;
}
