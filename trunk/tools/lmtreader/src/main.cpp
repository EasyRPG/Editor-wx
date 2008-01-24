#include "tools.h"
#include "LMT.h"

int main()
{
	LMT MYLMT;
	MYLMT.Load("RPG_RT.lmt");
	MYLMT.ShowInformation();
	return 0;
}
