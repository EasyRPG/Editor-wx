
#include "CRpgLmt.h"

smart_buffer CRpgLmt::ReadData2()
{   unsigned char c;
	smart_buffer buf;
	int length =120;//no existe asi que lo invento saco de la manga;
	// un poco más de lo que pueda medir 
 // printf("\n tamaño del buffer %d ",length); 
begin=GetSeek();//la psicion atees de lalectura dle buffer 

//printf("\n la lactura inica en %d ",begin); 
	if(length>0){
		buf.New(length);
		Read(buf, length);
	}

	return buf;
}

bool CRpgLmt::Init(const char* szDir)
{
	int type, type2, id, max,max2,exa,seek;
	smart_buffer	buf;
	string			strFile;
	CRpgArray2		array2;
	CRpgArray2		array21;
    CRpgArray1		array1;
    bool exit = false;
	bInit = false;
	int count=0;
	
	if(strlen(szDir)){
		strFile += szDir;
		strFile += "\\";
	}
	strFile += "RPG_RT.lmt";

	// abre el achivo
	if(!OpenFile(strFile.c_str())){		
     printf("no puedo abrirlo\n ");                                
     return false;}
 
     treesize=ReadBerNumber();
 //    printf("\n tamaño del arbol %d ",treesize); 
saDataofTree.Resize(treesize);

	while((!IsEof())&&(!exit)){// no se nesesita el tipo es solo el array

if(count<treesize)
{		buf = ReadData2();
		array2 = CRpgUtil::GetArray2_1(buf);//asignamos el array
		
		end=CRpgUtil::get_set_sizeused(0,1)+1;//+1 para que inicie en el nuevo dato
	//	printf("\n los datos leidos tiene una longitud de %d ",end); 
		SetSeek((begin+end),0);//vete a la poscion real del final
	saDataofTree[count].strName	= array2.GetString(count, 0x01);
	
	saDataofTree[count].intIdMapF	= array2.GetNumber(count, 0x02);
	saDataofTree[count].intDepth	= array2.GetNumber(count, 0x03);
	saDataofTree[count].intFlagMA	= array2.GetNumber(count, 0x04);
	saDataofTree[count].intXbar	= array2.GetNumber(count, 0x05);
	saDataofTree[count].intYbar	= array2.GetNumber(count, 0x06);
	saDataofTree[count].intSon	= array2.GetNumber(count, 0x07);
	saDataofTree[count].intMusic	= array2.GetNumber(count, 0x0B);
	saDataofTree[count].strMusic	= array2.GetString(count, 0x0C);
	saDataofTree[count].intBatle	= array2.GetNumber(count, 0x15);
	saDataofTree[count].strBatle	= array2.GetString(count, 0x16);
	saDataofTree[count].intTelepor	= array2.GetNumber(count, 0x1F);
	saDataofTree[count].intScape	= array2.GetNumber(count, 0x20);
	saDataofTree[count].intSave	= array2.GetNumber(count, 0x21);
	array21	= CRpgUtil::GetArray2(array2.GetData(count, 0x29));//si tiene el tamaño
	max = array21.GetMaxRow();
	saDataofTree[count].intsaEnemy.Resize(max+1);
	for(id = 1; id<=max; id++){
	 saDataofTree[count].intsaEnemy[id] = array21.GetNumber(id, 0x01);
     }

	saDataofTree[count].intNofsteeps	= array2.GetNumber(count, 0x2C);
count++;
}else
{  
     
  	SetSeek((begin+end+5),0);//comete lo que no entiendo
      //  seek=GetSeek();
 //  printf("\n pos %d \n",seek);  
    buf = ReadData2();
    array1=CRpgUtil::GetArray1(buf);//asignamos el array
    InitD.intPartymapId=array1.GetNumber( 0x01);
    InitD.intPartymapX=array1.GetNumber( 0x02);
    InitD.intPartymapY=array1.GetNumber( 0x03);     
    InitD.intSkiffId=array1.GetNumber( 0x0B);
    InitD.intSkiffX=array1.GetNumber( 0x0C);
    InitD.intSkiffY=array1.GetNumber( 0x0D); 
    InitD.intBoatId=array1.GetNumber( 0x15);
    InitD.intBoatX=array1.GetNumber( 0x16);
    InitD.intBoatY=array1.GetNumber( 0x17); 
    InitD.intAirshipId=array1.GetNumber( 0x1F);
    InitD.intAirshipX=array1.GetNumber( 0x20);
    InitD.intAirshipY=array1.GetNumber( 0x21); 

exit=true;
}

	}	
        

	bInit = true;
	return true;
}

