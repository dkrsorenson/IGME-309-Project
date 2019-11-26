#include "PlayerSolver.h"
#include "AppClass.h"
using namespace Simplex;
//  MySolver
void PlayerSolver::Release(void){/*nothing to deallocate*/ }
PlayerSolver::PlayerSolver(MyEntity* player){ 
	Init(player); 
}
PlayerSolver::~PlayerSolver() { Release(); }

void Simplex::PlayerSolver::SetIsCollidingMinX(bool a_isCollidingMinX) { isCollidingMinX = a_isCollidingMinX; }
bool Simplex::PlayerSolver::GetIsCollidingMinX(void){ return isCollidingMinX; }

void Simplex::PlayerSolver::SetIsCollidingMaxX(bool a_isCollidingMaxX) { isCollidingMaxX = a_isCollidingMaxX; }
bool Simplex::PlayerSolver::GetIsCollidingMaxX(void) { return isCollidingMaxX; }

void PlayerSolver::SetIsGrounded(bool a_isGrounded) { isGrounded = a_isGrounded; }
bool PlayerSolver::GetIsGrounded(void) { return isGrounded; }

void PlayerSolver::Init(MyEntity* player)
{
	this->player = player;
}

//Methods
void PlayerSolver::ApplyFriction(float a_fFriction)
{
	if (a_fFriction < 0.01f)
		a_fFriction = 0.01f;
	
	player->SetVelocity(player->GetVelocity() *= 1.0f - a_fFriction);

	//if velocity is really small make it zero
	if (glm::length(player->GetVelocity()) < 0.01f)
		player->SetVelocity(ZERO_V3);
}
vector3 CalculateMaxVelocity(vector3 a_v3Velocity, float maxVelocity)
{
	if (glm::length(a_v3Velocity) > maxVelocity)
	{
		a_v3Velocity = glm::normalize(a_v3Velocity);
		a_v3Velocity *= maxVelocity;
	}
	return a_v3Velocity;
}
vector3 RoundSmallVelocity(vector3 a_v3Velocity, float minVelocity = 0.01f)
{
	if (glm::length(a_v3Velocity) < minVelocity)
	{
		a_v3Velocity = ZERO_V3;
	}
	return a_v3Velocity;
}
void PlayerSolver::Update(void)
{
	player->ApplyForce(m_fGravity);

	player->SetVelocity(player->GetVelocity() + player->GetAcceleration());
	
	float fMaxVelocity = 5.0f;
	player->SetVelocity(CalculateMaxVelocity(player->GetVelocity(), fMaxVelocity));

	ApplyFriction(0.1f);
	player->SetVelocity(RoundSmallVelocity(player->GetVelocity(), 0.0028f));

	player->SetPosition(player->GetPosition() + player->GetVelocity());

	player->SetAcceleration(ZERO_V3);
}
void PlayerSolver::ResolveCollision(MyEntity* other)
{
	vector3 accelLimiter = vector3(1.0f);
	vector3 velocityLimiter = vector3(1.0f);

	SetIsCollidingMaxX(false);
	SetIsCollidingMinX(false);

	uint collidingPlane = player->GetRigidBody()->GetCollidingPlane(other->GetRigidBody());

	//Depending on which plane of this is colliding with other
	//we will 0 out the accel and velocity of that direction
	vector3 tmppos;
	vector3 tmpvel;
	switch (collidingPlane)
	{
	//ex: if the right side of this is colliding with the other object,
	case eContactPlane::MAX_X:
		tmppos = player->GetPosition();
		tmppos.x = other->GetPosition().x - player->GetSize().x / 2;
		player->SetPosition(tmppos);
		SetIsCollidingMaxX(true);
		break;
	case eContactPlane::MIN_X:
		tmppos = player->GetPosition();
		tmppos.x = other->GetPosition().x + other->GetSize().x + player->GetSize().x / 2;
		player->SetPosition(tmppos);
		SetIsCollidingMinX(true);
		break;
	case eContactPlane::MAX_Y:
		if (player->GetAcceleration().y > 0)
			accelLimiter.y = 0;
		if (player->GetVelocity().y > 0)
			velocityLimiter.y = 0;
		break;
	case eContactPlane::MIN_Y:

		tmppos = player->GetPosition();
		if (tmppos.y <= other->GetPosition().y + other->GetSize().y)
		{
			tmppos.y = other->GetPosition().y + other->GetSize().y;
			tmpvel = player->GetAcceleration();
			tmpvel.y = 0;
			player->SetPosition(tmppos);
			player->SetVelocity(tmpvel);
			SetIsGrounded(true);
		}
		break;
	case eContactPlane::MAX_Z:
		if (player->GetAcceleration().z > 0)
			accelLimiter.z = 0;
		if (player->GetVelocity().z > 0)
			velocityLimiter.z = 0;
		break;
	case eContactPlane::MIN_Z:
		if (player->GetAcceleration().z < 0)
			accelLimiter.z = 0;
		if (player->GetVelocity().z < 0)
			velocityLimiter.z = 0;
		break;
	default:
		return;
	}

	player->SetVelocity(player->GetVelocity() * velocityLimiter);
	player->SetAcceleration(player->GetAcceleration() * accelLimiter);

}
