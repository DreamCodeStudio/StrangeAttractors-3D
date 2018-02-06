#include "Jumper.h"

Jumper::Jumper(irr::scene::ISceneManager *SceneManager, std::vector<Attractor*> Attractors)
{
	/* Random numbers for random jumping between attractors */
	srand(static_cast<unsigned int>(time(NULL)));

	/* Create green JumpPoint */
	_JumpPoint = SceneManager->addSphereSceneNode(2.0f, 32, 0, -1, irr::core::vector3df(0, 0, 0));
	_JumpPoint->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_JumpPoint->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("Data\\Green.png"));

	/* Safe pointer to Attractor list and SceneManager */
	_Attractors = Attractors;
	_SceneManager = SceneManager;
}

void Jumper::Jump()
{
	/* Get a random attractor */
	int RandomAttractor = rand() % _Attractors.size();
	
	/* Jump a specific distance to this attractor */
	irr::core::vector3df JumpDistance;
	JumpDistance.X = (_Attractors[RandomAttractor]->GetPosition().X - _JumpPoint->getPosition().X) * _JumpDistance;
	JumpDistance.Y = (_Attractors[RandomAttractor]->GetPosition().Y - _JumpPoint->getPosition().Y) * _JumpDistance;
	JumpDistance.Z = (_Attractors[RandomAttractor]->GetPosition().Z - _JumpPoint->getPosition().Z) * _JumpDistance;

	/* Move JumpPoint, mark this location as visited */
	_JumpPoint->setPosition(irr::core::vector3df(_JumpPoint->getPosition().X + JumpDistance.X, _JumpPoint->getPosition().Y + JumpDistance.Y, _JumpPoint->getPosition().Z + JumpDistance.Z));
	_JumpedPositions.push_back(_SceneManager->addSphereSceneNode(0.4f, 32, 0, -1, _JumpPoint->getPosition()));
}

void Jumper::SetJumpDistance(float Distance)
{
	/* Set the Jump Distance to the attractor */
	_JumpDistance = Distance;
}

void Jumper::Reset()
{
	if (_JumpedPositions.size() == 0)
	{
		return;
	}

	std::cout << "Clearing " << _JumpedPositions.size() << " objects" << std::endl;
	/* Set to start position */
	_JumpPoint->setPosition(irr::core::vector3df(0, 0, 0));

	/* Remove all marked positions */
	for (unsigned int c = 0; c < _JumpedPositions.size(); c++)
	{
		_JumpedPositions[c]->remove();
	}
	_JumpedPositions.clear();
}

void Jumper::SetAttractorList(std::vector<Attractor*> Attractors)
{
	_Attractors = Attractors;
}