#pragma once

#include "ShSDK/ShSDK.h"
#include "Projectile.h"

#include "Projectile.h"

#define PROJECTILE_POOL_SIZE 250

class b2World;

class ProjectileManager
{
public:
	virtual							~ProjectileManager	(void);

	static ProjectileManager *		GetInstance			(void);

	void							Initialize			(const CShIdentifier & levelIdentifier, b2World * pWorld);
	void							Release				(void);

	void							Update				(float dt);

	void							CreateProjectile	(EObjectType eObjectType, EProjectileType eType, EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection);
	void							FreeProjectile		(Projectile * pProjectile);

private:

	explicit						ProjectileManager	(void);

private:
	Projectile m_aProjectilePool[PROJECTILE_POOL_SIZE];
	Projectile * m_pNextUsableProjectile;
};
