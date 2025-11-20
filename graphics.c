#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

char* replaceNewlineWithEntity(const char* s)
{
  if (s == NULL) return NULL;

  size_t len = strlen(s);
  size_t new_len = 0;
  for (size_t i = 0; i < len; ++i)
  {
    if (s[i] == '\n')
    {
      new_len += 5;
      continue;
    }
    if (s[i] != '\r')
    {
      new_len += 1;
    }
  }

  char* out = (char*)malloc(new_len + 1);
  if (out == NULL) return NULL;

  char* p = out;
  for (size_t i = 0; i < len; ++i)
  {
    if (s[i] == '\n')
    {
      memcpy(p, "&#10;", 5);
      p += 5;
      continue;
    }
    if (s[i] != '\r')
    {
      *p++ = s[i];
    }
  }
  *p = '\0';
  return out;
}

void setLineWidth(int width)
{
  printf("LW %i\n", width);
}

void drawLine(int x1, int x2, int x3, int x4)
{
  printf("DL %i %i %i %i\n", x1, x2, x3, x4);
}

void drawRect(int x1, int x2, int x3, int x4)
{
  printf("DR %i %i %i %i\n", x1, x2, x3, x4);
}

void drawRectRotated(int x, int y, int width, int height, int angle)
{
  printf("DT %i %i %i %i %i\n", x, y, width, height, angle);
}

void fillRect(int x1, int x2, int x3, int x4)
{
  printf("FR %i %i %i %i\n", x1, x2, x3, x4);
}

void fillRectRotated(int x, int y, int width, int height, int angle)
{
  printf("FT %i %i %i %i %i\n", x, y, width, height, angle);
}

void drawOval(int x, int y, int width, int height)
{
  printf("DO %i %i %i %i\n",x,y,width,height);
}

void fillOval(int x, int y, int width, int height)
{
  printf("FO %i %i %i %i\n",x,y,width,height);
}

void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
  printf("DA %i %i %i %i %i %i\n",x,y,width,height, startAngle, arcAngle);
}

void fillArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
  printf("FA %i %i %i %i %i %i\n",x,y,width,height, startAngle, arcAngle);
}

void drawPolygon(int count, int x[], int y[])
{
  printf("DP ");
  printf("%d ", count);
  for (int n = 0 ; n < count ; n++)
  {
    printf("%d %d ", x[n], y[n]);
  }
  printf("\n");
}

void fillPolygon(int count, int x[], int y[])
{
  printf("FP ");
  printf("%d ", count);
  for (int n = 0 ; n < count ; n++)
  {
    printf("%d %d ", x[n], y[n]);
  }
  printf("\n");
}

void drawString(char* s, int x, int y)
{
  printf("DS %i %i @%s\n",x,y,s);
}

void drawStringRotated(char* s, int x, int y, int angle)
{
  printf("SR %i %i %i @%s\n",x,y,angle,s);
}

void setStringTextSize(int size)
{
  printf("SZ %i\n", size);
}

void displayImage(char* fileName, int x, int y)
{
  printf("DI %i %i @%s\n", x, y, fileName );
}

void setColour(colour c)
{
  char* colourName;
  switch(c)
  {
    case black : colourName = "black"; break;
    case blue : colourName = "blue"; break;
    case cyan : colourName = "cyan"; break;
    case darkgray : colourName = "darkgray"; break;
    case gray : colourName = "gray"; break;
    case green : colourName = "green"; break;
    case lightgray : colourName = "lightgray"; break;
    case magenta : colourName = "magenta"; break;
    case orange : colourName = "orange"; break;
    case pink : colourName = "pink"; break;
    case red : colourName = "red"; break;
    case white : colourName = "white"; break;
    case yellow : colourName = "yellow"; break;
  }
  printf("SC %s\n", colourName);
}

void setRGBColour(int red, int green, int blue)
{
  printf("RG %i %i %i\n", red, green, blue);
}

void clear(void)
{
  printf("CL\n");
}

void setWindowSize(int width, int height)
{
  printf("SW %i %i\n", width, height);
}

void sleep(int time)
{
  printf("SL %i\n", time);
}

void foreground(void)
{
  printf("FG\n");
}

void background(void)
{
  printf("BG\n");
}

void message(char *s)
{
  printf("MS @%s\n", replaceNewlineWithEntity(s));
}