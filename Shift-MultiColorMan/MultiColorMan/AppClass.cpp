#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	currentSteve = "BlueSteve";
	steveTempPosition = vector3(-100, -100, 0);
	steveStartingPosition = vector3(-20, 0, 0);

	// Add blue steve
	m_pEntityMngr->AddEntity("Minecraft\\BlueSteve.obj", "BlueSteve", eColor::BLUE);
	vector3 v3Position = steveStartingPosition;
	matrix4 m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	// Add red steve
	m_pEntityMngr->AddEntity("Minecraft\\RedSteve.obj", "RedSteve", eColor::RED);
	v3Position = steveTempPosition;
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().x, 2.0f, 15.0f), //Position
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().x, 2.0f, 5.0f),	//Target
		AXIS_Y);					//Up
	

	//Array of the x-value of Platform Locations
	float xPlatPosRed[25] = {
		//1st block
		-14.0f,-10.0f,-12.0f,
		//2nd pixel block
		0,
		//4th series Pixel Blocks
		14.0f, 20.0f, 36.0f, 38.0f,
		//5th 
		48.0f,52.0f, 56.0f
		};

	float yPlatPosRed[25] = {
		//1st
		0,0,0,
		//2nd
		2.0f,
		//4th
		0,2.0f,-2.0f, -2.0f,
		//5th
		0,0,0,0,
		0,0,0,
		0,0,0,
		0,0,0,
		0,0,0
	};

	float xPlatPosBlue[25] = {
		//1st block
		-10.0f, -12.0f, 
		//3rd block
		6.0f, 8.0f, 10.0f,
		6.0f, 8.0f, 10.0f,
		//4th Series Pixel Blocks
		16.0f, 24.0f, 28.0f,
		//5th
		50.0f, 54.0f, 58.0f,
		//6th
		64.0f, 66.0f, 68.0f
	};
	float yPlatPosBlue[25] = {
		//1st block
		2.0f,2.0f,
		//3rd Block
		-2.0f,-2.0f,-2.0f,
		-4.0f,-4.0f,-4.0f,
		//4th
		0,2.0f,4.0f,
		//5th
		0,0,0,
		//6th
		2.0f,2.0f, 2.0f,
		0,0,
		0,0,0
	};

	//Make Red Platforms
	for (int i = 0; i < std::size(xPlatPosRed); i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\RedCube.obj", "Cube_" + std::to_string(i), eColor::RED);
		//This puts a cube in every so often. Need to make an array of x and y positions, stick them together and make it look like a platformer.
		vector3 v3Position = vector3(xPlatPosRed[i], yPlatPosRed[i],
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().z -
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Cube_"))->GetRigidBody()->GetHalfWidth().z));
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));
	}
	//Make Blue Platforms
	for (int i = 0; i < std::size(xPlatPosBlue); i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\BlueCube.obj", "Cube_" + std::to_string(i), eColor::BLUE);
		vector3 v3Position = vector3(xPlatPosBlue[i], yPlatPosBlue[i],
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().z -
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Cube_"))->GetRigidBody()->GetHalfWidth().z));
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));
	}

	//Beginning Platform
	static float nextXPos = -28.0f;
	for (int i = 0; i < 5; i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\BlueCube.obj", "Cube_" + std::to_string(i), eColor::BLUE);
		vector3 v3Position = vector3(nextXPos, -6.0f, 
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().z -
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Cube_"))->GetRigidBody()->GetHalfWidth().z));
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));

		nextXPos += 2.0f;
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

	//If Steve falls off the map
	if (m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().y <= -10.0f)
	{
		vector3 v3Position = steveStartingPosition;
		m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetPosition(steveStartingPosition);
		currentSteve = "BlueSteve";
		//matrix4 m4Position = glm::translate(v3Position);
		//m_pEntityMngr->SetModelMatrix(m4Position);
	}


	//comment this chunk if camera movement needed during debugging
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().x, 2.0f, 15.0f), //Position
		vector3(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().x, 2.0f, 5.0f),	//Target
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