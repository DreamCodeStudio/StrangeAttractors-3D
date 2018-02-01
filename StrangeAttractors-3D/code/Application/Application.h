#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

/* Engine */
#include <irrlicht.h>

/* Attractor */
#include "Attractor\Attractor.h"

/* Jumper */
#include "Jumper\Jumper.h"

/* GUI environment */
#include "GUI\GUI.h"

class Application
{
	public:

		Application();

		void Run();

		bool IsOpen();

	private:

		irr::IrrlichtDevice *_Device;
		irr::video::IVideoDriver *_Driver;
		irr::scene::ISceneManager *_SceneManager;
		irr::scene::ICameraSceneNode *_Camera;

		std::vector<Attractor*> _Attractors;
		Jumper *_Jumper;
		GUI *_GUI;
};