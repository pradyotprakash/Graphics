#include "humanoid.hpp"

	Humanoid::Humanoid(){
		hip = head = neck = shoulder = torso = up_arm1 = up_arm2 = l_arm1 = l_arm2 = wrist1 = wrist2 = up_leg1 = up_leg2 = l_leg1 = l_leg2 = foot1 = foot2 = saber1 = saber2 = elbow1 = elbow2 = knee1 = knee2 = NULL;
	}

	csX75::HNode* Humanoid::create_elem(std::vector <glm::vec4> v_positions, std::vector <glm::vec4> v_colors, int elem){
		csX75::HNode *parent, *curr;
		
		if(elem == HIP){
			parent = NULL;
			hip = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = hip;
		}
		else if(elem == TORSO){
			parent = hip;
			torso = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = torso;
		}
		else if(elem == UPPER_LEG_LEFT){
			parent = torso;
			up_leg1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = up_leg1;
		}
		else if(elem == UPPER_LEG_RIGHT){
			parent = torso;
			up_leg2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = up_leg2;
		}
		else if(elem == KNEE_LEFT){
			parent = up_leg1;
			knee1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = knee1;
		}
		else if(elem == KNEE_RIGHT){
			parent = up_leg2;
			knee2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = knee2;
		}
		else if(elem == LOWER_LEG_LEFT){
			parent = knee1;
			l_leg1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = l_leg1;
		}
		else if(elem == LOWER_LEG_RIGHT){
			parent = knee2;
			l_leg2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = l_leg2;
		}
		else if(elem == FOOT_LEFT){
			parent = l_leg1;
			foot1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = foot1;
		}
		else if(elem == FOOT_RIGHT){
			parent = l_leg2;
			foot2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = foot2;
		}
		else if(elem == SHOULDER){
			parent = torso;
			shoulder = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = shoulder;
		}
		else if(elem == NECK){
			parent = shoulder;
			neck = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = neck;
		}
		else if(elem == UPPER_ARM_LEFT){
			parent = shoulder;
			up_arm1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = up_arm1;
		}
		else if(elem == UPPER_ARM_RIGHT){
			parent = shoulder;
			up_arm2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = up_arm2;
		}
		else if(elem == ELBOW_LEFT){
			parent = up_arm1;
			elbow1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = elbow1;
		}
		else if(elem == ELBOW_RIGHT){
			parent = up_arm2;
			elbow2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = elbow2;
		}
		else if(elem == LOWER_ARM_LEFT){
			parent = elbow1;
			l_arm1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = l_arm1;
		}
		else if(elem == LOWER_ARM_RIGHT){
			parent = elbow2;
			l_arm2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = l_arm2;
		}
		else if(elem == HEAD){
			parent = neck;
			head = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size()); 
			curr = head;
		}
		else if(elem == WRIST_LEFT){
			parent = l_arm1;
			wrist1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = wrist1;
		}
		else if(elem == WRIST_RIGHT){
			parent = l_arm2;
			wrist2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = wrist2;
		}
		else if(elem == LIGHT_SABER_LEFT){
			parent = wrist1;
			saber1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = saber1;
		}
		else if(elem == LIGHT_SABER_RIGHT){
			parent = wrist2;
			saber2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size());
			curr = saber2;
		}
		return curr;
	}

	csX75::HNode* Humanoid::get_current(int elem){

		if(elem == HIP){
			return hip;
		}
		else if(elem == TORSO){
			return torso;
		}
		else if(elem == UPPER_LEG_LEFT){
			return up_leg1;
		}
		else if(elem == UPPER_LEG_RIGHT){
			return up_leg2;
		}
		else if(elem == LOWER_LEG_LEFT){
			return l_leg1; 
		}
		else if(elem == LOWER_LEG_RIGHT){
			return l_leg2;
		}
		else if(elem == FOOT_LEFT){
			return foot1;
		}
		else if(elem == FOOT_RIGHT){
			return foot2;
		}
		else if(elem == SHOULDER){
			return shoulder;
		}
		else if(elem == NECK){
			return neck;
		}
		else if(elem == UPPER_ARM_LEFT){
			return up_arm1;
		}
		else if(elem == UPPER_ARM_RIGHT){
			return up_arm2;
		}
		else if(elem == LOWER_ARM_LEFT){
			return l_arm1;
		}
		else if(elem == LOWER_ARM_RIGHT){
			return l_arm2;
		}
		else if(elem == HEAD){
			return head;
		}
		else if(elem == WRIST_LEFT){
			return wrist1;
		}
		else if(elem == WRIST_RIGHT){
			return wrist2;
		}
		else if(elem == LIGHT_SABER_LEFT){
			return saber1;
		}
		else if(elem == LIGHT_SABER_RIGHT){
			return saber2;
		}
		else if(elem == ELBOW_RIGHT){
			return elbow2;
		}
		else if(elem == ELBOW_LEFT){
			return elbow1;
		}
		else if(elem == KNEE_RIGHT){
			return knee2;
		}
		else if(elem == KNEE_LEFT){
			return knee1;
		}
	}

	csX75::HNode* Humanoid::get_root(){
		return hip;
	}

	int Humanoid::sizeOfvec4 = sizeof(glm::vec4);	