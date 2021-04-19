#ifndef RLIB_GL_IMPORTED_HPP_
#define RLIB_GL_IMPORTED_HPP_ 1

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <common/stb/stb_image.h>
#include <rlib/macro.hpp>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;

//vec2 and vec3 are part of the glm math library. 
//Include in your own project by putting the glm directory in your project, 
//and including glm/glm.hpp as I have at the top of the file.
//"using namespace glm;" will allow you to avoid writing everyting as glm::vec2
std::vector<vec3> points;
std::vector<vec2> uvs;

namespace VAO {
	enum {GEOMETRY=0, COUNT};		//Enumeration assigns each name a value going up
	//LINES=0, COUNT=1
}

namespace VBO {
	enum {POINTS=0, NORMALS, UVS, INDICES, COUNT};	//POINTS=0, COLOR=1, COUNT=2
};

GLuint vbo [VBO::COUNT];		//Array which stores OpenGL's vertex buffer object handles
GLuint vao [VAO::COUNT];		//Array which stores Vertex Array Object handles
GLuint programID;

#ifdef DEBUG
#define R_GL_ERROR_CHECKPOINT CheckGLErrors("GL Error at " __FILE__ ":" RLIB_MACRO_TO_CSTR(__LINE__))
#else
#define R_GL_ERROR_CHECKPOINT 
#endif
bool CheckGLErrors(string location)
{
    bool error = false;
    for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
    {
        cout << "OpenGL ERROR:  ";
        switch (flag) {
        case GL_INVALID_ENUM:
            cout << location << ": " << "GL_INVALID_ENUM" << endl; break;
        case GL_INVALID_VALUE:
            cout << location << ": " << "GL_INVALID_VALUE" << endl; break;
        case GL_INVALID_OPERATION:
            cout << location << ": " << "GL_INVALID_OPERATION" << endl; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << location << ": " << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
        case GL_OUT_OF_MEMORY:
            cout << location << ": " << "GL_OUT_OF_MEMORY" << endl; break;
        default:
            cout << "[unknown error code]" << endl;
        }
        error = true;
    }
    if(error)
        throw std::runtime_error("CheckGLErrors failed. See log.");
	return true;
}


//Describe the setup of the Vertex Array Object
void initVAO()
{
	glBindVertexArray(vao[VAO::GEOMETRY]);		//Set the active Vertex Array
	R_GL_ERROR_CHECKPOINT;

	glEnableVertexAttribArray(0);		//Tell opengl you're using layout attribute 0 (For shader input)
	R_GL_ERROR_CHECKPOINT;
	glBindBuffer( GL_ARRAY_BUFFER, vbo[VBO::POINTS] );		//Set the active Vertex Buffer
	R_GL_ERROR_CHECKPOINT;
	glVertexAttribPointer(
		0,				//Attribute
		3,				//Size # Components
		GL_FLOAT,	//Type
		GL_FALSE, 	//Normalized?
		sizeof(vec3),	//Stride
		(void*)0			//Offset
		);
	R_GL_ERROR_CHECKPOINT;

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO::NORMALS]);
	glVertexAttribPointer(
		1,				//Attribute
		3,				//Size # Components
		GL_FLOAT,	//Type
		GL_FALSE, 	//Normalized?
		sizeof(vec3),	//Stride
		(void*)0			//Offset
		);
	
	glEnableVertexAttribArray(2);		//Tell opengl you're using layout attribute 1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO::UVS]);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vec2),
		(void*)0
		);	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[VBO::INDICES]);
	R_GL_ERROR_CHECKPOINT;
}
//Gets handles from OpenGL
void generateIDs()
{
	glGenVertexArrays(VAO::COUNT, vao);		//Tells OpenGL to create VAO::COUNT many
														// Vertex Array Objects, and store their
														// handles in vao array
	glGenBuffers(VBO::COUNT, vbo);		//Tells OpenGL to create VBO::COUNT many
													//Vertex Buffer Objects and store their
													//handles in vbo array
}
//Clean up IDs when you're done using them
void deleteIDs()
{
	glDeleteProgram(programID);
	
	glDeleteVertexArrays(VAO::COUNT, vao);
	glDeleteBuffers(VBO::COUNT, vbo);	
}



//Loads buffers with data
void loadBuffer(const vector<vec3>& points, const vector<vec3> normals, 
				const vector<vec2>& uvs, const vector<unsigned int>& indices)
{
	R_GL_ERROR_CHECKPOINT;
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO::POINTS]);
	R_GL_ERROR_CHECKPOINT;
	glBufferData(
		GL_ARRAY_BUFFER,				//Which buffer you're loading too
		sizeof(vec3)*points.size(),	//Size of data in array (in bytes)
		&points[0],							//Start of array (&points[0] will give you pointer to start of vector)
		GL_DYNAMIC_DRAW						//GL_DYNAMIC_DRAW if you're changing the data often
												//GL_STATIC_DRAW if you're changing seldomly
		);

	R_GL_ERROR_CHECKPOINT;
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO::NORMALS]);
	R_GL_ERROR_CHECKPOINT;
	glBufferData(
		GL_ARRAY_BUFFER,				//Which buffer you're loading too
		sizeof(vec3)*normals.size(),	//Size of data in array (in bytes)
		&normals[0],							//Start of array (&points[0] will give you pointer to start of vector)
		GL_DYNAMIC_DRAW						//GL_DYNAMIC_DRAW if you're changing the data often
												//GL_STATIC_DRAW if you're changing seldomly
		);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO::UVS]);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vec2)*uvs.size(),
		&uvs[0],
		GL_STATIC_DRAW
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[VBO::INDICES]);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int)*indices.size(),
		&indices[0],
		GL_STATIC_DRAW
		);

	R_GL_ERROR_CHECKPOINT;
}

//For reference:
//	https://open.gl/textures
GLuint createTexture(const char* filename)
{
	int components;
	GLuint texID;
	int tWidth, tHeight;

	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &tWidth, &tHeight, &components, 0);
	
	if(data != NULL)
	{
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		if(components==3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if(components==4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tWidth, tHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Clean up
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);

		return texID;
	} 
	
	return 0;	//Error
}

//Use program before loading texture
//	texUnit can be - GL_TEXTURE0, GL_TEXTURE1, etc...
void loadTexture(GLuint texID, GLuint texUnit, GLuint program, const char* uniformName)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	GLuint uniformLocation = glGetUniformLocation(program, uniformName);
	glUniform1i(uniformLocation, 0);
		
	R_GL_ERROR_CHECKPOINT;
}

// fun fact: did you know planets are just elaborate spheres? Believe it.
void generateSphere(vector<vec3>& positions, vector<vec3>& normals, 
					vector<vec2>& uvs, vector<unsigned int>& indices,
					vec3 center, float radius, int divisions)
{
	float step = 1.f / (float)(divisions - 1);
	float u = 0.f;

	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;

		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {
			vec3 pos = vec3(	radius * cos(2.f * M_PI * u) * sin(M_PI * v),
								radius * sin(2.f * M_PI * u) * sin(M_PI * v),
								radius * cos(M_PI * v)) + center;

			vec3 normal = normalize(pos - center);
			
			positions.push_back(pos);
			normals.push_back(normal);
			uvs.push_back(vec2(u, v));

			v += step;
		}

		u += step;
	}

	for(int i = 0; i < divisions - 1; i++)
	{
		for(int j = 0; j < divisions - 1; j++)
		{
			unsigned int p00 = i * divisions + j;
			unsigned int p01 = i * divisions + j + 1;
			unsigned int p10 = (i + 1) * divisions + j;
			unsigned int p11 = (i + 1) * divisions + j + 1;

			indices.push_back(p00);
			indices.push_back(p10);
			indices.push_back(p01);

			indices.push_back(p01);
			indices.push_back(p10);
			indices.push_back(p11);
		}
	}
}

//Draws buffers to screen
void render(mat4 MVP, mat4 viewMatrix, mat4 modelMatrix, int startElement, int numElements)
{
	//Don't need to call these on every draw, so long as they don't change
	glBindVertexArray(vao[VAO::GEOMETRY]);		//Use the LINES vertex array
	glUseProgram(programID);

	//mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"),
						1,
						false,
						&MVP[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(programID, "V"),
						1,
						false,
						&viewMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(programID, "M"),
						1,
						false,
						&modelMatrix[0][0]);

	
	CheckGLErrors("loadUniforms");

	glDrawElements(
			GL_TRIANGLES,		//What shape we're drawing	- GL_TRIANGLES, GL_LINES, GL_POINTS, GL_QUADS, GL_TRIANGLE_STRIP
			numElements,		//How many indices
			GL_UNSIGNED_INT,	//Type
			(void*)0			//Offset
			);

	CheckGLErrors("render");
}

void rotatePlanet(vector<vec3>& points, vector<vec3>& normals, vec3 center, vec3 axis, float theta) {
	axis = normalize(axis);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	mat3 rMat = mat3(	cos(theta) + x2 * (1 - cos(theta)), x * y * (1 - cos(theta)) - z * sin(theta), x * z * (1 - cos(theta)) + y * sin(theta),
						y * x * (1 - cos(theta)) + z * sin(theta), cos(theta) + y2 * (1 - cos(theta)), y * z * (1 - cos(theta)) - x * sin(theta),
						z * x * (1 - cos(theta)) - y * sin(theta), z * y * (1 - cos(theta)) + x * sin(theta), cos(theta) + z2 * (1 - cos(theta)));

	for (int i = 0; i < points.size(); i++) {
		points[i] = (rMat * (points[i] - center)) + center;
		normals[i] = normalize(points[i] - center);
	}

}

void orbitPlanet(vector<vec3>& points, vector<vec3>& normals, vec3& childCenter, vec3 parentCenter, vec3 axis, float theta) {
	axis = normalize(axis);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	rotatePlanet(points, normals, childCenter, axis, -theta);

	mat3 rMat = mat3(	cos(theta) + x2 * (1 - cos(theta)), x * y * (1 - cos(theta)) - z * sin(theta), x * z * (1 - cos(theta)) + y * sin(theta),
						y * x * (1 - cos(theta)) + z * sin(theta), cos(theta) + y2 * (1 - cos(theta)), y * z * (1 - cos(theta)) - x * sin(theta),
						z * x * (1 - cos(theta)) - y * sin(theta), z * y * (1 - cos(theta)) + x * sin(theta), cos(theta) + z2 * (1 - cos(theta)));

	childCenter = (rMat * (childCenter - parentCenter)) + parentCenter;

	for (int i = 0; i < points.size(); i++) {
		points[i] = (rMat * (points[i] - parentCenter)) + parentCenter;
		normals[i] = normalize(points[i] - childCenter);
	}

}



#endif
