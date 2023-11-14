#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

void Camera::applyView(GLuint shaderId) {
    auto view = glm::mat4(0.5f);

    int viewLog = glGetUniformLocation(shaderId, "view");
    glUniformMatrix4fv(viewLog, 1, GL_FALSE, glm::value_ptr(view));
}