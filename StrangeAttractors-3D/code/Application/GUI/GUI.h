#pragma once
#include <iostream>

/* Engine */
#include <irrlicht.h>

/* The user can adjust settings in the Jumper class */
#include "../Jumper/Jumper.h"

class GUI
{
	public:

		GUI(irr::scene::ISceneManager *SceneManager, Jumper *Jumper);

		void Update();
		void Render();

		bool IsStarted();

		bool CreatePressed();
		bool DeletePressed();

	private:

		Jumper *_Jumper;

		irr::gui::IGUIEnvironment *_GUIEnv;

		irr::gui::IGUIScrollBar *_Distance;
		irr::gui::IGUIButton *_Start, *_Stop, *_Reset, *_Create, *_Delete;

		bool _Started;
		bool _PressedDelete, _PressedCreate;
};