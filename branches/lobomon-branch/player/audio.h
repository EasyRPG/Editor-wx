#ifndef AUDIO_H_
#define AUDIO_H_
class Audio {
protected:
   Mix_Music * musica;  
   Mix_Chunk * sonido;

public:
    void musicload(char* string);
    void stopmusic();
    void soundload(char* string);
    void freesound();
};
#endif 
