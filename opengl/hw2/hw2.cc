// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/fps.hpp>

#include <rlib/stdio.hpp>
#include "imported.hpp"

#include <thread>

int main()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 08 - Basic Shading", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	R_GL_ERROR_CHECKPOINT;

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glGetError();

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS); 
	glDepthFunc(GL_LEQUAL);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	R_GL_ERROR_CHECKPOINT;

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
	R_GL_ERROR_CHECKPOINT;

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// import begin
	R_GL_ERROR_CHECKPOINT;
	generateIDs();
	R_GL_ERROR_CHECKPOINT;
	initVAO();
	R_GL_ERROR_CHECKPOINT;
	float distScale = 35.0 / 149597870.7; // AU in km
	float radScale = 1.0 / 6378.1; // E in km
	// world space
	vec3 sunCenter = vec3(0.0);
	vec3 earthCenter = vec3(0.0);
	vec3 moonCenter = vec3(0.0);

	// make sun
	std::vector<vec3> sunVertices;
	std::vector<vec3> sunNormals;
	std::vector<vec2> sunUvs;
	std::vector<unsigned int> sunIndices;
	sunCenter = vec3(0.0);
	float sunRadius = pow(radScale * 696000.0, 0.5);
	R_GL_ERROR_CHECKPOINT;
	generateSphere(sunVertices, sunNormals, sunUvs, sunIndices, sunCenter, sunRadius, 96);
	R_GL_ERROR_CHECKPOINT;
	GLuint sun = createTexture("sun.jpg");
	R_GL_ERROR_CHECKPOINT;

	// make earth
	std::vector<vec3> earthVertices;
	std::vector<vec3> earthNormals;
	std::vector<vec2> earthUvs;
	std::vector<unsigned int> earthIndices;
	earthCenter = vec3(distScale * 149597890, 0.0, 0.0);
	float earthRadius = pow(radScale * 6378.1, 0.5);
	generateSphere(earthVertices, earthNormals, earthUvs, earthIndices, earthCenter, earthRadius, 72);
	GLuint earth = createTexture("earth.jpg");

	rlib::println("Sun.R = ", sunRadius, "earth.R=", earthRadius);

	// make moon
	std::vector<vec3> moonVertices;
	std::vector<vec3> moonNormals;
	std::vector<vec2> moonUvs;
	std::vector<unsigned int> moonIndices;
	moonCenter = earthCenter - vec3((20 * distScale * 384399.0), 0.0, 0.0);
	float moonRadius = pow(radScale * 1737.1 / 2, 0.5);
	generateSphere(moonVertices, moonNormals, moonUvs, moonIndices, moonCenter, moonRadius, 48);
	GLuint moon = createTexture("moonyy.jpg");
	
	// make space
	std::vector<vec3> spaceVertices;
	std::vector<vec3> spaceNormals;
	std::vector<vec2> spaceUvs;
	std::vector<unsigned int> spaceIndices;
	vec3 spaceCenter = vec3(0.0);
	generateSphere(spaceVertices, spaceNormals, spaceUvs, spaceIndices, spaceCenter, 400.0, 128);
	GLuint space = createTexture("space1.png");
	R_GL_ERROR_CHECKPOINT;

	auto debugMsg = [&](){
		rlib::println("DEBUGLINE: SunNode_model=", glm::to_string(sunVertices[0]), ", Earth=", glm::to_string(earthVertices[0]));
	};
	
	float scale; 
	float sunRot;
	float earthOrb;
	float earthRot;
	float moonOrb; 
	float moonRot;
	float spaceRot;
	GLuint diffUniformLocation;
	// import end

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	glfwSetKeyCallback(window, key_callback);

    init_fps();
	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glm::vec3 lightPos = glm::vec3(0,0,0);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);



		scale = universeTimeSpeed * M_PI;
		sunRot = scale / 25.38;
		earthOrb = scale / 365;
		earthRot = -scale;
		moonOrb = scale / 27.32;
		moonRot = scale / 27.32;
		spaceRot = scale / 5000;

        // call function to draw our scene
        rotatePlanet(sunVertices, sunNormals, sunCenter, vec3(0.0, 0.0, 1.0), sunRot);
        orbitPlanet(earthVertices, earthNormals, earthCenter, sunCenter, vec3(0.0, 0.0, 1.0), earthOrb);
        rotatePlanet(earthVertices, earthNormals, earthCenter, vec3(0.0, 0.0, 1.0), earthRot);
        orbitPlanet(moonVertices, moonNormals, moonCenter, earthCenter, vec3(0.0, 0.0, 1.0), moonOrb);
        rotatePlanet(moonVertices, moonNormals, moonCenter, vec3(0.0, 0.0, 1.0), moonRot);
        rotatePlanet(spaceVertices, spaceNormals, spaceCenter, vec3(0.0, 0.0, 1.0), spaceRot);
	R_GL_ERROR_CHECKPOINT;

        loadBuffer(sunVertices, sunNormals, sunUvs, sunIndices);
        loadTexture(sun, GL_TEXTURE0, programID, "myTextureSampler");
        diffUniformLocation = glGetUniformLocation(programID, "diffuse");
        glUniform1i(diffUniformLocation, false); // change this to sunDiffuse or something in your free time because this is sloppy
        render(MVP, ViewMatrix, ModelMatrix, 0, sunIndices.size());
	R_GL_ERROR_CHECKPOINT;
        

        loadBuffer(earthVertices, earthNormals, earthUvs, earthIndices);
        loadTexture(earth, GL_TEXTURE0, programID, "myTextureSampler");
        diffUniformLocation = glGetUniformLocation(programID, "diffuse");
        glUniform1i(diffUniformLocation, true);
        render(MVP, ViewMatrix, ModelMatrix, 0, earthIndices.size());
	R_GL_ERROR_CHECKPOINT;
        
        
        loadBuffer(moonVertices, moonNormals, moonUvs, moonIndices);
        loadTexture(moon, GL_TEXTURE0, programID, "myTextureSampler");
        diffUniformLocation = glGetUniformLocation(programID, "diffuse");
        glUniform1i(diffUniformLocation, true);
        render(MVP, ViewMatrix, ModelMatrix, 0, moonIndices.size());
        

		loadBuffer(spaceVertices, spaceNormals, spaceUvs, spaceIndices);
        loadTexture(space, GL_TEXTURE0, programID, "myTextureSampler");
        diffUniformLocation = glGetUniformLocation(programID, "diffuse");
        glUniform1i(diffUniformLocation, false);
        render(MVP, ViewMatrix, ModelMatrix, 0, spaceIndices.size());

        ++fps_counter;

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);


/*
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
	*/
	deleteIDs();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

