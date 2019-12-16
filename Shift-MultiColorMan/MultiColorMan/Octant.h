/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/07
----------------------------------------------*/
#ifndef __OCTANTCLASS_H_
#define __OCTANTCLASS_H_

#include "Definitions.h"
#include "MyEntityManager.h"

namespace Simplex
{

	//System Class
	class Octant
	{
		static uint m_uMaxLevel;//will store the maximum level an octant can go to

		uint m_uID = 0; //Will store the current ID for this octant
		uint m_uLevel = 0; //Will store the current level of the octant
		uint m_uChildren = 0;// Number of children on the octant (either 0 or 8)

		float m_fSize = 0.0f; //Size of the octant

		MeshManager* m_pMeshMngr = nullptr;//Mesh Manager singleton


		vector3 m_v3Center = vector3(0.0f); //Will store the center point of the octant
		vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the octant
		vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the octant

		Octant* m_pParent = nullptr;// Will store the parent of current octant
		Octant* m_pChild[8];//Will store the children of the current octant

		std::vector<int> m_EntityList; //List of Entities under this octant (Index in Entity Manager)

	public:
		/*
		USAGE: Constructor, will create an octant containing all MagnaEntities Instances in the Mesh
		manager	currently contains
		ARGUMENTS:
		- uint a_nMaxLevel = 2 -> Sets the maximum level of subdivision
		- uint nIdealEntityCount = 5 -> Sets the ideal level of objects per octant
		OUTPUT: class object
		*/
		Octant(uint a_nMaxLevel = 2);
		/*
		USAGE: Constructor
		ARGUMENTS:
		- vector3 a_v3Center -> Center of the octant in global space
		- float a_fSize -> size of each side of the octant volume
		OUTPUT: class object
		*/
		Octant(vector3 a_v3Center, vector3 a_v3Size, uint a_uLevel);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~Octant(void);
		/*
		USAGE: Displays the MyOctant volume in the color specified
		ARGUMENTS:
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void Display(vector3 a_v3Color = C_YELLOW);
		/*
		USAGE: Clears the Entity list for each node
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void ClearEntityList(void);
		/*
		USAGE: allocates 8 smaller octants in the child pointers
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Subdivide(void);
		/*
		USAGE: Asks the MyOctant if it does not contain any children (its a leaf)
		ARGUMENTS: ---
		OUTPUT: It contains no children
		*/
		bool IsLeaf(void);
		/*
		USAGE: Deletes all children and the children of their children (almost sounds apocalyptic)
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void KillBranches(void);

		int GetOctant(int entity);

		bool ResizeToFit(int entity);

		void AddEntity(int entity);
		std::vector<int> GetAllEntities();
		std::vector<int> GetRelevantEntities(int entity);

	private:
		/*
		USAGE: Deallocates member fields
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);
	};//class

} //namespace Simplex

#endif //__OCTANTCLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */