#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;

    float yaw;
    float pitch;
    float speed;
    float sensitivity;

    int width, height;

    Camera(int w, int h, glm::vec3 pos);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    void Inputs(GLFWwindow* window);

private:
    bool firstMouse;
    float lastX, lastY;
};

#endif
