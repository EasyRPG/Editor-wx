/**
	@file
	@brief		RPG_RT.ldb(LcfDataBase)を管理するクラス
	@author		sue445
*/
#ifndef _INC_CRPGLDB
#define _INC_CRPGLDB

#include "CRpgIOBase.h"

/// RPG_RT.ldb(LcfDataBase)を管理するクラス
class CRpgLdb : public CRpgIOBase{
private:
   const char* GetHeader(){ return "LcfDataBase"; }	///< ファイルごとの固有ヘッダ(CRpgIOBaseからオーバーライドして使います)

public:

	struct Hero{//casi completo
		string strName;		  ///< 0x01
		string strTitle  ;	  ///< 0x02
		string strCharaname;  ///< 0x03
		int  intPos; 	      ///< 0x04
		bool bltraslucid;     ///< 0x05
		int  intInitlevel;    ///< 0x07
		int  intMaxlevel;     ///< 0x08
		bool blKnock;         ///< 0x09
		int  intKnock;        ///< 0x0A
		string strFacename;  ///<  0x0F
		int  intFacePos; 	  ///< 0x10
		bool bl2weapons;      ///< 0x15
		bool blEquip;         ///< 0x16
		bool blAIcontrol;     ///< 0x17
		bool blPowDef;        ///< 0x18
		int  intExpCbasic;    ///< 0x29
		int  intExpCincre;    ///< 0x2A
		int  intExpCorrec;    ///< 0x2B
		bool blComandBT;      ///< 0x42
		string strComandBT;   ///< 0x43
		int intEfec1;          ///< 0x47
		int intEfec2;          ///< 0x48
		int intEfec3;          ///< 0x49
		int intEfec4;          ///< 0x4A
	};
	struct Skill{
		string strName;		///< 0x01
		string strDescription;		///< 0x02
	};
	struct Item{
		string strName;		///< 0x01
		string strDescription;		///< 0x02
	};
	struct Enemy{//casi completo
		string strName;		///< 0x01
		string strGraphics;		///< 0x02
		int intHue; ///< 0x03
		int intMaxHP;  ///< 0x04
		int intMaxMP;  ///< 0x05
		int intAttack; ///< 0x06
		int intDefense; ///< 0x07
		int intSpirit; ///< 0x08
		int intSpeed; ///< 0x09
		bool blTraslucid; ///< 0x0A
		int intExperience; ///< 0xB
		int intMoney ;  ///< 0x0C
		int intItem;    ///< 0x0D
		int intItemrate;  ///< 0x0E
		bool blKnockdown; ///< 0x15 
		int intKnockdownprob;///< 0x16 
		bool blTipicalFail; ///< 0x1A 
		bool blFly;         ///< 0x1C 
		int  intStateeffec; ///< 0x1F
		//char
		int  intAtributeffec;///< 0x21
		//char
		//patrones de ataque
	};
	struct Enemy_group{//casi completo
		string strName;		///< 0x01
		//< 0x02 array 2 dim enemylist
		int intEmegepos; //< 0 x04
		bool blEmegepos;
	};

	struct Terrain{ //completo para el 2000
		string strName;		///< 0x01
		int intdamnge;      ///< 0x02
		int intFrec;        ///< 0x03
		string strBackgrnName;	///< 0x04	
		bool blLship;///< 0x05
		bool blShip;///< 0x06
		bool blAirship;///< 0x07
		bool blAirshipLand;///< 0x09
		int Charatras;///< 0x0B
		
	};
	struct Attribute{//completo
		string strName;		///< 0x01
		int intType;///< 0x2
		int intTEa;///< 0xB
		int intTEb;///< 0xC
		int intTEc;///< 0xD
		int intTEd;///< 0xE
		int intTEe;///< 0xF
	};
	struct State{//casi completo
		string strName;		///< 0x01
		int intType;///< 0x02
		int intColor;///< 0x03
        int intPriority;///< 0x04
        int intAtckrest;///< 0x05
        int intIndA;///< 0x0B
        int intIndB;///< 0x0C
        int intIndC;///< 0x0D
        int intIndD;///< 0x0E
        int intIndE;///< 0x0F
        int intNHealminD;///< 0x15       	
        int intNHealCh;///< 0x16     
        int intShockCh;///< 0x17  
        bool blAtackforce; ///< 0x1F
        bool blDefenseforce;///< 0x20  
        bool blSpirit;///< 0x21  
        bool blSpeed;  ///< 0x22 
        int intHitchange;  ///< 0x23
        bool blUspecialskill;///< 0x29
        int intUspecialskill;///< 0x2A
        bool blUspecialskill2;///< 0x2B
        int intUspecialskill2;///< 0x2C
        string strStatemsgP;///< 0x33
        string strStatemsgE;///< 0x34
        string strStatemsgA;///< 0x35
        string strStatemsgI;///< 0x36
        string strStatemsgR;///< 0x37
        
	};
	struct Fight_anim{
		string strName;		///< 0x01
/*0x01		Name
0x02		Animation file
0x06	M	Timing data
0x09		Apply to
0x0A		Y coordinate line
0x0C	M	Frame data*/

	};
		struct ChipSet{
		string strName;		///< 0x01
		string strFile;		///< 0x02
/*	falta por analizar	
Lower tile terrain	All 1	Array of 16-bit values for terrain data
Lower tile passable		Arrays of 8-bit values for pass data (0x01-down 0x02-left 0x04-right 0x08-up). 0x00 is impassable.
Upper tile passable		0x10: Draw above player. 0x02: Roof tile (only upper edge is passable). 0x04: Counter (activate events across).
Water animation	0	0->ABCBABCB, ABCABC
Animation speed	0	0->Slow, Fast
*/
	};
	struct Glosary{
/* //todas son cadenas
0x01		Enemy encounter
0x02		Headstart attack
0x03		Escape success
0x04		Escape failure
0x05		Battle victory
0x06		Battle defeat
0x07		Experience received
0x08		Money recieved A
0x09		Money recieved B
0x0A		Item recieved
0x0B		Attack message
0x0C		Ally critical hit
0x0D		Enemy critical hit
0x0E		Defend message
0x0F		Watch message
0x10		Gathering energy
0x11		Sacrificial attack
0x12		Enemy escape
0x13		Enemy transform
0x14		Enemy damaged
0x15		Enemy undamaged
0x16		Ally damaged
0x17		Ally undamaged
0x18		Skill failure A
0x19		Skill failure B
0x1A		Skill failure C
0x1B		Attack dodged
0x1C		Item use
0x1D		Stat recovery
0x1E		Stat increase
0x1F		Stat decrease
0x20		Ally lost via absorb
0x21		Enemy lost via absorb
0x22		Resistance increase
0x23		Resistance decrease
0x24		Level up message
0x25		Skill learned
0x29		Shop greeting A
0x2A		Shop regreeting A
0x2B		Buy message A
0x2C		Sell message A
0x2D		Leave message A
0x2E		Buying message A
0x2F		Quantity to buy A
0x30		Purchase end A
0x31		Selling message A
0x32		Quantity to sell A
0x33		Selling end A
0x36		Shop greeting A
0x37		Shop regreeting A
0x38		Buy message A
0x39		Sell message A
0x3A		Leave message A
0x3B		Buying message A
0x3C		Quantity to buy A
0x3D		Purchase end A
0x3E		Selling message A
0x3F		Quantity to sell A
0x40		Selling end A
0x43		Shop greeting A
0x44		Shop regreeting A
0x45		Buy message A
0x46		Sell message A
0x47		Leave message A
0x48		Buying message A
0x49		Quantity to buy A
0x4A		Purchase end A
0x4B		Selling message A
0x4C		Quantity to sell A
0x4D		Selling end A
0x50		Inn A Greeting A
0x51		Inn A Greeting B
0x52		Inn A Greeting C
0x53		Inn A Accept
0x54		Inn A Cancel
0x55		Inn B Greeting A
0x56		Inn B Greeting B
0x57		Inn B Greeting C
0x58		Inn B Accept
0x59		Inn B Cancel
0x5C		Loose items
0x5D		Equipped items
0x5F		Monetary Unit
0x65		Combat: Command
0x66		Combat: Auto
0x67		Combat: Run
0x68		Command: Attack
0x69		Command: Defend
0x6A		Command: Item
0x6B		Command: Skill
0x6C		Menu: Equipment
0x6E		Menu: Save
0x70		Menu: Quit
0x72		New Game
0x73		Load Game
0x75		Exit to Windows
0x7B		Level
0x7C		Health
0x7D		Mana
0x7E		"Normal" status
0x7F		Experience (short)
0x80		Level (short)
0x81		Health (short)
0x82		Mana (short)
0x83		Mana cost
0x84		Attack
0x8		Defense
0x86		Mind
0x87		Agility
0x88		Weapon
0x89		Shield
0x8A		Armor
0x8B		Helmet
0x8C		Accessory
0x92		Save game message
0x93		Load game message
0x94		Exit game message
0x97		File name
0x98		General Yes
0x99		General No
*/
    };
    
struct System{    
/*//sistema
0x0A    
0x0B		Skiff graphic //string
0x0C		Boat graphic //string
0x0D		Airship graphic//string
0x0E		Skiff index  //entero
0x0F		Boat index//entero
0x10		Airship index//entero
0x11		Title graphic //string
0x12		Game Over graphic //string	
0x13		System graphic	//string
0x15		Heroes in starting	1//entero
0x16		Starting party	//entero
0x1F	G	Title music	//string
0x20	G	Battle music	//string
0x21	G	Battle end music //string	
0x22	G	Inn music	//string
0x23	G	Skiff music	//string
0x24	G	Boat music	//string
0x25	G	Airship music //string	
0x26	G	Game Over music	//string
0x29	G	Cursor SFX	//string
0x2A	G	Accept SFX	//string
0x2B	G	Cancel SFX	//string
0x2C	G	Illegal SFX	//string
0x2D	G	Battle SFX //string
0x2E	G	Escape SFX //string
0x2F	G	Enemy attack SFX //string
0x30	G	Enemy damaged SFX //string
0x31	G	Ally damaged SFX //string
0x32	G	Evasion SFX //string
0x33	G	Enemy dead SFX //string
0x34	G	Item use SFX //string
0x3D		Map exit transition//entero
0x3E		Map enter transition//entero
0x3F		Battle start fadeout//entero
0x40		Battle start fadein//entero
0x41		Battle end fadeout//entero
0x42		Battle end fadein//entero
0x47		//entero
0x48		//entero
0x51		Selected condition//entero
0x52		Selected hero//entero
0x54		Battle test BG //string
0x55	M	Battle test data //array
0x5B		//entero
0x60  //entero
0x61//entero
0x63//entero
*/
  };	
	struct Event{//casi completo
		string strName;		///< 0x01
		int intStcondition;///< 0x0B
		bool blswitch;///< 0x0C
		int intswitch;///< 0xD
		int dtsize;///< 0x15
		//event data /< 0x16
	};	
	smart_array< ChipSet >	saChipSet;//yo usaria vector
	smart_array< Hero >	saHero;
	smart_array< Skill > saSkill;
	smart_array< Item > saItem;
	smart_array< Enemy > saEnemy;
    smart_array< Enemy_group > saEnemy_group;
	smart_array< Terrain > saTerrain;
	smart_array< Attribute > saAttribute;
	smart_array< State > saState;
	smart_array< Fight_anim > saFight_anim;
	smart_array< Event > saEvent;
    smart_array< string > saSwitch;//solo strings
    smart_array< string > saVariable;//solo strings


public:
	CRpgLdb(){}								///< コンストラクタ
	~CRpgLdb(){}							///< デストラクタ

	bool Init(const char* szDir="");		///< 初期化
};


#endif
