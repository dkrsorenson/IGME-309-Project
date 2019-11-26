/*----------------------------------------------
Team: Name Pending - Dakota, Sonya, David, Matt
Date: 11/2019
----------------------------------------------*/
#ifndef __PLAYERSOLVER_H_
#define __PLAYERSOLVER_H_

#include "MyRigidBody.h"
#include "MyEntity.h"

namespace Simplex
{

class PlayerSolver
{
	MyEntity* player;
	bool isGrounded = false; // If the entity is grounded or not
	bool isCollidingMinX = false;
	bool isCollidingMaxX = false;
	const vector3 m_fGravity = vector3(0.0f, -0.035f, 0.0f);
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: object instance
	*/
	PlayerSolver(MyEntity* player);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~PlayerSolver(void);
	/*
	USAGE: Sets whether or not the solver is colliding on the min x
	ARGUMENTS: If the solver is colliding on the min x
	OUTPUT: ---
	*/
	void SetIsCollidingMinX(bool a_isCollidingMinX);
	/*
	USAGE: Gets whether or not the solver is colliding on the min x
	ARGUMENTS: ---
	OUTPUT: If the solver is colliding on the min x
	*/
	bool GetIsCollidingMinX(void);
	/*
	USAGE: Sets whether or not the solver is colliding on the max x
	ARGUMENTS: If the solver is colliding on the max x
	OUTPUT: ---
	*/
	void SetIsCollidingMaxX(bool a_isCollidingMaxX);
	/*
	USAGE: Gets whether or not the solver is colliding on the max x
	ARGUMENTS: ---
	OUTPUT: If the solver is colliding on the max x
	*/
	bool GetIsCollidingMaxX(void);
	/*
	USAGE: Sets whether or not the solver is grounded
	ARGUMENTS: If the solver is grounded
	OUTPUT: ---
	*/
	void SetIsGrounded(bool a_isGrounded);
	/*
	USAGE: Gets whether or not the solver is grounded
	ARGUMENTS: ---
	OUTPUT: If the solver is grounded
	*/
	bool GetIsGrounded(void);
	/*
	USAGE: Applies friction to the movement
	ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
	OUTPUT: ---
	*/
	void ApplyFriction(float a_fFriction = 0.1f);
	/*
	USAGE: Updates the MySolver
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Resolve the collision between two solvers
	ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
	OUTPUT: ---
	*/
	void ResolveCollision(MyEntity* a_pOther);
private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(MyEntity* player);
};//class

} //namespace Simplex

#endif //__PLAYERSOLVER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
