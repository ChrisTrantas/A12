/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHCLASS_H_
#define __MESHCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\System\ShaderManagerSingleton.h"
#include "RE\Materials\MaterialManagerSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL MeshClass
{
protected:

	bool m_bCopy = false;	//Checks to see if this Mesh is a copy or the original
	bool m_bWire = false;	//Checks to see if the Mesh is going to be drawn in wires
	bool m_bBinded = false; //Binded flag

	int m_nMaterial = 0; //Material index of this mesh
	int m_nVertexCount = 0; //Number of vertices in this Mesh

	GLuint m_vao = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)
	GLuint m_UVBuffer = 0;		//OpenGL Buffer (Will hold the UV buffer pointer)
	GLuint m_NormalBuffer = 0;	//OpenGL Buffer (will hold the Normal Buffer)
	GLuint m_TangentBuffer = 0;	//OpenGL Buffer (will hold the Tangent Buffer)
	GLuint m_BinormalBuffer = 0;//OpenGL Buffer (will hold the Binormal Buffer)

	GLuint m_nShader = 0;	//Index of the shader
	GLuint m_nShaderO = 0;	//Index of the original shader

	ShaderManagerSingleton* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManagerSingleton* m_pMatMngr = nullptr;		//Material Manager

	String m_sName = "NULL";	//Identifier of the Mesh
	vector3 m_v3Tint; //Color modifier

	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors
	std::vector<vector3> m_lVertexNor;	//List of Normals
	std::vector<vector3> m_lVertexTan;	//List of Tangents
	std::vector<vector3> m_lVertexBin;	//List of Binormals
	std::vector<vector3> m_lVertexUV;	//List of UVS
	
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MeshClass(void);
	/*
	USAGE:Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	MeshClass(MeshClass const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	MeshClass& operator=(MeshClass const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MeshClass(void);
	/*
	USAGE: Swaps the contents of the object with another object's content
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(MeshClass& other);
	/*
	USAGE: Compiles the Mesh for OpenGL 3.X use
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);
	/*
	USAGE: Asks the Mesh if it has been binded
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetBinded(void);
	/*
	USAGE: Set the shader to the newly loaded shader
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the shader of the Shape to a loaded shader
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the material of the shape by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetMaterial(String a_sMaterialName);
	/*
	USAGE: Returns the total number of vertices in this Mesh
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetVertexCount(void);
	/*
	USAGE: Sets the material index by index in the material manager
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetMaterialIndex(int a_nIndex);
	/*
	USAGE: Gets the material used in the shape by index of the material manager
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetMaterialIndex(void);
	/*
	USAGE: Asks the mesh for the Shader program used
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetShaderIndex(void);
	/*
	USAGE: Adds a new point to the vector of vertices
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddVertexPosition(vector3 a_v3Input);
	/*
	USAGE: Adds a new color to the vector of vertices
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddVertexColor(vector3 a_v3Input);
	/*
	USAGE: Adds a new normal to the vector of vertices
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddVertexNormal(vector3 a_v3Input);
	/*
	USAGE: Adds a new binormal to the vector of vertices
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddVertexBinormal(vector3 a_v3Input);
	/*
	USAGE: Adds a new tangent to the vector of vertices
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddVertexTangent(vector3 a_v3Input);
	/*
	USAGE: Adds a new uv to the vector of vertices
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddVertexUV(vector3 a_v3Input);
	/*
	USAGE: Asks the shape for the list of vertices
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	void SetVertexList(std::vector<vector3> a_lVertex);
	/*
	USAGE: Asks the shape for the list of Color vertices
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetColor(void);
	/*
	USAGE: Asks the shape for the list of UV vertices
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetUVs(void);
	/*
	USAGE: Asks the shape for the list of Normal vertices
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetNormals(void);
	/*
	USAGE: Asks the shape for the list of tangents
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetTangents(void);
	/*
	USAGE: Asks the shape for the list of bitangents
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetBitangets(void);
	/*
	USAGE: Return the tint applied to the mesh
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetTint(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVertexBuffer(GLuint a_nIndex);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetVertexBuffer(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetUVBuffer(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetColorBuffer(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetNormalBuffer(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetTangentBuffer(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetBinormalBuffer(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsWire(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetColorSize(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetFirstColor(void);
	/*
	USAGE: Asks the Mesh for its name
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetName(void);
	/*
	USAGE: Sets the Mesh's name
	ARGUMENTS:
	OUTPUT: ---
	*/
	virtual void SetName(String a_sName);
	/*
	USAGE:
	ARGUMENTS:
		MeshClass* a_pMesh
		matrix4 a_mViewProjection
		matrix4 a_mToWorld
		vector3 a_v3Color
	OUTPUT: ---
	*/
	virtual void RenderWire(matrix4 a_mViewProjection, matrix4 a_mToWorld, vector3 a_v3Color);
	/*
	USAGE:
	ARGUMENTS:
		MeshClass* a_pMesh
		matrix4 a_mViewProjection
		matrix4 a_mToWorld
		vector3 a_v3Color
	OUTPUT: ---
	*/
	virtual void RenderSolid(matrix4 a_mViewProjection, matrix4 a_mToWorld, vector3 a_v3Color);

protected:
	/*
	USAGE: Initialize the object's fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Completes the information missing to create the mesh
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompleteMesh(void);
	/*
	USAGE: Disconnects OpenGL3.x from the Mesh without releasing the buffers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DisconnectOpenGL3X(void);

public:
	/*
	USAGE: Completes the triangle information
	ARGUMENTS:
	OUTPUT: ---
	*/
	void CompleteTriangleInfo(bool a_bAverageNormals = false);

	/*
	USAGE: Calculates the missing tangets
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateTangents(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass*>;

}

#endif //__MESHCLASS_H_