/* main.cpp, LcfMapTree reader main program.
   Copyright (C) 2007 EasyRPG Project <http://easyrpg.sourceforge.net/>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "tools.h"
#include "lmt.h"

void proccessFile(char *file)
{
    lmt my_lmt;
	my_lmt.load(file);
	my_lmt.print();
}

int main(int argc, char *argv[])
{
    //User need to know what the program is about, right?
    printf("== LmtReader ==\n");
    printf("LmtReader is a tool of the EasyRPG project created to read .Lmt files.\n\n");
	if(argc != 2)
	{
		printf("Usage:\n%s file\n", argv[0]);
		printf("\nDo you want to type the file path?(y/n)");
		char in[1];
		scanf("%s", in);
		switch (in[0])
		{
		    case 'y':
		    case 'Y':
                char fileName[500];
                printf("Write the file path: ");
                scanf("%s",fileName);
                proccessFile(fileName);
                free(fileName);
		    break;
		    case 'n':
		    case 'N':
		    default:
		    break;
		}
		free (in);
	}
	else
	{
        proccessFile(argv[1]);
	}
	return 0;
}
