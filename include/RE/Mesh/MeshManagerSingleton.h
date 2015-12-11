/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHMANAGERSINGLETON_H_
#define __MESHMANAGERSINGLETON_H_

#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"
#include "RE\Mesh\ModelManagerSingleton.h"
#include "RE\Mesh\TextSingleton.h"

namespace ReEng
{
//MeshManagerSingleton
class ReEngDLL MeshManagerSingleton
{
	static MeshManagerSingleton* m_pInstance; // Singleton pointer

	TextSingleton* m_pText; //Text Singleton

public:
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//pointer to the Mesh Drawer singleton
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //pointer to the Primitive Manager singleton
	ModelManagerSingleton* m_pModelMngr = nullptr; //pointer to the Model Manager singleton

	/* Gets/Constructs the singleton pointer */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static MeshManagerSingleton* GetInstance();

	/* Destroys the singleton */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);

	/* Saves the specified model file, needs to specify the file extension (ATO or BTO) */
	/*
	 SaveModel
	USAGE: Will translate a model in the list to the specified format
	ARGUMENTS:
		String a_sFileName -> Name of the file
		FORMAT a_Format -> Extension of the file FORMAT::ATO or FORMAT::BTO
		String a_sInstanceName -> Name of the instance to save
		bool a_bAbsoluteRoute = false -> whether the filename specifies an absolute route or not
	OUTPUT: REERRORS -> ERROR_FREE if everything went right, reason for failure otherwise
	*/
	REERRORS SaveModel(String a_sFileName,
						FORMAT a_Format,
						String a_sInstanceName,
						bool a_bAbsoluteRoute = false);

	/* Loads the specified model file */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadModel(String a_sFileName,
							String a_sInstanceName,
							bool a_bAbsoluteRoute = false,
							matrix4 a_m4ToWorld = matrix4(1.0),
							int a_nVisibility = 1,
							int a_nCollidable = 1,
							int a_nState = 0);

	/* Loads the specified level file */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void LoadLevel(String a_sFileName);

	/* Loads an add-on file for the specified instance*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadAddOn(String a_sInstanceName, String a_sFileName);

	/* Sets the model matrix of an specific instance finding it by name */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, String a_sInstance = "ALL", bool a_bUpdateOctree = false);

	/* Sets the model matrix of an specific instance finding it by index */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, int a_nIndex, bool a_bUpdateOctree = false);

	/* Asks the manager for an specific instance's model to world matrix */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 GetModelMatrix(String a_sInstance);

	/* Updates the model manager */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Update(bool a_bCheckCollisions = true);

	/* Renders a line on with the specified vectors and color */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddLineToRenderList(vector3 a_v3Origin, vector3 a_v3Ending, vector3 a_v3StartColor = REDEFAULT, vector3 a_v3EndColor = REDEFAULT);

	/* Renders a mesh on the specified space */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMeshToRenderList(MeshClass* a_pMesh, matrix4& a_m4ToWorld);

	/* Renders a mesh on the specified space */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMeshToRenderList(int a_nIndex, matrix4& a_m4ToWorld);

	/* Render the axis on the specified position */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddAxisToQueue(matrix4 a_m4ToWorld);

	/* Renders the cube on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddPlaneToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);

	/* Renders the cube on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the cone on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddConeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the cylinder on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCylinderToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the tube on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the torus on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTorusToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the sphere on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddSphereToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);

	/* Renders the sphere on the specified position*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddGridToQueue(float a_fSize = 1.0f, int a_Axis = REAXIS::XY, vector3 a_v3Color = REDEFAULT);

	/* Renders a String in the specified color */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Print(String a_sInput, vector3 a_v3Color = REWHITE);
	/* Renders a String Line in the specified color */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PrintLine(String a_sInput, vector3 a_v3Color = REWHITE);

	/* Renders a char array in the specified color */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTextToQueue(vector3 a_v3Color, const char * _Format, ...);
	/* Renders a char array in the specified color */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTextLineToQueue(vector3 a_v3Color, const char * _Format, ...);

	/* Renders the a Camera Mesh on the specified camera's position, -1 for active camera*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCameraToQueue(int a_nID = -1, vector3 a_v3Color = REWHITE);
	/*
	USAGE: Adds an instance to the render list specified by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(uint a_nInstance);
	/* Renders the specified instance */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(String a_sInstance = "ALL");

	/* Renders the list of meshes */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Render(void);

	/* Asks the Manager for the number of models */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetModelCount(void);

	/* Asks the Manager for the number of instances */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetInstanceCount(void);

	/* Asks the name of the specified instance by its index returns empty if not found */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	String GetNameOfInstanceByIndex(int a_nIndex);

	/* Gets the Instance by an index number */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByIndex(int a_nIndex);

	/* Gets the Instance by a name */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByName(String a_sInstanceName);

	/* Asks for the Bounding Object of the specified instance by index*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass* GetBoundingObject(int a_nIndex);

	/* Asks for the Bounding Object of the specified instance by name*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass* GetBoundingObject(String a_sInstanceName);

	/* Asks the manager for the list of vertices of an specified instance */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(String a_sInstanceName);

	/* Asks the manager if an instance with this name has been created */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool IsInstanceCreated(String a_sInstanceName);

	/* Sets the visibility flag of the Bounding Object */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleBoundingObject(bool a_bVisible, String a_sInstanceName = "ALL");

	/* Sets the visibility flag of the Bounding Object */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleBoundingObject(bool a_bVisible, int a_nInstanceIndex);

	/* Returns a vector4 with the indices of the Instances and groups colliding */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector4> GetCollisionList(void);

	/* Returns the index of the specified instance name, -1 if not found */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyInstance(String a_sInstanceName);

	/* Sets the shader program of an specific instance by name */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgramByName(String a_sInstanceName = "ALL", String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the shader program of an specific instance by index */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgramByNumber(int a_nInstance = -1, int a_nGroup = -1, String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);

	/* Sets the visibility of the axis of the instance */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bVisible, String a_sInstanceName = "ALL", bool a_bAllGroups = false);

	/* Sets the visibility of the hierarchical Bounding Object */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleBoundingObjectHierarchy(bool a_bVisible, String a_sInstanceName = "ALL");

	/* Sets the texture for the font */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFont(String a_sTextureName);

private:
	/* Constructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	MeshManagerSingleton(void);

	/* Copy Constructor */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManagerSingleton(MeshManagerSingleton const& other);

	/* Copy Assignment Operator */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManagerSingleton& operator=(MeshManagerSingleton const& other);

	/* Destructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MeshManagerSingleton(void);

	/* Initializes the objects fields */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/* Releases the objects memory */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

}

#endif //__MESHMANAGERSINGLETON_H_