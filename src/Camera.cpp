#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(int w, int h, glm::vec3 pos)
{
    width = w;
    height = h;
    Position = pos;

    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);

    yaw = -90.0f;
    pitch = 0.0f;

    speed = 0.1f;
    sensitivity = 0.1f;

    firstMouse = true;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(
        glm::radians(45.0f),
        (float)width / (float)height,
        0.1f,
        100.0f
    );
}

void Camera::Inputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += speed * Front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= speed * Front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * speed;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float dx = (x - lastX) * sensitivity;
    float dy = (lastY - y) * sensitivity;

    lastX = x;
    lastY = y;

    yaw += dx;
    pitch += dy;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front = glm::normalize(dir);
}
