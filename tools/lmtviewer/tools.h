/* tools.h, miscellaneous shared routines.
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

#ifndef TOOLS_H
#define TOOLS_H

#include "wx/wx.h"
#include "wx/ffile.h"

// --- Chunk structure -----------------------------------------------------
// usada para guardar temporalemmte informacion de id y tama�os de pedazos de mapa
struct tChunk
{
	wxByte ID;

	union
	{
		unsigned long Length;
		unsigned long NumEvents;
	};

	unsigned long BytesRead;
};

// --- Read functions ------------------------------------------------------
unsigned long ReadCompressedInteger(wxFFile * FileStream);
wxString ReadString(wxFFile * FileStream);
wxString ReadString(wxFFile * FileStream, wxByte Lenght);
#endif
