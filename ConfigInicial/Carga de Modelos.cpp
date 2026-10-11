//Practica #8
//Garcés Hernández Luis Angel
// Fecha de Entrega: 11/10/2026
//NCuenta: 31919948-8

// Std. Includes
#include <string>

#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

glm::vec3 lightPos(0.0f);      // Sol
glm::vec3 lightPos2(0.0f);    // Luna
//Rotacion
const glm::vec3 centroOrbita(0.4f, 1.0f, -20.0f);
//Distancia pal centro
const float radioOrbita = 9.0f;
//Sol arriba
float anguloOrbita = glm::radians(90.0f);
//Velocidad pa girar
const float velocidadOrbita = glm::radians(70.0f);

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica#8 GarcesHernandezLuisAngel Materiales e Iluminacion", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    // Load models
    Model dog((char*)"Models/RedDog.obj");
   /* Model springbonnie((char*)"Models/86jfmjiufzv2.obj");*/

    Model banca((char*)"Models/bench+27.obj");

    Model arbol((char*)"Models/tree_mango_var01.obj");

    Model arbol2((char*)"Models/tree_mango_var02.obj");

    Model mesa((char*)"Models/picnictable.obj");

    Model piso((char*)"Models/hair+grass.obj");

    Model sol((char*)"Models/Sun.obj");

    Model luna((char*)"Models/Moon.obj");

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        //Sol y Luna Rotacion
        if (keys[GLFW_KEY_R])
        {
            anguloOrbita += velocidadOrbita * deltaTime;

            if (anguloOrbita >= 6.28318530718f)
            {
                anguloOrbita -= 6.28318530718f;
            }
        }

        float coseno = std::cos(anguloOrbita);
        float seno = std::sin(anguloOrbita);

        glm::vec3 desplazamiento(radioOrbita * coseno,radioOrbita * seno,0.0f);

        lightPos = centroOrbita + desplazamiento;
        lightPos2 = centroOrbita - desplazamiento;
      
        bool solActivo = (seno >= 0.0f);

        float intensidadSol = solActivo ? 1.0f : 0.0f;
        float intensidadLuna = solActivo ? 0.0f : 1.0f;

        // Clear the colorbuffer
        if (solActivo)
        {
            // Dia: cielo azul
            glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
        }
        else
        {
            // Noche: cielo oscuro
            glClearColor(0.025f, 0.035f, 0.10f, 1.0f);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //shader.Use();

        //Iluminacion:
        lightingShader.Use();

        //// Posición de las dos luces
        GLint lightPosLoc =glGetUniformLocation(lightingShader.Program,"light.position");

        GLint lightPosLoc2 =glGetUniformLocation(lightingShader.Program,"light2.position");

        GLint viewPosLoc =glGetUniformLocation(lightingShader.Program,"viewPos");

        // SOL
        glUniform3f(lightPosLoc,lightPos.x,lightPos.y,lightPos.z);

        // LUNA
        glUniform3f(lightPosLoc2,lightPos2.x,lightPos2.y,lightPos2.z);

        // Posicion Camara
        glUniform3f(viewPosLoc,camera.GetPosition().x,camera.GetPosition().y,camera.GetPosition().z);


        //Luces
        // SOL
        // Luz ambiental Sol
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"),0.35f * intensidadSol,0.30f * intensidadSol,0.20f * intensidadSol);

        // Luz difusa Sol
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"),1.0f * intensidadSol,0.85f * intensidadSol,0.55f * intensidadSol);

        // Luz especular Sol
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"),1.0f * intensidadSol,0.9f * intensidadSol,0.7f * intensidadSol);

        //LUNA
        // Luz ambiental Luna
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"),0.08f * intensidadLuna,0.08f * intensidadLuna,0.15f * intensidadLuna);

        // Luz difusa Luna
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"),0.25f * intensidadLuna,0.30f * intensidadLuna,0.55f * intensidadLuna);

        // Luz especular Luna
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"),0.40f * intensidadLuna,0.45f * intensidadLuna,0.70f * intensidadLuna);

        //// Material

        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"),0.5f, 0.5f, 0.5f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"),0.7f, 0.7f, 0.7f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"),0.6f, 0.6f, 0.6f);

        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"),16.0f);

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"),1,GL_FALSE,glm::value_ptr(projection));

        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"),1,GL_FALSE,glm::value_ptr(view));

        // Draw the loaded model (Dog)
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.4f, 0.7f, -0.7f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(lightingShader);

        // Banca
        glm::mat4 modelBanca(1.0f);
        modelBanca = glm::translate(modelBanca, glm::vec3(-2.5f, 0.0f, -2.0f));
        modelBanca = glm::scale(modelBanca, glm::vec3(3.2f, 3.2f, 3.2f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelBanca));
        banca.Draw(lightingShader);

        //Arbol1
        glm::mat4 modelArbol(1.0f);
        modelArbol = glm::translate(modelArbol, glm::vec3(-13.0f, -0.0f, -10.0f));
        modelArbol = glm::scale(modelArbol, glm::vec3(0.09f, 0.09f, 0.09f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelArbol));
        arbol.Draw(lightingShader);

        //Arbol2
        glm::mat4 modelArbol2(1.0f);
        modelArbol2 = glm::translate(modelArbol2, glm::vec3(9.0f, -0.1f, -5.0f));
        modelArbol2 = glm::scale(modelArbol2, glm::vec3(0.09f, 0.09f, 0.09f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelArbol2));
        arbol2.Draw(lightingShader);
        //
        //Mesa
        glm::mat4 modelMesa(1.0f);
        modelMesa = glm::translate(modelMesa, glm::vec3(4.0f, 0.1f, 5.0f));
        modelMesa = glm::scale(modelMesa, glm::vec3(0.035f, 0.035f, 0.035f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMesa));
        mesa.Draw(lightingShader);

        //Cesped
        glm::mat4 modelPiso(1.0f);
        modelPiso = glm::translate(modelPiso, glm::vec3(0.0f, -0.8f, -5.0f));
        modelPiso = glm::scale(modelPiso, glm::vec3(30.0f, 4.0f, 30.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPiso));
        piso.Draw(lightingShader);


        shader.Use();

        // Proyeccion
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"),1,GL_FALSE,glm::value_ptr(projection));

        // Vista
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"),1,GL_FALSE,glm::value_ptr(view));
        // SOL
        glm::mat4 modelSol(1.0f);
        // Su modelo sigue la posicion de su luz
        modelSol = glm::translate(modelSol, lightPos);
        // Tamaño del Sol
        modelSol = glm::scale(modelSol, glm::vec3(2.5f));
        // Centrar la geometria del OBJ
        modelSol = glm::translate(modelSol,glm::vec3(0.0f, -1.0923145f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"),1,GL_FALSE,glm::value_ptr(modelSol));
        sol.Draw(lightingShader);


        //LUNA
        glm::mat4 modelLuna(1.0f);
        // Modelo sigue posicion de la luz
        modelLuna = glm::translate(modelLuna, lightPos2);
        // Tamaño de la Luna
        modelLuna = glm::scale(modelLuna, glm::vec3(2.5f));
        // Centrar la geometria OBJ
        modelLuna = glm::translate(modelLuna,glm::vec3(0.0f, -1.0923145f, -6.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"),1,GL_FALSE,glm::value_ptr(modelLuna));
        luna.Draw(lightingShader);

        //// Draw the loaded model (Springbonnie)
//glm::mat4 modelBonnie(1.0f);

//// Lo movemos a la izquierda (-3.0f) y MUCHO más al fondo (-15.0f) para que no te trague
//modelBonnie = glm::translate(modelBonnie, glm::vec3(-3.0f, 0.0f, -15.0f));

//// Lo hacemos todavía más miniatura
//modelBonnie = glm::scale(modelBonnie, glm::vec3(0.001f, 0.001f, 0.001f));

//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelBonnie));
//springbonnie.Draw(shader);

        glfwSwapBuffers(window);
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

