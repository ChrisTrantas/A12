/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __GROUP_H_
#define __GROUP_H_

#include "RE\Materials\MaterialManagerSingleton.h"
#include "RE\Animation\FrameClass.h"
#include "RE\Animation\AnimationClass.h"
#include "RE\Physics\BoundingObjectClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\mesh\AxisClass.h"

namespace ReEng
{

class ReEngDLL GroupClass
{	
	bool m_bVisible = true;	//Visibility flag
	bool m_bVisibleBO = false;	//Debug flag
	bool m_bCollidable = false;	//Collision flag
	bool m_bGlobalized = false;	//Global coordinates flag
	bool m_bModified = false;	//Modified flag

	int m_nHP = 0;			//Hit Points of this group
	uint m_nShapeCount = 0;		//number of shapes in this group
	uint m_nFrameCount = 0;		//Frames in this group
	
	SystemSingleton* m_pSystem = nullptr;	//System pointer
	MaterialManagerSingleton* m_pMatMngr = nullptr;//Material Manager Pointer
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//Mesh Manager Pointer
	GroupClass* m_pParent = nullptr;	//Parent group pointer
	FrameClass* m_pFrame = nullptr;	//List of frames of animation in the group
	BoundingObjectClass* m_pBO = nullptr;	//Bounding Object of the group
	AxisClass* m_pAxis = nullptr;		//Axis of the group
	
	String m_sName = "NULL";			//Name of the group
	String m_sParent = "NULL";		//Name of the parent of the group

	vector3 m_v3Pivot;		//Point in which the point is going to rotate around
	matrix4 m_m4ToWorld;	//Model to world matrix

	std::vector<MeshClass*> m_lMeshList;//List of shapes that compose the group
	std::vector<int> m_lMesh; //List of Meshes that compose a group
	std::vector<int> m_lMeshM; //List of Meshes that compose a group when modified
	matrix4 m_m4Mesh; //List of matrices for all Meshes that compose a group

public:
	/*
	 GroupClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	GroupClass(void);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GroupClass(const GroupClass& other);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GroupClass& operator=(const GroupClass& other);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	~GroupClass(void);
	
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(GroupClass& other);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetShapeCount(void); //Returns the number of shapes in the vector of shapes
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetName(void); //Return the name of the group
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetName(String a_sName);
	//__declspec(property(get = GetName, put = SetName)) String Name; //Name Property

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MeshClass* GetMesh(uint a_nIndex);//Returns the shape in the given index

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void RemoveEmptyMeshes(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMesh(String a_sName);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyShapeByMaterial(String a_sName);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool CloneFromGroup(const GroupClass& other);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ReleaseOpenGL(); //DeleteOpenGL

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void CompleteMissingShapeInfo(bool a_bAverageNormals = false);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SwapMaterial(String a_sOldMaterialName, String a_sNewMaterialName);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetMaterial(String a_sMaterialName);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetPivot(void);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPivot(vector3 a_v3Pivot);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetParent(GroupClass* a_pParent);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetHP(int a_nHP);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetHP(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetCollidable(bool a_bCollidable);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetCollidable(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisible(bool a_bVisible);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetVisible(void);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetParentName(void);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetParentName(String a_sParent);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	FrameClass GetFrame(uint nFrame);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetGlobalized(bool a_bGlobalized);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetFrameCount(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateFrames(int a_nFrames);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReleaseFrames(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFrame(int a_nFrame, vector3 a_v3Translation, vector3 a_v3Rotation, vector3 a_v3Scale, bool a_bVisible, bool a_bKeyframe);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosX(float a_fValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosY(float a_fValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosZ(float a_fValue, int a_nFrame);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetAngX(float a_fValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetAngY(float a_fValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetAngZ(float a_fValue, int a_nFrame);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSizeX(float a_fValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSizeY(float a_fValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSizeZ(float a_fValue, int a_nFrame);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisible(bool a_bValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetKeyframe(bool a_bValue, int a_nFrame);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleBO(bool a_bVisibleBO);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bVisible);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ComputeMatrix(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Interpolate(int a_nFrames);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	matrix4& GetModelMatrix(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 TraverseHierarchy(GroupClass* a_Group, int a_nFrame = 0);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(int a_nShape = -1);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Update(uint a_nFrame, matrix4 a_mToWorld);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	BoundingObjectClass* GetBoundingObject(void);
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileBoundingObject(void);
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetBoundingObject(BoundingObjectClass* a_pBO);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);

	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DisconectAnimationFrames(void);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_nMatrix);

	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddToRenderList(uint a_nFrame = 0);//Add all shapes to the render list
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddBOToRenderList(bool a_bForce = false);//Render all debug
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddAxisToRenderList(bool a_bForce = false);//Render all debug

private:
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass*>;

}
#endif //__GROUP_H__