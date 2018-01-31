#include "Jumper.h"

Jumper::Jumper(irr::scene::ISceneManager *SceneManager, std::vector<Attractor*> Attractors)
{
	srand(static_cast<unsigned int>(time(NULL)));

	_JumpPoint = SceneManager->addSphereSceneNode(2.0f, 32, 0, -1, irr::core::vector3df(0, 0, 0));
	_JumpPoint->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_JumpPoint->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("Data\\JumpTexture.png"));

	_Attractors = Attractors;
	_SceneManager = SceneManager;
}

void Jumper::Jump()
{
	int RandomAttractor = rand() % _Attractors.size();
	
	irr::core::vector3df JumpDistance;
	JumpDistance.X = (_Attractors[RandomAttractor]->GetPosition().X - _JumpPoint->getPosition().X) / 2;
	JumpDistance.Y = (_Attractors[RandomAttractor]->GetPosition().Y - _JumpPoint->getPosition().Y) / 2;
	JumpDistance.Z = (_Attractors[RandomAttractor]->GetPosition().Z - _JumpPoint->getPosition().Z) / 2;

	_JumpPoint->setPosition(irr::core::vector3df(_JumpPoint->getPosition().X + JumpDistance.X, _JumpPoint->getPosition().Y + JumpDistance.Y, _JumpPoint->getPosition().Z + JumpDistance.Z));
	_JumpedPositions.push_back(_SceneManager->addSphereSceneNode(0.4f, 32, 0, -1, _JumpPoint->getPosition()));
}