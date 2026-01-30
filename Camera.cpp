#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

Camera::Camera(int width, int height, glm::vec3 position){
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform){
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}
glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Orientation, Up);
}

glm::mat4 Camera::GetProjectionMatrix(){
    return glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
}

void Camera::Inputs(GLFWwindow* window){
    float actualSpeed = speed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
       glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS){
        actualSpeed *= 2;
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += actualSpeed * Orientation;

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= actualSpeed * Orientation;

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Orientation, Up)) * actualSpeed;

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Orientation, Up)) * actualSpeed;

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        Position += speed * Up;

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        Position -= speed * Up;
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (firstMouse){
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }

    float xOffset = mouseX - lastX;
    float yOffset = lastY - mouseY; // Notice the inverted y: lastY - mouseY, not mouseY - lastY
    lastX = mouseX;
    lastY = mouseY;

    xOffset *= sensitivity * 0.1f;
    yOffset *= sensitivity * 0.1f;

    yaw += xOffset;
    pitch += yOffset;

    // Clamp pitch to prevent camera flip
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Calculate new orientation vector
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation = glm::normalize(direction);
}