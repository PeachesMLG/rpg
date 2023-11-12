#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

float Camera::x = 0;
float Camera::y = 0;
float Camera::zoom = 1;

void Camera::applyView(GLuint shaderId) {
    auto view = glm::mat4(1.0f);

    // Apply translation
    view = glm::translate(view, glm::vec3(x, y, 0));

    // Apply zoom (scaling)
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

    int viewLog = glGetUniformLocation(shaderId, "view");
    glUniformMatrix4fv(viewLog, 1, GL_FALSE, glm::value_ptr(view));
}