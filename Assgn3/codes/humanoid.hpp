#include "hierarchy_node.hpp"
#include <vector>

#define HIP_ID 1
#define UA1_ID 2
#define UA2_ID 3
#define LA1_ID 4
#define LA2_ID 5
#define W1_ID 6
#define W2_ID 7
#define UL1_ID 8
#define UL2_ID 9
#define LL1_ID 10
#define LL2_ID 11
#define F1_ID 12
#define F2_ID 13
#define S_ID 14
#define T_ID 15
#define N_ID 16
#define H_ID 17


class Humanoid{
public:	
	csX75::HNode *hip,*head, *neck,*shoulder,*torso,*up_arm1,*up_arm2,*l_arm1,*l_arm2,*wrist1,*wrist2,*up_leg1,*up_leg2,*l_leg1,*l_leg2,*foot1,*foot2;	

	Humanoid();

	void create_elem(std::vector <glm::vec4> v_positions,std::vector <glm::vec4> v_colors,int elem);

	csX75::HNode* get_current(int elem);
};