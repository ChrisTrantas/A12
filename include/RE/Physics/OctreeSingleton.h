/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __OCTREESINGLETON_H_
#define __OCTREESINGLETON_H_

#include "RE\system\SystemSingleton.h"
#include "RE\Physics\OctantClass.h"

namespace ReEng
{

//System Class
class ReEngDLL OctreeSingleton
{
	int m_nOctantCount = 0;			//Number of octants in the Tree
	int m_nMaxSubtrees = 0;		//Maximum sublevel of the tree
	int m_nMaxObjects = 0;		//Maximum number of objects per octant
	OctantClass* m_pRoot = nullptr;	//Root of the Tree
	static OctreeSingleton* m_pInstance; // Singleton pointer

public:
	/* Gets/Constructs the singleton pointer */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static OctreeSingleton* GetInstance();
	/* Destroys the singleton */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);

	/* Gets an octant from the tree by ID*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	OctantClass* GetOctant(int a_nOctantID);

	/* Generates the Tree using the provided Bounding Object List and maximum levels and objects per octant */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateOctree(std::vector<BoundingObjectClass*> a_lBoundingObject, int a_nMaxSubtrees = 4, int a_nMaxObjects = 2);
	
	/* Calculates the Octant(s) the provided Bounding object is currently located without reconstructing the tree*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void UpdatePositionInTree(BoundingObjectClass* a_pBO);

	/* Renders the Non-empty leaf octant nodes of the Octree*/
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Render(void);

private:
	/* Constructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	OctreeSingleton(void);
	/* Copy Constructor */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	OctreeSingleton(OctreeSingleton const& other);
	/* Copy Assignment Operator */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	OctreeSingleton& operator=(OctreeSingleton const& other);
	/* Destructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~OctreeSingleton(void);

	/* Releases the objects memory */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/* Initializates the objects fields */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/* Taverses the tree finding the octant nodes the provided Bounding Object collides with*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void TraverseUpdatePosition(OctantClass* a_pNode, BoundingObjectClass* a_pBO);

	/* Traverse the tree for rendering */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void TraverseRender(OctantClass* a_pNode);

	/* Traverses the tree filling internal information */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void TraverseInfo(OctantClass* a_pNode);

	/* Traverses finding the node that contains the specidied ID, it will store it in a_pOutput */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void TraverseGet(OctantClass* a_pNode, OctantClass*& a_pOutput, int a_nID);

	/* Generates the 8 octant nodes for the specified a_pNode with a maximum level of subdivisions and max objects per node */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateSubTree(OctantClass* a_pNode, bool a_bResetCount = false);

	/* Deletes the specidied node and subtrees */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void DeleteNode(OctantClass*& a_pNode);
};

}

#endif //__OCTREESINGLETON_H_