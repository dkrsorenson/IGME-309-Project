#include "MyEntity.h"
using namespace Simplex;
std::map<String, MyEntity*> MyEntity::m_IDMap;
//  Accessors
bool Simplex::MyEntity::HasThisRigidBody(MyRigidBody* a_pRigidBody) { return m_pRigidBody == a_pRigidBody; }
Simplex::MyRigidBody::PRigidBody* Simplex::MyEntity::GetColliderArray(void) { return m_pRigidBody->GetColliderArray(); }
uint Simplex::MyEntity::GetCollidingCount(void) { return m_pRigidBody->GetCollidingCount(); }
matrix4 Simplex::MyEntity::GetModelMatrix(void){ return m_m4ToWorld; }
void Simplex::MyEntity::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (!m_bInMemory)
		return;

	m_m4ToWorld = a_m4ToWorld;
	if (m_pModel) {
		m_pModel->SetModelMatrix(m_m4ToWorld);
	}
	m_pRigidBody->SetModelMatrix(m_m4ToWorld);

	//experimental way of calculating a matrix components
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(m_m4ToWorld, scale, rotation, translation, skew, perspective);

}
//Model* Simplex::MyEntity::GetModel(void){return m_pModel;}
MyRigidBody* Simplex::MyEntity::GetRigidBody(void){	return m_pRigidBody; }
bool Simplex::MyEntity::IsInitialized(void){ return m_bInMemory; }
String Simplex::MyEntity::GetUniqueID(void) { return m_sUniqueID; }
void Simplex::MyEntity::SetAxisVisible(bool a_bSetAxis) { m_bSetAxis = a_bSetAxis; }
void Simplex::MyEntity::SetPosition(vector3 a_v3Position) {  
	m_v3Position = a_v3Position;
}
Simplex::vector3 Simplex::MyEntity::GetPosition(void)
{
	return m_v3Position;
}

void Simplex::MyEntity::SetVelocity(vector3 a_v3Velocity) { 
	this->m_v3Velocity = a_v3Velocity;
}
Simplex::vector3 Simplex::MyEntity::GetVelocity(void)
{
	return m_v3Velocity;
}

void Simplex::MyEntity::SetMass(float a_fMass) {  }
float Simplex::MyEntity::GetMass(void)
{
	return 1.0f;
}
//  MyEntity
void Simplex::MyEntity::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();
	m_bInMemory = true; // we aren't starting with a rigid body anymore
	                    // so loaded by default?
	m_bSetAxis = false;
	m_pRigidBody = nullptr;
	m_DimensionArray = nullptr;
	m_m4ToWorld = IDENTITY_M4;
	m_sUniqueID = "";
	m_nDimensionCount = 0;
}
void Simplex::MyEntity::SetModel(Model* model) {
	m_pModel = model;
	m_pRigidBody = new MyRigidBody(m_pModel->GetVertexList());
}

void Simplex::MyEntity::Release(void)
{
	m_pMeshMngr = nullptr;
	//it is not the job of the entity to release the model, 
	//it is for the mesh manager to do so.
	//m_pModel = nullptr;
	if (m_DimensionArray)
	{
		delete[] m_DimensionArray;
		m_DimensionArray = nullptr;
	}
	SafeDelete(m_pRigidBody);
	m_IDMap.erase(m_sUniqueID);
}
//The big 3
//Simplex::MyEntity::MyEntity(String a_sFileName, String a_sUniqueID)
Simplex::MyEntity::MyEntity(vector3 bounds, String a_sUniqueID)
{
	Init();

	GenUniqueID(a_sUniqueID);
	m_sUniqueID = a_sUniqueID;
	m_IDMap[a_sUniqueID] = this;
	m_pRigidBody = new MyRigidBody(std::vector<vector3>({ bounds, -bounds }));
	m_bInMemory = true; // no clue what this actually does
}
Simplex::MyEntity::MyEntity(MyEntity const& other)
{
	m_bInMemory = other.m_bInMemory;
	m_pRigidBody = other.m_pRigidBody;
	m_m4ToWorld = other.m_m4ToWorld;
	m_pMeshMngr = other.m_pMeshMngr;
	m_sUniqueID = other.m_sUniqueID;
	m_bSetAxis = other.m_bSetAxis;
	m_nDimensionCount = other.m_nDimensionCount;
	m_DimensionArray = other.m_DimensionArray;
}
MyEntity::~MyEntity(){Release();}
//--- Methods
void Simplex::MyEntity::AddToRenderList(bool a_bDrawRigidBody)
{
	//if not in memory return
	if (!m_bInMemory)
		return;

	//draw model
	if (m_pModel) {
		m_pModel->AddToRenderList();
	}
	
	//draw rigid body
	if(a_bDrawRigidBody)
		m_pRigidBody->AddToRenderList();

	if (m_bSetAxis)
		m_pMeshMngr->AddAxisToRenderList(m_m4ToWorld);
}
MyEntity* Simplex::MyEntity::GetEntity(String a_sUniqueID)
{
	//look the entity based on the unique id
	auto entity = m_IDMap.find(a_sUniqueID);
	//if not found return nullptr, if found return it
	return entity == m_IDMap.end() ? nullptr : entity->second;
}
void Simplex::MyEntity::GenUniqueID(String& a_sUniqueID)
{
	static uint index = 0;
	String sName = a_sUniqueID;
	MyEntity* pEntity = GetEntity(a_sUniqueID);
	//while MyEntity exists keep changing name
	while (pEntity)
	{
		a_sUniqueID = sName + "_" + std::to_string(index);
		index++;
		pEntity = GetEntity(a_sUniqueID);
	}
	return;
}
void Simplex::MyEntity::AddDimension(uint a_uDimension)
{
	//we need to check that this dimension is not already allocated in the list
	if (IsInDimension(a_uDimension))
		return;//it is, so there is no need to add

	//insert the entry
	uint* pTemp;
	pTemp = new uint[m_nDimensionCount + 1];
	if(m_DimensionArray)
	{
		memcpy(pTemp, m_DimensionArray, sizeof(uint) * m_nDimensionCount);
		delete[] m_DimensionArray;
		m_DimensionArray = nullptr;
	}
	pTemp[m_nDimensionCount] = a_uDimension;
	m_DimensionArray = pTemp;

	++m_nDimensionCount;

	SortDimensions();
}
void Simplex::MyEntity::RemoveDimension(uint a_uDimension)
{
	//if there are no dimensions return
	if (m_nDimensionCount == 0)
		return;

	//we look one by one if its the one wanted
	for (uint i = 0; i < m_nDimensionCount; i++)
	{
		if (m_DimensionArray[i] == a_uDimension)
		{
			//if it is, then we swap it with the last one and then we pop
			std::swap(m_DimensionArray[i], m_DimensionArray[m_nDimensionCount - 1]);
			uint* pTemp;
			pTemp = new uint[m_nDimensionCount - 1];
			if (m_DimensionArray)
			{
				memcpy(pTemp, m_DimensionArray, sizeof(uint) * (m_nDimensionCount-1));
				delete[] m_DimensionArray;
				m_DimensionArray = nullptr;
			}
			m_DimensionArray = pTemp;
			
			--m_nDimensionCount;
			SortDimensions();
			return;
		}
	}
}
void Simplex::MyEntity::ClearDimensionSet(void)
{
	if (m_DimensionArray)
	{
		delete[] m_DimensionArray;
		m_DimensionArray = nullptr;
	}
	m_nDimensionCount = 0;
}
bool Simplex::MyEntity::IsInDimension(uint a_uDimension)
{
	//see if the entry is in the set
	for (uint i = 0; i < m_nDimensionCount; i++)
	{
		if (m_DimensionArray[i] == a_uDimension)
			return true;
	}
	return false;
}
bool Simplex::MyEntity::SharesDimension(MyEntity* const a_pOther)
{
	
	//special case: if there are no dimensions on either MyEntity
	//then they live in the special global dimension
	if (0 == m_nDimensionCount)
	{
		//if no spatial optimization all cases should fall here as every 
		//entity is by default, under the special global dimension only
		if(0 == a_pOther->m_nDimensionCount)
			return true;
	}

	//for each dimension on both Entities we check if there is a common dimension
	for (uint i = 0; i < m_nDimensionCount; ++i)
	{
		for (uint j = 0; j < a_pOther->m_nDimensionCount; j++)
		{
			if (m_DimensionArray[i] == a_pOther->m_DimensionArray[j])
				return true; //as soon as we find one we know they share dimensionality
		}
	}

	//could not find a common dimension
	return false;
}
bool Simplex::MyEntity::IsColliding(MyEntity* const other)
{
	//if not in memory return
	if (!m_bInMemory || !other->m_bInMemory)
		return true;

	//if the entities are not living in the same dimension
	//they are not colliding
	if (!SharesDimension(other))
		return false;

	return m_pRigidBody->IsColliding(other->GetRigidBody());
}
void Simplex::MyEntity::ClearCollisionList(void)
{
	m_pRigidBody->ClearCollidingList();
}
void Simplex::MyEntity::SortDimensions(void)
{
	std::sort(m_DimensionArray, m_DimensionArray + m_nDimensionCount);
}
void Simplex::MyEntity::ApplyForce(vector3 a_v3Force)
{
	if (m_fMass < 0.01f)
		m_fMass = 0.01f;

	m_v3Acceleration += a_v3Force / m_fMass;
}
void Simplex::MyEntity::Update(void)
{
	m_v3Velocity += m_v3Acceleration;
	m_v3Position += m_v3Velocity;

	SetModelMatrix(glm::translate(m_v3Position) * glm::scale(m_v3Size));
}

vector3 Simplex::MyEntity::GetAcceleration(void)
{
	return m_v3Acceleration;
}

vector3 Simplex::MyEntity::GetSize(void)
{
	return m_v3Size;
}

void Simplex::MyEntity::SetAcceleration(vector3 accel)
{
	m_v3Acceleration = accel;
}

void Simplex::MyEntity::SetSize(vector3 size)
{
	m_v3Size = size;
}
