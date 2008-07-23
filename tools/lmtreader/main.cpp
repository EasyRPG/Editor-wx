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

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s file\n", argv[0]);
	}
	else
	{
		lmt my_lmt;
		my_lmt.load(argv[1]);
		my_lmt.print();
	}
	return 0;
}
