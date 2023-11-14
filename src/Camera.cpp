#include "Camera.h"
#include "Player.h"
#include <glm/gtc/type_ptr.hpp>

void Camera::applyView(GLuint shaderId, Player player) {

    auto projection = glm::ortho(-16.0f, +16.0f, -16.0f, +16.0f);

    int projLog = glGetUniformLocation(shaderId, "proj");
    glUniformMatrix4fv(projLog, 1, GL_FALSE, glm::value_ptr(projection));

    auto view = glm::mat4(1.0f);

    // Apply translation
    view = glm::translate(view, glm::vec3(-player.x, -player.y, 0));

    int viewLog = glGetUniformLocation(shaderId, "view");
    glUniformMatrix4fv(viewLog, 1, GL_FALSE, glm::value_ptr(view));
}