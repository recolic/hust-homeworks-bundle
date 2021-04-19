// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <vector>
#include <chrono>
using namespace std::chrono;

#include <rlib/stdio.hpp>
#include <common/fps.hpp>

auto calc_square_vertex_buf_data(std::pair<float, float> center) {
    auto dx = 0.1, dy = 0.07;
    auto x1 = center.first - dx, x2 = center.first + dx,
         y1 = center.second - dy, y2 = center.second + dy;

#ifdef DEBUG
    rlib::println("debug: square, x1,y1,x2,y2 = ", x1, y1, x2, y2);
#endif

    return std::vector<float>{
        x1, y1,
        x1, y2,
        x1, y1,
        x2, y1,

        x2, y2,
        x1, y2,
        x2, y2,
        x2, y1
    };
}

auto calc_ellipse_point(float location_0_to_1) {
    auto y_sign = location_0_to_1 > 0.5 ? -1.0 : 1.0;
    auto x = cos(location_0_to_1 * 2 * M_PI);
    auto y = sqrt(1.0-x*x) * 0.75 * y_sign;
#ifdef DEBUG
    rlib::println("debug: center x,y = ", x, y);
#endif
    return std::make_pair((float)x, (float)y);
}

auto calc_ellipse_vertex_buf_data()
{
    const float cx = 0, cy = 0, rx = 1, ry = 0.75, num_segments = 64;

    float theta = M_PI * 2 / float(num_segments);
    float c = cosf(theta); //precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    std::vector<float> buf;
    for(int ii = 0; ii < num_segments; ++ii)
    {
        //apply radius and offset
        if(ii != 0) { buf.emplace_back(x * rx + cx); buf.emplace_back(y * ry + cy); }
        if(ii != num_segments-1) { buf.emplace_back(x * rx + cx); buf.emplace_back(y * ry + cy); }

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }

    return buf;
}

int main( void )
{
    // Make println faster
    // rlib::enable_endl_flush(false);
    rlib::sync_with_stdio(false);

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
	window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    const size_t msPerRound = 10000;
    auto ellipse_vertex_buffer = calc_ellipse_vertex_buf_data();

    init_fps();

	do {
        // Prepare vertex buffer
        auto g_vertex_buffer = ellipse_vertex_buffer;

        auto location = (float)( duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
        ).count() % msPerRound ) / msPerRound;
        auto square_vertex_buffer = std::move(calc_square_vertex_buf_data(calc_ellipse_point(location)));

        g_vertex_buffer.insert(g_vertex_buffer.end(), square_vertex_buffer.begin(), square_vertex_buffer.end());
	    glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer.size() * sizeof(float), g_vertex_buffer.data(), GL_STATIC_DRAW);

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
   
		// Draw the lines!
		glDrawArrays(GL_LINES, 0, g_vertex_buffer.size() / 2);
        ++ fps_counter;

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

