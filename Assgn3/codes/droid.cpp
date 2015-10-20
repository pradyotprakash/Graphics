#include "droid.hpp"

	Droid::Droid(){
		head = body = up_leg1 = up_leg2 = knee1= knee2 = l_leg1 = l_leg2 = wheel1 = wheel2 =NULL;
	}

	csX75::HNode* Droid::create_elem(std::vector <glm::vec4> v_positions, std::vector <glm::vec4> v_colors, std::vector<glm :: vec4> v_normals, std::vector<glm :: vec2> v_textures, GLuint tex, int elem){
		csX75::HNode *parent, *curr;
		
		if(elem == D_TORSO){
			parent = NULL;
			body = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = body;
		}
		else if(elem == D_UPPER_LEG_LEFT){
			parent = body;
			up_leg1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = up_leg1;
		}
		else if(elem == D_UPPER_LEG_RIGHT){
			parent = body;
			up_leg2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = up_leg2;
		}
		else if(elem == D_KNEE_LEFT){
			parent = up_leg1;
			knee1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = knee1;
		}
		else if(elem == D_KNEE_RIGHT){
			parent = up_leg2;
			knee2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = knee2;
		}
		else if(elem == D_LOWER_LEG_LEFT){
			parent = knee1;
			l_leg1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = l_leg1;
		}
		else if(elem == D_LOWER_LEG_RIGHT){
			parent = knee2;
			l_leg2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = l_leg2;
		}
		else if(elem == D_HEAD){
			parent = body;
			head = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex); 
			curr = head;
		}
		else if(elem == D_WHEEL_LEFT){
			parent = l_leg1;
			wheel1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex); 
			curr = wheel1;
		}
		else if(elem == D_WHEEL_RIGHT){
			parent = l_leg2;
			wheel2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex); 
			curr = wheel2;
		}
		return curr;
	}

	csX75::HNode* Droid::get_current(int elem){

		if(elem == D_TORSO){
			return body;
		}
		else if(elem == D_UPPER_LEG_LEFT){
			return up_leg1;
		}
		else if(elem == D_UPPER_LEG_RIGHT){
			return up_leg2;
		}
		else if(elem == D_LOWER_LEG_LEFT){
			return l_leg1; 
		}
		else if(elem == D_LOWER_LEG_RIGHT){
			return l_leg2;
		}
		else if(elem == D_HEAD){
			return head;
		}
		else if(elem == D_KNEE_RIGHT){
			return knee2;
		}
		else if(elem == D_KNEE_LEFT){
			return knee1;
		}
		else if(elem == D_WHEEL_LEFT){
			return wheel1;
		}
		else if(elem == D_WHEEL_RIGHT){
			return wheel2;
		}
	}

	csX75::HNode* Droid::get_root(){
		return body;
	}

	int Droid::sizeOfvec4 = sizeof(glm::vec4);
	int Droid::sizeOfvec2 = sizeof(glm::vec2);