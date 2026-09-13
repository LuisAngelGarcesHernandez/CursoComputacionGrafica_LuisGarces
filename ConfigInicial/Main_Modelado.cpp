//Practica #4
//Garcés Hernández Luis Angel
//Fecha de Entrega: 13/09/2026
//NCuenta: 31919948-8

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Practica#4 Garces Hernandez Luis Angel", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.15f, 0.65f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);

		//ColorCuerpo
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//CuerpoPrincipal
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 2.0f, 4.5f)); //ancho | Grosor | Profundidad
		////                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//ColorPata1
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		//Pata1
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(1.8f, -1.5f, 4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorPata2
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		//Pata2
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-1.8f, -1.5f, 4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Colorpata3
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		//Pata3
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-1.8f, -1.5f, -4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Colorpata4
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		//Pata4
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(1.8f, -1.5f, -4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
// 
//		//////////////////////////////////////////////////////////////
// 
		//ColorPata1UÑA
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.5f, 0.55f); //Rosita Salmon
		//Pata1UÑA
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.55f, 0.3f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(1.8f, -7.0f, 4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorPata2UÑA
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.5f, 0.55f); //Rosita Salmon
		//Pata2UÑA
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.55f, 0.3f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-1.8f, -7.0f, 4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorPata3UÑA
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.5f, 0.55f); //Rosita Salmon
		//Pata3UÑA
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.55f, 0.3f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-1.8f, -7.0f, -4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorPata4UÑA
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.5f, 0.55f); //Rosita Salmon
		//Pata4UÑA
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.55f, 0.3f, 0.5f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(1.8f, -7.0f, -4.0f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
// 
////////////////////////////////////////////////////////////
 
		//ColorCuello
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		//Cuello
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(2.5f, 1.9f, 1.1f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 1.02f, 1.55f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

//		///////////////////////////////////////////////////////
 
		//ColorCabeza
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Gris
		//Cabeza
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(2.5f, 1.8f, 2.0f)); //Tamaño de la pata
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 1.11f, 1.61f));//Posicionde la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
// 
//		///////////////////////////////////////////////////////////////
// 
		//ColorColaBase
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //RosaFuerte
		//ColaBase
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.3f)); //Posicionde la colabase
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
		//ColorColaBase
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.7f, 0.0f, 0.9f); //RosaFuerte
		//ColaBase
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -4.2f)); //Posicionde la colabase
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorColaBase
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //RosaFuerte
		//ColaBase
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -4.2f)); //Posicionde la colabase
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// 		/////////////////////////////////////////////////////////////////////
// 
		//ColorOjoDerecho
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.0f, 0.2f, 0.8f); //AzulOscuro
		//OjoDerecho
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(4.26f, 5.0f, 8.2f)); //Posicionde el ojo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorBrilloOjoDerecho
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.0f, 1.0f, 1.0f); //Cian
		//BrilloOjoDerecho
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.2f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(8.5f, 9.5f, 15.0f)); //Posicionde el brillo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
		//ColorOjoIzquierdo
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.0f, 0.2f, 0.8f); //AzulOscuro
		//OjoIzquierdo
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-4.26f, 5.0f, 8.2f)); //Posicionde el ojo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorBrilloOjoIzquierdo
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.0f, 1.0f, 1.0f); //Cian
		//BrilloOjoIzquierdo
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.2f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-8.5f, 9.5f, 15.0f)); //Posicionde el brillo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
// 
// 		   /////////////////////////////////////////////////////////
//
		//ColorOrejaDerecha
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Blanco
		//OrejaDerecha
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.0f, 5.0f, 7.0f)); //Posicionde la oreja
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorOrejaIzquierda
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Blanco
		//OrejaIzquierda
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.0f, 5.0f, 7.0f)); //Posicionde la oreja
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// 		   ///////////////////////////////////////////////////////////
// 
		//ColorCuernoBase
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.2f, 0.8f); //RosaFuerte
		//CuernoBase
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.4f, 0.6f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 7.75f, 6.3f)); //Posicionde la base
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
		//ColorCuernoMedio
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//CuernoMedio
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 8.75f, 9.5f)); //Posicion del medio
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorCuernoPunta
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 0.9f, 0.95f); //RosaPalido
		//CuernoPunta
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 9.75f, 19.0f)); //Posicionde la punta
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
// 
// 		   //////////////////////////////////////////////////////////////
//
		//ColorCabelloArriba
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.2f, 0.8f); //RosaFuerte
		//CabelloArriba
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 5.16f, 4.5f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
		//ColorCabelloMedio
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//CabelloMedio
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 5.5f, 3.5f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
		//ColorCabelloMedioAtras
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.2f, 0.8f); //RosaFuerte
		//CabelloArriba
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 5.16f, 2.5f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
		//ColorCabelloMedioAtrasAbajo
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//CabelloMedio
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 1.5f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorCabelloAbajoPrimero
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.2f, 0.8f); //RosaFuerte
		//CabelloArriba
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.9f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, 1.0f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
		//ColorCabelloAbajoMedio
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//CabelloArriba
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 1.2f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.7f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorCabelloAbajoAbajo
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.2f, 0.8f); //RosaFuerte
		//CabelloArriba
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 1.3f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.5f)); //Posicionde cabello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
 
// 		   ////////////////////////////////////////////////
//
		//ColorAlaDerechaBase
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.4f, 0.9f, 1.0f); //AzulClaro
		//AlaDerechaBase
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 2.0f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(3.0f, 4.9f, -0.4f)); //Posicionde ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorAlaDerechaPunta
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.4f, 0.9f, 1.0f); //AzulClaro
		//AlaDerechaPunta
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 1.2f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(3.0f, 1.3f, 1.0f)); //Posicionde ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// 
		//ColorAlaIzquierdaBase
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.4f, 0.9f, 1.0f); //AzulClaro
		//AlaIzquierdaBase
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 2.0f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-3.0f, 4.9f, -0.4f)); //Posicionde ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorAlaIzquierdaPunta
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.4f, 0.9f, 1.0f); //AzulClaro
		//AlaIzquierdaPunta
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 1.2f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-3.0f, 1.3f, 1.0f)); //Posicionde ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// /////////////////////////////////////////////////////////////////77
// 
		//ColorAlaDerechaInterior
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Blanco
		//AlaDerechaInterior
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.25f, 0.8f, 1.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(3.6f, 1.7f, -0.3f)); //Posicion del interior del ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorAlaDerechaInteriorArriba
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.8f, 0.8f, 0.8f); //Blanco
		//AlaDerechaInterior
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(3.2f, 3.0f, -2.5f)); //Posicion del interior del ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorAlaIzquierdaInterior
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f); //Blanco
		//AlaDerechaInterior
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.25f, 0.8f, 1.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-3.6f, 1.7f, -0.3f)); //Posicion del interior del ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorAlaIzquierdaInteriorArriba
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.8f, 0.8f, 0.8f); //Blanco
		//AlaDerechaInterior
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.5f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-3.2f, 3.0f, -2.5f)); //Posicion del interior del ala
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// //////////////////////////////////////////////////////////////
// 
		//ColorNarizDerecha
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.1f, 0.1f); //Rojo
		//NarizDerecha
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.8f, 0.3f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.3f, 2.5f, 13.8f)); //Posicion de la nariz
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorNarizDerechaizquierda
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.84f, 0.48f, 0.51f); //Rojo
		//NarizDerecha
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.8f, 0.3f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(1.4f, 2.5f, 13.75f)); //Posicion de la nariz
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//ColorNarizDerecha
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.84f, 0.48f, 0.51f); //Rojo
		//NarizDerecha
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.8f, 0.3f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.3f, 2.5f, 13.8f)); //Posicion de la nariz
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorNarizDerechaizquierda
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.9f, 0.1f, 0.1f); //Rojo
		//NarizDerecha
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.3f, 0.8f, 0.3f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-1.4f, 2.5f, 13.75f)); //Posicion de la nariz
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// //////////////////////////////////////////////////////////7
// 
		//ColorMarcaDerechaAbajo1
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaDerechaAbajo1
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.7f, -1.1f, -2.5f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaDerechaAbajo2
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaDerechaAbajo2
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.7f, -1.1f, 0.0f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaDerechaAbajo3
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaDerechaAbajo3
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.7f, -1.1f, 2.5f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaDerechaArriba1
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaDerechaArriba1
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.7f, 0.7f, 1.6f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaDerechaArriba2
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaDerechaArriba2
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(2.7f, 0.7f, -0.95f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaIZQUIERDAAbajo1
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaIZQUIERDAAbajo1
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.7f, -1.1f, -2.5f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaIZQUIERDAAbajo2
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaIZQUIERDAAbajo2
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.7f, -1.1f, 0.0f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaIZQUIERDAAbajo3
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaIZQUIERDAAbajo3
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.7f, -1.1f, 2.5f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaIZQUIERDAArriba1
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaIZQUIERDAArriba1
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.7f, 0.7f, 1.6f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ColorMarcaIZQUIERDAArriba2
		colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
		glUniform3f(colorLoc, 0.75f, 0.45f, 0.9f); //MoradoClaro
		//MarcaIZQUIERDAArriba2
		model = glm::mat4(1.0f);
		//                                ancho | Grosor | Profundidad
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//                                       x      y     z
		model = glm::translate(model, glm::vec3(-2.7f, 0.7f, -0.95f)); //Posicion de la marca
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.1f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.1f;
 }


