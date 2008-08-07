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

#include "wx/ffile.h"
#include "tools.h"

int read_int(wxFFile * file)
{
	int	value		= 0;
	wxByte	temporal	= 0;

	do
	{
		value = value << 7;

		// Get byte's value
		file->Read(&temporal, 1);

		// Check if it's a BER integer
		value = value | (temporal & 0x7F);
	}
	while (temporal & 0x80);

	return value;
}

wxString read_string(wxFFile * file)
{
	wxByte		length;
	char		* characters;
	wxString	result_string;

	// Read string length
	file->Read(&length, 1);
	if (length == 0) return wxString(_T(""));

	// Allocate string buffer
	characters = new char[length + 1];
	memset(characters, 0, length + 1);
	file->Read(characters, length);

	// Get string and free characters buffer. FIXME: Character set from locale or selectable
	result_string = wxString(characters, wxCSConv(wxT("CP1252")));
	delete characters;

	return result_string;
}

wxString read_string(wxFFile * file, int length)
{
	char		* characters;
	wxString	result_string;

	// Allocate string buffer
	characters = new char[length + 1];
	memset(characters, 0, length + 1);
	file->Read(characters, length);

	// Get string and free characters buffer. FIXME: Character set from locale or selectable
	result_string = wxString(characters, wxCSConv(wxT("CP1252")));
	delete characters;

	return result_string;
}
