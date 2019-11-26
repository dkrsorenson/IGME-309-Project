#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	steve = new Model();
	steve->Load("Minecraft\\Steve.obj");
	player = new MyEntity(vector3(1, 1, 1), "Player");
	player->SetModel(steve);
	player->SetPosition(vector3(0, 10, 0));

	platform_physics = new PlayerSolver(player);

	level1 = new MyEntityGroup();
	

	for (int i = -4; i < 5; i++)
	{
		if (i == 0)
			continue;

		MyEntity* current_block = new MyEntity(vector3(1, 1, 1));
		cube = new Model();
		cube->Load("Minecraft\\Cube.obj");
		current_block->SetModel(cube);

		vector3 v3Position = vector3(glm::sphericalRand(12.0f));
		v3Position.y = 0.0f;

		// removing Z dimension
		v3Position.z = 0.0f;

		matrix4 m4Position = glm::translate(v3Position);
		current_block->SetPosition(v3Position);
		current_block->SetPosition(vector3(i, 0, 0));
		current_block->SetModelMatrix(m4Position);

		level1->AddEntity(current_block);
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
		vector3(player->GetPosition().x, 4.0f, 15.0f), //Position
		vector3(player->GetPosition().x, 4.0f, 5.0f),	//Target
		AXIS_Y);					//Up

	platform_physics->Update();

	if (level1->IsColliding(player)) {
		platform_physics->ResolveCollision(level1);
	}

	player->Update();
	level1->Update();

	player->AddToRenderList(true);
	level1->AddToRenderList(true);
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
	//release GUI
	ShutdownGUI();
}
