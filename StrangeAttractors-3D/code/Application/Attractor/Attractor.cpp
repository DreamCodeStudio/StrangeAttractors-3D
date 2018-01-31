#include "Attractor.h"

Attractor::Attractor(irr::scene::ISceneManager *SceneManager, irr::core::vector3df Position)
{
	/* Create Attractor and add sphere to the scene manager */
	_Attractor = SceneManager->addSphereSceneNode(2.0f, 32, 0, -1, Position);
	_Attractor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_Attractor->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("Data\\AttractorTexture.png"));
}

void Attractor::SetPosition(irr::core::vector3df NewPosition)
{
	_Attractor->setPosition(NewPosition);
}

irr::core::vector3df Attractor::GetPosition()
{
	return _Attractor->getPosition();
}