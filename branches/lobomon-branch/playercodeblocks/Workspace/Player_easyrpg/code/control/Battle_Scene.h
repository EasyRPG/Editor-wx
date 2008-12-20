#ifndef SCENE_H_
#define SCENE_H_
typedef struct view
{
	int x;
	int y;
} View;



class Item {
protected:
   	public String name;
	public int Itindex;
public: 
  Item(String cname,int cindex)
	{Itindex=cindex;
	name=cname;	
	}

};

 
class Title_Scene: public Scene {
private:  
   int indexX,indexY;
   Sprite title;
   void action();
public: 
   void init(Audio myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();       
};

#endif 
