/* lmt.h, LcfMapTree reader class.
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

#ifndef LMT_H
#define LMT_H

#include <vector>

struct bgm_data
{
	std::string	name;
	int		fade_in;
	int		volume;
	int		tempo;
	int		balance;
};

struct item
{
	std::string		name;			///< 0x01 nombre del mapa
	int			parent_id;		///< 0x02 ID del mapa padre
	int			depth;			///< 0x03 Profundidad del árbol
	int			type;			///< 0x04 Bandera de mapa o área
	int			scrollbar_x;		///< 0x05 Barra de desplazamiento  X del mapa
	int			scrollbar_y;		///< 0x06 Barra de desplazamiento Y del mapa
	int			expanded;		///< 0x07 Tiene subrama (hijo)
	int			bgm;			///< 0x0B Música de fondo 
	bgm_data		bgm_file;		///< 0x0C Música de fondo (archivo) String
	int			battle;			///< 0x15 Fondo de batalla 
	std::string		battle_file;		///< 0x16 Fondo de batalla (archivo) String
	int			teleport;		///< 0x1F Teletransporte
	int			escape;			///< 0x20 Escapar Entero
	int			save;			///< 0x21 Guardar Entero
	std::vector<int>	encounter;		///< 0x29 arreglo dos dimensiones con enemigos
	int			encounter_steps;	///< 0x2C Pasos entre encuentros
	int			area_start_x;		///< 0x33 Datos del área
	int			area_start_y;
	int			area_end_x;
	int			area_end_y;
};

class lmt
{
	public: 
		int			start_map_id;	///< 0x01 Party start map
		int			start_x;	///< 0x02 Party start X
		int			start_y;	///< 0x03 Party start Y
		int			skiff_map_id;	///< 0x0B Skiff start map
		int			skiff_x;	///< 0x0C Skiff start X
		int			skiff_y;	///< 0x0D Skiff start Y
		int			boat_map_id;	///< 0x15 Boat start map
		int			boat_x;		///< 0x16 Boat start X
		int			boat_y;		///< 0x17 Boat start Y
		int			airship_map_id;	///< 0x1F Airship start map
		int			airship_x;	///< 0x20 Airship start X
		int			airship_y;	///< 0x21 Airship start Y
		int			size;
		std::vector<item>	list;
		std::vector<int>	order;
		// Methods
		bool	load(std::string filename);
		void	print();
	private:
		void	read_tree(FILE * file);
		void	clear(item * leaf);
};

#endif
