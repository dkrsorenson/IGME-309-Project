#include "MyEntityGroup.h"
#include "MyEntity.h"

namespace Simplex
{

Simplex::MyEntityGroup::MyEntityGroup(Simplex::String id) : Simplex::MyEntity(vector3(0), id)
{
	// this is a group of entities. so we need to make an empty container here
	// we can add entities to this group laer
}

void Simplex::MyEntityGroup::AddEntity(MyEntity* new_entity) {
	entities.push_back(new_entity);
}

bool Simplex::MyEntityGroup::IsInitialized(void)
{
	return false;
}

void Simplex::MyEntityGroup::AddToRenderList(bool a_bDrawRigidBody)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->AddToRenderList(a_bDrawRigidBody);
	}
}

bool Simplex::MyEntityGroup::IsColliding(MyEntity * const other)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->IsColliding(other)) {
			return true;
		}
	}
	return false;
}

void Simplex::MyEntityGroup::SetAxisVisible(bool a_bSetAxis)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->SetAxisVisible(a_bSetAxis);
	}
}

void Simplex::MyEntityGroup::AddDimension(uint a_uDimension)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->AddDimension(a_uDimension);
	}
}

void Simplex::MyEntityGroup::RemoveDimension(uint a_uDimension)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->RemoveDimension(a_uDimension);
	}
}

void Simplex::MyEntityGroup::ClearDimensionSet(void)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->ClearDimensionSet();
	}
}

bool Simplex::MyEntityGroup::IsInDimension(uint a_uDimension)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->IsInDimension(a_uDimension)) {
			return true;
		}
	}
	return false;
}

bool Simplex::MyEntityGroup::SharesDimension(MyEntity * const a_pOther)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->SharesDimension(a_pOther)) {
			return true;
		}
	}
	return false;
}

void Simplex::MyEntityGroup::ClearCollisionList(void)
{
	// ????
}

void Simplex::MyEntityGroup::SortDimensions(void)
{
}

MyRigidBody::PRigidBody * Simplex::MyEntityGroup::GetColliderArray(void)
{
	return nullptr;
}

uint Simplex::MyEntityGroup::GetCollidingCount(void)
{
	return uint();
}

bool Simplex::MyEntityGroup::HasThisRigidBody(MyRigidBody * a_pRigidBody)
{
	return false;
}

void Simplex::MyEntityGroup::Update(void)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Update();
	}
}

}