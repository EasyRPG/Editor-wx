/**
	@file
	@brief		RPG_RT.ldb(LcfDataBase)を管理するクラス
	@author		sue445
*/
#include "CRpgLdb.h"

//=============================================================================
/**
	初期化

	@param	szDir			[in] 読み込み先のディレクトリ

	@retval					データベースの読み込みに成功
	@retval					データベースの読み込みに失敗
*/
//=============================================================================
bool CRpgLdb::Init(const char* szDir)
{
	int type, id, max,exa,pos;
	smart_buffer	buf;
	string			strFile;
	CRpgArray2		array2;
    CRpgArray1		array;

	bInit = false;
	if(strlen(szDir)){
		strFile += szDir;
		strFile += "\\";
	}
	strFile += "RPG_RT.ldb";

	// abre el RPG_RT.ldb 
	if(!OpenFile(strFile.c_str()))		return false;


	// mientras no lleges al dfinal del achivo
	while(!IsEof()){

		type = ReadBerNumber();
	//	 printf("\n el tipo %d",type);
		pos=GetSeek();//la psicion atees de lalectura dle buffer 
    	buf = ReadData();
		switch(type){
		case  0x0B:	//hero
	/*		array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saHero.Resize(max+1);
			for(id = 1; id<=max; id++){//faltan solo 2 arrays  
        		saHero[id].strName = array2.GetString(id, 0x01);
				saHero[id].strTitle = array2.GetString(id, 0x02);
			    saHero[id].strCharaname = array2.GetString(id, 0x03);
                saHero[id].intPos = array2.GetNumber(id, 0x04);
                saHero[id].bltraslucid = array2.GetFlag(id, 0x05);
                saHero[id].intInitlevel = array2.GetNumber(id, 0x07);
                saHero[id].intMaxlevel = array2.GetNumber(id, 0x08);
                saHero[id].blKnock = array2.GetFlag(id, 0x09);
                saHero[id].intKnock = array2.GetNumber(id, 0x0A);
                saHero[id].strFacename = array2.GetString(id, 0x0F);
                saHero[id].intFacePos = array2.GetNumber(id, 0x10);
                saHero[id].bl2weapons = array2.GetFlag(id, 0x15);
                saHero[id].blEquip = array2.GetFlag(id, 0x16);
                saHero[id].blAIcontrol = array2.GetFlag(id, 0x17);
                saHero[id].blPowDef = array2.GetFlag(id, 0x18);
                saHero[id].intExpCbasic = array2.GetNumber(id, 0x29);
                saHero[id].intExpCincre = array2.GetNumber(id, 0x2A);
                saHero[id].intExpCorrec = array2.GetNumber(id, 0x2B);
                saHero[id].blComandBT = array2.GetFlag(id, 0x42);
                saHero[id].strComandBT = array2.GetString(id, 0x43);
                saHero[id].intEfec1 = array2.GetNumber(id, 0x47);
              //  saHero[id].intEfec2 = array2.GetNumber(id, 0x48);// falta un get char
                saHero[id].intEfec3 = array2.GetNumber(id, 0x49);
               // saHero[id].intEfec4 = array2.GetNumber(id, 0x4A);	//igual
             return true;//simplificar
            }*/
			break;
		case  0x0C:	//skills
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saSkill.Resize(max+1);
			for(id = 1; id<=max; id++){
				saSkill[id].strName = array2.GetString(id, 0x01);
				saSkill[id].strDescription = array2.GetString(id, 0x02);
			}*/
			break;
		case  0x0D:	//items
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saItem.Resize(max+1);
			for(id = 1; id<=max; id++){
				saItem[id].strName = array2.GetString(id, 0x01);
				saItem[id].strDescription = array2.GetString(id, 0x02);
			}*/
			break;
		case   0x0E:	//Enemigos
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saEnemy.Resize(max+1);
			for(id = 1; id<=max; id++){
				saEnemy[id].strName = array2.GetString(id, 0x01);
				saEnemy[id].strGraphics = array2.GetString(id, 0x02);
				saEnemy[id].intHue = array2.GetNumber(id, 0x03);
				saEnemy[id].intMaxHP = array2.GetNumber(id, 0x04);
				saEnemy[id].intMaxMP = array2.GetNumber(id, 0x05);
				saEnemy[id].intAttack = array2.GetNumber(id, 0x06);
				saEnemy[id].intDefense = array2.GetNumber(id, 0x07);
				saEnemy[id].intSpirit = array2.GetNumber(id, 0x08);
				saEnemy[id].intSpeed = array2.GetNumber(id, 0x09);
                saEnemy[id].blTraslucid = array2.GetFlag(id, 0x0A);
                saEnemy[id].intExperience = array2.GetNumber(id, 0x0B);
                saEnemy[id].intMoney = array2.GetNumber(id, 0x0C);
                saEnemy[id].intItem = array2.GetNumber(id, 0x0D);
                saEnemy[id].intItemrate = array2.GetNumber(id, 0x0E);
                saEnemy[id].blKnockdown = array2.GetFlag(id, 0x15);
                saEnemy[id].intKnockdownprob = array2.GetNumber(id, 0x16);
                saEnemy[id].blTipicalFail = array2.GetFlag(id, 0x1A);
                saEnemy[id].blFly = array2.GetFlag(id, 0x1C);
                saEnemy[id].intStateeffec = array2.GetNumber(id, 0x1F);
                saEnemy[id].intAtributeffec = array2.GetNumber(id, 0x21);	
			}*/
			break;
		case    0x0F:	//Grupo Enemigos
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saEnemy_group.Resize(max+1);
			for(id = 1; id<=max; id++){
				saEnemy_group[id].strName = array2.GetString(id, 0x01);
			}*/
			break;
		case     0x10:	//Terreno
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saTerrain.Resize(max+1);
			for(id = 1; id<=max; id++){
				saTerrain[id].strName = array2.GetString(id, 0x01);
				saTerrain[id].intdamnge = array2.GetNumber(id, 0x02);
				saTerrain[id].intFrec = array2.GetNumber(id, 0x03);
				saTerrain[id].strBackgrnName = array2.GetString(id, 0x04);
				saTerrain[id].blLship = array2.GetFlag(id, 0x05);
				saTerrain[id].blShip = array2.GetFlag(id, 0x06);
				saTerrain[id].blAirship = array2.GetFlag(id, 0x07);
				saTerrain[id].blAirshipLand = array2.GetFlag(id, 0x09);
				saTerrain[id].Charatras = array2.GetNumber(id, 0x0B);
			}*/
			break;
		case     0x11:	//Atributos competo
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saAttribute.Resize(max+1);
			for(id = 1; id<=max; id++){
		 saAttribute[id].strName = array2.GetString(id, 0x01);
		 saAttribute[id].intType = array2.GetNumber(id, 0x02);		
		 saAttribute[id].intTEa = array2.GetNumber(id, 0x0B);		
         saAttribute[id].intTEb = array2.GetNumber(id, 0x0C);		
		 saAttribute[id].intTEc = array2.GetNumber(id, 0x0D);
		 saAttribute[id].intTEd = array2.GetNumber(id, 0x0E);		
		 saAttribute[id].intTEe = array2.GetNumber(id, 0x0F);
			}*/
			break;
		case      0x12:	//Estados
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saState.Resize(max+1);
			for(id = 1; id<=max; id++){
				saState[id].strName = array2.GetString(id, 0x01);
			}*/
			break;
		case      0x13:	//Animacion de batalla
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saFight_anim.Resize(max+1);
			for(id = 1; id<=max; id++){
				saFight_anim[id].strName = array2.GetString(id, 0x01);
			}*/
			break;
		case 0x14:	//chipset
			array2 = CRpgUtil::GetArray2(buf);
			/*max = array2.GetMaxRow();
			saChipSet.Resize(max+1);
			for(id = 1; id<=max; id++){
				saChipSet[id].strName = array2.GetString(id, 0x01);
				saChipSet[id].strFile = array2.GetString(id, 0x02);
			}*/
			break;
	    case 0x15:	//glosario
			//array= CRpgUtil::GetArray1(buf);
            break;
        case 0x16:	//sistema
			//array= CRpgUtil::GetArray1(buf);
            break;
		case 0x17:	//Nombre del switch ***********completo
    	/*array2 = CRpgUtil::GetArray2(buf);
    	max = array2.GetMaxRow();
    	saSwitch.Resize(max+1);
    	for(id = 1; id<=max; id++){
    	saSwitch[id]= array2.GetString(id, 0x01);}*/
		break;
		case 0x18:	//Nombre de variable *********completo
	    /*array2 = CRpgUtil::GetArray2(buf);
    	max = array2.GetMaxRow();
    	saVariable.Resize(max+1);
    	for(id = 1; id<=max; id++){
    	saVariable[id]= array2.GetString(id, 0x01);}*/
		break;
		case 0x19:	//Eventos espesiales
		/*	array2 = CRpgUtil::GetArray2(buf);
			max = array2.GetMaxRow();
			saEvent.Resize(max+1);
			for(id = 1; id<=max; id++){
			 saEvent[id].strName = array2.GetString(id, 0x01);
 	         saEvent[id].intStcondition = array2.GetNumber(id, 0x0B);
             saEvent[id].blswitch = array2.GetFlag(id, 0x0C);
		     saEvent[id].intswitch = array2.GetNumber(id, 0x0D);
		     saEvent[id].dtsize = array2.GetNumber(id, 0x15);
        	}*/
		break;
			/// Exlcusivos del rpgmaker 2003
			// eventos duplicados
			case      0x1A:	//Eventos espesiales	
			break;
			case      0x1B:	//Eventos espesiales	
			break;
			case      0x1C:	//Eventos espesiales	
			break;  

			case       0x1D:	//Comandos de combate	
			break;  			
			case       0x1E:	//Profession	
			break;  
			case       0x1F:	//Profession	
			break; 			 
            case       0x20:	// Fighting animation 2	
			break;    
			
		}
	
	
	}

	bInit = true;
	return true;
}

