#include "humanoid.hpp"

	Humanoid::Humanoid(){
		hip = head = neck = shoulder = torso = up_arm1 = up_arm2 = l_arm1 = l_arm2 = wrist1 = wrist2 = up_leg1 = up_leg2 = l_leg1 = l_leg2 = foot1 = foot2 = saber1 = saber2 = elbow1 = elbow2 = knee1 = knee2 = NULL;
		hip_joint = torso_joint = NULL;
	}

	csX75::HNode* Humanoid::create_elem(std::vector <glm::vec4> v_positions, std::vector <glm::vec4> v_colors, std::vector<glm :: vec4> v_normals, std::vector<glm :: vec2> v_textures, GLuint tex, int elem){
		csX75::HNode *parent, *curr;
		
		if(elem == HIP){
			parent = NULL;
			hip = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = hip;
		}
		else if(elem == TORSO_JOINT){
			parent = hip;
			torso_joint = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = torso_joint;
		}
		else if(elem == HIP_JOINT){
			parent = hip;
			hip_joint = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = hip_joint;
		}
		else if(elem == TORSO){
			parent = torso_joint;
			torso = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = torso;
		}
		else if(elem == UPPER_LEG_LEFT){
			parent = hip_joint;
			up_leg1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = up_leg1;
		}
		else if(elem == UPPER_LEG_RIGHT){
			parent = hip_joint;
			up_leg2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = up_leg2;
		}
		else if(elem == KNEE_LEFT){
			parent = up_leg1;
			knee1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = knee1;
		}
		else if(elem == KNEE_RIGHT){
			parent = up_leg2;
			knee2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = knee2;
		}
		else if(elem == LOWER_LEG_LEFT){
			parent = knee1;
			l_leg1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = l_leg1;
		}
		else if(elem == LOWER_LEG_RIGHT){
			parent = knee2;
			l_leg2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = l_leg2;
		}
		else if(elem == FOOT_LEFT){
			parent = l_leg1;
			foot1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = foot1;
		}
		else if(elem == FOOT_RIGHT){
			parent = l_leg2;
			foot2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = foot2;
		}
		else if(elem == SHOULDER){
			parent = torso;
			shoulder = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = shoulder;
		}
		else if(elem == NECK){
			parent = shoulder;
			neck = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = neck;
		}
		else if(elem == UPPER_ARM_LEFT){
			parent = shoulder;
			up_arm1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = up_arm1;
		}
		else if(elem == UPPER_ARM_RIGHT){
			parent = shoulder;
			up_arm2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = up_arm2;
		}
		else if(elem == ELBOW_LEFT){
			parent = up_arm1;
			elbow1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = elbow1;
		}
		else if(elem == ELBOW_RIGHT){
			parent = up_arm2;
			elbow2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = elbow2;
		}
		else if(elem == LOWER_ARM_LEFT){
			parent = elbow1;
			l_arm1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = l_arm1;
		}
		else if(elem == LOWER_ARM_RIGHT){
			parent = elbow2;
			l_arm2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = l_arm2;
		}
		else if(elem == HEAD){
			parent = neck;
			head = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex); 
			curr = head;
		}
		else if(elem == WRIST_LEFT){
			parent = l_arm1;
			wrist1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = wrist1;
		}
		else if(elem == WRIST_RIGHT){
			parent = l_arm2;
			wrist2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = wrist2;
		}
		else if(elem == LIGHT_SABER_LEFT){
			parent = wrist1;
			saber1 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
			curr = saber1;
		}
		else if(elem == LIGHT_SABER_RIGHT){
			parent = wrist2;
			saber2 = new csX75::HNode(elem, parent, v_positions.size(), &v_positions[0], &v_colors[0], &v_normals[0], &v_textures[0], sizeOfvec4*v_positions.size(), sizeOfvec4*v_colors.size(), sizeOfvec4*v_normals.size(), sizeOfvec2*v_textures.size(), tex);
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
		else if(elem == TORSO_JOINT){
			return torso_joint;
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
		else if(elem == HIP_JOINT){
			return hip_joint;
		}
	}

	csX75::HNode* Humanoid::get_root(){
		return hip;
	}

	void Humanoid::interpolate(Humanoid* h1, Humanoid* h2, std::vector<Humanoid*> h, int frames){

		int tx, ty, tz, rx, ry, rz, a, b;
		
		for(int j=0;j<=frames;++j){

			for(int i=0;i<25;++i){
				csX75::HNode *n1, *n2;
				n1 = h1->get_current(i);
				n2 = h2->get_current(i);

				a = n1->tx; b = n2->tx;
				tx = a + (b-a)*j/frames;

				a = n1->ty; b = n2->ty;
				ty = a + (b-a)*j/frames;

				a = n1->tz; b = n2->tz;
				tz = a + (b-a)*j/frames;

				a = n1->rx; b = n2->rx;
				rx = a + (b-a)*j/frames;

				a = n1->ry; b = n2->ry;
				ry = a + (b-a)*j/frames;

				a = n1->rz; b = n2->rz;
				rz = a + (b-a)*j/frames;

				h[j]->get_current(i)->change_parameters(tx, ty, tz, rx, ry, rz);
			}
		}
	}

	void Humanoid::interpolate(Humanoid* h1, Humanoid* h2, int j, int frames){

		int tx, ty, tz, rx, ry, rz, a, b;
		
		for(int i=0;i<25;++i){
			csX75::HNode *n1, *n2;
			n1 = h1->get_current(i);
			n2 = h2->get_current(i);

			a = n1->tx; b = n2->tx;
			tx = a + (b-a)*j/frames;

			a = n1->ty; b = n2->ty;
			ty = a + (b-a)*j/frames;

			a = n1->tz; b = n2->tz;
			tz = a + (b-a)*j/frames;

			a = n1->rx; b = n2->rx;
			rx = a + (b-a)*j/frames;

			a = n1->ry; b = n2->ry;
			ry = a + (b-a)*j/frames;

			a = n1->rz; b = n2->rz;
			rz = a + (b-a)*j/frames;

			this->get_current(i)->change_parameters(tx, ty, tz, rx, ry, rz);
		}
	}

	int Humanoid::sizeOfvec4 = sizeof(glm::vec4);
	int Humanoid::sizeOfvec2 = sizeof(glm::vec2);