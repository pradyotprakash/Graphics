#include "hierarchy_node.hpp"
#include "constants.hpp"
#include <vector>



class Droid{
public:	
	static int sizeOfvec4, sizeOfvec2;
	csX75::HNode *head,*body,*up_leg1,*up_leg2,*l_leg1,*l_leg2, *knee1, *knee2, *wheel1, *wheel2;

	Droid();

	csX75::HNode* create_elem(std::vector <glm::vec4> v_positions, std::vector <glm::vec4> v_colors,std::vector <glm::vec4> v_normals,std::vector <glm::vec2> v_textures, GLuint tex, int elem);

	csX75::HNode* get_current(int elem);

	csX75::HNode* get_root();
};