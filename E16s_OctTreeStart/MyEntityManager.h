/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYENTITYMANAGER_H_
#define __MYENTITYMANAGER_H_

#include "MyEntityClass.h"

//System Class
class MyEntityManager
{
	uint m_nEntityCount = 0; //number of elements in the list
	static MyEntityManager* m_pInstance; // Singleton pointer
	std::vector<MyEntityClass*> m_lEntity; //list of elements
	std::map<String, uint> m_map;//Map relating the mesh and the index
	MyBOManager* m_pColliderManager = nullptr; //Collider manager
public:
	/*
	USAGE: returns the singleton pointer
	ARGUMENTS: ---
	OUTPUT: MyEntityManager* -> singleton Accessor
	*/
	static MyEntityManager* GetInstance();
	/*
	USAGE: releases the singleton pointer
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Adds a new entry to the list of Entity
	ARGUMENTS:
	--- MyEntityClass* a_nEntity-> Entity to add
	OUTPUT: ---
	*/
	void AddEntity(MyEntityClass* a_nEntity);
	/*
	USAGE: Adds a new entry to the list of Entity
	ARGUMENTS:
	--- String a_nsEntity-> Creates an entity
	OUTPUT: ---
	*/
	void AddEntity(String a_sEntity, float a_fMass);
	/*
	USAGE: Returns the entry in the specified index, nullptr if un-existent
	ARGUMENTS:
	--- int a_nIndex -> index to return
	OUTPUT: MyEntityClass* -> value on list
	*/
	MyEntityClass* GetEntity(int a_nIndex);
	/*
	USAGE: Returns the entry in the specified index, nullptr if un-existent
	ARGUMENTS:
	--- int a_nIndex -> index to return
	OUTPUT: MyEntityClass* -> value on list
	*/
	MyEntityClass* GetEntity(String a_sEntity);
	/*
	USAGE: Gets the number of entries on vector
	ARGUMENTS: ---
	OUTPUT: int -> number of entries
	*/
	int GetEntityCount(void);
	/*
	USAGE: Returns the index specified by name from the dictionary
	ARGUMENTS:
	--- String a_sIndex -> name of the index
	OUTPUT: index of the specified name, -1 if not found
	*/
	int GetIndex(String a_sEntity);
	/*
	USAGE: Accessor of mass
	ARGUMENTS: 
	--- float a_fMass -> mass input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetMass(float a_fMass, String a_sEntity);
	/*
	USAGE: Accessor of friction
	ARGUMENTS:
	--- float a_fFriction -> friction input
	OUTPUT: ---
	*/
	void SetFriction(float a_fFriction, String a_sEntity);
	/*
	USAGE: Accessor of Maximum velocity
	ARGUMENTS:
	--- float a_fMaxVelocity -> Max Acceleration input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetMaxVelocity(float a_fMaxVelocity, String a_sEntity);
	/*
	USAGE: Accessor of Position
	ARGUMENTS: 
	--- vector3 a_v3Position -> position input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position, String a_sEntity);
	/*
	USAGE: Accessor of velocity
	ARGUMENTS:
	--- vector3 a_v3Velocity -> velocity input
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity, String a_sEntity);
	/*
	USAGE: Accessor of gravity
	ARGUMENTS:
	--- bool a_bGravity -> Gravity flag
	--- String a_sEntity -> Entity ID
	OUTPUT: ---
	*/
	void SetGravityAffected(bool a_bGravity, String a_sEntity);
	/*
	USAGE: Applies a force into the entity
	ARGUMENTS:
	--- vector3 a_v3Force -> input force
	--- String a_sEntity -> entity id
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force, String a_sEntity);
	/*
	USAGE: Updates all the Entity
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Calculates the position of the entity based on the
	acceleration and mass, will also update its mesh and collider
	ARGUMENTS:
	--- int a_nRenderMode = ER_MESH -> specifies what to render
	ie ( ER_MESH | ER_RB ) will render the mesh and the Realligned Box
	OUTPUT: ---
	*/
	void Display(int a_nRenderMode = ER_MESH);

private:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: Class object
	*/
	MyEntityManager(void);
	/*
	USAGE: copy constructor
	ARGUMENTS: Class object to copy
	OUTPUT: Class object
	*/
	MyEntityManager(MyEntityManager const& other);
	/*
	USAGE: copy assignment operator
	ARGUMENTS: Class object to copy
	OUTPUT: Class object
	*/
	MyEntityManager& operator=(MyEntityManager const& other);
	/*
	USAGE: destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyEntityManager(void);
	/*
	USAGE: Releases the memory of the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initializes the default values
	ARGUMENTS: --- 
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__MYENTITYMANAGER_H_