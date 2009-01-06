/* lmt.cpp, LcfMapTree reader class.
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
#include <string>
#include <vector>
#include <algorithm>
#include "tools.h"
#include "lmt.h"

bool lmt::load(std::string filename)
{
    FILE *file;
    char dummy;
    int vehicle_chunk_id;
    int vehicle_chunk_size;

    file = fopen(filename.c_str(), "rb");
    //Check if the file is valid, if not...
    if (file == NULL)
    {
        printf("Unable to open file %s. make sure the file exists and you have read privileges on it.\n", filename.c_str());
        return 1;
    }
    //Read header
    if (read_string(file) != "LcfMapTree")
    {
        printf("Reading error: File is not a valid RPG Maker 2000/2003 map tree.\n");
        fclose(file);
        return 2;
    }
    //Read number of nodes
    total_nodes = read_int(file);
    read_int(file); //00 end of block
    //Read tree
    read_tree(file);
    read_int(file); //00 end of block
    //Read tree order
    tree_order.push_back(0); // Add 0 to the tree root
    for (int i = 0; i < total_nodes - 1; i++) //Root zero node is not included in this list, so total_nodes - 1
    {
        tree_order.push_back(read_int(file));
    }
    //Read selected node
    selected_node = read_int(file);
    //Read vehicles (if any)
    party_map_id = 0;
    party_x = 0;
    party_y = 0;
    skiff_map_id = 0;
    skiff_x = 0;
    skiff_y = 0;
    boat_map_id = 0;
    boat_x = 0;
    boat_y = 0;
    airship_map_id = 0;
    airship_x = 0;
    airship_y = 0;
    while (!feof(file))
    {
        vehicle_chunk_id = read_int(file);
        vehicle_chunk_size = read_int(file);
        switch (vehicle_chunk_id)
        {
        case 1: //0x01
            party_map_id = read_int(file);
            break;
        case 2: //0x02
            party_x = read_int(file);
            break;
        case 3: //0x03
            party_y = read_int(file);
            break;
        case 11: //0x0B
            skiff_map_id = read_int(file);
            break;
        case 12: //0x0C
            skiff_x = read_int(file);
            break;
        case 13: //0x0D
            skiff_y = read_int(file);
            break;
        case 21: //0x15
            boat_map_id = read_int(file);
            break;
        case 22: //0x16
            boat_x = read_int(file);
            break;
        case 23: //0x17
            boat_y = read_int(file);
            break;
        case 31: //0x1F
            airship_map_id = read_int(file);
            break;
        case 32: //0x20
            airship_x = read_int(file);
            break;
        case 33: //0x21
            airship_y = read_int(file);
            break;
        case 0: //0x00
            if (vehicle_chunk_size != 0)
            {
                printf("WARNING: Unexpected byte after end of block. Size: %d\n", vehicle_chunk_size);
            }
            break;
        default:
            printf("WARNING: Unknown vehicle block ID: %d (size: %d)\n", vehicle_chunk_id, vehicle_chunk_size);
            // skip unknown vehicle_chunk_id case
            for (int i = 1 ; i > vehicle_chunk_size; i++)
            {
                fread(&dummy, 1, 1, file);
                printf("Byte read: %d\n", dummy);
            }
            break;
        }
    }

    fclose(file);
    //Assign tree IDs to the tree list
    //First, create a copy of tree_order
    tree_order_ordered = tree_order;
    //Next, sort this tree order copy
    std::sort(tree_order_ordered.begin(), tree_order_ordered.end());
    //Assign 0 to the tree root. This is always the 0. Because 0 is not stored in the tree_order vector.
    tree_list[0].id = 0;
    //Next from i = 0 to skip unexisting 0 on the tree_order and assign the IDs for each id.
    for(int i = 1; i < total_nodes; i++)
    {
        tree_list[i].id = tree_order_ordered[i];
    }

    return true;
}

void lmt::clear(node_data *node)
{
    node->id = 0;
    node->name = "";
    node->parent_id = 0;
    node->depth = 0;
    node->type = 0;
    node->scrollbar_x = 0;
    node->scrollbar_y = 0;
    node->expanded = 0;
    node->music = 0;
    node->music_file.name = "";
    node->music_file.fade_in = 0;
    node->music_file.volume = 100;
    node->music_file.tempo = 100;
    node->music_file.balance = 50;
    node->backdrop = 0;
    node->backdrop_file = "";
    node->teleport = 0;
    node->escape = 0;
    node->save = 0;
    node->encounter.clear();
    node->encounter_steps = 0;
}

void lmt::read_tree(FILE *file)
{
    int enemygroups = 0;
    int idgroup = 0;
    int enemy = 0;
    int current_node = 0;
    node_data node;
    char dummy;
    int node_chunk_id;
    int node_chunk_size;

    clear(&node);

    // Loop while we haven't reached the end of the file
    while (current_node < total_nodes)
    {
        node_chunk_id = read_int(file); // lectura de tipo del pedazo
        node_chunk_size = read_int(file);
        switch (node_chunk_id) // segun el tipo
        {
        case 1:
            node.name = read_string(file, node_chunk_size);
            break;
        case 2:
            node.parent_id = read_int(file);
            break;
        case 3:
            node.depth = read_int(file); //redundant data, parent_id can discover this. rm2k editor can't have more than 256 depth nodes in TreeCtrl
            break;
        case 4:
            node.type = read_int(file);
            break;
        case 5:
            node.scrollbar_x = read_int(file); //editor data
            break;
        case 6:
            node.scrollbar_y = read_int(file); //editor data
            break;
        case 7:
            node.expanded = read_int(file); //editor data
            break;
        case 11: //0x0B
            node.music = read_int(file);
            break;
        case 12: //0x0C
            while (node_chunk_id != 0)
            {
                node_chunk_id = read_int(file);
                if (node_chunk_id != 0)
                {
                    node_chunk_size = read_int(file);
                }
                switch (node_chunk_id)
                {
                case 0x01:
                    node.music_file.name = read_string(file, node_chunk_size);
                    break;
                case 0x02:
                    node.music_file.fade_in = read_int(file);
                    break;
                case 0x03:
                    node.music_file.volume = read_int(file);
                    break;
                case 0x04:
                    node.music_file.tempo = read_int(file);
                    break;
                case 0x05:
                    node.music_file.balance = read_int(file);
                    break;
                case 0x00:
                    break;
                default:
                    printf("WARNING: Unknown Music block ID: %d (size: %d)\n", node_chunk_id, node_chunk_size);
                    // skip unknown node_chunk_id case
                    while (node_chunk_size--)
                    {
                        fread(&dummy, 1, 1, file);
                        printf("Byte read: %d\n", dummy);
                    }
                    break;
                }
            }
            break;
        case 21: //0x15
            node.backdrop = read_int(file);
            break;
        case 22: //0x16
            node.backdrop_file = read_string(file, node_chunk_size);
            break;
        case 31: //0x1F
            node.teleport = read_int(file);
            break;
        case 32: //0x20
            node.escape = read_int(file);
            break;
        case 33: //0x21
            node.save = read_int(file);
            break;
        case 41: //0x29
            enemygroups = read_int(file); // numero de grupos
            idgroup = 0;
            while (idgroup < enemygroups)
            {
                idgroup = read_int(file); //id de dato
                // no se para que escribieron los dos primeros enteros pero el 3ro es el id de grupo
                // probablemente quedo incompleto el rm2k
                read_int(file);
                read_int(file);
                enemy = read_int(file);
                node.encounter.push_back(enemy);
                read_int(file); //fin de bloque
            }
            break;
        case 44: //0x2C
            node.encounter_steps = read_int(file);
            break;
        case 51: //0x33 Area data
            fread(&node.area_start_x, 4, 1, file);
            fread(&node.area_start_y, 4, 1, file);
            fread(&node.area_end_x, 4, 1, file);
            fread(&node.area_end_y, 4, 1, file);
            tree_list.push_back(node);
            break;
        case 0: //0x00 End of block
            clear(&node);
            current_node++;
            break;
        default:
            printf("WARNING: Unknown node block ID: %d (size: %d)\n", node_chunk_id, node_chunk_size);
            // skip unknown node_chunk_id case
            while (node_chunk_size--)
            {
                fread(&dummy, 1, 1, file);
                printf("Byte read: %d\n", dummy);
            }
            break;
        }
    }
}

void lmt::print() // muestra de informacion del mapa
{
    printf("==========================================================================\n");
    printf("Map tree\n");
    for(int i = 0; i < total_nodes; i++)
    {
        printf("--------------------------------------------------------------------------\n");
        printf("ID:                                                            %d\n", tree_list[i].id);
        printf("Name:                                                          %s\n", tree_list[i].name.c_str());
        printf("Parent ID:                                                     %d\n", tree_list[i].parent_id);
        printf("Depth:                                                         %d\n", tree_list[i].depth);
        printf("Type (0=root, 1=map, 2=area):                                  %d\n", tree_list[i].type);
        printf("Scrollbars:                                                    %d,%d\n", tree_list[i].scrollbar_x, tree_list[i].scrollbar_y);
        printf("Is expanded?:                                                  %d\n", tree_list[i].expanded);
        printf("Has Music? (0=inherit, 1=don't change, 2=specify):             %d\n", tree_list[i].music);
        printf("Music name:                                                    %s\n", tree_list[i].music_file.name.c_str());
        printf("Music fade in:                                                 %d\n", tree_list[i].music_file.fade_in);
        printf("Music volume:                                                  %d\n", tree_list[i].music_file.volume);
        printf("Music tempo:                                                   %d\n", tree_list[i].music_file.tempo);
        printf("Music balance:                                                 %d\n", tree_list[i].music_file.balance);
        printf("Has battle background? (0=inherit, 1=don't change, 2=specify): %d\n", tree_list[i].backdrop);
        printf("Battle baground name:                                          %s\n", tree_list[i].backdrop_file.c_str());
        printf("Teleport options (0=inherit, 1=don't change, 2=specify):       %d\n", tree_list[i].teleport);
        printf("Escape options (0=inherit, 1=don't change, 2=specify):         %d\n", tree_list[i].escape);
        printf("Save options (0=inherit, 1=don't change, 2=specify):           %d\n", tree_list[i].save);
        for (unsigned int j = 0; j < tree_list[i].encounter.size(); j++)
        {
            printf("Enemy encounter:                                               %d\n", tree_list[i].encounter[j]);
        }
        printf("Encounter steps:                                               %d\n", tree_list[i].encounter_steps);
        printf("Area coordinates:                                              %d,%d-%d,%d\n", tree_list[i].area_start_x, tree_list[i].area_start_y, tree_list[i].area_end_y, tree_list[i].area_end_y);
    }
    printf("==========================================================================\n");
    printf("End of tree. Data after the tree:\n");
    printf("--------------------------------------------------------------------------\n");
    printf("Branch order:\n");
    for(int i = 0; i < total_nodes; i++)
    {
        printf("%d ", tree_order[i]);
    }
    printf("(0 is always faked)\n\n");
    printf("Selected node:                                                 %d\n", selected_node);
    printf("--------------------------------------------------------------------------\n");
    printf("Party map ID:                                                  %d\n", party_map_id);
    printf("Party X:                                                       %d\n", party_x);
    printf("Party Y:                                                       %d\n", party_y);
    printf("Skiff map ID:                                                  %d\n", skiff_map_id);
    printf("Skiff X:                                                       %d\n", skiff_x);
    printf("Skiff Y:                                                       %d\n", skiff_y);
    printf("Boat map ID:                                                   %d\n", boat_map_id);
    printf("Boat X:                                                        %d\n", boat_x);
    printf("Boat Y:                                                        %d\n", boat_y);
    printf("Airship map ID:                                                %d\n", airship_map_id);
    printf("Airship X:                                                     %d\n", airship_x);
    printf("Airship Y:                                                     %d\n", airship_y);
}
