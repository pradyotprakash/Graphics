#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>

#include <fstream>
#include <iostream>

class Camera{
public:
	GLfloat x_pos, y_pos, z_pos;
	GLfloat x_rot, y_rot, z_rot;
	GLfloat x_up, y_up, z_up;
	glm::mat4 rotation_matrix;
	glm::mat4 lookat_matrix;

	Camera(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_rot, GLfloat y_rot, GLfloat z_rot);

	Camera();

	void update_x(GLfloat x_trans, GLfloat x_rot_v);

	void update_y(GLfloat y_trans, GLfloat y_rot_v);

	void update_z(GLfloat z_trans, GLfloat z_rot_v);

	void update_matrices();
	void write_params(std::ostream&);
	void read_params(std::istream&);
	void update_params(glm::vec3 pos);
	void show();

	glm::mat4 get_lookat_matrix();
};