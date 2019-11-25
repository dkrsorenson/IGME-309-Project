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

	for (int i = -4; i < 5; i++)
	{
		if (i == 0)
			continue;
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));
		vector3 v3Position = vector3(i*5, 0, 
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Steve"))->GetPosition().z - 
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Cube_"))->GetRigidBody()->GetHalfWidth().z)));
		v3Position.y = 0.0f;
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));
		m_pEntityMngr->UsePhysicsSolver();
		//m_pEntityMngr->SetMass(2);

		//m_pEntityMngr->SetMass(i+1);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	//CameraRotation();
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