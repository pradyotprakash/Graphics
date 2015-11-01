#include "hierarchy_node.hpp"
#include "constants.hpp"
#include <vector>



class Humanoid{
public:	
	static int sizeOfvec4, sizeOfvec2;
	csX75::HNode *torso_joint, *hip_joint, *knee1, *knee2, *elbow1, *elbow2, *hip,*head, *neck,*shoulder,*torso,*up_arm1,*up_arm2,*l_arm1,*l_arm2,*wrist1,*wrist2,*up_leg1,*up_leg2,*l_leg1,*l_leg2,*foot1,*foot2,*saber1, *saber2;	

	Humanoid();

	csX75::HNode* create_elem(std::vector <glm::vec4> v_positions, std::vector <glm::vec4> v_colors, std::vector<glm :: vec4> v_normals, std::vector<glm :: vec2> v_textures, GLuint tex, int elem);

	csX75::HNode* get_current(int elem);

	csX75::HNode* get_root();

	void interpolate(Humanoid*, Humanoid*, std::vector<Humanoid*>, int);
	void interpolate(Humanoid*, Humanoid*, int, int);
};