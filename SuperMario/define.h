#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define L_NORMAL_SPEED -150
#define R_NORMAL_SPEED 150

#define L_DASH_SPEED -250
#define R_DASH_SPEED 250

#define GRAVITY 80.0f
struct KEY
{
	bool key_pressed = false;
	bool key_down = false;
	bool key_up = false;
};
struct SAVE_DATA
{
	short x;
	short y;
	short background;
	short block;
	short item;
	short enemy;
	short itemsize;
};

enum PLAYER_STATE
{
	PLAYER_STATE_SMALL,
	PLAYER_STATE_BIG,
	PLAYER_STATE_FIRE,
};
enum HITBOX
{
	HITBOX_FRONT,
	HITBOX_REAR,
	HITBOX_TOP,
	HITBOX_BOTTOM,
	HITBOX_BODY
};

enum JUMP_HEIGHT
{
	JUMP_HEIGHT_LOW,
	JUMP_HEIGHT_MIDDLE,
	JUMP_HEIGHT_HIGH
};

enum MOVE_STATE
{
	MOVE_STATE_LEFT,
	MOVE_STATE_RIGHT
};

enum PMOVE_STATE
{
	PMOVE_STATE_LEFT,
	PMOVE_STATE_RIGHT,
	PMOVE_STATE_STOP
};

enum GAME_STATE
{
	GAME_STATE_PLAY,
	GAME_STATE_SEMITITLE
};
class define
{
public:
	define();
	~define();
};

