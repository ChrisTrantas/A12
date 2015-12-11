/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "MyBOManager.h"
enum ENTITYRM
{
	ER_MESH = 1,
	ER_BS = 2,
	ER_OB = 4,
	ER_RB = 8,
};

class MyEntityClass
{
	bool m_bGravityAffected = true; //flag for gravity
	vector3 m_v3Position = ZERO_V3; //Position of the Entity
	vector3 m_v3PositionPrevious = ZERO_V3; //Position of the Entity

	vector3 m_v3Velocity = ZERO_V3; //Velocity of the Entity
	vector3 m_v3Force = ZERO_V3; //Acceleration of the Entity

	float m_fFriction = 0.0f; //Friction factor of the entity between 0 and 1
	float m_fMass = 1.0f;	//Mass of the Entity
	float m_fMaxVelocity = 1.0f; //Limit of the acceleration of the entity

	String m_sName = ""; // Name index

	MyBOManager* m_pColliderManager = nullptr; //Collider manager
	MeshManagerSingleton* m_pMeshManager = nullptr;//Mesh Manager

public:
	/*
	USAGE: Constructor
	ARGUMENTS:
	--- String a_sName -> Name assigned to the entity
	--- float a_fMass -> Mass of the Entity
	OUTPUT: class object
	*/
	MyEntityClass(String a_sName, float a_fMass);
	/*
	USAGE: Constructor
	ARGUMENTS: class object
	OUTPUT: class object
	*/
	MyEntityClass(MyEntityClass const& other);
	/*
	USAGE: Copy Assignment operator
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyEntityClass& operator=(MyEntityClass const& other);
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	~MyEntityClass();
	/*
	USAGE: Calculates the position of the entity based on the 
		acceleration and mass, will also update its mesh and collider
	ARGUMENTS:
	--- float a_fDeltaTime -> time difference between calls
	OUTPUT: ---
	*/
	void Update(float a_fDeltaTime);
	/*
	USAGE: Calculates the position of the entity based on the
	acceleration and mass, will also update its mesh and collider
	ARGUMENTS:
	--- int a_nRenderMode = ER_MESH -> specifies what to render
		ie ( ER_MESH | ER_RB ) will render the mesh and the Realligned Box
	OUTPUT: ---
	*/
	void Display(int a_nRenderMode = ER_MESH);
	/*
	USAGE: Takes one step back in the update method
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void RevertPositionToLastUpdate(void);
	/*
	USAGE: Accessor of Maximum velocity
	ARGUMENTS:
	--- float a_fMaxVelocity -> Max Velocity input
	OUTPUT: ---
	*/
	void SetMaxVelocity(float a_fMaxVelocity);
	/*
	USAGE: Accessor of friction
	ARGUMENTS:
	--- float a_fFriction -> friction input
	OUTPUT: ---
	*/
	void SetFriction(float a_fFriction);
	/*
	USAGE: Accessor of mass
	ARGUMENTS: float a_fMass -> mass input
	OUTPUT: ---
	*/
	void SetMass(float a_fMass);
	/*
	USAGE: Accessor of mass
	ARGUMENTS: ---
	OUTPUT: float -> mass
	*/
	float GetMass(void);
	/*
	USAGE: Accessor of gravity
	ARGUMENTS:
	--- bool a_bGravity -> Gravity flag
	OUTPUT: ---
	*/
	void SetGravityAffected(bool a_bGravity);
	/*
	USAGE: Accessor of gravity
	ARGUMENTS: ---
	OUTPUT: bool -> gravity flag
	*/
	bool GetGravityAffected(void);
	/*
	USAGE: Accessor of Position
	ARGUMENTS:
	--- vector3 a_v3Position -> position input
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Returns the position the object was last call
	ARGUMENTS: ---
	OUTPUT: vector3 -> Last known position
	*/
	vector3 GetLastPosition(void);
	/*
	USAGE: Accessor of Position
	ARGUMENTS: ---
	OUTPUT:  vector3 -> position
	*/
	vector3 GetPosition(void);
	/*
	USAGE: Accessor of velocity
	ARGUMENTS:
	--- vector3 a_v3Velocity -> velocity input
	OUTPUT: ---
	*/
	void SetVelocity(vector3 a_v3Velocity);
	/*
	USAGE: Applies a force into the entity
	ARGUMENTS: vector3 a_v3Force -> input force
	OUTPUT: ---
	*/
	void ApplyForce(vector3 a_v3Force);
	/*
	USAGE: Accessor of force
	ARGUMENTS: ---
	OUTPUT: vector3 -> acceleration of entity
	*/
	vector3 GetForce(void);
	/*
	USAGE: Accessor of force
	ARGUMENTS: vector3 -> acceleration of entity
	OUTPUT: ---
	*/
	void SetForce(vector3 a_v3Force);
	/*
	USAGE: Accessor of Velocity
	ARGUMENTS: ---
	OUTPUT: vector3 -> velocity of entity
	*/
	vector3 GetVelocity(void);
	/*
	USAGE: Adds gravity on the entity based on the time difference
	ARGUMENTS:
	--- float a_fDeltaTime -> Time difference between calls
	OUTPUT: ---
	*/
	void ApplyGravity(float a_fDeltaTime);
	/*
	USAGE: Accessor of name
	ARGUMENTS: ---
	OUTPUT: String -> name of entity
	*/
	String GetName(void);

protected:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	void Init(void);
	/*
	USAGE: Exchanges member information with object
	ARGUMENTS: class object
	OUTPUT: ---
	*/
	void Swap(MyEntityClass& other);
	/*
	USAGE: Releases the allocated memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};
#endif //__MYENTITY_H_