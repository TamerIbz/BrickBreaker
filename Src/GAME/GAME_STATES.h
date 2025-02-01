#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H
typedef enum GAME_STATES
{
	NONE_GS,
	WIN,
	LOSE
} GAME_STATES;

extern enum GAME_STATES CURRENTGAMESTATE;
#endif 

