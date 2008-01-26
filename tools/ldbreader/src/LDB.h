
#ifndef LDB_H
#define LDB_H
    #include <vector>
    #include "LDBChunks.h"
    #include "ldbstr.h"
    #include "tools.h"
    
    class LDB
    {
    public: 
   
    // --- Methods declaration ---------------------------------------------
    private:
    void GetNextChunk(FILE * Stream); //lectra de pedasos

    std:: vector <Magicblock> heroskillChunk(int Length,FILE * Stream);   
    std:: vector <stcHero> heroChunk(int Length,FILE * Stream);//lectura de pedasos del heroe
    stcSound_effect musicChunk(int Length,FILE * Stream);
    std:: vector <stcSkill> skillChunk(int Length,FILE * Stream);//lectura de pedasos del habilidades
    std:: vector <stcItem> itemChunk(int Length,FILE * Stream);//lectura de pedasos del objetos
    std:: vector <stcEnemy_Action> mosteractionChunk(int Length,FILE * Stream);
    std:: vector <stcEnemy> mosterChunk(int Length,FILE * Stream);// lectura de monstruos

    std:: vector <stcEnemy_group_data> MonsterPartyMonsterChunk(int Length,FILE * Stream);
    stcEnemy_group_condition MonsterPartyEventconditionChunk(int Length,FILE * Stream);
    std:: vector <stcEnemy_group_event_page> MonsterPartyevent_pageChunk(int Length,FILE * Stream);

    std:: vector <stcEnemy_group> mosterpartyChunk(int Length,FILE * Stream);//lectura de party de monster
    std:: vector <stcTerrain> TerrainChunk(int Length,FILE * Stream);// informacion de los terrenos
    std:: vector <stcAttribute> AttributeChunk(int Length,FILE * Stream);// atributos
    std:: vector <stcState> StatesChunk(int Length,FILE * Stream);//estados

    std:: vector <stcAnimationTiming> AnimationTimingChunk(int Length,FILE * Stream);
    std:: vector <stcAnimationCell> FramedataChunk(int Length,FILE * Stream);
    std:: vector <stcAnimationCelldata> AnimationCelldataChunk(int Length,FILE * Stream);

    std:: vector <stcAnimated_battle> AnimationChunk(int Length,FILE * Stream);// animacion
    std:: vector <stcChipSet> TilesetChunk(int Length,FILE * Stream);// titles
    stcGlosary StringChunk(int Length,FILE * Stream);
    stcSystem SystemChunk(int Length,FILE * Stream);
    std:: vector <stcEvent> EventChunk(int Length,FILE * Stream);// eventos
    std:: vector <std::string> Switch_VariableChunk(int Length,FILE * Stream);// nombres de variables y swiches
    void Comand_Chunk(int Length,FILE * Stream);// comandos de combate
    void Comand_Chunk2(int Length,FILE * Stream);
    std:: vector <stcProfetion> Profession_Chunk(int Length,FILE * Stream);
    std:: vector <stcFight_anim> Fightanim_Chunk(int Length,FILE * Stream);
    unsigned char Void;
    tChunk ChunkInfo; // informacion del pedazo leido
    public: 
    bool Load(std::string Filename); // carga  
   
    void ShowInformation();
};

#endif
