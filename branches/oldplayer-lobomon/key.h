/*key.h, EasyRPG player keyboard definition and protoype declaration file.
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

///autonota para NeLO -no tocar por ahora
/* comentario de NeLo -> he quitado casi todos los defines ya que el codigo ascii
varia depende de la configuracion el sistema y_pos del teclado*/

//Teclado clasico

#define KEY_Q         113
#define KEY_W         119
#define KEY_E         101
#define KEY_R         114
#define KEY_T         116
#define KEY_Y         121
#define KEY_U         117
#define KEY_I         105
#define KEY_O         111
#define KEY_P         112
#define KEY_A         97
#define KEY_S         115
#define KEY_D         100
#define KEY_F         102
#define KEY_G         103
#define KEY_H         104
#define KEY_J         106
#define KEY_K         107
#define KEY_L         108
#define KEY_Z         122
#define KEY_X         120
#define KEY_C         99
#define KEY_V         118
#define KEY_B         98
#define KEY_N         110
#define KEY_M         109

bool key_pressed_and_released( Uint8 key );

