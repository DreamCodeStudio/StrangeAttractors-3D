#pragma once
#include <iostream>
#include <Windows.h>

/* Engine */
#include <irrlicht.h>

#define HORIZONTAL 0
#define VERTICAL 1
#define DEPTH 2

class Attractor
{
	public:

		Attractor(irr::IrrlichtDevice *Device, irr::scene::ISceneManager *SceneManager, irr::core::vector3df Position);

		void SetPosition(irr::core::vector3df NewPosition);
		irr::core::vector3df GetPosition();

		void Update();

		bool IsSelected();

	private:

		irr::IrrlichtDevice *_Device;
		
		irr::scene::ISceneManager *_Manager;
		irr::scene::ISceneNode *_Attractor;	
		irr::scene::IAnimatedMeshSceneNode *_ArrowY, *_ArrowX;

		bool _IsSelected;
		int _CurrentMovement;

};