// =========================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "tools.h"
#include "LDB.h"
// =========================================================================

// --- Create list of chunks opcodes ---------------------------------------

bool LDB::Load(std::string Filename)
{
	unsigned char Void;
	tChunk ChunkInfo;
	// Open map file to read
	FILE * Stream;// apertura de archivo
	Stream = fopen(Filename.c_str(), "rb");
	std::string Header = ReadString(Stream); // lectura de cabezera
	if (Header != "LcfDataBase") // comparacion con cabezera del mapa
	{ // si no concuerda imprime un error y finaliza
		printf("Reading error: File is not a valid RPG2000 database\n");
		fclose(Stream);
		return false;
	}
	GetNextChunk(Stream);
	fclose(Stream);
	return true;
}

std::vector <Magicblock> LDB::heroskillChunk(int Length, FILE * Stream)
{
	int id,datatoread=0,datareaded=0;
	Magicblock skill;
	std::vector <Magicblock> vecSkills;
	datatoread = ReadCompressedInteger(Stream); //numero de datos
	while(datatoread>datareaded) //si no hay mas en el array
	{
		id= ReadCompressedInteger(Stream);//lectura de id 1 de array
		do
		{
			ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo
			if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño
			switch(ChunkInfo.ID)// tipo de la primera dimencion
			{
				case MagicblockChunk_Level:
					skill.Level = ReadCompressedInteger(Stream);
					printf("\n Level %d", skill.Level);
					break;
				case MagicblockChunk_Spell_ID:
					skill.Spell_ID = ReadCompressedInteger(Stream);
					printf("\n Spell_ID %d",skill.Spell_ID);
					break;
				case CHUNK_MAP_END_OF_BLOCK:
					break;
				default:
					while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
					break;
			}
		} while(ChunkInfo.ID!=0);
		vecSkills.push_back(skill);
		skill.clear();
		datareaded++;
	}
	ChunkInfo.ID=1;
	return(vecSkills);
}


std::vector <stcHero> LDB::heroChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0;
		 int levels;
		 short dat; 
		 std:: vector <stcHero> vecHero;
		 stcHero hero;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		  do{ 
			  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño									
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {	 
								  
						  case CHUNK_Name:
							   hero.strName = ReadString(Stream, ChunkInfo.Length);
							   printf("\n nombre ");	
							   printf(hero.strName.c_str());		
							   break;
						  case CHUNK_Class:
							   hero.strClass = ReadString(Stream, ChunkInfo.Length);
							   printf("\n clase ");	
							   printf(hero.strClass.c_str());		
							   break;
						  case CHUNK_Graphicfile:
							   hero.strGraphicfile = ReadString(Stream, ChunkInfo.Length);
							   printf("\n Graphicfile ");	
							   printf(hero.strGraphicfile.c_str());		
							   break;
						  case CHUNK_Graphicindex:
							   hero.intGraphicindex = ReadCompressedInteger(Stream);
							   printf("\n Graphicindex %d",hero.intGraphicindex);			
							   break;
						  case CHUNK_Transparent:
							   hero.intTransparent = ReadCompressedInteger(Stream);
							   printf("\n Transparent %d",hero.intTransparent);	 
							   break;
						  case CHUNK_Startlevel:
							   hero.intStartlevel = ReadCompressedInteger(Stream);
							   printf("\n intStartlevel %d",hero.intStartlevel);	 
							   break;
						  case CHUNK_Maxlevel:
							   hero.intMaxlevel = ReadCompressedInteger(Stream);
							   printf("\n intMaxlevel %d",hero.intMaxlevel); 
							   break;
						  case CHUNK_Crithit:
							   hero.intCrithit = ReadCompressedInteger(Stream);
							   printf("\n intCrithit %d",hero.intCrithit);	   
							   break;
						  case CHUNK_Hitchance:
							   hero.intHitchance = ReadCompressedInteger(Stream);
							   printf("\n intHitchance %d",hero.intHitchance);	  
							   break;
						  case CHUNK_Facegraphic:
							   hero.strFacegraphic = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strFacegraphic ");	
							   printf(hero.strFacegraphic.c_str());		
							   break;
						  case CHUNK_Faceindex:
							   hero.intFaceindex = ReadCompressedInteger(Stream);
							   printf("\n intFaceindex %d",hero.intFaceindex);		
							   break;
						  case CHUNK_Dualwield:
							   hero.blDualwield = ReadCompressedInteger(Stream);
							   printf("\n blDualwield %d",hero.blDualwield);		
							   break;
						  case CHUNK_Fixedequipment:
							   hero.blFixedequipment = ReadCompressedInteger(Stream);
							   printf("\n blFixedequipment %d",hero.blFixedequipment);	   
							   break;
						  case CHUNK_AI:
							   hero.blAI = ReadCompressedInteger(Stream);
							   printf("\n blAI %d",hero.blAI);		 
							   break;
						  case CHUNK_Highdefense:
							   hero.blHighdefense = ReadCompressedInteger(Stream);
							   printf("\n blHighdefense %d",hero.blHighdefense);		 
							   break;
						case CHUNK_Statisticscurves:
						levels=ChunkInfo.Length/6;
						 while(levels--) 
						 {fread(&dat, sizeof(short), 1, Stream);
						  hero.vc_sh_Hp.push_back(dat);
						 printf(" %d",dat); 
						 levels--;
						 }   
						 levels=ChunkInfo.Length/6;
						 while(levels--) 
						 {fread(&dat, sizeof(short), 1, Stream);
						  hero.vc_sh_Mp.push_back(dat);
						 printf(" %d",dat); 
						 levels--;
						 }   
						  levels=ChunkInfo.Length/6;
						 while(levels--) 
						 {fread(&dat, sizeof(short), 1, Stream);
						  hero.vc_sh_Attack.push_back(dat);
						 printf(" %d",dat); 
						 levels--;
						 }  
						  levels=ChunkInfo.Length/6;
						 while(levels--) 
						 {fread(&dat, sizeof(short), 1, Stream);
						  hero.vc_sh_Defense.push_back(dat);
						 printf(" %d",dat); 
						 levels--;
						 }  
						  levels=ChunkInfo.Length/6;
						 while(levels--) 
						 {fread(&dat, sizeof(short), 1, Stream);
						  hero.vc_sh_Mind.push_back(dat);
						 printf(" %d",dat); 
						 levels--;
						 }  
						 levels=ChunkInfo.Length/6;
						 while(levels--) 
						 {fread(&dat, sizeof(short), 1, Stream);
						  hero.vc_sh_Agility.push_back(dat);
						 printf(" %d",dat); 
						 levels--;
						 }	
						 break;
						  case CHUNK_EXPBaseline:
							   hero.intEXPBaseline = ReadCompressedInteger(Stream);
							   printf("\n intEXPBaseline %d",hero.intEXPBaseline);	 
							   break;
						  case CHUNK_EXPAdditional:
							   hero.intEXPAdditional = ReadCompressedInteger(Stream);
							   printf("\n intEXPAdditional %d",hero.intEXPAdditional);   
							   break;
						  case CHUNK_EXPCorrection:
							   hero.intEXPCorrection = ReadCompressedInteger(Stream);
							   printf("\n intEXPCorrection %d",hero.intEXPCorrection);	  
							   break;
						  case CHUNK_Startequip:
							   printf("\n CHUNK_Startequip ");	 
							   fread(&dat, sizeof(short), 1, Stream);
							   hero.sh_Weapon = dat;
							   printf("\n sh_Weapon %d",hero.sh_Weapon);   
							   fread(&dat, sizeof(short), 1, Stream);
							   hero.sh_Shield = dat;
							   printf("\n sh_Shield %d",hero.sh_Shield);  
							   fread(&dat, sizeof(short), 1, Stream);
							   hero.sh_Armor = dat;
							   printf("\n sh_Armor %d",hero.sh_Armor);  
							   fread(&dat, sizeof(short), 1, Stream);
							   hero.sh_Head = dat;
							   printf("\n sh_Head %d",hero.sh_Head);  
							   fread(&dat, sizeof(short), 1, Stream);
							   hero.sh_Accessory = dat;
							   printf("\n sh_Accessory %d",hero.sh_Accessory);  
							 break;
						  case CHUNK_Skills:
							   printf("\n CHUNK_Skills "); 
							  hero.skills=heroskillChunk(ChunkInfo.Length, Stream);
							   break; 
							  break;
						  case CHUNK_RenameMagic:
							   hero.blRenameMagic = ReadCompressedInteger(Stream);
							   printf("\n blRenameMagic %d",hero.blRenameMagic);	 
							   break;
						  case CHUNK_Magicname:
							   hero.strMagicname = ReadCompressedInteger(Stream);
							   printf("\n CHUNK_Magicname ");	
							   printf(hero.strMagicname.c_str());		
							   break;
						  case CHUNK_Condlength:
							   hero.intCondlength = ReadCompressedInteger(Stream);
							   printf("\n intCondlength %d",hero.intCondlength);		
							   break;
						  case CHUNK_Condeffects:
							   printf("\n CHUNK_Condeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								hero.vc_ch_Condeffects.push_back(Void);
								printf("%d ",Void);}
								break;
						  case CHUNK_Attriblength:
							   hero.intAttriblength = ReadCompressedInteger(Stream);
							   printf("\n intAttriblength %d",hero.intAttriblength);	   
							   break;
						  case CHUNK_Attribeffects:
							   printf("\n CHUNK_Attribeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								hero.vc_ch_Attribeffects.push_back(Void);
								printf("%d ",Void);}
								break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;			 
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			}while(ChunkInfo.ID!=0);
			vecHero.push_back(hero);
			hero.clear();
		  datareaded++;
		  }   
		  return(vecHero);
}
stcSound_effect LDB::musicChunk(int Length,FILE * Stream)
{ printf("\n musicChunk ");
stcSound_effect  stcMusic;  
  stcMusic.clear();
do   
 {	  
			ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			if(ChunkInfo.ID!=0)
			ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	
			
			switch(ChunkInfo.ID)// segun el tipo
			{   
			   case 0x01:
					 stcMusic.Name_of_Sound_effect	 = ReadString(Stream, ChunkInfo.Length); 
					printf(stcMusic.Name_of_Sound_effect.c_str()); 
					break;
			   case 0x03:
					 stcMusic.Volume	 = ReadCompressedInteger(Stream);
					printf("\n Volume %d", stcMusic.Volume);	   
					break;	 
			   case 0x04:
					 stcMusic.Tempo	 = ReadCompressedInteger(Stream);
					printf("\n Tempo %d",stcMusic.Tempo);	   
					break;
			   case 0x05:
					 stcMusic.Balance	 = ReadCompressedInteger(Stream);
					printf("\n Balance %d",stcMusic.Balance );	   
					break;		
			   case 0x00:
					break;
			   default:
					while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
					break;	 
			}
 }while (ChunkInfo.ID!=0);
   ChunkInfo.ID=1;
 return(stcMusic);
}

std:: vector <stcSkill> LDB::skillChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std:: vector <stcSkill> vecSkill;
		 stcSkill skill;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		   
			  do{			   
						  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {		
						  case SkillChunk_Name:
							   skill.strName = ReadString(Stream, ChunkInfo.Length);
							   printf("\n nombre ");	
							   printf(skill.strName.c_str());		
								break;
						  case SkillChunk_Description:
							   skill.strDescription = ReadString(Stream, ChunkInfo.Length);
							   printf("\n Chunk_Description ");	
							   printf(skill.strDescription.c_str());		
							   break;						  
						  case SkillChunk_text:
							   skill.strtext = ReadString(Stream, ChunkInfo.Length);
							   printf("\n  SkillChunk_text ");	
							   printf(skill.strtext.c_str());		
							   break; 
						  case SkillChunk_textline:
							   skill.strtextline = ReadString(Stream, ChunkInfo.Length);
							   printf("\n textline ");	
							   printf(skill.strtextline.c_str());		
							   break; 
						  case SkillChunk_Failure:
							   skill.intFailure = ReadCompressedInteger(Stream);
							   printf("\n intFailure %d",skill.intFailure);	   
							   break;
						  case SkillChunk_Spelltype:
							   skill.intSpelltype = ReadCompressedInteger(Stream);
							   printf("\n intSpelltype %d",skill.intSpelltype);	   
							   break;
						  case SkillChunk_Cost:
							   skill.intCost = ReadCompressedInteger(Stream);
							   printf("\n intCost %d",skill.intCost);	   
							   break;
						  case SkillChunk_Range:
							   skill.intRange = ReadCompressedInteger(Stream);
							   printf("\n intRange %d",skill.intRange);	   
							   break;
						  case SkillChunk_Switch:
							   skill.intSwitch = ReadCompressedInteger(Stream);
							   printf("\n intSwitch %d",skill.intSwitch);	   
							   break;
						  case SkillChunk_Battleanimation:
							   skill.intBattleanimation = ReadCompressedInteger(Stream);
							   printf("\n intBattleanimation %d",skill.intBattleanimation);	   
							   break;
						  case SkillChunk_Soundeffect:
							   skill.Soundeffect =musicChunk(ChunkInfo.Length,Stream);
							   break;
						  case SkillChunk_Fieldusage:
							   skill.blFieldusage = ReadCompressedInteger(Stream);
							   printf("\n blFieldusage %d",skill.blFieldusage);	   
							   break;
						  case SkillChunk_Combatusage:
							   skill.blCombatusage = ReadCompressedInteger(Stream);
							   printf("\n blCombatusage %d",skill.blCombatusage);	   
							   break;
						  case SkillChunk_Strengtheffect:
							   skill.intStrengtheffect = ReadCompressedInteger(Stream);
							   printf("\n intStrengtheffect %d",skill.intStrengtheffect);	   
							   break;
						  case SkillChunk_Mindeffect:
							   skill.intMindeffect = ReadCompressedInteger(Stream);
							   printf("\n intMindeffect %d",skill.intMindeffect);	   
							   break;
						  case SkillChunk_Variance:
							   skill.intVariance = ReadCompressedInteger(Stream);
							   printf("\n intVariance %d",skill.intVariance);	   
							   break;
						  case SkillChunk_Basevalue:
							   skill.intBasevalue = ReadCompressedInteger(Stream);
							   printf("\n intBasevalue %d",skill.intBasevalue);	   
							   break;
						  case SkillChunk_Successrate:
							   skill.intSuccessrate = ReadCompressedInteger(Stream);
							   printf("\n intSuccessrate %d",skill.intSuccessrate);	   
							   break;
						  case SkillChunk_AffectHP:
							   skill.blAffectHP = ReadCompressedInteger(Stream);
							   printf("\n blAffectHP %d",skill.blAffectHP);	   
							   break;
						  case SkillChunk_AffectMP:
							   skill.blAffectMP = ReadCompressedInteger(Stream);
							   printf("\n blAffectMP %d",skill.blAffectMP);	   
							   break;
						  case SkillChunk_AffectAttack:
							   skill.blAffectAttack = ReadCompressedInteger(Stream);
							   printf("\n blAffectAttack %d",skill.blAffectAttack);	   
							   break;
						  case SkillChunk_AffectDefense:
							   skill.blAffectDefense = ReadCompressedInteger(Stream);
							   printf("\n blAffectDefense %d",skill.blAffectDefense);	   
							   break;
						  case SkillChunk_AffectMind:
							   skill.blAffectMind = ReadCompressedInteger(Stream);
							   printf("\n blAffectMind %d",skill.blAffectMind);	   
							   break;
						  case SkillChunk_AffectAgility:
							   skill.blAffectAgility = ReadCompressedInteger(Stream);
							   printf("\n blAffectAgility %d",skill.blAffectAgility);	   
							   break;
						  case SkillChunk_Absorbdamage:
							   skill.blAbsorbdamage = ReadCompressedInteger(Stream);
							   printf("\n blAbsorbdamage %d",skill.blAbsorbdamage);	   
							   break;
						  case SkillChunk_Ignoredefense:
							   skill.blIgnoredefense = ReadCompressedInteger(Stream);
							   printf("\n blIgnoredefense %d",skill.blIgnoredefense);	   
							   break;
						  case SkillChunk_Conditionslength:
							   skill.intConditionslength = ReadCompressedInteger(Stream);
							   printf("\n intConditionslength %d",skill.intConditionslength);	   
							   break;					  
						  case SkillChunk_Changecondition:
							   printf("\n CHUNK_Condeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								skill.vc_ch_Condeffects.push_back(Void);
								printf("%d ",Void);}
								break;	 
						  case SkillChunk_Attributeslength:
							   skill.intAttributeslength = ReadCompressedInteger(Stream);
							   printf("\n intAttributeslength %d",skill.intAttributeslength);	   
							   break;
						  case SkillChunk_Attackattribute:
							   printf("\n CHUNK_Attribeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								skill.vc_ch_Attribeffects.push_back(Void);
								printf("%d ",Void);}
								break;   
						  case SkillChunk_Affectresistance:
							   skill.blAffectresistance = ReadCompressedInteger(Stream);
							   printf("\n blAffectresistance %d",skill.blAffectresistance);	   
							   break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			} while(ChunkInfo.ID!=0);
		  vecSkill.push_back(skill);
		  skill.clear();
		  datareaded++;
		  }   
		  return(vecSkill);
}
std:: vector <stcItem> LDB::itemChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std::vector <stcItem> vecItem;
		 stcItem Item; 
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			  do{			   
						  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño		  
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case ItemChunk_Name:
							   Item.Name = ReadString(Stream, ChunkInfo.Length);
							   printf("\n nombre ");	
							   printf(Item.Name.c_str());		
							   break;
						  case ItemChunk_Description:
							   Item.Description = ReadString(Stream, ChunkInfo.Length);
							   printf("\n clase ");	
							   printf(Item.Description.c_str());		
							   break;
						  case ItemChunk_Type:
							   Item.Type = ReadCompressedInteger(Stream);
							   printf("\n Type %d",Item.Type);	   
							   break;
						  case ItemChunk_Cost:
							   Item.Cost = ReadCompressedInteger(Stream);
							   printf("\n Cost %d",Item.Cost);	   
							   break;
						  case ItemChunk_Uses:
							   Item.Uses = ReadCompressedInteger(Stream);
							   printf("\n Uses %d",Item.Uses);	   
							   break;
						  case ItemChunk_Attack:
							   Item.Attack = ReadCompressedInteger(Stream);
							   printf("\n Attack %d",Item.Attack);	   
							   break;
						  case ItemChunk_Defense:
							   Item.Defense = ReadCompressedInteger(Stream);
							   printf("\n Defense %d",Item.Defense);	   
							   break;
						  case ItemChunk_Mind:
							   Item.Mind = ReadCompressedInteger(Stream);
							   printf("\n Mind %d",Item.Mind);	   
							   break;
						  case ItemChunk_Speed:
							   Item.Speed = ReadCompressedInteger(Stream);
							   printf("\n Speed %d",Item.Speed);	   
							   break;
						  case ItemChunk_Equip:
							   Item.Equip = ReadCompressedInteger(Stream);
							   printf("\n Equip %d",Item.Equip);	   
							   break;
						  case ItemChunk_MPcost:
							   Item.MPcost = ReadCompressedInteger(Stream);
							   printf("\n MPcost %d",Item.MPcost);	   
							   break;
						  case ItemChunk_Chancetohit:
							   Item.Chancetohit = ReadCompressedInteger(Stream);
							   printf("\n Chancetohit %d",Item.Chancetohit);	   
							   break;
						  case ItemChunk_Criticalhit:
							   Item.Criticalhit = ReadCompressedInteger(Stream);
							   printf("\n Criticalhit %d",Item.Criticalhit);	   
							   break;
						  case ItemChunk_Battleanimation:
							   Item.Battleanimation = ReadCompressedInteger(Stream);
							   printf("\n Battleanimation %d",Item.Battleanimation);	   
							   break;
						  case ItemChunk_Preemptiveattack:
							   Item.Preemptiveattack = ReadCompressedInteger(Stream);
							   printf("\n Preemptiveattack %d",Item.Preemptiveattack);	   
							   break;
						  case ItemChunk_Doubleattack:
							   Item.Doubleattack = ReadCompressedInteger(Stream);
							   printf("\n Doubleattack %d",Item.Doubleattack);	   
							   break;
						  case ItemChunk_Attackallenemies:
							   Item.Attackallenemies = ReadCompressedInteger(Stream);
							   printf("\n Attackallenemies %d",Item.Attackallenemies);	   
							   break;
						  case ItemChunk_Ignoreevasion:
							   Item.Ignoreevasion = ReadCompressedInteger(Stream);
							   printf("\n Ignoreevasion %d",Item.Ignoreevasion);	   
							   break;
						  case ItemChunk_Preventcriticalhits:
							   Item.Preventcriticalhits = ReadCompressedInteger(Stream);
							   printf("\n Preventcriticalhits %d",Item.Preventcriticalhits);	   
							   break;
						  case ItemChunk_Raiseevasion:
							   Item.Raiseevasion = ReadCompressedInteger(Stream);
							   printf("\n Raiseevasion %d",Item.Raiseevasion);	   
							   break;
						  case ItemChunk_MPusecutinhalf:
							   Item.MPusecutinhalf = ReadCompressedInteger(Stream);
							   printf("\n MPusecutinhalf %d",Item.MPusecutinhalf);	   
							   break;
						  case ItemChunk_Noterraindamage:
							   Item.Noterraindamage = ReadCompressedInteger(Stream);
							   printf("\n Noterraindamage %d",Item.Noterraindamage);	   
							   break;
						  case ItemChunk_Healsparty:
							   Item.Healsparty = ReadCompressedInteger(Stream);
							   printf("\n Healsparty %d",Item.Healsparty);	   
							   break;
						  case ItemChunk_HPrecovery ://0x20,
							   Item.HPrecovery = ReadCompressedInteger(Stream);
							   printf("\n HPrecovery %d",Item.HPrecovery);	   
							   break;
						  case ItemChunk_HPrecoveryvalue://0x21,
							   Item.HPrecoveryvalue = ReadCompressedInteger(Stream);
							   printf("\n Type %d",Item.HPrecoveryvalue);	   
							   break;
						  case ItemChunk_MPrecovery://0x22,
							   Item.MPrecovery = ReadCompressedInteger(Stream);
							   printf("\n MPrecovery %d",Item.MPrecovery);	   
							   break;
						  case ItemChunk_MPrecoveryvalue://0x23,
							   Item.MPrecoveryvalue = ReadCompressedInteger(Stream);
							   printf("\n MPrecoveryvalue %d",Item.MPrecoveryvalue);	   
							   break;							   
						  case ItemChunk_Useonfieldonly://0x25,
							   Item.Useonfieldonly = ReadCompressedInteger(Stream);
							   printf("\n Useonfieldonly %d",Item.Useonfieldonly);	   
							   break;
						  case ItemChunk_Onlyondeadheros://0x26,
							   Item.Onlyondeadheros = ReadCompressedInteger(Stream);
							   printf("\n Onlyondeadheros %d",Item.Onlyondeadheros);	   
							   break;
						  case ItemChunk_MaxHPmodify://0x29,
							   Item.MaxHPmodify = ReadCompressedInteger(Stream);
							   printf("\n MaxHPmodify %d",Item.MaxHPmodify);	   
							   break;
						  case ItemChunk_MaxMPmodify://0x2A,
							   Item.MaxMPmodify = ReadCompressedInteger(Stream);
							   printf("\n MaxMPmodify %d",Item.MaxMPmodify);	   
							   break;
						  case ItemChunk_Attackmodify://0x2B,
							   Item.Attackmodify = ReadCompressedInteger(Stream);
							   printf("\n Attackmodify %d",Item.Attackmodify);	   
							   break;
						  case ItemChunk_Defensemodify://0x2C,
							   Item.Defensemodify = ReadCompressedInteger(Stream);
							   printf("\n Defensemodify %d",Item.Defensemodify);	   
							   break;
						  case ItemChunk_Mindmodify://0x2D,
							   Item.Mindmodify = ReadCompressedInteger(Stream);
							   printf("\n Mindmodify %d",Item.Mindmodify);	   
							   break;
						  case ItemChunk_Speedmodify://0x2E,
							   Item.Speedmodify = ReadCompressedInteger(Stream);
							   printf("\n Speedmodify %d",Item.Speedmodify);	   
							   break;
						  case ItemChunk_Usagemessage://0x33,
							   Item.Usagemessage = ReadCompressedInteger(Stream);
							   printf("\n Usagemessage %d",Item.Usagemessage);	   
							   break;
						  case ItemChunk_Switchtoturnon://0x37,
							   Item.Switchtoturnon = ReadCompressedInteger(Stream);
							   printf("\n Switchtoturnon %d",Item.Switchtoturnon);	   
							   break;
						  case ItemChunk_Useonfield://0x39,
							   Item.Useonfield = ReadCompressedInteger(Stream);
							   printf("\n Useonfield %d",Item.Useonfield);	   
							   break;
						  case ItemChunk_Useinbattle://0x3A,
							   Item.Useinbattle = ReadCompressedInteger(Stream);
							   printf("\n Useinbattle %d",Item.Useinbattle);	   
							   break;
						  case ItemChunk_Heroeslength://0x3D,
							   Item.Heroeslength = ReadCompressedInteger(Stream);
							   printf("\n Heroeslength %d",Item.Heroeslength);	   
							   break;
						 case ItemChunk_Heroescanuse:
							   printf("\nChunk_Heroescanuse ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								Item.vc_ch_Heroescanuse.push_back(Void);
								printf("%d ",Void);}
								break;						   
						  case ItemChunk_Conditionslength://0x3F,
							   Item.Conditionslength = ReadCompressedInteger(Stream);
							   printf("\n Conditionslength %d",Item.Conditionslength);	   
							   break;
							case ItemChunk_Conditionchanges:
							   printf("\n CHUNK_Condeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								Item.vc_ch_Condeffects.push_back(Void);
								printf("%d ",Void);}
								break;								 
						  case ItemChunk_Attributeslength://0x41,
							   Item.Attributeslength = ReadCompressedInteger(Stream);
							   printf("\n Attributeslength %d",Item.Attributeslength);	   
							   break;
						  case ItemChunk_Attributes:
							   printf("\n CHUNK_Attribeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								Item.vc_ch_Attribeffects.push_back(Void);
								printf("%d ",Void);}
								break;						 
						  case ItemChunk_Chancetochange://0x43  
							   Item.Chancetochange = ReadCompressedInteger(Stream);
							   printf("\n Chancetochange %d",Item.Chancetochange);	   
							   break;															  
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
									 while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			 } while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecItem.push_back(Item);
		  Item.clear();
		  }   
		  return(vecItem);
}

std:: vector <stcEnemy_Action> LDB::mosteractionChunk(int Length,FILE * Stream)
{ 
 int id,datatoread=0,datareaded=0;
 stcEnemy_Action Action;
std::vector <stcEnemy_Action> vecActions;
	datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		  do{ 
			  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño									
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {	 
						  case	MonsterActionsChunk_Action:
							   Action.intAction = ReadCompressedInteger(Stream);
							   printf("\n intAction %d", Action.intAction);			
							   break;
						  case MagicblockChunk_Spell_ID:
							   Action.intAction_data = ReadCompressedInteger(Stream);
							   printf("\n intAction_data %d",Action.intAction_data);			
							   break; 
						  case MonsterActionsChunk_Skill_ID:
							   Action.intSkill_ID = ReadCompressedInteger(Stream);
							   printf("\n intSkill_ID %d",Action.intSkill_ID);			
							   break; 
						  case MonsterActionsChunk_Monster_ID:
							   Action.intMonster_ID = ReadCompressedInteger(Stream);
							   printf("\n intMonster_ID %d",Action.intMonster_ID);			
							   break; 
						  case MonsterActionsChunk_Condition:
							   Action.intCondition = ReadCompressedInteger(Stream);
							   printf("\n intCondition %d",Action.intCondition);			
							   break; 
						  case MonsterActionsChunk_Lower_limit:
							   Action.intLower_limit = ReadCompressedInteger(Stream);
							   printf("\n intLower_limit %d",Action.intLower_limit);			
							   break; 
						  case MonsterActionsChunk_Upper_limit:
							   Action.intUpper_limit = ReadCompressedInteger(Stream);
							   printf("\n intUpper_limit %d",Action.intUpper_limit);			
							   break; 
						  case MonsterActionsChunk_Priority:
							   Action.intPriority = ReadCompressedInteger(Stream);
							   printf("\n intPriority %d",Action.intPriority);			
							   break; 
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			}while(ChunkInfo.ID!=0);
			vecActions.push_back(Action);
			Action.clear();
		  datareaded++;
		  }
		  ChunkInfo.ID	 =1;   
		  return(vecActions);
}

std:: vector <stcEnemy> LDB::mosterChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std:: vector <stcEnemy> vecEnemy;
		 stcEnemy Enemy;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			  do{
						  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño					
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case MonsterChunk_Name:
								Enemy.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n MonsterChunk_Name ");	
								 printf( Enemy.strName.c_str());		
								break;
						  case MonsterChunk_Graphicfile:
							   Enemy.strGraphicfile = ReadString(Stream, ChunkInfo.Length);
							   printf("\n MonsterChunk_Graphicfile ");	
							   printf( Enemy.strGraphicfile.c_str());		
							   break;
						  case MonsterChunk_Huealteration://0x03,
							   Enemy.intHuealteration = ReadCompressedInteger(Stream);
							   printf("\n intHuealteration %d",Enemy.intHuealteration); 
							   break; 
						  case MonsterChunk_MaxHP://0x04,
							   Enemy.intMaxHP = ReadCompressedInteger(Stream);
							   printf("\n intMaxHP %d",Enemy.intMaxHP); 
							   break; 
						  case MonsterChunk_MaxMP://0x05,
							   Enemy.intMaxMP = ReadCompressedInteger(Stream);
							   printf("\n intMaxMP %d",Enemy.intMaxMP); 
							   break; 
						  case MonsterChunk_Attack://0x06,
							   Enemy.intAttack = ReadCompressedInteger(Stream);
							   printf("\n intAttack %d",Enemy.intAttack); 
							   break; 
						  case MonsterChunk_Defense://0x07,
							   Enemy.intDefense = ReadCompressedInteger(Stream);
							   printf("\n intDefense %d",Enemy.intDefense); 
							   break; 
						  case MonsterChunk_Mind://0x08,
							   Enemy.intMind = ReadCompressedInteger(Stream);
							   printf("\n intMind %d",Enemy.intMind); 
							   break; 
						  case MonsterChunk_Speed://0x09,
							   Enemy.intSpeed = ReadCompressedInteger(Stream);
							   printf("\n intSpeed %d",Enemy.intSpeed); 
							   break; 
						  case MonsterChunk_Translucentgraphic://0x0A,
							   Enemy.blTranslucentgraphic = ReadCompressedInteger(Stream);
							   printf("\n blTranslucentgraphic %d",Enemy.blTranslucentgraphic); 
							   break; 
						  case MonsterChunk_Experience://0x0B,
							   Enemy.intExperience = ReadCompressedInteger(Stream);
							   printf("\n intExperience %d",Enemy.intExperience); 
							   break; 
						  case MonsterChunk_Gold://0x0C,
							   Enemy.intGold = ReadCompressedInteger(Stream);
							   printf("\n intGold %d",Enemy.intGold); 
							   break; 
						  case MonsterChunk_SpoilsitemID://0x0D,
							   Enemy.intSpoilsitemID = ReadCompressedInteger(Stream);
							   printf("\n intSpoilsitemID %d",Enemy.intSpoilsitemID); 
							   break; 
						  case MonsterChunk_Spoilschance://0x0E,
							   Enemy.intSpoilschance = ReadCompressedInteger(Stream);
							   printf("\n intSpoilschance %d",Enemy.intSpoilschance); 
							   break; 
						  case MonsterChunk_Canusecriticalhits://0x15,
							   Enemy.blCanusecriticalhits = ReadCompressedInteger(Stream);
							   printf("\n blCanusecriticalhits %d",Enemy.blCanusecriticalhits); 
							   break; 
						  case MonsterChunk_Criticalhitchance://0x16,
							   Enemy.intCriticalhitchance = ReadCompressedInteger(Stream);
							   printf("\n intCriticalhitchance %d",Enemy.intCriticalhitchance); 
							   break; 
						  case MonsterChunk_Usuallymiss://0x1A,
							   Enemy.blUsuallymiss = ReadCompressedInteger(Stream);
							   printf("\n blUsuallymiss %d",Enemy.blUsuallymiss); 
							   break; 
						  case MonsterChunk_Airborne://0x1C,
							   Enemy.blAirborne = ReadCompressedInteger(Stream);
							   printf("\n blAirborne %d",Enemy.blAirborne); 
							   break; 
						  case MonsterChunk_Conditionslength://0x1F,
							   Enemy.intConditionslength = ReadCompressedInteger(Stream);
							   printf("\n intConditionslength %d",Enemy.intConditionslength); 
							   break; 
						  case MonsterChunk_Conditionseffects://0x20,
							   printf("\n CHUNK_Condeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								Enemy.vc_ch_Condeffects.push_back(Void);
								printf("%d ",Void);}
								break;  
						  case MonsterChunk_Attributeslength://0x21,
							   Enemy.inyAttributeslength = ReadCompressedInteger(Stream);
							   printf("\n inyAttributeslength %d",Enemy.inyAttributeslength); 
							   break; 
						  case MonsterChunk_Attributeseffect://0x22,
							   printf("\n CHUNK_Attribeffects ");
							   while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								Enemy.vc_ch_Attribeffects.push_back(Void);
								printf("%d ",Void);}
								break;	
						  case MonsterChunk_Actionslist://0x2A 
							   mosteractionChunk( ChunkInfo.Length,Stream);
							   break; 
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			} while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecEnemy.push_back(Enemy);
		  Enemy.clear();
		  }  
		  return(vecEnemy); 
}

std:: vector <stcEnemy_group_data> LDB::MonsterPartyMonsterChunk(int Length,FILE * Stream)
{ 
 int id,datatoread=0,datareaded=0;
 stcEnemy_group_data Monster;
std::vector <stcEnemy_group_data> vecPartyMonster;
	datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		  do{ 
			  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño									
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {	 
						  case	Monster_ID:
							   Monster.Enemy_ID = ReadCompressedInteger(Stream);
							   printf("\n Monster_ID %d", Monster.Enemy_ID);			
							   break;
						  case X_position:
							   Monster.X_position = ReadCompressedInteger(Stream);
							   printf("\n X_position %d",Monster.X_position);			
							   break; 
						  case Y_position:
							   Monster.Y_position = ReadCompressedInteger(Stream);
							   printf("\n Y_position %d",Monster.Y_position);			
							   break; 
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			}while(ChunkInfo.ID!=0);
			vecPartyMonster.push_back(Monster);
			Monster.clear();
		  datareaded++;
		  }
		  ChunkInfo.ID	 =1;   
		  return(vecPartyMonster);
}




stcEnemy_group_condition  LDB::MonsterPartyEventconditionChunk(int Length,FILE * Stream)
{ printf("\n MonsterPartyEventconditionChunk ");
  stcEnemy_group_condition  stcCondition; 
  short dat; 
  stcCondition.clear();
do   
 {	  
			ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			if(ChunkInfo.ID!=0)
			ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	
			
			switch(ChunkInfo.ID)// segun el tipo
			{   
			   case Condition_flags:// en el 2003 se usan 2 chars
				   if(ChunkInfo.Length==2)
				   stcCondition.Condition_flags =fread(&dat, sizeof(short), 1, Stream);
					else
					stcCondition.Condition_flags = ReadCompressedInteger(Stream);
					 printf("\n Condition_flags %d", stcCondition.Condition_flags); 
					break;
			   case Switch_A:
					stcCondition.Switch_A	 = ReadCompressedInteger(Stream);
					printf("\n Switch_A %d",stcCondition.Switch_A );	   
					break;	 
			   case Turn_number_A:
					 stcCondition.Turn_number_A	 = ReadCompressedInteger(Stream);
					printf("\n Turn_number_A %d",stcCondition.Turn_number_A );	   
					break;
			   case Lower_limit:
					 stcCondition.Lower_limit	 = ReadCompressedInteger(Stream);
					printf("\n Lower_limit %d",stcCondition.Lower_limit );	   
					break;   
			   case Upper_limit:
					 stcCondition.Upper_limit	 = ReadCompressedInteger(Stream);
					printf("\n Upper_limit %d",stcCondition.Upper_limit  );	   
					break;		 
			   case CHUNK_MAP_END_OF_BLOCK:
					break;
			   default:
					while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
					break;	 
			}
 }while (ChunkInfo.ID!=0);
   ChunkInfo.ID=1;
 return(stcCondition);
}


std:: vector <stcEnemy_group_event_page> LDB::MonsterPartyevent_pageChunk(int Length,FILE * Stream)
{ 
 int id,datatoread=0,datareaded=0;
 stcEnemy_group_event_page Monsterevent;
std::vector <stcEnemy_group_event_page> vecPartyMonsterevent;
	datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		  do{ 
			  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño									
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {	 
						  case	Page_conditions:
							 Monsterevent.conditions=MonsterPartyEventconditionChunk(ChunkInfo.Length,Stream);
							  break;
						  case Event_length:
							   Monsterevent.Event_length = ReadCompressedInteger(Stream);
							   printf("\n Event_length %d", Monsterevent.Event_length );			
							   break; 
						  //case Event:
						   //	
							   //break; 
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			}while(ChunkInfo.ID!=0);
			vecPartyMonsterevent.push_back(Monsterevent);
			Monsterevent.clear();
		  datareaded++;
		  }
		  ChunkInfo.ID	 =1;   
		  return(vecPartyMonsterevent);
}



std:: vector <stcEnemy_group> LDB::mosterpartyChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std:: vector <stcEnemy_group> vecEnemy_group;
		 stcEnemy_group Enemy_group;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			 do{
						 ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño					
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case MonsterPartyChunk_Name:
								 Enemy_group.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(Enemy_group.strName.c_str());		
								break;					   
						  case MonsterPartyChunk_Monsterdata://0x02,
							   Enemy_group.Enemy_data =MonsterPartyMonsterChunk(ChunkInfo.Length,Stream);
							   break;  
						  case MonsterPartyChunk_Terrainlength://0x04,
							   Enemy_group.intTerrainlength = ReadCompressedInteger(Stream);
							   printf("\n intTerrainlength %d",Enemy_group.intTerrainlength); 
							   break; 
						  case MonsterPartyChunk_Terraindata://0x05,
								printf("\n Terraindata");
								while(ChunkInfo.Length--) 
								{
								fread(&Void, sizeof(char), 1, Stream);
								printf("%d",Void);
								Enemy_group.vc_ch_Terraindata.push_back(Void);
								}
							   break; 
						  case MonsterPartyChunk_eventpages://0x0B	
							   Enemy_group.vecPartyMonsterevent=MonsterPartyevent_pageChunk(ChunkInfo.Length,Stream);
							   break;
							
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		  }while(ChunkInfo.ID!=0);
		  datareaded++;
		 vecEnemy_group.push_back(Enemy_group);
		 Enemy_group.clear();
		  }   
		  return(vecEnemy_group);
}

std:: vector <stcTerrain> LDB:: TerrainChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std::vector <stcTerrain> vecTerrain;
		 stcTerrain Terrain;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array				
			  do{
						  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño					
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case TerrainChunk_Name:
								 Terrain.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(Terrain.strName.c_str());		
								break;
						  case TerrainChunk_Damageontravel://0x02,
							   Terrain.intDamageontravel = ReadCompressedInteger(Stream);
							   printf("\n intDamageontravel %d",Terrain.intDamageontravel); 
							   break; 
						  case TerrainChunk_Encounterate://0x03,
							   Terrain.intEncounterate = ReadCompressedInteger(Stream);
							   printf("\n intEncounterate %d",Terrain.intEncounterate); 
							   break; 
						  case TerrainChunk_Battlebackground://0x04,
							   Terrain.strBattlebackground = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strBattlebackground ");	
							   printf(Terrain.strBattlebackground.c_str());
							   break;						   
						  case TerrainChunk_Skiffmaypass://0x05,
							   Terrain.blSkiffmaypass = ReadCompressedInteger(Stream);
							   printf("\n blSkiffmaypass %d",Terrain.blSkiffmaypass); 
							   break;						   
						  case TerrainChunk_Boatmaypass://0x06,
							   Terrain.blBoatmaypass = ReadCompressedInteger(Stream);
							   printf("\n blBoatmaypass %d",Terrain.blBoatmaypass); 
							   break;						   
						  case TerrainChunk_Airshipmaypass://0x07,
							   Terrain.blAirshipmaypass = ReadCompressedInteger(Stream);
							   printf("\n blAirshipmaypass %d",Terrain.blAirshipmaypass); 
							   break;						   
						  case TerrainChunk_Airshipmayland://0x09,
							   Terrain.blAirshipmayland = ReadCompressedInteger(Stream);
							   printf("\n blAirshipmayland %d",Terrain.blAirshipmayland); 
							   break;						   
						  case TerrainChunk_Heroopacity://0x0B						  
							   Terrain.intHeroopacity = ReadCompressedInteger(Stream);
							   printf("\n intHeroopacity %d",Terrain.intHeroopacity); 
							   break;										 
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecTerrain.push_back(Terrain);
		 Terrain.clear();
		  }   
		  return(vecTerrain);
}

std:: vector <stcAttribute> LDB:: AttributeChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std::vector <stcAttribute> vecAttribute;
		 stcAttribute Attribute;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			  do{				
						 ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case AttributeChunk_Name:
								 Attribute.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(Attribute.strName.c_str());		
								break;
						 case AttributeChunk_Type://0x02,
							   Attribute.intType = ReadCompressedInteger(Stream);
							   printf("\n intType %d",Attribute.intType); 
							   break;  
						 case AttributeChunk_A_damage://0x0B,
							   Attribute.intA_damage = ReadCompressedInteger(Stream);
							   printf("\n intA_damage %d",Attribute.intA_damage); 
							   break;  
						 case AttributeChunk_B_damage://0x0C,
							   Attribute.intB_damage = ReadCompressedInteger(Stream);
							   printf("\n intB_damage %d",Attribute.intB_damage); 
							   break;  
						 case AttributeChunk_C_damage://0x0F,
							   Attribute.intC_damage = ReadCompressedInteger(Stream);
							   printf("\n intC_damage %d",Attribute.intC_damage); 
							   break;  
						 case AttributeChunk_D_damage://0x0F,
							   Attribute.intD_damage = ReadCompressedInteger(Stream);
							   printf("\n intD_damage %d",Attribute.intD_damage); 
							   break;  
						 case AttributeChunk_E_damage://0x0F
							   Attribute.intE_damage = ReadCompressedInteger(Stream);
							   printf("\n intE_damage %d",Attribute.intE_damage); 
							   break;	   
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
						 
			  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecAttribute.push_back(Attribute);
		  Attribute.clear();
		  }   
		  return(vecAttribute);
}

std:: vector <stcState> LDB:: StatesChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std:: vector <stcState> vecState;
		 stcState State;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{
						   ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	   
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case StatesChunk_Name:
							   State.strName = ReadString(Stream, ChunkInfo.Length);
							   printf("\n nombre ");	
							   printf( State.strName.c_str());		
							   break;
						  case StatesChunk_Length://0x02,
							   State.intLength = ReadCompressedInteger(Stream);
							   printf("\n intLength %d",State.intLength); 
							   break; 
						  case StatesChunk_Color://0x03,
							   State.intColor = ReadCompressedInteger(Stream);
							   printf("\n intColor %d",State.intColor); 
							   break;							 
						  case StatesChunk_Priority://0x04,
							   State.intPriority = ReadCompressedInteger(Stream);
							   printf("\n intPriority %d",State.intPriority); 
							   break;							
						  case StatesChunk_Limitation://0x05,
							   State.intLimitation = ReadCompressedInteger(Stream);
							   printf("\n intLimitation %d",State.intLimitation); 
							   break;  
						  case StatesChunk_A_chance://0x0B,
							   State.intA_chance = ReadCompressedInteger(Stream);
							   printf("\n intA_chance %d",State.intA_chance); 
							   break;							
						  case StatesChunk_B_chance://0x0C,
							   State.intB_chance = ReadCompressedInteger(Stream);
							   printf("\n intB_chance %d",State.intB_chance); 
							   break;							
						  case StatesChunk_C_chance://0x0D,
							   State.intC_chance = ReadCompressedInteger(Stream);
							   printf("\n intC_chance %d",State.intC_chance); 
							   break;							
						  case StatesChunk_D_chance://0x0E,
							   State.intD_chance = ReadCompressedInteger(Stream);
							   printf("\n intD_chance %d",State.intD_chance); 
							   break;							
						  case StatesChunk_E_chance://0x0F,
								State.intE_chance = ReadCompressedInteger(Stream);
							   printf("\n intE_chance %d",State.intE_chance); 
							   break;						   
						  case StatesChunk_Turnsforhealing://0x15,
								State.intTurnsforhealing = ReadCompressedInteger(Stream);
							   printf("\n intTurnsforhealing %d",State.intTurnsforhealing); 
							   break;						   
						  case StatesChunk_Healperturn://0x16,
								State.intHealperturn = ReadCompressedInteger(Stream);
							   printf("\n intHealperturn %d",State.intHealperturn); 
							   break;						   
						  case StatesChunk_Healonshock://0x17,
							   State.intHealonshock = ReadCompressedInteger(Stream);
							   printf("\n intHealonshock %d",State.intHealonshock); 
							   break;							
						  case StatesChunk_HalveAttack://0x1F,
							   State.blHalveAttack = ReadCompressedInteger(Stream);
							   printf("\n blHalveAttack %d",State.blHalveAttack); 
							   break;							
						  case StatesChunk_HalveDefense://0x20,
							   State.blHalveDefense = ReadCompressedInteger(Stream);
							   printf("\n blHalveDefense %d",State.blHalveDefense); 
							   break;						   
						  case StatesChunk_HalveMind://0x21,
							   State.blHalveMind = ReadCompressedInteger(Stream);
							   printf("\n blHalveMind %d",State.blHalveMind); 
							   break;							
						  case StatesChunk_HalveAgility://0x22,
							   State.blHalveAgility = ReadCompressedInteger(Stream);
							   printf("\n blHalveAgility %d",State.blHalveAgility); 
							   break;							
						  case StatesChunk_Hitratechange://0x23,
							   State.intHitratechange = ReadCompressedInteger(Stream);
							   printf("\n intHitratechange %d",State.intHitratechange); 
							   break;							
						  case StatesChunk_Preventskilluse://0x29,
							   State.blPrevent_skill_use = ReadCompressedInteger(Stream);
							   printf("\n blPrevent_skill_use %d",State.blPrevent_skill_use); 
							   break;							
						  case StatesChunk_Minimumskilllevel://0x2A,
							   State.intMinimum_skill_level = ReadCompressedInteger(Stream);
							   printf("\n intMinimum_skill_level %d",State.intMinimum_skill_level); 
							   break;							
						  case StatesChunk_Preventmagicuse://0x2B,
							   State.blPreventmagicuse = ReadCompressedInteger(Stream);
							   printf("\n blPreventmagicuse %d",State.blPreventmagicuse); 
							   break;							
						  case StatesChunk_Minimummindlevel://0x2C,
							   State.intMinimummindlevel = ReadCompressedInteger(Stream);
							   printf("\n intMinimummindlevel %d",State.intMinimummindlevel); 
							   break;							
						  case StatesChunk_Allyenterstate://0x33,
							  State.strAllyenterstate = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strAllyenterstate ");	
							   printf(State.strAllyenterstate.c_str());  
							   break;							
						  case StatesChunk_Enemyentersstate://0x34,
							   State.strEnemyentersstate = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strEnemyentersstate ");	
							   printf(State.strEnemyentersstate.c_str());  
							   break;							
						  case StatesChunk_Alreadyinstate://0x35,
							   State.strAlreadyinstate = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strAlreadyinstate ");	
							   printf(State.strAlreadyinstate.c_str());  
							   break;							
						  case StatesChunk_Affectedbystate://0x36,
							   State.strAffectedbystate = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strAffectedbystate ");	
							   printf(State.strAffectedbystate.c_str());  
							   break;							
						  case StatesChunk_Statusrecovered://0x37,
							   State.strStatusrecovered = ReadString(Stream, ChunkInfo.Length);
							   printf("\n strStatusrecovered ");	
							   printf(State.strStatusrecovered.c_str());  
							   break;							
						  case StatesChunk_HPloss://0x3D,
							   State.intHPloss = ReadCompressedInteger(Stream);
							   printf("\n intHPloss %d",State.intHPloss); 
							   break;							
						  case StatesChunk_HPlossvalue://0x3E,
							   State.intHPlossvalue = ReadCompressedInteger(Stream);
							   printf("\n intHPlossvalue %d",State.intHPlossvalue); 
							   break;							
						  case StatesChunk_HPmaploss://0x3F,
							   State.intHPmaploss = ReadCompressedInteger(Stream);
							   printf("\n intHPmaploss %d",State.intHPmaploss); 
							   break;							
						  case StatesChunk_HPmapsteps://0x40,
							   State.intHPmapsteps = ReadCompressedInteger(Stream);
							   printf("\n intHPmapsteps %d",State.intHPmapsteps); 
							   break;							
						  case StatesChunk_MPloss://0x41,
								State.intMPloss = ReadCompressedInteger(Stream);
							   printf("\n intMPloss %d",State.intMPloss); 
							   break;						   
						  case StatesChunk_MPlossvalue://0x42,
							   State.intMPlossvalue = ReadCompressedInteger(Stream);
							   printf("\n intMPlossvalue %d",State.intMPlossvalue); 
							   break;							
						  case StatesChunk_MPmaploss://0x43,
							   State.intMPmaploss = ReadCompressedInteger(Stream);
							   printf("\n intMPmaploss %d",State.intMPmaploss); 
							   break;							
						  case StatesChunk_MPmapsteps://0x44
							   State.intMPmapsteps = ReadCompressedInteger(Stream);
							   printf("\n intMPmapsteps %d",State.intMPmapsteps); 
							   break;							
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		   }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecState.push_back(State);
		  State.clear();
		  } 
		  return(vecState);  
}

std:: vector <stcAnimationTiming> LDB:: AnimationTimingChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 stcAnimationTiming AnimationTiming;
		 std:: vector <stcAnimationTiming> vecAnimationTiming;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{   
			   ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			   if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			   ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				 
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case Frame://0x01,
							   AnimationTiming.Frame=ReadCompressedInteger(Stream);
							   printf("\n Frame %d",AnimationTiming.Frame); 
							   break;						  
						  case Sound_effect://0x02,
							   AnimationTiming.Sound_effect =musicChunk(ChunkInfo.Length,Stream);						  
							   break;						  
						  case Flash_effect://0x03,
							   AnimationTiming.Frame=ReadCompressedInteger(Stream);
							   printf("\n Frame %d",AnimationTiming.Frame);						   
							   break;						  
						  case Green_component://0x05,
							   AnimationTiming.Frame=ReadCompressedInteger(Stream);
							   printf("\n Frame %d",AnimationTiming.Frame);						   
								break;						 
						  case Blue_component://0x06,
							   AnimationTiming.Frame=ReadCompressedInteger(Stream);
							   printf("\n Frame %d",AnimationTiming.Frame);						   
							   break;						  
						  case Flash_power://0x07
							   AnimationTiming.Frame=ReadCompressedInteger(Stream);
							   printf("\n Frame %d",AnimationTiming.Frame);						   
							   break;						  
		
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecAnimationTiming.push_back(AnimationTiming);
		  AnimationTiming.clear();
		  }
		  ChunkInfo.ID=1;
		  return(vecAnimationTiming);   
}

std:: vector <stcAnimationCelldata> LDB:: AnimationCelldataChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 stcAnimationCelldata Celldata;
		 std:: vector <stcAnimationCelldata> vecCelldata;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{   
			   ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			   if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			   ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				 
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case AnimationCelldata_Cell_source://0x02,
							   Celldata.Cell_source = ReadCompressedInteger(Stream);
							   printf("\n Cell_source %d",Celldata.Cell_source);	
							   break;							
						  case AnimationCelldata_X_location://0x03,
							   Celldata.X_location = ReadCompressedInteger(Stream);
							   printf("\n X_location %d",Celldata.X_location);	
							   break;							
						  case AnimationCelldata_Y_location://0x04,
							   Celldata.Y_location = ReadCompressedInteger(Stream);
							   printf("\n Y_location %d",Celldata.Y_location);	
							   break;							
						  case AnimationCelldata_Magnification://0x05,
							   Celldata.Magnification = ReadCompressedInteger(Stream);
							   printf("\n Magnification %d",Celldata.Magnification);	
							   break;							
						  case AnimationCelldata_Red_component://0x06,
							   Celldata.Red_component = ReadCompressedInteger(Stream);
							   printf("\n Red_component %d",Celldata.Red_component);	
							   break;							
						  case AnimationCelldata_Green_component://0x07,
							   Celldata.Green_component = ReadCompressedInteger(Stream);
							   printf("\n Green_component %d",Celldata.Green_component);	
							   break;							
						  case AnimationCelldata_Blue_component://0x08,
							   Celldata.Blue_component = ReadCompressedInteger(Stream);
							   printf("\n Blue_component %d",Celldata.Blue_component);	
							   break;							
						  case AnimationCelldata_Chroma_component://0x09,
							   Celldata.Chroma_component = ReadCompressedInteger(Stream);
							   printf("\n Chroma_component %d",Celldata.Chroma_component);	
							   break;							
						  case AnimationCelldata_Alpha://0x0A,
							   Celldata.Alpha = ReadCompressedInteger(Stream);
							   printf("\n Alpha %d",Celldata.Alpha);	
							   break;  
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecCelldata.push_back(Celldata);
		  Celldata.clear();
		  }
		  ChunkInfo.ID=1;
		  return(vecCelldata);   
}

std:: vector <stcAnimationCell> LDB:: FramedataChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 stcAnimationCell AnimationCell;
		 std:: vector <stcAnimationCell> vecAnimationCell;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{   
			   ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			   if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			   ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				 
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case Cell_data:
							  printf("arrays");
							  AnimationCell.Cell_data=AnimationCelldataChunk(ChunkInfo.Length, Stream);
							  break;							
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecAnimationCell.push_back(AnimationCell);
		  AnimationCell.clear();
		  }
		  ChunkInfo.ID=1;
		  return(vecAnimationCell);   
}

std:: vector <stcAnimated_battle> LDB:: AnimationChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 stcAnimated_battle Animated_battle;
		 std:: vector <stcAnimated_battle> vecAnimated_battle;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{   
			   ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			   if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
			   ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				 
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case AnimationChunk_Name:
								 Animated_battle.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(Animated_battle.strName.c_str());		
								break;
								

						  case AnimationChunk_Animation_file://=0x02,
								 Animated_battle.strAnimation_file = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(Animated_battle.strAnimation_file.c_str());		
								break;
						  case AnimationChunk_Timing_data://=0x06,
							   Animated_battle.vecAnimationTiming= AnimationTimingChunk( ChunkInfo.Length,Stream); 
							  break;						
						  case AnimationChunk_Apply_to://=0x09,
							   Animated_battle.intApply_to = ReadCompressedInteger(Stream);
							   printf("\n intApply_to %d",Animated_battle.intApply_to); 
							   break;  
						  case AnimationChunk_Y_coordinate_line://=0x0A,
							   Animated_battle.intY_coordinate_line = ReadCompressedInteger(Stream);
							   printf("\n intY_coordinate_line %d",Animated_battle.intY_coordinate_line); 
							   break;  
						  case AnimationChunk_Framedata://=0x0C
							   Animated_battle.Framedata= FramedataChunk(Length,Stream);
							   break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecAnimated_battle.push_back(Animated_battle);
		  Animated_battle.clear();
		  }
		  return(vecAnimated_battle);   
}
std:: vector <stcChipSet> LDB:: TilesetChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 short dat=0;
		 stcChipSet ChipSet;
		 std:: vector <stcChipSet> vecChipset;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{				
				   ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
				   if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
				   ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	 
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case TilesetChunk_Name:
								ChipSet.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(ChipSet.strName.c_str());		
								break;
						  case TilesetChunk_Graphic://0x02,
								ChipSet.strGraphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(ChipSet.strGraphic.c_str());		
								break;
						  case TilesetChunk_Lower_tile_terrain://0x03,
								printf("\n Lower_tile_terrain ");
								while(ChunkInfo.Length--)
								{fread(&dat, sizeof(short), 1, Stream);
								ChipSet.vc_sh_Lower_tile_terrain.push_back(dat);
								printf("%d ",dat);
								ChunkInfo.Length--;
								}
								break;
						  case TilesetChunk_Lower_tile_passable://0x04,
								printf("\n Lower_tile_passable ");
								while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								ChipSet.vc_ch_Lower_tile_passable.push_back(Void);
								printf("%d ",Void);}
								break;
						  case TilesetChunk_Upper_tile_passable://0x05,
								printf("\n Upper_tile_passable ");
								while(ChunkInfo.Length--)
								{fread(&Void, sizeof(char), 1, Stream);
								ChipSet.vc_ch_Upper_tile_passable.push_back(Void);
								printf("%d ",Void);}
								break;
						  case TilesetChunk_Water_animation://0x0B,
							   ChipSet.Water_animation = ReadCompressedInteger(Stream);
							   printf("\n Water_animation %d",ChipSet.Water_animation); 
							   break;  
						  case TilesetChunk_Animation_speed://0x0C  
							   ChipSet.Animation_speed = ReadCompressedInteger(Stream);
							   printf("\n Animation_speed %d",ChipSet.Animation_speed); 
							   break;							  
								
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
		  }while(ChunkInfo.ID!=0);
		  datareaded++;
		  vecChipset.push_back(ChipSet);
		  ChipSet.clear();
		  }   
		  return(vecChipset);
}

std:: vector <stcEvent> LDB:: EventChunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std::vector <stcEvent> vecEvent;
		 stcEvent Event;		
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
		 do{  
						ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				  
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case Common_EventChunk_Name:
								 Event.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(Event.strName.c_str());		
								break;
						  case Common_EventChunk_NameActivation_condition://0x0B,
							   Event.intNameActivation_condition = ReadCompressedInteger(Stream);
							   printf("\n intNameActivation_condition %d",Event.intNameActivation_condition); 
							   break;  
						 case Common_EventChunk_NameActivate_on_switch://0x0C,
							  Event.blNameActivate_on_switch = ReadCompressedInteger(Stream);
							   printf("\n blNameActivate_on_switch %d",Event.blNameActivate_on_switch); 
							   break;
						 case Common_EventChunk_NameSwitch_ID://0x0D,
							   Event.intNameSwitch_ID = ReadCompressedInteger(Stream);
							   printf("\n intNameSwitch_ID %d",Event.intNameSwitch_ID); 
							   break;
						 case Common_EventChunk_NameScript_length://0x15,
							   Event.intNameScript_length = ReadCompressedInteger(Stream);
							   printf("\n intNameScript_length %d",Event.intNameScript_length); 
							   break;
						 //case Common_EventChunk_NameScript://0x16
						   //	Event.intNameActivation_condition = ReadCompressedInteger(Stream);
						   //	printf("\n intE_damage %d",Event.intNameActivation_condition); 
						   //	break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			 }while(ChunkInfo.ID!=0);
		  datareaded++;
		 vecEvent.push_back(Event);
		 Event.clear();
		  } 
		  return(vecEvent);  
}

stcGlosary LDB::StringChunk(int Length,FILE * Stream)//movimientos de la pagina
{		
		int id,data; 
		std::string name;
		stcGlosary Glosary;  
			  do{ 
					ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
					if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
					ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño				 
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {					 
							   case  Enemy_encounter://0x01,
								 Glosary.Enemy_encounter = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_encounter ");	
								 printf(Glosary.Enemy_encounter.c_str());
							   break;
							   case Headstart_attack://0x02,
								 Glosary.Headstart_attack = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Headstart_attack ");	
								 printf(Glosary.Headstart_attack.c_str());
							   break;
							   case Escape_success://0x03,
								 Glosary.Escape_success = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Escape_success ");	
								 printf(Glosary.Escape_success.c_str());
							   break;
							   case Escape_failure://0x04,
								 Glosary.Escape_failure = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Escape_failure ");	
								 printf(Glosary.Escape_failure.c_str());
							   break;
							   case Battle_victory://0x05,
								 Glosary.Battle_victory = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Battle_victory ");	
								 printf(Glosary.Battle_victory.c_str());
							   break;
							   case Battle_defeat://0x06,
								 Glosary.Battle_defeat = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Battle_defeat ");	
								 printf(Glosary.Battle_defeat.c_str());
							   break;
							   case Experience_received://0x07,
								 Glosary.Experience_received = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Experience_received ");	
								 printf(Glosary.Experience_received.c_str());
							   break;
							   case Money_recieved_A://0x08,
								 Glosary.Money_recieved_A = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Money_recieved_A ");	
								 printf(Glosary.Money_recieved_A.c_str());
							   break;
							   case Money_recieved_B://0x09,
								 Glosary.Money_recieved_B = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Money_recieved_B ");	
								 printf(Glosary.Money_recieved_B.c_str());
							   break;
							   case Item_recieved://0x0A,
								 Glosary.Item_recieved = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Item_recieved ");	
								 printf(Glosary.Item_recieved.c_str());
							   break;
							   case Attack_message://0x0B,
								 Glosary.Attack_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Attack_message ");	
								 printf(Glosary.Attack_message.c_str());
							   break;
							   case Ally_critical_hit://0x0C,
								 Glosary.Ally_critical_hit = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Ally_critical_hit ");	
								 printf(Glosary.Ally_critical_hit.c_str());
							   break;
							   case Enemy_critical_hit://0x0D,
								 Glosary.Enemy_critical_hit = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_critical_hit ");	
								 printf(Glosary.Enemy_critical_hit.c_str());
							   break;
							   case Defend_message://0x0E,
								 Glosary.Defend_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Defend_message ");	
								 printf(Glosary.Defend_message.c_str());
							   break;
							   case Watch_message://0x0F,
								 Glosary.Watch_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Watch_message ");	
								 printf(Glosary.Watch_message.c_str());
							   break;
							   case Gathering_energy://0x10,
								 Glosary.Gathering_energy = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Gathering_energy ");	
								 printf(Glosary.Gathering_energy.c_str());
							   break;
							   case Sacrificial_attack://0x11,
								 Glosary.Sacrificial_attack = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Sacrificial_attack ");	
								 printf(Glosary.Sacrificial_attack.c_str());
							   break;
							   case Enemy_escape://0x12,
								 Glosary.Enemy_escape = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_escape ");	
								 printf(Glosary.Enemy_escape.c_str());
							   break;
							   case Enemy_transform://0x13,
								 Glosary.Enemy_transform = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_transform ");	
								 printf(Glosary.Enemy_transform.c_str());
							   break;
							   case Enemy_damaged://0x14,
								 Glosary.Enemy_damaged = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_damaged ");	
								 printf(Glosary.Enemy_damaged.c_str());
							   break;
							   case Enemy_undamaged://0x15,
								 Glosary.Enemy_undamaged = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_undamaged ");	
								 printf(Glosary.Enemy_undamaged.c_str());
							   break;
							   case Ally_damaged://0x16,
								 Glosary.Ally_damaged = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Ally_damaged ");	
								 printf(Glosary.Ally_damaged.c_str());
							   break;
							   case Ally_undamaged://0x17,
								 Glosary.Ally_undamaged = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Ally_undamaged ");	
								 printf(Glosary.Ally_undamaged.c_str());
							   break;
							   case Skill_failure_A://0x18,
								 Glosary.Skill_failure_A = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Skill_failure_A ");	
								 printf(Glosary.Skill_failure_A.c_str());
							   break;
							   case Skill_failure_B://0x19,
								 Glosary.Skill_failure_B = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Skill_failure_B ");	
								 printf(Glosary.Skill_failure_B.c_str());
							   break;
							   case Skill_failure_C://0x1A,
								 Glosary.Skill_failure_C = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Skill_failure_C ");	
								 printf(Glosary.Skill_failure_C.c_str());
							   break;
							   case Attack_dodged://0x1B,
								 Glosary.Attack_dodged = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Attack_dodged ");	
								 printf(Glosary.Attack_dodged.c_str());
							   break;
							   case Item_use://0x1C,
								 Glosary.Item_use = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Item_use ");	
								 printf(Glosary.Item_use.c_str());
							   break;
							   case Stat_recovery://0x1D,
								 Glosary.Stat_recovery = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Stat_recovery ");	
								 printf(Glosary.Stat_recovery.c_str());
							   break;
							   case Stat_increase://0x1E,
								 Glosary.Stat_increase = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Stat_increase ");	
								 printf(Glosary.Stat_increase.c_str());
							   break;
							   case Stat_decrease://0x1F,
								 Glosary.Stat_decrease = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Stat_decrease ");	
								 printf(Glosary.Stat_decrease.c_str());
							   break;
							   case Ally_lost_via_absorb://0x20,
								 Glosary.Ally_lost_via_absorb = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Ally_lost_via_absorb ");	
								 printf(Glosary.Ally_lost_via_absorb.c_str());
							   break;
							   case Enemy_lost_via_absorb://0x21,
								 Glosary.Enemy_lost_via_absorb = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Enemy_lost_via_absorb ");	
								 printf(Glosary.Enemy_lost_via_absorb.c_str());
							   break;
							   case Resistance_increase://0x22,
								 Glosary.Resistance_increase = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Resistance_increase ");	
								 printf(Glosary.Resistance_increase.c_str());
							   break;
							   case Resistance_decrease://0x23,
								 Glosary.Resistance_decrease = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Resistance_decrease ");	
								 printf(Glosary.Resistance_decrease.c_str());
							   break;
							   case Level_up_message://0x24,
								 Glosary.Level_up_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Level_up_message ");	
								 printf(Glosary.Level_up_message.c_str());
							   break;
							   case Skill_learned://0x25,
								 Glosary.Skill_learned = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Skill_learned ");	
								 printf(Glosary.Skill_learned.c_str());
							   break;
							   case Shop_greeting ://0x29,
								 Glosary.Shop_greeting = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shop_greeting ");	
								 printf(Glosary.Shop_greeting.c_str());
							   break;
							   case Shop_regreeting ://0x2A,
								 Glosary.Shop_regreeting = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shop_regreeting ");	
								 printf(Glosary.Shop_regreeting.c_str());
							   break;
							   case Buy_message ://0x2B,
								 Glosary.Buy_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Buy_message ");	
								 printf(Glosary.Buy_message.c_str());
							   break;
							   case Sell_message ://0x2C,
								 Glosary.Sell_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Sell_message ");	
								 printf(Glosary.Sell_message.c_str());
							   break;
							   case Leave_message ://0x2D,
								 Glosary.Leave_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Leave_message ");	
								 printf(Glosary.Leave_message.c_str());
							   break;
							   case Buying_message ://0x2E,
								 Glosary.Buying_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Buying_message ");	
								 printf(Glosary.Buying_message.c_str());
							   break;
							   case Quantity_to_buy ://0x2F,
								 Glosary.Quantity_to_buy = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Quantity_to_buy ");	
								 printf(Glosary.Quantity_to_buy.c_str());
							   break;
							   case Purchase_end ://0x30,
								 Glosary.Purchase_end = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Purchase_end ");	
								 printf(Glosary.Purchase_end.c_str());
							   break;
							   case Selling_message ://0x31,
								 Glosary.Selling_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Selling_message ");	
								 printf(Glosary.Selling_message.c_str());
							   break;
							   case Quantity_to_sell ://0x32,
								 Glosary.Quantity_to_sell = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Quantity_to_sell ");	
								 printf(Glosary.Quantity_to_sell.c_str());
							   break;
							   case Selling_end ://0x33,
								 Glosary.Selling_end = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Selling_end ");	
								 printf(Glosary.Selling_end.c_str());
							   break;
							   case Shop_greeting_2 ://0x36,
								 Glosary.Shop_greeting_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shop_greeting_2 ");	
								 printf(Glosary.Shop_greeting_2.c_str());
							   break;
							   case Shop_regreeting_2 ://0x37,
								 Glosary.Shop_regreeting_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shop_regreeting_2 ");	
								 printf(Glosary.Shop_regreeting_2.c_str());
							   break;
							   case Buy_message_2 ://0x38,
								 Glosary.Buy_message_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Buy_message_2 ");	
								 printf(Glosary.Buy_message_2.c_str());
							   break;
							   case Sell_message_2 ://0x39,
								 Glosary.Sell_message_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Sell_message_2 ");	
								 printf(Glosary.Sell_message_2.c_str());
							   break;
							   case Leave_message_2 ://0x3A,
								 Glosary.Leave_message_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Leave_message_2 ");	
								 printf(Glosary.Leave_message_2.c_str());
							   break;
							   case Buying_message_2 ://0x3B,
								 Glosary.Buying_message_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Buying_message_2 ");	
								 printf(Glosary.Buying_message_2.c_str());
							   break;
							   case Quantity_to_buy_2 ://0x3C,
								 Glosary.Quantity_to_buy_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Quantity_to_buy_2 ");	
								 printf(Glosary.Quantity_to_buy_2.c_str());
							   break;
							   case Purchase_end_2 ://0x3D,
								 Glosary.Purchase_end_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Purchase_end_2 ");	
								 printf(Glosary.Purchase_end_2.c_str());
							   break;
							   case Selling_message_2 ://0x3E,
								 Glosary.Selling_message_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Selling_message_2 ");	
								 printf(Glosary.Selling_message_2.c_str());
							   break;
							   case Quantity_to_sell_2 ://0x3F,
								 Glosary.Quantity_to_sell_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Quantity_to_sell_2 ");	
								 printf(Glosary.Quantity_to_sell_2.c_str());
							   break;
							   case Selling_end_2 ://0x40,
								 Glosary.Selling_end_2 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Selling_end_2 ");	
								 printf(Glosary.Selling_end_2.c_str());
							   break;
							   case Shop_greeting_3 ://0x43,
								 Glosary.Shop_greeting_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shop_greeting_3 ");	
								 printf(Glosary.Shop_greeting_3.c_str());
							   break;
							   case Shop_regreeting_3 ://0x44,
								 Glosary.Shop_regreeting_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shop_regreeting_3 ");	
								 printf(Glosary.Shop_regreeting_3.c_str());
							   break;
							   case Buy_message_3 ://0x45,
								 Glosary.Buy_message_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Buy_message_3 ");	
								 printf(Glosary.Buy_message_3.c_str());
							   break;
							   case Sell_message_3 ://0x46,
								 Glosary.Sell_message_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Sell_message_3 ");	
								 printf(Glosary.Sell_message_3.c_str());
							   break;
							   case Leave_message_3 ://0x47,
								 Glosary.Leave_message_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Leave_message_3 ");	
								 printf(Glosary.Leave_message_3.c_str());
							   break;
							   case Buying_message_3 ://0x48,
								 Glosary.Buying_message_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Buying_message_3 ");	
								 printf(Glosary.Buying_message_3.c_str());
							   break;
							   case Quantity_to_buy_3 ://0x49,
								 Glosary.Quantity_to_buy_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Quantity_to_buy_3 ");	
								 printf(Glosary.Quantity_to_buy_3.c_str());
							   break;
							   case Purchase_end_3 ://0x4A,
								 Glosary.Purchase_end_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Purchase_end_3 ");	
								 printf(Glosary.Purchase_end_3.c_str());
							   break;
							   case Selling_message_3 ://0x4B,
								 Glosary.Selling_message_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Selling_message_3 ");	
								 printf(Glosary.Selling_message_3.c_str());
							   break;
							   case Quantity_to_sell_3 ://0x4C,
								 Glosary.Quantity_to_sell_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Quantity_to_sell_3 ");	
								 printf(Glosary.Quantity_to_sell_3.c_str());
							   break;
							   case Selling_end_3 ://0x4D,
								 Glosary.Selling_end_3 = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Selling_end_3 ");	
								 printf(Glosary.Selling_end_3.c_str());
							   break;
							   case Inn_A_Greeting_A://0x50,
								 Glosary.Inn_A_Greeting_A = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_A_Greeting_A ");	
								 printf(Glosary.Inn_A_Greeting_A.c_str());
							   break;
							   case Inn_A_Greeting_B://0x51,
								 Glosary.Inn_A_Greeting_B = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_A_Greeting_B ");	
								 printf(Glosary.Inn_A_Greeting_B.c_str());
							   break;
							   case Inn_A_Greeting_C://0x52,
								 Glosary.Inn_A_Greeting_C = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_A_Greeting_C ");	
								 printf(Glosary.Inn_A_Greeting_C.c_str());
							   break;
							   case Inn_A_Accept://0x53,
								 Glosary.Inn_A_Accept = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_A_Accept ");	
								 printf(Glosary.Inn_A_Accept.c_str());
							   break;
							   case Inn_A_Cancel://0x54,
								 Glosary.Inn_A_Cancel = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_A_Cancel ");	
								 printf(Glosary.Inn_A_Cancel.c_str());
							   break;
							   case Inn_B_Greeting_A://0x55,
								 Glosary.Inn_B_Greeting_A = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_B_Greeting_A ");	
								 printf(Glosary.Inn_B_Greeting_A.c_str());
							   break;
							   case Inn_B_Greeting_B://0x56,
								 Glosary.Inn_B_Greeting_B = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_B_Greeting_B ");	
								 printf(Glosary.Inn_B_Greeting_B.c_str());
							   break;
							   case Inn_B_Greeting_C://0x57,
								 Glosary.Inn_B_Greeting_C = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_B_Greeting_C ");	
								 printf(Glosary.Inn_B_Greeting_C.c_str());
							   break;
							   case Inn_B_Accept://0x58,
								 Glosary.Inn_B_Accept = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_B_Accept ");	
								 printf(Glosary.Inn_B_Accept.c_str());
							   break;
							   case Inn_B_Cancel://0x59,
								 Glosary.Inn_B_Cancel = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Inn_B_Cancel ");	
								 printf(Glosary.Inn_B_Cancel.c_str());
							   break;
							   case Loose_items://0x5C,
								 Glosary.Loose_items = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Loose_items ");	
								 printf(Glosary.Loose_items.c_str());
							   break;
							   case Equipped_items://0x5D,
								 Glosary.Equipped_items = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Equipped_items ");	
								 printf(Glosary.Equipped_items.c_str());
							   break;
							   case Monetary_Unit://0x5F,
								 Glosary.Monetary_Unit = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Monetary_Unit ");	
								 printf(Glosary.Monetary_Unit.c_str());
							   break;
							   case Combat_Command://0x65,
								 Glosary.Combat_Command = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Combat_Command ");	
								 printf(Glosary.Combat_Command.c_str());
							   break;
							   case Combat_Auto://0x66,
								 Glosary.Combat_Auto = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Combat_Auto ");	
								 printf(Glosary.Combat_Auto.c_str());
							   break;
							   case Combat_Run://0x67,
								 Glosary.Combat_Run = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Combat_Run ");	
								 printf(Glosary.Combat_Run.c_str());
							   break;
							   case Command_Attack://0x68,
								 Glosary.Command_Attack = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Command_Attack ");	
								 printf(Glosary.Command_Attack.c_str());
							   break;
							   case Command_Defend://0x69,
								 Glosary.Command_Defend = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Command_Defend ");	
								 printf(Glosary.Command_Defend.c_str());
							   break;
							   case Command_Item://0x6A,
								 Glosary.Command_Item = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Command_Item ");	
								 printf(Glosary.Command_Item.c_str());
							   break;
							   case Command_Skill://0x6B,
								 Glosary.Command_Skill = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Command_Skill ");	
								 printf(Glosary.Command_Skill.c_str());
							   break;
							   case Menu_Equipment://0x6C,
								 Glosary.Menu_Equipment = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Menu_Equipment ");	
								 printf(Glosary.Menu_Equipment.c_str());
							   break;
							   case Menu_Save://0x6E,
								 Glosary.Menu_Save = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Menu_Save ");	
								 printf(Glosary.Menu_Save.c_str());
							   break;
							   case Menu_Quit://0x70,
								 Glosary.Menu_Quit = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Menu_Quit ");	
								 printf(Glosary.Menu_Quit.c_str());
							   break;
							   case New_Game://0x72,
								 Glosary.New_Game = ReadString(Stream, ChunkInfo.Length);
								 printf("\n New_Game ");	
								 printf(Glosary.New_Game.c_str());
							   break;
							   case Load_Game://0x73,
								 Glosary.Load_Game = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Load_Game ");	
								 printf(Glosary.Load_Game.c_str());
							   break;
							   case Exit_to_Windows://0x75,
								 Glosary.Exit_to_Windows = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Exit_to_Windows ");	
								 printf(Glosary.Exit_to_Windows.c_str());
							   break;
							   case Level://0x7B,
								 Glosary.Level = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Level ");	
								 printf(Glosary.Level.c_str());
							   break;
							   case Health://0x7C,
								 Glosary.Health = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Health ");	
								 printf(Glosary.Health.c_str());
							   break;
							   case Mana://0x7D,
								 Glosary.Mana = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Mana ");	
								 printf(Glosary.Mana.c_str());
							   break;
							   case Normal_status://0x7E,
								 Glosary.Normal_status = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Normal_status ");	
								 printf(Glosary.Normal_status.c_str());
							   break;
							   case Experience ://0x7F,//(short)
								 Glosary.Experience = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Experience ");	
								 printf(Glosary.Experience.c_str());
							   break;
							   case Level_short ://0x80,//(short)
								 Glosary.Level_short = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Level_short ");	
								 printf(Glosary.Level_short.c_str());
							   break;
							   case Health_short ://0x81,//(short)
								 Glosary.Health_short = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Health_short ");	
								 printf(Glosary.Health_short.c_str());
							   break;
							   case Mana_short ://0x82,//(short)
								 Glosary.Mana_short = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Mana_short ");	
								 printf(Glosary.Mana_short.c_str());
							   break;
							   case Mana_cost://0x83,
								 Glosary.Mana_cost = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Mana_cost ");	
								 printf(Glosary.Mana_cost.c_str());
							   break;
							   case Attack://0x84,
								 Glosary.Attack = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Attack ");	
								 printf(Glosary.Attack.c_str());
							   break;
							   case Defense://0x85,
								 Glosary.Defense = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Defense ");	
								 printf(Glosary.Defense.c_str());
							   break;
							   case Mind://0x86,
								 Glosary.Mind = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Mind ");	
								 printf(Glosary.Mind.c_str());
							   break;
							   case Agility://0x87,
								 Glosary.Agility = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Agility ");	
								 printf(Glosary.Agility.c_str());
							   break;
							   case Weapon://0x88,
								 Glosary.Weapon = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Weapon ");	
								 printf(Glosary.Weapon.c_str());
							   break;
							   case Shield://0x89,
								 Glosary.Shield = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Shield ");	
								 printf(Glosary.Shield.c_str());
							   break;
							   case Armor://0x8A,
								 Glosary.Armor = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Armor ");	
								 printf(Glosary.Armor.c_str());
							   break;
							   case Helmet://0x8B,
								 Glosary.Helmet = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Helmet ");	
								 printf(Glosary.Helmet.c_str());
							   break;
							   case Accessory://0x8C,
								 Glosary.Accessory = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Accessory ");	
								 printf(Glosary.Accessory.c_str());
							   break;
							   case Save_game_message://0x92,
								 Glosary.Save_game_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Save_game_message ");	
								 printf(Glosary.Save_game_message.c_str());
							   break;
							   case Load_game_message://0x93,
								 Glosary.Load_game_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Load_game_message ");	
								 printf(Glosary.Load_game_message.c_str());
							   break;
							   case Exit_game_message://0x94,
								 Glosary.Exit_game_message = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Exit_game_message ");	
								 printf(Glosary.Exit_game_message.c_str());
							   break;
							   case File_name://0x97,
								 Glosary.File_name = ReadString(Stream, ChunkInfo.Length);
								 printf("\n File_name ");	
								 printf(Glosary.File_name.c_str());
							   break;
							   case General_Yes://0x98,
								 Glosary.General_Yes = ReadString(Stream, ChunkInfo.Length);
								 printf("\n General_Yes ");	
								 printf(Glosary.General_Yes.c_str());
							   break;
							   case General_No://0x99
								 Glosary.General_No = ReadString(Stream, ChunkInfo.Length);
								 printf("\n General_No ");	
								 printf(Glosary.General_No.c_str());
							   break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;			 
							   default:
									   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
				 } while(ChunkInfo.ID!=0);	   
return(Glosary);
}  
stcSystem LDB::SystemChunk(int Length,FILE * Stream)//movimientos de la pagina
{		short dat;
		 int id,data; 
		 std::string name;
		 stcSystem System; 
			  do{			   
						  ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
						  if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
						  ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {					 
							   case Skiff_graphic://0x0B,
								 System.Skiff_graphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Skiff_graphic ");	
								 printf(System.Skiff_graphic.c_str());
								 break;
							   case Boat_graphic://0x0C,
								 System.Boat_graphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Boat_graphic ");	
								 printf(System.Boat_graphic.c_str());
								 break;
							   case Airship_graphic://0x0D,
								 System.Airship_graphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Airship_graphic ");	
								 printf(System.Airship_graphic.c_str());
								 break;
							   case Skiff_index://0x0E,
								 System.Skiff_index = ReadCompressedInteger(Stream);
								 printf("\n Skiff_index %d",System.Skiff_index); 
								 break;
							   case Boat_index://0x0F,
								 System.Boat_index = ReadCompressedInteger(Stream);
								 printf("\n Boat_index %d",System.Boat_index); 
								 break;
							   case Airship_index://0x10,
								 System.Airship_index = ReadCompressedInteger(Stream);
								 printf("\n Airship_index %d",System.Airship_index); 
								 break;
							   case Title_graphic://0x11,
								 System.Title_graphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Title_graphic ");	
								 printf(System.Title_graphic.c_str());
								 break;
							   case Game_Over_graphic://0x12,
								 System.Game_Over_graphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n Game_Over_graphic ");	
								 printf(System.Game_Over_graphic.c_str());
								 break;
							   case System_graphic://0x13,
								 System.System_graphic = ReadString(Stream, ChunkInfo.Length);
								 printf("\n System_graphic ");	
								 printf(System.System_graphic.c_str());
								 break;
							   case Heroes_in_starting://0x15,
								 System.Heroes_in_starting = ReadCompressedInteger(Stream);
								 printf("\n Heroes_in_starting %d",  System.Heroes_in_starting); 
								 break;
							   case Starting_party://0x16,
									printf("\n Starting_party");
									while(ChunkInfo.Length--){
									fread(&dat, sizeof(short), 1, Stream);
									System.vc_sh_Starting_party.push_back(dat);
								   printf("%d ",dat);
								   ChunkInfo.Length--;
								   }
							   break; 
							   case Title_music://0x1F,
									System.Title_music=musicChunk(ChunkInfo.Length,Stream);//0x1F,
								 break;
							   case Battle_music://0x20,
									System.Battle_music=musicChunk(ChunkInfo.Length,Stream);//0x20,
								 break;
							   case Battle_end_music://0x21,
									System.Battle_end_music=musicChunk(ChunkInfo.Length,Stream);//0x21,
								 break;
							   case Inn_music://0x21,
									System.Inn_music=musicChunk(ChunkInfo.Length,Stream);//0x22,
								 break;
							   case Skiff_music://0x21,
									System.Skiff_music=musicChunk(ChunkInfo.Length,Stream);//0x23,
								 break;
							   case Boat_music://0x21,
									System.Boat_music=musicChunk(ChunkInfo.Length,Stream);//0x24,
								 break;
							   case Airship_music://0x21,
									System.Airship_music=musicChunk(ChunkInfo.Length,Stream);//0x25,
								 break;
							   case Game_Over_music://0x21,
									System.Game_Over_music=musicChunk(ChunkInfo.Length,Stream);//0x26,
								 break;
							   case Cursor_SFX://0x21,
									System.Cursor_SFX=musicChunk(ChunkInfo.Length,Stream);//0x29,
								 break;
							   case Accept_SFX://0x21,
									System.Accept_SFX=musicChunk(ChunkInfo.Length,Stream);//0x2A,
								 break;
							   case Cancel_SFX://0x21,
									System.Cancel_SFX=musicChunk(ChunkInfo.Length,Stream);//0x2B,
								 break;
							   case Illegal_SFX://0x21,
									System.Illegal_SFX=musicChunk(ChunkInfo.Length,Stream);//0x2C,
								 break;
							   case Battle_SFX://0x21,
									System.Battle_SFX=musicChunk(ChunkInfo.Length,Stream);//0x2D,
								 break;
							   case Escape_SFX://0x21,
									System.Escape_SFX=musicChunk(ChunkInfo.Length,Stream);//0x2E,
								 break;
							   case Enemy_attack_SFX://0x21,
									System.Enemy_attack_SFX=musicChunk(ChunkInfo.Length,Stream);//0x2F,
								 break;
							   case Enemy_damaged_SFX://0x21,
									System.Enemy_damaged_SFX=musicChunk(ChunkInfo.Length,Stream);//0x30,
								 break;
							   case Ally_damaged_SFX://0x21,
									System.Ally_damaged_SFX=musicChunk(ChunkInfo.Length,Stream);//0x31,
								 break;
							   case Evasion_SFX://0x21,
									System.Evasion_SFX=musicChunk(ChunkInfo.Length,Stream);//0x32,
								 break;
							   case Enemy_dead_SFX://0x21,
									System.Enemy_dead_SFX=musicChunk(ChunkInfo.Length,Stream);//0x33,
								 break;
							   case Item_use_SFX://0x21,
									System.Item_use_SFX=musicChunk(ChunkInfo.Length,Stream);//0x34,
								 break;
							   case Map_exit_transition://0x3D,
								 System.Map_exit_transition = ReadCompressedInteger(Stream);
								 printf("\n Map_exit_transition %d",  System.Map_exit_transition); 
								 break;
							   case Map_enter_transition://0x3E,
								 System.Map_enter_transition = ReadCompressedInteger(Stream);
								 printf("\n Map_enter_transition %d",  System.Map_enter_transition); 
								 break;
							   case Battle_start_fadeout://0x3F,
								 System.Battle_start_fadeout = ReadCompressedInteger(Stream);
								 printf("\n Battle_start_fadeout %d",  System.Battle_start_fadeout); 
								 break;
							   case Battle_start_fadein://0x40,
								 System.Battle_start_fadein = ReadCompressedInteger(Stream);
								 printf("\n Battle_start_fadein %d",  System.Battle_start_fadein); 
								 break;
							   case Battle_end_fadeout://0x41,
								 System.Battle_end_fadeout = ReadCompressedInteger(Stream);
								 printf("\n Battle_end_fadeout %d",  System.Battle_end_fadeout); 
								 break;
							   case Battle_end_fadein://0x42,
								 System.Battle_end_fadein = ReadCompressedInteger(Stream);
								 printf("\n Battle_end_fadein %d",  System.Battle_end_fadein); 
								 break;
//0x47							   case 	//no identificados	
//0x48	//no identificados	
							   case Selected_condition://0x51,
								 System.Selected_condition = ReadCompressedInteger(Stream);
								 printf("\n Selected_condition %d",  System.Selected_condition); 
								 break;
							   case Selected_hero://0x52,
								 System.Selected_hero = ReadCompressedInteger(Stream);
								 printf("\n Selected_hero %d",  System.Selected_hero); 
								 break;
							   case Battle_test_BG://0x54,
								 System.Battle_test_BG = ReadCompressedInteger(Stream);
								 printf("\n Battle_test_BG %d",  System.Battle_test_BG); 
								 break;
							   case Battle_test_data://0x55
								  printf("\n Battle_test_data "); 
									while(ChunkInfo.Length--){
									fread(&Void, sizeof(char), 1, Stream);
									printf("%d",Void);
									}
							   break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;			 
						  default:
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
			  }while(ChunkInfo.ID!=0);  
	   return(System);	  
}  
std:: vector <std::string> LDB::Switch_VariableChunk(int Length,FILE * Stream)//simplemente un vector de string
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std:: vector <std::string> names;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			 do {	 
				ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
				if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
				ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño			   
				
				if((id>datareaded)&&(ChunkInfo.ID==0))
				{names.push_back("");
				printf("\n nombre ");
				datareaded++;
					}
				
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case 0x01:// nombres de los swiches
								 name = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(name.c_str());   
								 names.push_back(name);
								 datareaded++;
								break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
				} while(ChunkInfo.ID!=0);
		  
		  }   
		 return(names);
}

void LDB:: Comand_Chunk2(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 datatoread=Length;//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			 do {	 
				ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
				if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
				ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño			   
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case 0x01:// nombres de los swiches
								 name = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(name.c_str());		
								break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
				} while(ChunkInfo.ID!=0);
		  datareaded++;
		  }   
		   ChunkInfo.ID	 = 1;//no afectar el otro ciclo
}
void LDB:: Comand_Chunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;int datico;
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array  
			 do {	 
				ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	  
				if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
				ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño			   
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case 0x01:// nombres de los swiches
							  name = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(name.c_str());		
								break;
						  case 0x0C:// nombres de los swiches
							Comand_Chunk2(ChunkInfo.Length,Stream);
							   datareaded++;
								break;	 
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
				} while(ChunkInfo.ID!=0);
		  datareaded++;
		  }   
}



std:: vector <stcProfetion>  LDB:: Profession_Chunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std::vector <stcProfetion> vecProfetion;
		 stcProfetion Profetion;	 
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			 do {	 
				ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
				if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
				ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño			   
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case Profetion_Name://0x01,
								 Profetion.strName = ReadString(Stream, ChunkInfo.Length);
								 printf("\n strName ");	
								 printf(Profetion.strName.c_str());		
								break;		
						  case  Profetion_TwoWeapon://0x15,
								Profetion.TwoWeapon = ReadCompressedInteger(Stream);
								printf("\n TwoWeapon %d",  Profetion.TwoWeapon); 
								break;
						  case  Profetion_fixed_equipment ://0x16,
								Profetion.fixed_equipment = ReadCompressedInteger(Stream);
								printf("\n fixed_equipment %d",  Profetion.fixed_equipment); 
								break;
						  case  Profetion_AI_forced_action ://0x17,
								Profetion.AI_forced_action = ReadCompressedInteger(Stream);
								printf("\n AI_forced_action %d",  Profetion.AI_forced_action); 
								break;
						  case  Profetion_strong_defense ://0x18,
								Profetion.strong_defense = ReadCompressedInteger(Stream);
								printf("\n strong_defense %d",  Profetion.strong_defense); 
								break;
 						 // case  Profetion_Each_level ://0x1F,
							//	Profetion.TwoWeapon = ReadCompressedInteger(Stream);
							 //   printf("\n TwoWeapon %d",  Profetion.TwoWeapon); 
							//	break;
 						  case  Profetion_Experience_curve_basic_values ://0x29,
								Profetion.Experience_curve_basic_values = ReadCompressedInteger(Stream);
								printf("\n Experience_curve_basic_values %d",  Profetion.Experience_curve_basic_values); 
								break;
						  case  Profetion_Experience_curve_increase_degree ://0x2A,
								Profetion.Experience_curve_increase_degree = ReadCompressedInteger(Stream);
								printf("\n Experience_curve_increase_degree %d",  Profetion.Experience_curve_increase_degree); 
								break;
 						  case  Profetion_Experience_curve_correction_value://0x2B,
								Profetion.Experience_curve_correction_value = ReadCompressedInteger(Stream);
								printf("\n Experience_curve_correction_value %d",  Profetion.Experience_curve_correction_value); 
								break;
 						  case  Profetion_Animated_battle	://0x3E,
								Profetion.Animated_battle = ReadCompressedInteger(Stream);
								printf("\n Animated_battle %d",  Profetion.Animated_battle); 
								break;
 						  //case  Profetion_Special_skills_level://0x3F,
						   //	 Profetion.TwoWeapon = ReadCompressedInteger(Stream);
						   //	 printf("\n TwoWeapon %d",  Profetion.TwoWeapon); 
						   //	 break;
 						  case  Profetion_Effectiveness_state_number ://0x47,
								Profetion.Effectiveness_state_number = ReadCompressedInteger(Stream);
								printf("\n Effectiveness_state_number %d",  Profetion.Effectiveness_state_number); 
								break;
						 // case  Profetion_Effectiveness_state_data ://0x48,
						 //	   Profetion.TwoWeapon = ReadCompressedInteger(Stream);
						 //	   printf("\n TwoWeapon %d",  Profetion.TwoWeapon); 
						 //	   break;
						  case  Profetion_Effectiveness_Attribute_number ://0x49,
								Profetion.Effectiveness_Attribute_number = ReadCompressedInteger(Stream);
								printf("\n Effectiveness_Attribute_number %d",  Profetion.Effectiveness_Attribute_number); 
								break; 
						//  case  Profetion_Effectiveness_Attribute_data ://0x4A,
						//		Profetion.TwoWeapon = ReadCompressedInteger(Stream);
						//		printf("\n TwoWeapon %d",  Profetion.TwoWeapon); 
						//		break;
						//  case  Profetion_Combat_Command://0x50								
						//		Profetion.TwoWeapon = ReadCompressedInteger(Stream);
						//		printf("\n TwoWeapon %d",  Profetion.TwoWeapon); 
						//		break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
				} while(ChunkInfo.ID!=0);
		  datareaded++;
		 vecProfetion.push_back(Profetion);
		 Profetion.clear();
		  }   
		  return(vecProfetion);
}

std:: vector <stcFight_anim> LDB:: Fightanim_Chunk(int Length,FILE * Stream)
{		
		 int id,datatoread=0,datareaded=0; 
		 std::string name;
		 std::vector <stcFight_anim> vecFight_anim;
		 stcFight_anim Fight_anim;	   
		 datatoread=ReadCompressedInteger(Stream);//numero de datos
		 while(datatoread>datareaded) // si no hay mas en el array
		 {	  
		 id= ReadCompressedInteger(Stream);//lectura de id 1 de array		 
			 do {	 
				ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
				if(ChunkInfo.ID!=0)// si es fin de bloque no leas la longitud
				ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño			   
						 switch(ChunkInfo.ID)// tipo de la primera dimencion
						 {   
						  case Name:// nombres de los swiches
								 name = ReadString(Stream, ChunkInfo.Length);
								 printf("\n nombre ");	
								 printf(name.c_str());		
								break;
						  case CHUNK_MAP_END_OF_BLOCK:
							   break;	  
							   default:
							   // saltate un pedazo del tamaño de la longitud
							   while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
							   break; 
						  }
				} while(ChunkInfo.ID!=0);
		  datareaded++;
		 vecFight_anim.push_back(Fight_anim);
		 Fight_anim.clear();
		  } 
		  return(vecFight_anim);  
}


void LDB::GetNextChunk(FILE * Stream)
{
		int nodes=0,temp=0,enemygroups=0,idgroup=0,enemy=0;
		unsigned char Void;
		tChunk ChunkInfo; // informacion del pedazo leido
		// Loop while we haven't reached the end of the file
		while(!feof(Stream))
		{
			ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo	 
			ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño	
		 if(ChunkInfo.Length>0)  
			switch(ChunkInfo.ID)// segun el tipo
			{																										   
			 
			/* case CHUNK_Hero://terminado para el 2000
					heroChunk(ChunkInfo.Length,Stream);
				 break;
			 case CHUNK_Skill://terminado para el 2000
					skillChunk(ChunkInfo.Length,Stream);
					break; 
			 case CHUNK_Item:
					itemChunk(ChunkInfo.Length,Stream);
					break;  
			case CHUNK_Monster:
					mosterChunk(ChunkInfo.Length,Stream);
					break;
			case CHUNK_MonsterP:
					mosterpartyChunk(ChunkInfo.Length,Stream);
					break;  
			case CHUNK_Terrain:
					TerrainChunk(ChunkInfo.Length,Stream);
					break;	   
			case CHUNK_Attribute:
				   AttributeChunk(ChunkInfo.Length,Stream);
					break;  
			case CHUNK_States:
				   StatesChunk(ChunkInfo.Length,Stream);
					break; 
			case CHUNK_Animation:
				   AnimationChunk(ChunkInfo.Length,Stream);
					break;  
			case CHUNK_Tileset:
				   TilesetChunk(ChunkInfo.Length,Stream);
					break;	  
			case CHUNK_String:
				   StringChunk(ChunkInfo.Length,Stream);
					break;	  */
			case CHUNK_System:	
				   SystemChunk(ChunkInfo.Length,Stream);
					break;   /*			
			case CHUNK_Event: 
				   EventChunk(ChunkInfo.Length,Stream);
					break;   
			case CHUNK_Switch:
				   Switch_VariableChunk(ChunkInfo.Length,Stream);
					break;
			case CHUNK_Variable:
				   Switch_VariableChunk(ChunkInfo.Length,Stream);
					break;				
			case CHUNK_Event1:
				   EventChunk(ChunkInfo.Length,Stream);
					break;
			case CHUNK_Event2:
				   EventChunk(ChunkInfo.Length,Stream);
					break;				
			case CHUNK_Event3:
				   EventChunk(ChunkInfo.Length,Stream);
					break;	   
		   case CHUNK_Comand:
				 Comand_Chunk(ChunkInfo.Length,Stream);
				 break; 
			case CHUNK_Profession:
				   Profession_Chunk(ChunkInfo.Length,Stream);
					break;  
			   case CHUNK_Profession2:
				   Profession_Chunk(ChunkInfo.Length,Stream);
					break; 
										  
			case CHUNK_Fightanim:
				   Fightanim_Chunk(ChunkInfo.Length,Stream);
					break; 
			 */				  
			case CHUNK_MAP_END_OF_BLOCK:
					  break;							
				default:
					// saltate un pedazo del tamaño de la longitud
					while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
					break;
			}
			
		}
	}
/*


void LDB::ShowInformation()
{ // muestra de informacion del mapa
int j,i;
for(j=0;j<treesize;j++)
{
printf("\n\nnombre ");	
printf(str_Vector[j].strName.c_str());
printf("\nid del mapa padre %d",str_Vector[j].intIdMapF);
printf("\nprofundiadad %d",str_Vector[j].intDepth);
printf("\nmapa-area %d",str_Vector[j].intFlagMA);
printf("\nbarra de desaplasamiento X %d",str_Vector[j].intXbar);
printf("\nbarra de desaplasamiento Y %d",str_Vector[j].intYbar);
printf("\ntiene hijo %d",str_Vector[j].intSon);
printf("\ntiene musica de fondo %d",str_Vector[j].intMusic);
//printf("\nnombre musica ");	
//printf(str_Vector[j].strMusic.c_str());
printf("\ntiene fondo de batalla %d",str_Vector[j].intBatle);
printf("\nnombre de fondo ");	
printf(str_Vector[j].strBatle.c_str());
printf("\npermite teletrasporte %d",str_Vector[j].intTelepor);
printf("\npermite guardar %d",str_Vector[j].intScape);
for(i=0;i< str_Vector[j].vcEnemyGroup.size();i++)
printf("\n grupo enemigo%d",str_Vector[j].vcEnemyGroup[i]);
printf("\npasos para encuentro enemigo%d",str_Vector[j].intNofsteeps);
}
printf("\nid party %d",intPartymapId);
printf("\nparty x%d",intPartymapX);
printf("\nparty y %d",intPartymapY);

printf("\nid Skiff %d",intSkiffId);
printf("\nSkiff x%d",intSkiffX);
printf("\nSkiff y %d",intSkiffY);
  
printf("\nid Boat %d",intBoatId);
printf("\nBoat x%d",intBoatX);
printf("\nBoat y %d",intBoatY);

printf("\nid Airship %d",intAirshipId);
printf("\nAirship x%d",intAirshipX);
printf("\nAirship y %d",intAirshipY);
	  
}*/

