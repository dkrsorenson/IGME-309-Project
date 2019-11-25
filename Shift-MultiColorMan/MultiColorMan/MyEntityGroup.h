#pragma once
#include "MyEntity.h"

namespace Simplex
{

class MyEntityGroup :
	public MyEntity
{
private:
	std::vector<MyEntity*> entities = std::vector<MyEntity*>();
public:
	// constructor
	MyEntityGroup(Simplex::String id = "NA");

	void AddEntity(MyEntity * new_entity);
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
	USAGE: Updates the MyEntity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void);
};

}
