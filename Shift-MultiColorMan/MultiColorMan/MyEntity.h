/*----------------------------------------------
Team: Name Pending - Dakota, Sonya, David, Matt
Date: 11/2019
----------------------------------------------*/
#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "MyRigidBody.h"

namespace Simplex
{

//System Class
class MyEntity
{
protected:
	bool m_bInMemory = false; //loaded flag
	bool m_bSetAxis = false; //render axis flag
	String m_sUniqueID = ""; //Unique identifier name

	uint m_nDimensionCount = 0; //tells how many dimensions this entity lives in
	uint* m_DimensionArray = nullptr; //Dimensions on which this entity is located

	Model* m_pModel = nullptr; //Model associated with this MyEntity
	MyRigidBody* m_pRigidBody = nullptr; //Rigid Body associated with this MyEntity

	matrix4 m_m4ToWorld = IDENTITY_M4; //Model matrix associated with this MyEntity
	MeshManager* m_pMeshMngr = nullptr; //For rendering shapes

	static std::map<String, MyEntity*> m_IDMap; //a map of the unique ID's

	vector3 m_v3Acceleration = ZERO_V3; //Acceleration of the MySolver
	vector3 m_v3Position = ZERO_V3; //Position of the MySolver
	vector3 m_v3Size = vector3(1.0f); //Size of the MySolver
	vector3 m_v3Velocity = ZERO_V3; //Velocity of the MySolver
	float m_fMass = 1.0f;

public:
	/*
	Usage: Constructor that specifies the name attached to the MyEntity
	Arguments:
	-	String a_sFileName -> Name of the model to load
	-	String a_sUniqueID -> Name wanted as identifier, if not available will generate one
	Output: class object instance
	*/
	//MyEntity(String a_sFileName, String a_sUniqueID = "NA");
	MyEntity(vector3 bounds, String a_sUniqueID = "NA");
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyEntity(MyEntity const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyEntity& operator=(MyEntity const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyEntity(void);
	/*
	Usage: Changes object contents for other object's
	Arguments: other -> object to swap content from
	Output: ---
	*/
	virtual matrix4 GetModelMatrix(void);
	/*
	USAGE: Sets the model matrix associated with this entity
	ARGUMENTS: matrix4 a_m4ToWorld -> model matrix to set
	OUTPUT: ---
	*/
	virtual void SetModelMatrix(matrix4 a_m4ToWorld);
	/*
	USAGE: Gets the model associated with this entity
	ARGUMENTS: ---
	OUTPUT: Model
	*/
	//Model* GetModel(void);
	/*
	USAGE: Gets the Rigid Body associated with this entity
	ARGUMENTS: ---
	OUTPUT: Rigid Body
	*/
	virtual MyRigidBody* GetRigidBody(void);
	/*
	USAGE: Will reply to the question, is the MyEntity Initialized?
	ARGUMENTS: ---
	OUTPUT: initialized?
	*/
	void SetModel(Model* model);

	virtual bool IsInitialized(void);
	/*
	USAGE: Adds the entity to the render list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void AddToRenderList(bool a_bDrawRigidBody = false);
	/*
	USAGE: Tells if this entity is colliding with the incoming one
	ARGUMENTS: MyEntity* const other -> inspected entity
	OUTPUT: are they colliding?
	*/
	virtual bool IsColliding(MyEntity* const other);
	/*
	USAGE: Gets the MyEntity specified by unique ID, nullptr if not exists
	ARGUMENTS: String a_sUniqueID -> unique ID if the queried entity
	OUTPUT: MyEntity specified by unique ID, nullptr if not exists
	*/
	static MyEntity* GetEntity(String a_sUniqueID);
	/*
	USAGE: Will generate a unique id based on the name provided
	ARGUMENTS: String& a_sUniqueID -> desired name
	OUTPUT: will output though the argument
	*/
	void GenUniqueID(String& a_sUniqueID);
	/*
	USAGE: Gets the Unique ID name of this model
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	String GetUniqueID(void);
	/*
	USAGE: Sets the visibility of the axis of this MyEntity
	ARGUMENTS: bool a_bSetAxis = true -> axis visible?
	OUTPUT: ---
	*/
	virtual void SetAxisVisible(bool a_bSetAxis = true);
	/*
	USAGE: Will set a dimension to the MyEntity
	ARGUMENTS: uint a_uDimension -> dimension to set
	OUTPUT: ---
	*/
	virtual void AddDimension(uint a_uDimension);
	/*
	USAGE: Will remove the entity from the specified dimension
	ARGUMENTS: uint a_uDimension -> dimension to remove
	OUTPUT: ---
	*/
	virtual void RemoveDimension(uint a_uDimension);
	/*
	USAGE: will remove all dimensions from entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ClearDimensionSet(void);
	/*
	USAGE: Will ask if the MyEntity is located in a particular dimension
	ARGUMENTS: uint a_uDimension -> dimension queried
	OUTPUT: result
	*/
	virtual bool IsInDimension(uint a_uDimension);
	/*
	USAGE: Asks if this entity shares a dimension with the incoming one
	ARGUMENTS: MyEntity* const a_pOther -> queried entity
	OUTPUT: shares at least one dimension?
	*/
	virtual bool SharesDimension(MyEntity* const a_pOther);

	/*
	USAGE: Clears the collision list of this entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ClearCollisionList(void);

	/*
	USAGE: Will sort the array of dimensions
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void SortDimensions(void);

	/*
	USAGE: Gets the array of rigid bodies pointer this one is colliding with
	ARGUMENTS: ---
	OUTPUT: list of colliding rigid bodies
	*/
	virtual MyRigidBody::PRigidBody* GetColliderArray(void);
	
	/*
	USAGE: Returns the number of objects colliding with this one
	ARGUMENTS: ---
	OUTPUT: colliding count
	*/
	virtual uint GetCollidingCount(void);

	/*
	USAGE: Asks this MyEntity if this is the rigid body that belogs to it
	ARGUMENTS: MyRigidBody* a_pRigidBody -> Queried Rigid Body
	OUTPUT: is this your rigid body?
	*/
	virtual bool HasThisRigidBody(MyRigidBody* a_pRigidBody);

	/*
	USAGE: Asks the entity to resolve the collision with the incoming one
	ARGUMENTS: MyEntity* a_pOther -> Queried entity
	OUTPUT: ---
	*/
	//virtual void ResolveCollision(MyEntity* a_pOther);

	/*
	USAGE: Gets the solver applied to this MyEntity
	ARGUMENTS: ---
	OUTPUT: MySolver applied
	*/
	//virtual MySolver* GetSolver(void);
	/*
	USAGE: Applies a force to the solver
	ARGUMENTS: vector3 a_v3Force -> force to apply
	OUTPUT: ---
	*/
	virtual void ApplyForce(vector3 a_v3Force);
	/*
	USAGE: Sets the position of the solver
	ARGUMENTS: vector3 a_v3Position -> position to set
	OUTPUT: ---
	*/
	virtual void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Gets the position of the solver
	ARGUMENTS: ---
	OUTPUT: position of the solver
	*/
	virtual vector3 GetPosition(void);

	/*
	USAGE: Sets the velocity of the solver
	ARGUMENTS: vector3 a_v3Velocity -> velocity to set
	OUTPUT: ---
	*/
	virtual void SetVelocity(vector3 a_v3Velocity);
	/*
	USAGE: Gets the velocity of the solver
	ARGUMENTS: ---
	OUTPUT: velocity of the solver
	*/
	virtual vector3 GetVelocity(void);

	/*
	USAGE: Sets the mass of the solver
	ARGUMENTS: float a_fMass -> mass to set
	OUTPUT: ---
	*/
	virtual void SetMass(float a_fMass);
	/*
	USAGE: Gets mass of the solver
	ARGUMENTS: ---
	OUTPUT: mass of the object
	*/
	virtual float GetMass(void);

	/*
	USAGE: Updates the MyEntity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void);
	/*
	USAGE: Resolves using physics solver or not in the update
	ARGUMENTS: bool a_bUse = true -> using physics solver?
	OUTPUT: ---
	*/
	//virtual void UsePhysicsSolver(bool a_bUse = true);

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

#endif //__MYENTITY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/