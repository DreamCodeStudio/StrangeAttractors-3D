#pragma once
#include <iostream>

/* Engine */
#include <irrlicht.h>

class Attractor
{
	public:

		Attractor(irr::scene::ISceneManager *SceneManager, irr::core::vector3df Position);

		void SetPosition(irr::core::vector3df NewPosition);
		irr::core::vector3df GetPosition();

	private:

		irr::scene::ISceneNode *_Attractor;		
};