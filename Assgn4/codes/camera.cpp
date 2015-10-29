#include "camera.hpp"

Camera::Camera(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, GLfloat x_rot, GLfloat y_rot, GLfloat z_rot){
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;
	this->x_rot = x_rot;
	this->y_rot = y_rot;
	this->z_rot = z_rot;

	x_up = 0; y_up = 1.0; z_up = 0;
	update_matrices();
}

Camera::Camera(){
	x_pos = 10.0;
	y_pos = 0.0;
	z_pos = 15.0;
	x_rot = 0.0;
	y_rot = 0.0;
	z_rot = 0.0;	

	x_up = 0; y_up = 1.0; z_up = 0;
	update_matrices();
}

void Camera::write_params(std::ostream &out){
	out<<x_pos<<" "<<y_pos<<" "<<z_pos<<" "<<x_rot<<" "<<y_rot<<" "<<z_rot<<" "<<x_up<<" "<<y_up<<" "<<z_up<<"\n";
}

void Camera::read_params(std::istream &inp){
	inp>>x_pos>>y_pos>>z_pos>>x_rot>>y_rot>>z_rot>>x_up>>y_up>>z_up;
}

void Camera::update_x(GLfloat x_trans, GLfloat x_rot_v){
	
	x_rot += x_rot_v;
	//update_matrices();

	//glm::vec4 temp = glm::vec4(x_up,y_up,z_up,1)*rotation_matrix;
	//x_up = temp.x/temp.w;y_up = temp.y/temp.w;z_up = temp.z/temp.w;
	x_pos += x_trans;
	if(x_pos < -100.0) x_pos = -100.0;
	if(x_pos > 100.0) x_pos = 100.0;
	update_matrices();
}

void Camera::update_y(GLfloat y_trans, GLfloat y_rot_v){
	y_pos += y_trans;
	y_rot += y_rot_v;

	if(y_pos < -100.0) y_pos = -100.0;
	if(y_pos > 100.0) y_pos = 100.0;

	update_matrices();
}

void Camera::update_z(GLfloat z_trans, GLfloat z_rot_v){
	z_pos += z_trans;
	z_rot += z_rot_v;

	if(z_pos < -100.0) z_pos = -100.0;
	if(z_pos > 100.0) z_pos = 100.0;

	update_matrices();
}

void Camera::update_matrices(){

	rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(x_rot), glm::vec3(1.0f,0.0f,0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, glm::radians(y_rot), glm::vec3(0.0f,1.0f,0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, glm::radians(z_rot), glm::vec3(0.0f,0.0f,1.0f));

	glm::vec4 pos_matrix = glm::vec4(x_pos, y_pos, z_pos, 1.0)*rotation_matrix;
	glm::vec4 up_matrix = glm::vec4(x_up, y_up, z_up, 1.0)*rotation_matrix;
	
	lookat_matrix = glm::lookAt(glm::vec3(pos_matrix),glm::vec3(0.0),glm::vec3(up_matrix));

}

glm::mat4 Camera::get_lookat_matrix(){
	return lookat_matrix;
}