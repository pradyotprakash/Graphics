#ifndef _MODELLER_HPP_
#define _MODELLER_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint pressed1 = 0, pressed2 = 0, pressed3 = 0, pressed4 = 0;
GLfloat xrot = 0, yrot = 0, zrot = 0, xpos = 0, ypos = 0, zpos = 0, scalex = 1, scaley = 1, scalez = 1;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;

//-------------------------------------------------------------------------


#endif
