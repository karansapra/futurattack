/*
 * Constants.h
 *
 *  Created on: 1 oct. 2009
 *      Author: clement
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define MAX_NAME_LENGTH			128		//String length for name in BaseObject
#define ENGINE_STEP				10 		//Engine step in ms.
#define MAX_DBG_MESSAGE_LENGTH	256		//Longueur max d'un message de debug
#define DBG_TIME				6000	//Duree d'affichage de la console de debug
#define EVENT_REFRESH_STEP		10		//Every ENGINE_STEP * EVENT_REFRESH_STEP ms, keyboard, mouse, ... are refreshed

#define OBJ_FILE_LINE_LENGTH	80
#define OBJ_FILE_MAX_VERTEX		128000
#define OBJ_FILE_MAX_NORMALS	128000
#define OBJ_FILE_MAX_TEXTCOORDS	128000
#define OBJ_FILE_MAX_TRIANGLES	64000
#define OBJ_FILE_MAX_MESHES		32
#define OBJ_FILE_MAX_MATERIALS	32

#define MAX_MESH_NAME_LENGTH	32

#define KEYCODE_UP				0x6F
#define KEYCODE_DOWN			0x74
#define KEYCODE_LEFT			0x71
#define KEYCODE_RIGHT			0x72

#define KEYCODE_A				0x18
#define KEYCODE_Z				0x19
#define KEYCODE_E				0x1A
#define KEYCODE_R				0x1B
#define KEYCODE_T				0x1C
#define KEYCODE_Y				0x1D
#define KEYCODE_U				0x1E
#define KEYCODE_I				0x1F
#define KEYCODE_O				0x20
#define KEYCODE_P				0x21
#define KEYCODE_Q				0x26
#define KEYCODE_S				0x27
#define KEYCODE_D				0x28
#define KEYCODE_F				0x29
#define KEYCODE_G				0x2A
#define KEYCODE_H				0x2B
#define KEYCODE_J				0x2C
#define KEYCODE_K				0x2D
#define KEYCODE_L				0x2E
#define KEYCODE_M				0x2F
#define KEYCODE_W				0x34
#define KEYCODE_X				0x35
#define KEYCODE_C				0x36
#define KEYCODE_V				0x37
#define KEYCODE_B				0x38
#define KEYCODE_N				0x39

#define MOUSE_LEFT				1
#define MOUSE_RIGHT				3
#define MOUSE_CENTER			2
#define MOUSE_CENTER_UP			4
#define MOUSE_CENTER_DOWN		5

#endif /* CONSTANTS_H_ */
