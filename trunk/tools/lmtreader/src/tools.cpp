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
	int Value = 0;
	unsigned char Temporal = 0;
	
	do
	{
		Value <<= 7;
		
		// Get byte's value
		fread(&Temporal, sizeof(char), 1, file);
		
		// Check if it's a BER integer
		Value |= Temporal & 0x7F;
		
	} while (Temporal & 0x80);
	
	return Value;
}

std::string read_string(FILE * file)
{
	unsigned char Length;
	char		* Characters;
	std::string		String;
	
	// Read string length
	fread(&Length, sizeof(char), 1, file);
	if (Length == 0) return std::string("");
	
	// Allocate string buffer
	Characters = new char[Length+1];
	memset(Characters, 0, Length+1);
	fread(Characters, sizeof(char), Length, file);
	
	// Get string and free characters buffer
	String = std::string(Characters);
	delete Characters;
	
	return String;
}

std::string read_string(FILE * file, int Length)
{
	char		* Characters;
	std::string	String;
	
	// Allocate string buffer
	Characters = new char[Length+1];
	memset(Characters, 0, Length+1);
	fread(Characters, sizeof(char), Length, file);
	
	// Get string and free characters buffer
	String = std::string(Characters);
	delete Characters;
	
	return String;
}

