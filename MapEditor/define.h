#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "ui\UIWidget.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=0; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=0; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=0; } }

#define BLOCKSIZE 10
#define BACKGROUNDSIZE 3
#define ITEMSIZE 6
#define ENEMYSIZE 4
#define SUMSIZE (BLOCKSIZE+BACKGROUNDSIZE+ITEMSIZE+ENEMYSIZE)

#define BLOCKWIDTH 32

#define BACKGROUND 0
#define BLOCK 1
#define ITEM 2
#define UI 4

enum GROUPINDEX
{
	GROUP_BACKGROUND,
	GROUP_BLOCK,
	GROUP_ITEM,
	GROUP_ENEMY,
	GROUP_ERASE,
	GROUP_ETC
};


struct SAVE_HEADER
{
	short width;
	short life;
	short time;
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

struct SAVE_STREAM
{
	SAVE_HEADER header;
	SAVE_DATA* piece;
};


class define
{
public:
	define();
	~define();
};

