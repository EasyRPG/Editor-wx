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

unsigned long ReadCompressedInteger(wxFFile * FileStream)
{
    unsigned long Value = 0;
    wxByte Temporal = 0;

    // int i = 0;
    do
    {
        Value <<= 7;

        // Get byte's value
        FileStream->Read(&Temporal, 1);

        // Check if it's a BER integer
        Value |= Temporal & 0x7F;

    }
    while (Temporal & 0x80);

    return Value;
}

wxString ReadString(wxFFile * FileStream)
{
    wxByte Length;
    char * Characters;
    wxString String;

    // Read string lenght's
    FileStream->Read(&Length, 1);
    if (Length == 0) return wxString(_T(""));

    // Allocate string buffer
    Characters = new char[Length+1];
    memset(Characters, 0, Length+1);
    FileStream->Read(Characters, Length);

    // Get string and free characters buffer. FIXME: Character set from locale or selectable
    String = wxString(Characters, wxCSConv(wxT("CP1252")));
    delete Characters;

    return String;
}

wxString ReadString(wxFFile * FileStream, wxByte Length)
{
    char * Characters;
    wxString String;

    // Allocate string buffer
    Characters = new char[Length+1];
    memset(Characters, 0, Length+1);
    FileStream->Read(Characters, Length);

    // Get string and free characters buffer. FIXME: Character set from locale or selectable
    String = wxString(Characters, wxCSConv(wxT("CP1252")));
    delete Characters;

    return String;
}

