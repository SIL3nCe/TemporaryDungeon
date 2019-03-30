#pragma once

#include "ShSDK/ShSDK.h"

#include "InputManager.h"
#include "Character/PlayerCharacter.h"
#include "Object.h"

#define SH_TO_B2 100

class World
{
public:

	explicit					 World			(void);
	virtual						~World			(void);

	void						Initialize		(const CShIdentifier & levelIdentifier);
	void						Release			(void);

	void						Update			(float dt);

	const PluginInputManager & 	GetInputManager	(void);
	

	static CShVector2			ShineToB2		(b2Vec2 vec);
	static b2Vec2				ShineToB2		(CShVector2 vec);

private:

	void						DatasetParser	(ShObject * pObject, ShDataSet * pDataSet);

	void						GenerateShape	(ShCollisionShape * pCollisionShape, const b2Vec2 & center, b2ChainShape & b2OutShape);
	void						GenerateShape	(ShDummyAABB2 * pObject, const b2Vec2 & center, b2PolygonShape & b2OutShape);

private:
	
	CShIdentifier		m_levelIdentifier;

	b2World *			m_pbWorld;

	CShArray<Object*>	m_aObjectList;

	PluginInputManager	m_inputManager;

	PlayerCharacter		m_playerCharacter;
};

