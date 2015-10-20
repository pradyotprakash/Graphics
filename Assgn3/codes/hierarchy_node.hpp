#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz,px,py,pz;
		
		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;
		std::size_t normal_buffer_size;
		std::size_t texture_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo, tex;

		glm::mat4 rotation;
		glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  public:
		int ID;
		HNode(int id, HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, glm::vec2* a_textures, std::size_t v_size, std::size_t c_size, std::size_t n_size, std::size_t t_size, GLuint tex);
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void sanity_check();
		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void change_rotation_parameters(GLfloat,GLfloat,GLfloat);
		void render_tree(GLfloat);
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void inc_tx();
		void inc_ty();
		void inc_tz();
		void dec_tx();
		void dec_ty();
		void dec_tz();
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );

};	

#endif