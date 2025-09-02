#include "entity/Entity2D.h"
#include "renderer/Renderer.h"
#include "window/Window.h"

#include "BaseGame.h"

#include <fstream>
#include <sstream>
#include <string>


int main(void)
{
	Entity2D entity2D = Entity2D();

	Renderer renderer;

	Window window = Window(640, 480, "Engine");

	if (!glfwInit())
		return -1;

	window.CreateWindow();

	renderer.MakeContextCurrent(window);

	glewInit();

	entity2D.Draw();

	// va en renderer
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, entity2D.GetVerticesSize(),
	//	entity2D.GetVertices(), GL_STREAM_DRAW);
	/*glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);*/


	entity2D.GetMaterial().SetFilepath("src/material/Basic.shader");
	entity2D.SetMaterial("src/material/Basic.shader");
	std::cout << "Vertex" << std::endl;
	std::cout << entity2D.GetMaterial().GetVertexSource() << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << entity2D.GetMaterial().GetFragmentSource() << std::endl;

	// va en material
	unsigned int shader = entity2D.GetMaterial().CreateShader(entity2D.GetMaterial().GetVertexSource(), entity2D.GetMaterial().GetFragmentSource());
	glUseProgram(shader);

	while (!window.ShouldClose())
	{
		renderer.Clear();

		// va en renderer
		glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.SwapBuffers(window);

		// va en renderer
		renderer.PollEvents();
	}

	// va en material
	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}