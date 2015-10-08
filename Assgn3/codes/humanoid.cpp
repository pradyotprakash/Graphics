#include "humanoid.hpp"

	Humanoid::Humanoid(){}

	csX75::HNode* Humanoid::create_elem(std::vector <glm::vec4> v_positions, std::vector <glm::vec4> v_colors, int elem){
		csX75::HNode *parent, *curr;
		
		if(elem == HIP_ID){
			parent = NULL;
			hip = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = hip;
		}
		else if(elem == T_ID){
			parent = hip;
			torso = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = torso;
		}
		else if(elem == UL1_ID){
			parent = torso;
			up_leg1 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = up_leg1;
		}
		else if(elem == UL2_ID){
			parent = torso;
			up_leg2 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = up_leg2;
		}
		else if(elem == LL1_ID){
			parent = up_leg1;
			l_leg1 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = l_leg1;
		}
		else if(elem == LL2_ID){
			parent = up_leg2;
			l_leg2 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = l_leg2;
		}
		else if(elem == F1_ID){
			parent = l_leg1;
			foot1 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = foot1;
		}
		else if(elem == F2_ID){
			parent = l_leg2;
			foot2 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = foot2;
		}
		else if(elem == S_ID){
			parent = torso;
			shoulder = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = shoulder;
		}
		else if(elem == N_ID){
			parent = shoulder;
			neck = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = neck;
		}
		else if(elem == UA1_ID){
			parent = shoulder;
			up_arm1 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = up_arm1;
		}
		else if(elem == UA2_ID){
			parent = shoulder;
			up_arm2 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = up_arm2;
		}
		else if(elem == LA1_ID){
			parent = up_arm1;
			l_arm1 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = l_arm1;	
		}
		else if(elem == LA2_ID){
			parent = up_arm2;
			l_arm2 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = l_arm2;
		}
		else if(elem == H_ID){
			parent = neck;
			head = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size()); 
			curr = head;
		}
		else if(elem == W1_ID){
			parent = l_arm1;
			wrist1 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = wrist1;
		}
		else if(elem == W2_ID){
			parent = l_arm2;
			wrist2 = new csX75::HNode(parent, v_positions.size(), &v_positions[0], &v_colors[0], v_positions.size(), v_colors.size());
			curr = wrist2;
		}

		return curr;
	}

	csX75::HNode* Humanoid::get_current(int elem){

		if(elem == HIP_ID){
			return hip;
		}
		else if(elem == T_ID){
			return torso;
		}
		else if(elem == UL1_ID){
			return up_leg1;
		}
		else if(elem == UL2_ID){
			return up_leg2;
		}
		else if(elem == LL1_ID){
			return l_leg1; 
		}
		else if(elem == LL2_ID){
			return l_leg2;
		}
		else if(elem == F1_ID){
			return foot1;
		}
		else if(elem == F2_ID){
			return foot2;
		}
		else if(elem == S_ID){
			return shoulder;
		}
		else if(elem == N_ID){
			return neck;
		}
		else if(elem == UA1_ID){
			return up_arm1;
		}
		else if(elem == UA2_ID){
			return up_arm2;
		}
		else if(elem == LA1_ID){
			return l_arm1;
		}
		else if(elem == LA2_ID){
			return l_arm2;
		}
		else if(elem == H_ID){
			return head;
		}
		else if(elem == W1_ID){
			return wrist1;
		}
		else if(elem == W2_ID){
			return wrist2;
		}
	}

	csX75::HNode* Humanoid::get_root(){
		return hip;
	}