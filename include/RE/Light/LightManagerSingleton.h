/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LIGHTMANAGERSINGLETON_H_
#define __LIGHTMANAGERSINGLETON_H_

#include "RE\light\LightClass.h"
#include <vector>
#include <assert.h>

namespace ReEng
{

//System Class
class ReEngDLL LightManagerSingleton
{
	//Private Fields
	int m_nLightCount = 0;		//Number of Lights
	float m_fAmbient = 0.0f;	//Ambient power
	static LightManagerSingleton* m_pInstance; // Singleton
	std::vector<LightClass*> m_lLight; //vector of lights

public:
	//Public Accessors
	/* Gets/Constructs the singleton pointer */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static LightManagerSingleton* GetInstance();
	/* Releases the singleton pointer */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/* Adds a light to the list of lights */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddLight(vector3 a_v4Position = vector3(1, 1, 1),
					vector3 a_v3Color = vector3(1,1,1),
					float a_vIntensity = 10.0f);
	/* Gets a copy from a light in the list of lights */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	LightClass* GetLight(int a_nIndex = 1);
	/* Sets the position of a light in the list of lights*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v4Position, int a_nLight = 1);
	/* Gets the position of a light in the list of lights*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	vector3 GetPosition(int a_nLight = 1);
	/* Sets the color of a light in the list of lights*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetColor(vector3 a_v3Color, int a_nLight = 1);
	/* Gets the color of a light in the list of lights*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	vector3 GetColor(int a_nLight = 1);
	/* Sets the intensity of a light in the list of lights*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetIntensity(float a_fIntensity, int a_nLight = 1);
	/* Gets the intensity of a light in the list of lights*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	float GetIntensity(int a_nLight = 1);

private:
	/* Constructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	LightManagerSingleton(void);
	/* Copy Constructor */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	LightManagerSingleton(LightManagerSingleton const& other);
	/* Copy Assignment Operator */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	LightManagerSingleton& operator=(LightManagerSingleton const& other);
	/* Destructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~LightManagerSingleton(void);

	/* Releases Memory */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/* Initialize variables */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}
#endif //__LIGHTMANAGERSINGLETON_H__