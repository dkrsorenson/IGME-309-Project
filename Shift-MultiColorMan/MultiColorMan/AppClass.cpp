#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pEntityMngr->UsePhysicsSolver();

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Steve"))->GetPosition().x, 4.0f, 15.0f), //Position
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Steve"))->GetPosition().x, 4.0f, 5.0f),	//Target
		AXIS_Y);					//Up
	

	//Array of the x-value of Platform Locations
	float xPlatPos[25] = {
		-6.0f,-8.0f,-10.0f,-12.0f,
		0, 2.0f, 4.0f, 6.0f, 
		12.0f, 14.0f, 16.0f, 18.0f, 20.0f,
		24.0f, 26.0f, 28.0f,
		34.0f, 36.0f, 38.0f,
		44.0f, 48.0f, 50.0f,
		58.0f, 62.0f, 64.0f
		};
	/* To add the y values to the cubes, comment out v3Position.y below
	float yPlatPos[25] = {
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,0,
		0,0,0,
		0,0,0,
		0,0,0,
		0,0,0
	};*/

	for (int i = 0; i < std::size(xPlatPos); i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));
		//This puts a cube in every so often. Need to make an array of x and y positions, stick them together and make it look like a platformer.
		vector3 v3Position = vector3(xPlatPos[i], 0,
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Steve"))->GetPosition().z -
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Cube_"))->GetRigidBody()->GetHalfWidth().z)));
		//Flattens the platform out more
		v3Position.y = 0;
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));
		m_pEntityMngr->UsePhysicsSolver();
	}
}

void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?

	//Uncomment for debugging if camera movement needed
	//CameraRotation();

	//comment this chunk if camera movement needed during debugging
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Steve"))->GetPosition().x, 4.0f, 15.0f), //Position
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Steve"))->GetPosition().x, 4.0f, 5.0f),	//Target
		AXIS_Y);					//Up

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Set the model matrix for the main object
	//m_pEntityMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	//m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}