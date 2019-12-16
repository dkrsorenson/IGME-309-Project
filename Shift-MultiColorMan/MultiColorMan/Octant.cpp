#include "Octant.h"

namespace Simplex {

	uint Simplex::Octant::m_uMaxLevel = 3;

	Octant::Octant(uint a_nMaxLevel)
	{
		m_pMeshMngr = MeshManager::GetInstance();
		m_uLevel = 0;
	}
	Octant::Octant(vector3 a_v3Center, vector3 a_v3Size, uint a_uLevel)
	{
		m_pMeshMngr = MeshManager::GetInstance();
		m_v3Center = a_v3Center;
		vector3 hw = a_v3Size / 2;
		m_v3Min = m_v3Center - hw;
		m_v3Max = m_v3Center + hw;
		m_uLevel = a_uLevel;
		Subdivide();
	}
	Octant::~Octant(void)
	{
	}
	void Octant::Display(vector3 a_v3Color)
	{
		for (uint i = 0; i < 8; i++)
		{
			if (m_pChild[i])
			{
				m_pChild[i]->Display(a_v3Color);
			}
		}
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(m_v3Center) * glm::scale(m_v3Max - m_v3Min), a_v3Color);
	}
	void Octant::ClearEntityList(void)
	{
	}
	void Octant::Subdivide(void)
	{
		if (m_uLevel >= m_uMaxLevel)
			return;
		m_uChildren = 8;
		vector3 hw = (m_v3Max - m_v3Min) / 2;
		vector3 qw = hw / 2;
		m_pChild[0] = new Octant(m_v3Center + vector3(qw.x, qw.y, qw.z), hw, m_uLevel + 1);
		m_pChild[1] = new Octant(m_v3Center + vector3(qw.x, qw.y, -qw.z), hw, m_uLevel + 1);
		m_pChild[2] = new Octant(m_v3Center + vector3(qw.x, -qw.y, qw.z), hw, m_uLevel + 1);
		m_pChild[3] = new Octant(m_v3Center + vector3(qw.x, -qw.y, -qw.z), hw, m_uLevel + 1);
		m_pChild[4] = new Octant(m_v3Center + vector3(-qw.x, qw.y, qw.z), hw, m_uLevel + 1);
		m_pChild[5] = new Octant(m_v3Center + vector3(-qw.x, qw.y, -qw.z), hw, m_uLevel + 1);
		m_pChild[6] = new Octant(m_v3Center + vector3(-qw.x, -qw.y, qw.z), hw, m_uLevel + 1);
		m_pChild[7] = new Octant(m_v3Center + vector3(-qw.x, -qw.y, -qw.z), hw, m_uLevel + 1);
	}
	bool Octant::IsLeaf(void)
	{
		return m_uChildren == 0;
	}
	void Octant::KillBranches(void)
	{
	}
	int Octant::GetOctant(int entity)
	{
		vector3 max = MyEntityManager::GetInstance()->GetEntity(entity)->GetRigidBody()->GetMaxGlobal();
		vector3 min = MyEntityManager::GetInstance()->GetEntity(entity)->GetRigidBody()->GetMinGlobal();
		if (min.x > m_v3Center.x) {
			if (min.y > m_v3Center.y) {
				if (min.z > m_v3Center.z) {
					return 0;
				}
				if (max.z < m_v3Center.z) {
					return 1;
				}
			}
			if (max.y < m_v3Center.y) {
				if (min.z > m_v3Center.z) {
					return 2;
				}
				if (max.z < m_v3Center.z) {
					return 3;
				}
			}
		}
		if (max.x < m_v3Center.x) {
			if (min.y > m_v3Center.y) {
				if (min.z > m_v3Center.z) {
					return 4;
				}
				if (max.z < m_v3Center.z) {
					return 5;
				}
			}
			if (max.y < m_v3Center.y) {
				if (min.z > m_v3Center.z) {
					return 6;
				}
				if (max.z < m_v3Center.z) {
					return 7;
				}
			}
		}
		return -1;
	}
	bool Octant::ResizeToFit(int entity)
	{
		vector3 oldmax = m_v3Max;
		vector3 oldmin = m_v3Min;
		vector3 max = MyEntityManager::GetInstance()->GetEntity(entity)->GetRigidBody()->GetMaxGlobal();
		vector3 min = MyEntityManager::GetInstance()->GetEntity(entity)->GetRigidBody()->GetMinGlobal();
		if (max.x > m_v3Max.x) {
			m_v3Max.x = max.x;
		}
		if (max.y > m_v3Max.y) {
			m_v3Max.y = max.y;
		}
		if (max.z > m_v3Max.z) {
			m_v3Max.z = max.z;
		}
		if (min.x < m_v3Min.x) {
			m_v3Min.x = min.x;
		}
		if (min.y < m_v3Min.y) {
			m_v3Min.y = min.y;
		}
		if (min.z < m_v3Min.z) {
			m_v3Min.z = min.z;
		}
		return oldmax != m_v3Max || oldmin != m_v3Min;
	}
	void Octant::AddEntity(int entity)
	{
		if (!m_uLevel && ResizeToFit(entity)) {
			KillBranches();
			Subdivide();
		}
		if (IsLeaf()) {
			m_EntityList.push_back(entity);
			return;
		}

		int octant = GetOctant(entity);
		if (octant != -1) {
			m_pChild[octant]->AddEntity(entity);
			return;
		}

		m_EntityList.push_back(entity);
		return;
	}
	std::vector<int> Octant::GetAllEntities() {
		std::vector<int> ae = std::vector<int>();
		for (int i = 0; i < m_EntityList.size(); i++) {
			ae.push_back(m_EntityList[i]);
		}
		if (IsLeaf()) {
			return ae;
		}
		for (int o = 0; o < 8; o++) {
			std::vector<int> c = m_pChild[o]->GetAllEntities();
			for (int i = 0; i < c.size(); i++) {
				ae.push_back(c[i]);
			}
		}
		return ae;
	}

	std::vector<int> Octant::GetRelevantEntities(int entity)
	{
		if (IsLeaf()) {
			return GetAllEntities();
		}
		int octant = GetOctant(entity);
		if (octant == -1) {
			return GetAllEntities();
		}
		return m_pChild[octant]->GetRelevantEntities(entity);
	}
	void Octant::Release(void)
	{
	}
}