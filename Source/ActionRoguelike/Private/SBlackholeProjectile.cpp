#include "SBlackholeProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

ASBlackholeProjectile::ASBlackholeProjectile()
{
	ProjectileMovementComp->InitialSpeed = 750.0f;
}
