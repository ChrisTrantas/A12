#include "MyEntityClass.h"
//---
void MyEntityClass::Init(void)
{
	//Set initial values
	m_bGravityAffected = true;

	m_v3Position = ZERO_V3;
	m_v3PositionPrevious = ZERO_V3;

	m_v3Velocity = ZERO_V3;
	m_v3Force = ZERO_V3;

	m_fFriction = 0.0f;
	m_fMass = 1.0f;
	m_fMaxVelocity = 1.0f;

	m_sName = "";

	m_pColliderManager = MyBOManager::GetInstance();
	m_pMeshManager = MeshManagerSingleton::GetInstance();
}
void MyEntityClass::Swap(MyEntityClass& other)
{
	//Swap content between objects
	std::swap(m_bGravityAffected, other.m_bGravityAffected);
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3PositionPrevious, other.m_v3PositionPrevious);

	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Force, other.m_v3Force);

	std::swap(m_fFriction, other.m_fFriction);
	std::swap(m_fMaxVelocity, other.m_fMaxVelocity);

	std::swap(m_pColliderManager, other.m_pColliderManager);
	std::swap(m_pMeshManager, other.m_pMeshManager);

	std::swap(m_sName, other.m_sName);
}
void MyEntityClass::Release(void)
{
	//No pointers allocated yet, this object is not responsible to
	//deallocate the singletons
}
// The rule of 3
MyEntityClass::MyEntityClass(String a_sName, float a_fMass)
{
	//Create a new object based on the name
	Init();//initialize members
	m_sName = a_sName;//set the name
	m_fMass = a_fMass;
	std::vector<vector3> list = m_pMeshManager->GetVertexList(m_sName);//Get the list of verts
	m_pColliderManager->AddObject(list, m_sName);//Construct a Bounding Object
}
MyEntityClass::MyEntityClass(MyEntityClass const& other)
{
	//Copy information from the other object
	m_bGravityAffected = other.m_bGravityAffected;

	m_v3Position = other.m_v3Position;
	m_v3PositionPrevious = other.m_v3PositionPrevious;

	m_v3Velocity = other.m_v3Velocity;
	m_v3Force = other.m_v3Force;

	m_fFriction = other.m_fFriction;
	m_fMaxVelocity = other.m_fMaxVelocity;
	m_sName = other.m_sName;

	m_pColliderManager = other.m_pColliderManager;
	m_pMeshManager = other.m_pMeshManager;
}
MyEntityClass& MyEntityClass::operator=(MyEntityClass const& other)
{
	//if this object is the same as the incoming one there is nothing to do
	if (this != &other)
	{
		Release(); //release the content of this object
		Init(); //Initialize the default values
		MyEntityClass temp(other);//create a temporal object using the incoming one's information
		Swap(temp); //Switch the content of this object and the temporal one
	}
	return *this;
}
// Destructor
MyEntityClass::~MyEntityClass()
{
	Release();//Call deallocators
}
//Accessors
void MyEntityClass::SetVelocity(vector3 a_v3Velocity){ m_v3Velocity = a_v3Velocity; }
void MyEntityClass::SetMaxVelocity(float a_fMaxVelocity) { m_fMaxVelocity = a_fMaxVelocity; }
void MyEntityClass::SetMass(float a_fMass){ m_fMass = a_fMass; }
void MyEntityClass::SetFriction(float a_fFriction) { m_fFriction = a_fFriction; }
void MyEntityClass::SetForce(vector3 a_v3Force) { m_v3Force = a_v3Force; }
void MyEntityClass::SetPosition(vector3 a_v3Position)
{
	m_v3Position = a_v3Position;
	matrix4 m4ToWorld = glm::translate(m_v3Position);
	//Set the model matrix for the objects
	m_pMeshManager->SetModelMatrix(m4ToWorld, m_sName);
	m_pColliderManager->SetModelMatrix(m4ToWorld, m_sName);
}
float MyEntityClass::GetMass(void) { return m_fMass; }
String MyEntityClass::GetName(void) { return m_sName; }
vector3 MyEntityClass::GetLastPosition(void) { return m_v3PositionPrevious; }
vector3 MyEntityClass::GetPosition(void) { return m_v3Position; }
vector3 MyEntityClass::GetForce(void) { return m_v3Force; }
vector3 MyEntityClass::GetVelocity(void) { return m_v3Velocity; }

void MyEntityClass::SetGravityAffected(bool a_bGravity) { m_bGravityAffected = a_bGravity; }
bool MyEntityClass::GetGravityAffected(void) {	return m_bGravityAffected; }

//---
void MyEntityClass::ApplyForce(vector3 a_v3Force)
{
	//force = mass * acceleration
	m_v3Force += a_v3Force / m_fMass;
}
void MyEntityClass::ApplyGravity(float a_fDeltaTime)
{
	if(m_bGravityAffected)
		m_v3Force += vector3(0.0f,-9.81f, 0.0f) * a_fDeltaTime;
}
void MyEntityClass::RevertPositionToLastUpdate(void)
{
	m_v3Position = m_v3PositionPrevious;

	matrix4 m4ToWorld = glm::translate(m_v3Position);

	//Set the model matrix for the objects
	m_pMeshManager->SetModelMatrix(m4ToWorld, m_sName);
	m_pColliderManager->SetModelMatrix(m4ToWorld, m_sName);

	//Display the objects
	m_pMeshManager->AddInstanceToRenderList(m_sName);
	m_pColliderManager->DisplayReAlligned(m_sName);
}
void MyEntityClass::Update(float a_fDeltaTime)
{
	//Store my previous position
	m_v3PositionPrevious = m_v3Position;
	//Apply friction
	float fFriction = MapValue(m_fFriction, 0.0f, 1.0f, 1.0f, 0.0f);
	m_v3Force = m_v3Force * fFriction;

	//Apply Gravity
	ApplyGravity(a_fDeltaTime);

	//Calculate the velocity based on acceleration delta time
	vector3 v3Velocity = m_v3Force * a_fDeltaTime;
	//if(m_bGravityAffected)
	//	v3Velocity += vector3(0.0f, -0.9f, 0.0f) * a_fDeltaTime;
	
	//Increase the velocity based on the acceleration
	m_v3Velocity = glm::clamp(v3Velocity, -m_fMaxVelocity, m_fMaxVelocity);
	//Set the position based on the position of this object and the acceleration
	m_v3Position += m_v3Velocity;
	
	//Transform to the position
	matrix4 m4ToWorld = glm::translate(m_v3Position);

	//Set the model matrix for the objects
	m_pMeshManager->SetModelMatrix(m4ToWorld, m_sName);
	m_pColliderManager->SetModelMatrix(m4ToWorld, m_sName);
}
void MyEntityClass::Display(int a_nRenderMode)
{
	//Display the objects
	if(a_nRenderMode & ER_MESH)
		m_pMeshManager->AddInstanceToRenderList(m_sName);
	if (a_nRenderMode & ER_RB)
		m_pColliderManager->DisplayReAlligned(m_sName);
	if (a_nRenderMode & ER_BS)
		m_pColliderManager->DisplaySphere(m_sName);
	if (a_nRenderMode & ER_OB)
		m_pColliderManager->DisplayOriented(m_sName);
}