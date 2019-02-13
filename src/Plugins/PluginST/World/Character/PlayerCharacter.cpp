#include "PlayerCharacter.h"
#include "../InputManager.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
PlayerCharacter::PlayerCharacter(void)
: BaseCharacter()
, m_pInputManager(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
PlayerCharacter::~PlayerCharacter(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void PlayerCharacter::Initialize(const CShIdentifier & levelIdentifier, b2World * pWorld, PluginInputManager * pInputManager)
{
	BaseCharacter::Initialize(pWorld);

	m_pInputManager = pInputManager;
	SH_ASSERT(shNULL != m_pInputManager);

	m_pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_player_test"));
	SH_ASSERT(shNULL != m_pEntity);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1, 1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	m_pBody->CreateFixture(&boxFixtureDef);
}

/**
 * @brief Release
 */
void PlayerCharacter::Release(void)
{
	m_pInputManager = shNULL;
}

/**
 * @brief Inputs::Update
 */
void PlayerCharacter::Update(float dt)
{
	bool bLeft = m_pInputManager->IsGoingLeft();
	bool bRight = m_pInputManager->IsGoingRight();
	bool bDown = m_pInputManager->IsGoingDown();
	bool bUp = m_pInputManager->IsGoingUp();

	if (bLeft)
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(-50.0f, 0.0f), m_pBody->GetWorldCenter(), true);
	}
	else if (bRight)
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(50.0f, 0.0f), m_pBody->GetWorldCenter(), true);
	}
	else if (bDown)
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, -50.0f), m_pBody->GetWorldCenter(), true);
	}
	else if (bUp)
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 50.0f), m_pBody->GetWorldCenter(), true);
	}
	else
	{
		m_pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	}
}

/**
 * @brief Inputs::PostUpdate
 */
void PlayerCharacter::UpdateAnimations(float dt)
{
	// rotate for test
	CShEulerAngles angle = ShEntity2::GetRelativeRotation(m_pEntity);
	angle.m_z += 10.0f * dt;
	ShEntity2::SetRelativeRotation(m_pEntity, angle);

	BaseCharacter::UpdateAnimations(dt);
}
