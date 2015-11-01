#include "hierarchy_node.hpp"
#include "constants.hpp"
#include <iostream>

extern GLuint vPosition2, vColor2, vNormal2, vTexture2, uModelViewMatrix2, normalMatrix , viewMatrix;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(int id, HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, glm::vec2* a_textures, std::size_t v_size, std::size_t c_size, std::size_t n_size, std::size_t t_size, GLuint tex1){
		ID = id;
		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		normal_buffer_size = n_size;
		texture_buffer_size = t_size;
		// initialize vao and vbo of the object;

		tex = tex1;
		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glBufferData (GL_ARRAY_BUFFER, normal_buffer_size+ vertex_buffer_size + color_buffer_size + texture_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+ color_buffer_size, normal_buffer_size, a_normals );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+ color_buffer_size+normal_buffer_size, texture_buffer_size, a_textures );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition2 );
		glVertexAttribPointer( vPosition2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor2 );
		glVertexAttribPointer( vColor2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vNormal2 );
 		glVertexAttribPointer( vNormal2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+color_buffer_size));

 		glEnableVertexAttribArray( vTexture2 );
 		glVertexAttribPointer( vTexture2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+color_buffer_size+normal_buffer_size));

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=px=py=pz=0;

		update_matrices();

	}

	void HNode::write_tree_to_file(std::ostream& out){
		out<<float(tx)<<" "<<float(ty)<<" "<<float(tz)<<" "<<float(rx)<<" "<<float(ry)<<" "<<float(rz)<<"\n";

		for(int i=0;i<children.size();i++){
			children[i]->write_tree_to_file(out);
		}
	}

	void HNode::read_tree_from_file(std::istream& inp){
		// std::cout<<tx<<" "<<ty<<" "<<tz<<" "<<rx<<" "<<ry<<" "<<rz<<std::endl;
		inp>>tx>>ty>>tz>>rx>>ry>>rz;
		// std::cout<<tx<<" "<<ty<<" "<<tz<<" "<<rx<<" "<<ry<<" "<<rz<<std::endl;
		update_matrices();

		for(int i=0;i<children.size();i++){
			children[i]->read_tree_from_file(inp);
		}
	}	

	void HNode::sanity_check(){
		// defines the constraints for each node movemet
		if(ID == KNEE_LEFT || ID == KNEE_RIGHT){
			ry = rz = 0;
			rx = glm::max(0.0f, glm::min(rx, 120.0f));
		}
		else if(ID == UPPER_LEG_LEFT){
			rx = glm::max(-90.0f, glm::min(rx, 70.0f));	
			ry = glm::max(-80.0f, glm::min(ry, 0.0f));	
			rz = glm::max(-50.0f, glm::min(rz, 0.0f));
		}
		else if(ID == UPPER_LEG_RIGHT){
			rx = glm::max(-90.0f, glm::min(rx, 70.0f));	
			ry = glm::max(0.0f, glm::min(ry, 80.0f));	
			rz = glm::max(0.0f, glm::min(rz, 50.0f));
		}
		else if(ID == HIP_JOINT){
			rx = glm::max(-110.0f, glm::min(rx, 40.0f));	
			ry = glm::max(-50.0f, glm::min(ry, 50.0f));	
			rz = glm::max(-25.0f, glm::min(rz, 25.0f));
		}
		else if(ID == NECK){
			rx = glm::max(-20.0f, glm::min(rx, 50.0f));	
			ry = glm::max(-50.0f, glm::min(ry, 50.0f));	
			rz = glm::max(-30.0f, glm::min(rz, 30.0f));
		}
		else if(ID == UPPER_ARM_RIGHT){
			rx = glm::max(-30.0f, glm::min(rx, 200.0f));	
			ry = glm::max(-130.0f, glm::min(ry, 50.0f));	
			rz = glm::max(-40.0f, glm::min(rz, 100.0f));	
		}
		else if(ID == UPPER_ARM_LEFT){
			rx = glm::max(-200.0f, glm::min(rx, 30.0f));	
			ry = glm::max(-130.0f, glm::min(ry, 50.0f));	
			rz = glm::max(-100.0f, glm::min(rz, 40.0f));	
		}
		else if(ID == ELBOW_LEFT){
			ry = rx = 0;
			rz = glm::max(-160.0f, glm::min(rz, -50.0f));
		}
		else if(ID == ELBOW_RIGHT){
			ry = rx = 0;
			rz = glm::max(50.0f, glm::min(rz, 150.0f));
		}
		// add constraints for the droid
		else if(ID == D_UPPER_LEG_LEFT){
			rx = glm::max(-90.0f, glm::min(rx, 70.0f));	
			ry = glm::max(-80.0f, glm::min(ry, 0.0f));	
			rz = glm::max(-50.0f, glm::min(rz, 0.0f));
		}
		else if(ID == D_UPPER_LEG_RIGHT){
			rx = glm::max(-90.0f, glm::min(rx, 70.0f));	
			ry = glm::max(0.0f, glm::min(ry, 80.0f));	
			rz = glm::max(0.0f, glm::min(rz, 50.0f));
		}
		else if(ID == D_KNEE_LEFT || ID == D_KNEE_RIGHT){
			ry = rz = 0;
			rx = glm::max(0.0f, glm::min(rx, 120.0f));
		}
		else if(ID == D_HEAD){
			rx = ry = 0;
		}
		else if(ID == TORSO_JOINT){
			rx = glm::max(-60.0f, glm::min(rx, 120.0f));	
			ry = glm::max(-40.0f, glm::min(ry, 40.0f));	
			rz = glm::max(-50.0f, glm::min(rz, 50.0f));
		}
	}

	void HNode::update_matrices(){
		sanity_check();
		glm::mat4 tr1 = glm::translate(glm::mat4(1.0f),glm::vec3(px,py,pz));		

		rotation = glm::rotate(tr1, glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx-px,ty-px,tz-px));
	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);
	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	// void HNode::change_rotation_parameters(GLfloat arx, GLfloat ary, GLfloat arz){
	// 	px += arx;
	// 	py += ary;
	// 	pz += arz;

	// 	update_matrices();
	// }

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);
		glUniformMatrix4fv(uModelViewMatrix2, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
  		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

		glBindTexture(GL_TEXTURE_2D, tex);
  		
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(GLfloat depth){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);
		matrixStack.push_back(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,depth)));
		render();
		matrixStack.pop_back();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree(depth);
		}
		matrixStack.pop_back();
		matrixStack.pop_back();
	}

	void HNode::inc_rx(){
		rx += 2;
		update_matrices();
	}

	void HNode::inc_ry(){
		ry += 2;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz += 2;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx -= 2;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry -= 2;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz -= 2;
		update_matrices();
	}

	void HNode::inc_tx(){
		tx += 2;
		update_matrices();
	}

	void HNode::inc_ty(){
		ty += 2;
		update_matrices();
	}

	void HNode::inc_tz(){
		tz += 2;
		update_matrices();
	}

	void HNode::dec_tx(){
		tx -= 2;
		update_matrices();
	}

	void HNode::dec_ty(){
		ty -= 2;
		update_matrices();
	}

	void HNode::dec_tz(){
		tz -= 2;
		update_matrices();
	}

	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}