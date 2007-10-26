#ifndef FONT_H_
#define FONT_H_

class Font{
protected:
          int size;
          int fR,  fG,  fB;
          char * Fname;
public:
      void init_Font();
      SDL_Surface* drawText(char* string);
      SDL_Surface* drawText(char* string,int r, int b,int g);
      SDL_Surface* drawText(const char* string);
      void Quit();

};

#endif 
