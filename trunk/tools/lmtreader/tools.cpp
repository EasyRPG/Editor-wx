/* tools.cpp, miscellaneous shared routines.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"

int read_int(FILE * file)
{
	int		value		= 0;
	unsigned char	temporal	= 0;

	do
	{
		value <<= 7;

		// Get byte's value
		fread(&temporal, 1, 1, file);

		// Check if it's a BER integer
		value |= temporal & 0x7F;

	} while(temporal & 0x80);

	return value;
}

std::string read_string(FILE * file)
{
	unsigned char	length;
	char		* characters;
	std::string	result_string;

	// Read string length
	fread(&length, 1, 1, file);
	if(length == 0)
	{
		return std::string("");
	}

	// Allocate string buffer
	characters = new char[length+1];
	memset(characters, 0, length+1);
	fread(characters, 1, length, file);

	// Get string and free characters buffer
	result_string = std::string(characters);
	delete characters;

	return result_string;
}

std::string read_string(FILE * file, int length)
{
	char		* characters;
	std::string	result_string;

	// Allocate string buffer
	characters = new char[length+1];
	memset(characters, 0, length+1);
	fread(characters, 1, length, file);

	// Get string and free characters buffer
	result_string = std::string(characters);
	delete characters;

	return result_string;
}
