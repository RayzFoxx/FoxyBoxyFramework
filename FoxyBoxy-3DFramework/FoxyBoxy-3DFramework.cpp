// FoxyBoxy-3DFramework.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <engine/engine.h>

float timeSwingGame;

Camera player(glm::vec3(0.0f, 0.0f, 3.0f));
Camera ypr(glm::vec3(0.0f, 0.0f, 3.0f));

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

int main()
{
    // start engine
    std::cout << "Loading framework\n";
    engineInit();

    // compile simple shaders and textures
    Shader debugShader(".\\resources\\shaderPack\\shader.vert", ".\\resources\\shaderPack\\shader.frag");
	Shader shaderPlane(".\\resources\\shaderPack\\shader.vert", ".\\resources\\shaderPack\\shader.frag");
	Shader shaderFlatColor(".\\resources\\shaderPack\\flatColorShader.vs", ".\\resources\\shaderPack\\flatColorShader.fs");

	stbi_set_flip_vertically_on_load(true);
	Texture debugCubeTexture(".\\resources\\texturePack\\blocks\\bedrock.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
	debugCubeTexture.activate(0);
	Texture textureDirt(".\\resources\\texturePack\\blocks\\dirt.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
	textureDirt.activate(1);

    // gen arrays
    unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// pos attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// col attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// tex attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// normal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);

    while (!engineCloseWindow())
    {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        engineUpdateDT();
        engineUpdateInput();

		int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
		//std::cout << "present: " << present << std::endl;
		if ((present) )//&& (glfwGetTime() > timeSwingGame + 1))
		{
			int count;
			const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

			ypr.ProcessMovementYPR(axes[0] * 180, axes[1] * 89, axes[2] * 180);

			
			/*
			std::cout << "=========" << std::endl;
			std::cout << "axis X: " << axes[0] << std::endl;
			std::cout << "axis Y: " << axes[1] << std::endl;
			std::cout << "axis Z: " << axes[2] << std::endl;
			std::cout << "axis Z: " << axes[3] << std::endl;*/

			//timeSwingGame = glfwGetTime();
		}
		else
		{

		}

		//ypr.ProcessMovementYPR(90.0, 0.0, 0.0);

		shaderPlane.use();
		debugCubeTexture.activate(0);

		glm::mat4 view = glm::mat4(1.0);
		view = ypr.GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0);
		projection = glm::perspective(glm::radians(ypr.Zoom), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

		shaderPlane.setMat4("view", view);
		//shaderPlane.setMat4("view", glm::mat4(1.0f));
		shaderPlane.setMat4("projection", projection);
		//shaderPlane.setMat4("projection", glm::mat4(1.0f));
		shaderPlane.setInt("dTexture", 0);
		//shaderPlane.setVec4("color", glm::vec4(0.0, 1.0, 1.0, 1.0));
		shaderPlane.setVec3("lightPos", glm::vec3(1.0, 1.0, 1.0));
		shaderPlane.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));

		// plane
		glBindVertexArray(VAO);
		glm::mat4 plane = glm::mat4(1.0);
		//plane = glm::translate(plane, glm::vec3(0.0));
		plane = glm::rotate(plane, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
		plane = glm::translate(plane, glm::vec3(-2.0, 0.0, 4.0));
		plane = glm::scale(plane, glm::vec3(0.5, 0.5, 0.5));
		for (int x = 0; x < 10; x++)
		{
			plane = glm::translate(plane, glm::vec3(2.0, -20.0, 0.0));
			for (int y = 0; y < 10; y++)
			{
				plane = glm::translate(plane, glm::vec3(0.0, 2.0, 0.0));
				shaderPlane.setMat4("model", plane);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			}
		}
		

		// cubes
		shaderFlatColor.use();
		shaderFlatColor.setMat4("view", view);
		shaderFlatColor.setMat4("projection", projection);
		//debugShader.setInt("dTexture", 1);

		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0);
			model = glm::translate(model, (glm::vec3)(cPos[i]));
			float angle = 20.0f * i;
			model = glm::scale(model, glm::vec3(0.5));
			model = glm::rotate(model, angle + (float)(glfwGetTime()),	glm::vec3(
				(sin(glm::radians((120.0f + glfwGetTime() + (60.0f * i)) * 20.0f))),
				(sin(glm::radians((240.0f + glfwGetTime() + (60.0f * i)) * 20.0f))),
				(sin(glm::radians((  0.0f + glfwGetTime() + (60.0f * i)) * 20.0f)))
			));

			shaderFlatColor.setVec4("color", 
				glm::vec4(
					glm::abs(sin(glm::radians((120.0f + glfwGetTime() + (60.0f * i)) * 20.0f))),
					glm::abs(sin(glm::radians((240.0f + glfwGetTime() + (60.0f * i)) * 20.0f))),
					glm::abs(sin(glm::radians((  0.0f + glfwGetTime() + (60.0f * i)) * 20.0f))),
					1.0f
				)
			);
			shaderFlatColor.setMat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

        engineSwapBuffers();
    }

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
    
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ypr.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ypr.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ypr.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		ypr.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double offsetX = xpos - lastX;
	double offsetY = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	player.ProcessMouseMovement(offsetX, offsetY);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//mouseScrollOffsetY = yoffset;
	ypr.ProcessMouseScroll(yoffset);
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
