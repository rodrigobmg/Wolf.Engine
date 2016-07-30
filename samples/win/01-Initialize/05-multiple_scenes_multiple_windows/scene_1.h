/*
	Project			 : Wolf Engine. Copyright(c) Pooya Eimandar (http://PooyaEimandar.com) . All rights reserved.
	Source			 : Please direct any bug to https://github.com/PooyaEimandar/Wolf.Engine/issues
	Website			 : http://WolfSource.io
	Name			 : pch.h
	Description		 : The second scene of Wolf Engine
	Comment          : Read more information about this sample on http://wolfsource.io/gpunotes/wolfengine/
*/

#ifndef __SCENE_1_H__
#define __SCENE_1_H__

#include <w_game.h>

class scene_1 sealed : public wolf::framework::w_game
{
public:
	scene_1();
	virtual ~scene_1();

	/*
		Allows the game to perform any initialization before starting to run.
		Calling Game::Initialize() will enumerate through any components and initialize them as well.
		The parameter pOutputWindowsInfo represents the information of output window(s) of this game.
	*/
	void initialize(std::map<int, std::vector<w_window_info>> pOutputWindowsInfo) override;

	//The function "load()" will be called once per game and it is the place to load all of your game assets.
	void load() override;

	//This is the place where allows the game to run logic such as updating the world, checking camera, collisions, physics, input, playing audio and etc.
	void update(const wolf::system::w_game_time& pGameTime) override;

	//Begin render on all graphics devices
	void begin_render(const wolf::system::w_game_time& pGameTime) override;

	//This is called when the game should draw itself.
	void render(const wolf::system::w_game_time& pGameTime) override;

	//End render on all graphics devices
	void end_render(const wolf::system::w_game_time& pGameTime) override;

	//Handle window messages
	HRESULT on_msg_proc(HWND pHWND, UINT pMessage, WPARAM pWParam, LPARAM pLParam) override;

	//Release will be called once per game and is the place to unload assets and release all resources
	ULONG release() override;
};

#endif

