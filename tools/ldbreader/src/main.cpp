#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "tools.h"
#include "LDB.h"

int main()
{
	LDB MYLDB;
	MYLDB.Load("RPG_RT.ldb");
	// MYLDB.ShowInformation();
	getchar();
	return 0;
}
