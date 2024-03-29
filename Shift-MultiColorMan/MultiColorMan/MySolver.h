/*----------------------------------------------
Team: Name Pending - Dakota, Sonya, David, Matt
Date: 11/2019
----------------------------------------------*/
#ifndef __MYSOLVER_H_
#define __MYSOLVER_H_

#include "MyRigidBody.h"

namespace Simplex
{

class MySolver
{
	vector3 m_v3Acceleration = ZERO_V3; //Acceleration of the MySolver
	vector3 m_v3Position = ZERO_V3; //Position of the MySolver
	vector3 m_v3Size = vector3(1.0f); //Size of the MySolver
	vector3 m_v3Velocity = ZERO_V3; //Velocity of the MySolver
	float m_fMass = 1.0f; //Mass of the solver
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
	MySolver(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: object to copy
	OUTPUT: object instance
	*/
	MySolver(MySolver const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: object to copy
	OUTPUT: this instance
	*/
	MySolver& operator=(MySolver const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MySolver(void);
	/*
	USAGE: Content Swap
	ARGUMENTS: object to swap content with
	OUTPUT: ---
	*/
	void Swap(MySolver& other);

	/*
	USAGE: Sets the position of the solver
	ARGUMENTS: vector3 a_v3Position -> position to set
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Gets the position of the solver
	ARGUMENTS: ---
	OUTPUT: position of the solver
	*/
	vector3 GetPosition(void);

	/*
	USAGE: Sets the Size of the solver
	ARGUMENTS: vector3 a_v3Size -> position to set
	OUTPUT: ---
	*/
	void SetSize(vector3 a_v3Size);
	/*
	USAGE: Gets the size of the solver
	ARGUMENTS: ---
	OUTPUT: size of the solver
	*/
	vector3 GetSize(void);

	/*
	USAGE: Sets the velocity of the solver
	ARGUMENTS: vector3 a_v3Velocity -> velocity to set
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity);
	/*
	USAGE: Gets the velocity of the solver
	ARGUMENTS: ---
	OUTPUT: velocity of the solver
	*/
	vector3 GetVelocity(void);
	/*
	USAGE: Sets the mass of the solver
	ARGUMENTS: float a_fMass -> mass to set
	OUTPUT: ---
	*/
	void SetMass(float a_fMass);
	/*
	USAGE: Gets mass of the solver
	ARGUMENTS: ---
	OUTPUT: mass of the object
	*/
	float GetMass(void);
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
	USAGE: Applies a force to the solver
	ARGUMENTS: vector3 a_v3Force -> Force to apply
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force);
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
	void ResolveCollision(MySolver* a_pOther, uint collidingPlane);
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
	void Init(void);
};//class

} //namespace Simplex

#endif //__SOLVER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/