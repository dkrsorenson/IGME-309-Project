#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	currentSteve = "BlueSteve";
	steveTempPosition = vector3(-100, -100, 0);
	steveStartingPosition = vector3(-25, 0, 0);

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
	
	// Set up the platforms
	InitPlatforms();
	oct = new MyOctant(3);
	int m_uEntityCount = m_pEntityMngr->GetEntityCount();
	for (uint i = 0; i < m_uEntityCount; i++)
	{
		m_pEntityMngr->GetEntity(i)->ClearCollisionList();
		oct->AddEntity(i);
	}
	oct->Subdivide();
	oct->PartitionEntities();
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

	if (m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetIsRespawned()) {
		if (currentSteve == "RedSteve") {
			matrix4 m4Position = glm::translate(steveTempPosition);
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetModelMatrix(m4Position);

			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetIsRespawned(false);
			currentSteve = "BlueSteve";

			m4Position = glm::translate(vector3(-20, 0, 0));
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetModelMatrix(m4Position);
		}
	}

	//If Steve falls off the map
	if (m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().y <= -10.0f)
	{
		if (currentSteve == "RedSteve") {
			matrix4 m4Position = glm::translate(steveTempPosition);
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetModelMatrix(m4Position);

			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetIsRespawned(false);
			currentSteve = "BlueSteve";

			m4Position = glm::translate(vector3(-20, 0, 0));
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetModelMatrix(m4Position);
		}
		else if (currentSteve == "BlueSteve") {
			vector3 v3Position = steveStartingPosition;
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->SetPosition(steveStartingPosition);
		}
	}
	//check collisions
	for (uint i = 0; i < 2; i++)
	{
		std::vector<int> ea = oct->GetRelevantEntities(i);
		for (uint j = 0; j < ea.size(); j++)
		{
			if (m_pEntityMngr->GetEntity(i)->IsColliding(m_pEntityMngr->GetEntity(ea[j])))
			{
				m_pEntityMngr->GetEntity(i)->ResolveCollision(m_pEntityMngr->GetEntity(ea[j]));
			}
		}
		m_pEntityMngr->GetEntity(i)->Update();
	}
	oct->Display();

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
void Application::InitPlatforms(void)
{
	//Array of the x-value of Platform Locations
	float xPlatPosRed[17] = {
		//1st block
		-14.0f,-12.0f,-10.0f,
		//2nd pixel block
		-2.0, -2.0, 8.0f,
		//4th series Pixel Blocks
		14.0f, 20.0f, 36.0f, 38.0f,
		//5th 
		48.0f,52.0f, 56.0f,
		72.0f, 74.0f,
		72.0f, 74.0f
	};

	float yPlatPosRed[17] = {
		//1st
		0,0,0,
		0,8.0f,-4.0f,
		0,0,0,0,
		0,0,0,
		6.0f,6.0f,
		0,0
	};

	float xPlatPosBlue[16] = {
		//1st block
		-10.0f,-8.0f, 
		//3rd block
		6.0f, 10.0f,
		6.0f, 10.0f,
		//4th Series Pixel Blocks
		16.0f, 24.0f, 28.0f,
		//5th
		50.0f, 54.0f, 58.0f,
		64.0f, 66.0f,
		78.0f, 80.0f
	};
	float yPlatPosBlue[16] = {
		//1st block
		2.0f,2.0f,
		//3rd Block
		-2.0f,-2.0f,
		-4.0f,-4.0f,
		//4th
		0,2.0f,4.0f,
		//5th
		0,0,0,
		-4.0f, -4.0f,
		-4.0f, -4.0f
	};

	float xPlatPosNeutral[9] = {
		-28.0f, -26.0f, -24.0f, -22.0f, -20.0f,
		8.0f,
		86.0f, 88.0f, 90.0f
	};
	float yPlatPosNeutral[9] = {
		-6.0f,-6.0f,-6.0f,-6.0f,-6.0f,
		6.0f,
		2.0f,2.0f,2.0f
	};

	//Make Red Platforms
	for (int i = 0; i < std::size(xPlatPosRed); i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\RedCube.obj", "Cube_" + std::to_string(i), eColor::RED);
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

	// Make Neutral Platforms
	for (int i = 0; i < std::size(xPlatPosNeutral); i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i), eColor::NEUTRAL);
		vector3 v3Position = vector3(xPlatPosNeutral[i], yPlatPosNeutral[i],
			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex(currentSteve))->GetPosition().z -
			(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Cube_"))->GetRigidBody()->GetHalfWidth().z));
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));
	}
}

void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}