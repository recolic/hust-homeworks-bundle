#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

extern float universeTimeSpeed;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif