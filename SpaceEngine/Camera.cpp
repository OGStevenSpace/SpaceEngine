#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += Orientation * speed;
		std::cout << "x:" << std::round(Position.x) << " y:" << std::round(Position.y) << " z:" << std::round(Position.z) << "        \r";
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position -= Orientation * speed;
		std::cout << "x:" << std::round(Position.x) << " y:" << std::round(Position.y) << " z:" << std::round(Position.z) << "        \r";
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
		std::cout << "x:" << std::round(Position.x) << " y:" << std::round(Position.y) << " z:" << std::round(Position.z) << "        \r";
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
		std::cout << "x:" << std::round(Position.x) << " y:" << std::round(Position.y) << " z:" << std::round(Position.z) << "        \r";
	}
}