// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//Declarar una ventana
GLFWwindow* window;

float posXTriangulo = 0.0f, posYTriangulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.7;
double angulo = 0.0f;

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Establecer la funcion par responder a los eventos del teclado
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_RIGHT)
	{
		posXTriangulo += 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_LEFT)
	{
		posXTriangulo -= 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_UP)
	{
		posYTriangulo += 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_DOWN)
	{
		posYTriangulo -= 0.01;
	}	
}

void actualizar()
{

	double velocidadRotacion = 80.0f;

	if (angulo >= 360.0f)
	{
		angulo += 360.0f;
	}	

	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS)
	{
		angulo -= velocidadRotacion * tiempoDiferencial;			
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS)
	{
		angulo += velocidadRotacion * tiempoDiferencial;				
	}

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS)
	{	//El 90 es la fase ej: tienes 50°, pero comportate como si tuvieras 40° mas
		posXTriangulo += velocidadTriangulo * tiempoDiferencial * cos((angulo + 90.0) * 3.141592 / 180);
		posYTriangulo += velocidadTriangulo * tiempoDiferencial * sin((angulo + 90.0) * 3.141592 / 180);

	}

	/*int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS)
	{
		posYTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}*/

	tiempoAnterior = tiempoActual;
	
}
 
void dibujar()
{
	glPushMatrix();
	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.4f, 0.7f, 0.7f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);

	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{  
	//Si no se pudo iniciar GLFW terminamos ejecucion
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW, inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);
	//Si no se pudo crear la ventana, terminamos la ejecucion
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);

	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado, se llama a la función teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(0.0, 0.0, 0.0, 1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Actualizar valores y dibujar
		actualizar();
		dibujar();
			

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo, eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}


