#include <stdio.h>
#include "glut.h"


int glutEnterGameMode()
{
  fprintf(stderr,"glutEnterGameMode...not implemented\n"); fflush(stderr);
  return 0;
}


void glutLeaveGameMode()
{
  fprintf(stderr,"glutLeaveGameMode...not implemented\n"); fflush(stderr);
}


void glutGameModeString(const char *str)
{
  fprintf(stderr,"glutGameModeString...not implemented\n"); fflush(stderr);
}


void glutKeyboardUpFunc(void (*func)(unsigned char key, int x, int y))
{
  glutKeyboardFunc(func);
}


void glutSpecialUpFunc(void (*func)(int key, int x, int y))
{
  glutSpecialFunc(func);
}


void glutJoystickFunc(void (*func)(unsigned int buttonMask, int x, int y, int z), int pollInterval)
{
  fprintf(stderr,"glutJoystickFunc...not implemented\n"); fflush(stderr);
}
