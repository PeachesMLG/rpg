#include "Camera.h"
#include "Player.h"
#include <glm/gtc/type_ptr.hpp>

float Camera::zoom = 1;

void Camera::applyView(GLuint shaderId, Player player) {
    auto view = glm::mat4(1.0f);

    // Apply translation
    view = glm::translate(view, glm::vec3(-player.x, -player.y, 0));

    // Apply zoom (scaling)
//    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

    int viewLog = glGetUniformLocation(shaderId, "view");
    glUniformMatrix4fv(viewLog, 1, GL_FALSE, glm::value_ptr(view));
}