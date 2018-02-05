#pragma once
#include <iostream>
#include <Windows.h>

/* Engine */
#include <irrlicht.h>

class Attractor
{
	public:

		Attractor(irr::IrrlichtDevice *Device, irr::scene::ISceneManager *SceneManager, irr::core::vector3df Position);

		void SetPosition(irr::core::vector3df NewPosition);
		irr::core::vector3df GetPosition();

		void Update();

	private:

		irr::IrrlichtDevice *_Device;
		irr::scene::ISceneManager *_Manager;

		irr::scene::ISceneNode *_Attractor;		

		bool _IsOnView, _IsSelected;
};