#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

float Camera::x = 0;
float Camera::y = 0;

void Camera::applyView(GLuint shaderId) {
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));

    int viewLog = glGetUniformLocation(shaderId, "view");
    glUniformMatrix4fv(viewLog, 1, GL_FALSE, glm::value_ptr(view));
}