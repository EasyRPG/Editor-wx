//#include <windows.h>
#include <stdio.h>
#include "./SDK/index.h"
//#include "sueLib/CImage/CImgUtil.h"
//#include "sueLib/CImage/CBmpIO.h"


int main(int argc, char *argv[])
{
	int num,i,j,max,naxe;
    CRpgLmt lmt;

	if(!lmt.Init()){
		printf("No encuentro el RPG_RT.lmt\n");
		return 0;
	}



 //smart_array< int > intsaEnemy;//< 0x29  arreglo dos dimenciones	 con enemigos


max=lmt.saDataofTree.GetSize();

for(j=0;j<max;j++)
{
printf("\n\nnombre ");	
printf(lmt.saDataofTree[j].strName.c_str());
printf("\nnombre musica ");	
printf(lmt.saDataofTree[j].strMusic.c_str());
printf("\nnombre de fondo ");	
printf(lmt.saDataofTree[j].strBatle.c_str());

printf("\nid del mapa padre %d",lmt.saDataofTree[j].intIdMapF);
printf("\nprofundiadad %d",lmt.saDataofTree[j].intDepth);
printf("\nmapa-area %d",lmt.saDataofTree[j].intFlagMA);
printf("\nbarra de desaplasamiento X %d",lmt.saDataofTree[j].intXbar);
printf("\nbarra de desaplasamiento Y %d",lmt.saDataofTree[j].intYbar);
printf("\ntiene hijo %d",lmt.saDataofTree[j].intSon);
printf("\ntiene musica de fondo %d",lmt.saDataofTree[j].intMusic);
printf("\ntiene fondo de batalla %d",lmt.saDataofTree[j].intBatle);
printf("\npermite teletrasporte %d",lmt.saDataofTree[j].intTelepor);
printf("\npermite guardar %d",lmt.saDataofTree[j].intScape);
printf("\npasos para encuentro enemigo%d",lmt.saDataofTree[j].intNofsteeps);
naxe=lmt.saDataofTree[j].intsaEnemy.GetSize();
for(i=1;i<naxe;i++)
printf("\nid encuetro enemigo %d",lmt.saDataofTree[j].intsaEnemy[i]);

}

printf(" \n\nparty id mapa %d \n",lmt.InitD.intPartymapId);
printf("posicion party x %d \n",lmt.InitD.intPartymapX);
printf("posicion party y %d \n",lmt.InitD.intPartymapY);
printf("bote id mapa %d \n",lmt.InitD.intSkiffId);
printf("posicion party x %d \n",lmt.InitD.intSkiffX);
printf("posicion party y %d \n",lmt.InitD.intSkiffY);
printf("barco id mapa %d \n",lmt.InitD.intBoatId);
printf("posicion barco x %d \n",lmt.InitD.intBoatX);
printf("posicion barco y %d \n",lmt.InitD.intBoatY);
printf("nave id mapa %d \n",lmt.InitD.intAirshipId);
printf("posicion nave x %d \n",lmt.InitD.intAirshipX);
printf("posicion nave y %d \n",lmt.InitD.intAirshipY);

printf("\n");

	return 0;
}
