#include "MyEntityManager.h"
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	m_nEntityCount = 0;
	m_pColliderManager = MyBOManager::GetInstance();
}
void MyEntityManager::Release(void)
{
	for (uint n = 0; n < m_nEntityCount; n++)
	{
		SafeDelete(m_lEntity[n]);
	}
	m_lEntity.clear();
}
// Singleton Accessors
MyEntityManager* MyEntityManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
// The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// Accessors
void MyEntityManager::AddEntity(String a_sEntity, float a_fMass)
{
	MyEntityClass* pEntity = new MyEntityClass(a_sEntity, a_fMass);
	AddEntity(pEntity);
}
void MyEntityManager::AddEntity(MyEntityClass* a_nEntity)
{
	if (a_nEntity == nullptr)
		return;
	m_lEntity.push_back(a_nEntity);
	m_map[a_nEntity->GetName()] = m_nEntityCount;
	m_nEntityCount++;
}
MyEntityClass* MyEntityManager::GetEntity(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex); //Identify the entry by name
	return GetEntity(nIndex); //return the entry if found
}
MyEntityClass* MyEntityManager::GetEntity(int a_nIndex)
{
	uint nIndex = static_cast<int>(m_lEntity.size());//check if the index is in bounds
	//assert(a_nIndex >= 0 && a_nIndex < nIndex); // Assert there is an entry
	if (nIndex == -1)//If the index was not found
		return nullptr; //return a nullptr
	return m_lEntity[a_nIndex];//return the entry
}
int MyEntityManager::GetEntityCount(void) { return m_nEntityCount; }
int MyEntityManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_map.find(a_sIndex);
	//If not found return -1
	if (var == m_map.end())
		return -1;
	return var->second;//Get the index
}
void MyEntityManager::SetMass(float a_fMass, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetMass(a_fMass);
}
void MyEntityManager::SetFriction(float a_fFriction, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetFriction(a_fFriction);
}
void MyEntityManager::SetMaxVelocity(float a_fMaxVelocity, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetMaxVelocity(a_fMaxVelocity);
}
void MyEntityManager::SetPosition(vector3 a_v3Position, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetPosition(a_v3Position);
}
void MyEntityManager::SetVelocity(vector3 a_v3Velocity, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetVelocity(a_v3Velocity);
}

void MyEntityManager::SetGravityAffected(bool a_bGravity, String a_sEntityName)
{
	int nIndex = GetIndex(a_sEntityName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetGravityAffected(a_bGravity);
}
//--- Non Standard Singleton Methods
void MyEntityManager::ApplyForce(vector3 a_v3Force, String a_sEntity)
{
	int nIndex = GetIndex(a_sEntity);
	if (nIndex >= 0)
	{
		m_lEntity[nIndex]->ApplyForce(a_v3Force);
	}
}
void MyEntityManager::Update(void)
{
	//Get the time difference
	SystemSingleton* m_pSystem = SystemSingleton::GetInstance();
	static int nClock = m_pSystem->AddClock();
	float fDeltaTime = static_cast<float>(m_pSystem->LapClock(nClock));
	//Get a Copy of the current forces and positions, then update the entities
	std::vector<vector3> lForceLast;
	std::vector<vector3> lPositionLast;
	for (uint nEntity = 0; nEntity < m_nEntityCount; nEntity++)
	{
		lPositionLast.push_back(m_lEntity[nEntity]->GetPosition());
		lForceLast.push_back(m_lEntity[nEntity]->GetForce());
		m_lEntity[nEntity]->Update(fDeltaTime);
	}
	//Update the collider manager based on the new positions
	m_pColliderManager->Update();
	//Get the forces applied this frame
	std::vector<vector3> lForce;
	for (uint nEntity = 0; nEntity < m_nEntityCount; nEntity++)
	{
		lForce.push_back(m_lEntity[nEntity]->GetForce());
	}
	bool bFloorColliding = false;
	//For each entity apply the forces of all colliding objects
	for (uint nEntity = 0; nEntity < m_nEntityCount; nEntity++)
	{
		if (m_lEntity[nEntity]->GetGravityAffected())
		{
			std::vector<int> list = m_pColliderManager->GetCollidingVector(nEntity);
			uint nColliderCount = list.size();
			vector3 v3AccelerationTotal = m_lEntity[nEntity]->GetForce();
			for (uint nCollidingEntity = 0; nCollidingEntity < nColliderCount; nCollidingEntity++)
			{
				int nIndex = list[nCollidingEntity];
				//Get other's acceleration
				vector3 v3AccelerationOther = m_lEntity[nIndex]->GetForce();
				//f = m * a
				v3AccelerationOther = v3AccelerationOther / m_lEntity[nIndex]->GetMass();
				v3AccelerationTotal += v3AccelerationOther;
				v3AccelerationTotal += vector3( 0.0f, 9.81f, 0.0f) * fDeltaTime;
				v3AccelerationTotal -= m_lEntity[nEntity]->GetForce();
				//a = f / m
				lForce[nEntity] = v3AccelerationTotal / m_lEntity[nEntity]->GetMass();
			}
			if (nColliderCount > 0)
			{
				vector3 v3PosLast = lPositionLast[nEntity];
				m_lEntity[nEntity]->SetPosition(v3PosLast);
			}
		}
	}

	//Set the new forces to the entities
	for (uint nEntity = 0; nEntity < m_nEntityCount; nEntity++)
	{
		m_lEntity[nEntity]->SetForce(lForce[nEntity]);
	}
}
void MyEntityManager::Display(int a_nRenderMode)
{
	//Display the objects
	for (uint nEntity = 0; nEntity < m_nEntityCount; nEntity++)
	{
		m_lEntity[nEntity]->Display(a_nRenderMode);
	}
}