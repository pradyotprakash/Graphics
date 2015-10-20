#include "starwars.hpp"
#include "texture.hpp"
#define PI 3.1415926

class Starwars{
public:
	GLuint shaderProgram1, shaderProgram2;

	glm::mat4 rotation_matrix;
	glm::mat4 projection_matrix;
	glm::mat4 c_rotation_matrix;
	glm::mat4 lookat_matrix;

	glm::mat4 model_matrix;
	glm::mat4 view_matrix;

	glm::mat4 modelview_matrix;
	glm::mat3 normal_matrix;

	std::vector<GLuint> vao_array, vbo_array;
	std::vector<int> num_vertices;
	std::vector<glm::vec2> t_coords;
	bool flag;
	GLfloat depth;

	Starwars(){
		humanoid = new Humanoid();
		droid = new Droid();
		camera = new Camera();

		t_coords.push_back(glm::vec2( 0.0, 0.0));
		t_coords.push_back(glm::vec2( 0.0, 1.0));
		t_coords.push_back(glm::vec2( 1.0, 0.0));
		t_coords.push_back(glm::vec2( 1.0, 1.0));

		flag = false;
		depth = 0.0f;
	}

	void make_pyramid(GLfloat xr, GLfloat yr, GLfloat zr, GLfloat height, GLfloat width, std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors, std::vector<glm::vec4> &v_normals, glm::vec4 object_color ){
		float x = depth;//15.0f;
		std::vector<glm::vec4> positions;
		
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(xr), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(yr), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(zr), glm::vec3(0.0f,0.0f,1.0f));

		positions.push_back(rotation*glm::vec4(0.0, -height, 0.0-x, 1.0));
		positions.push_back(rotation*glm::vec4(width/2, 0.0, width/2-x, 1.0));
		positions.push_back(rotation*glm::vec4(width/2, 0.0, -width/2-x, 1.0));
		positions.push_back(rotation*glm::vec4(-width/2, 0.0, width/2-x, 1.0));
		positions.push_back(rotation*glm::vec4(-width/2, 0.0, -width/2-x, 1.0));

		//RGBA colors
		v_positions.clear();
		
		v_positions.push_back(positions[0]);
		v_normals.push_back(positions[0]);		
		v_positions.push_back(positions[2]);
		v_normals.push_back(positions[2]);
		v_positions.push_back(positions[1]);
		v_normals.push_back(positions[1]);

		v_positions.push_back(positions[0]);
		v_normals.push_back(positions[0]);
		v_positions.push_back(positions[1]);
		v_normals.push_back(positions[1]);
		v_positions.push_back(positions[3]);
		v_normals.push_back(positions[3]);

		v_positions.push_back(positions[0]);
		v_normals.push_back(positions[0]);
		v_positions.push_back(positions[3]);
		v_normals.push_back(positions[3]);
		v_positions.push_back(positions[4]);
		v_normals.push_back(positions[4]);

		v_positions.push_back(positions[0]);
		v_normals.push_back(positions[0]);
		v_positions.push_back(positions[4]);
		v_normals.push_back(positions[4]);
		v_positions.push_back(positions[2]);
		v_normals.push_back(positions[2]);

		v_positions.push_back(positions[3]);
		v_normals.push_back(positions[3]);
		v_positions.push_back(positions[1]);
		v_normals.push_back(positions[1]);
		v_positions.push_back(positions[2]);
		v_normals.push_back(positions[2]);

		v_positions.push_back(positions[3]);
		v_normals.push_back(positions[3]);
		v_positions.push_back(positions[2]);
		v_normals.push_back(positions[2]);
		v_positions.push_back(positions[4]);
		v_normals.push_back(positions[4]);

		v_colors.clear();
		for (int i = 0; i < v_positions.size(); ++i)
		{	
			v_colors.push_back(object_color);
			/* code */
		}
	}

	void make_triangle(float height, float width, float angle, std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors,std::vector<glm::vec4> &v_normals, glm::vec4 object_color){
		angle = angle*PI/180;
		float x = depth;//15.0f;
		v_positions.clear();
		v_positions.push_back(glm::vec4(width/2,0, 0.0-x, 1.0));
		v_normals.push_back(glm::vec4(width/2,0, 0.0-x, 1.0));
		v_positions.push_back(glm::vec4(height*cos(angle),height*sin(angle), 0.0-x, 1.0));
		v_normals.push_back(glm::vec4(height*cos(angle),height*sin(angle), 0.0-x, 1.0));
		v_positions.push_back(glm::vec4(-width/2,0, 0.0-x, 1.0));		
		v_normals.push_back(glm::vec4(-width/2,0, 0.0-x, 1.0));		

		v_colors.clear();
		for (int i = 0; i < v_positions.size(); ++i)
		{	
			v_colors.push_back(object_color);
			/* code */
		}
	}

	void draw_cylinder(float length, float radius, float radius1, int numSteps,std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors, std::vector<glm::vec4> &v_normals,glm::vec4 object_color) {
 		float hl = length;
 		float a = 0.0f;
 		float step = 2.0f * PI / (float)numSteps;
		float z = 0.0;
		float x = depth;//15.0f;
		v_positions.clear();

	 	for (int i = 0; i < numSteps; ++i)
		{
	 		float x1 = cosf(a) * radius;
	 		float y1 = sinf(a) * radius;
			float x2 = cosf(a) * radius1;
			float y2 = sinf(a) * radius1;
			float next_x1 = cosf(a + step)*radius;
			float next_y1 = sinf(a + step)*radius;
			float next_x2 = cosf(a + step)*radius1;
			float next_y2 = sinf(a + step)*radius1;
	 		v_positions.push_back(glm::vec4(x2, y2, hl-x, 1.0));
	 		v_normals.push_back(glm::vec4(x2, y2, hl-x, 1.0));
	 		v_positions.push_back(glm::vec4(x1, y1, 0.0-x, 1.0));
	 		v_normals.push_back(glm::vec4(x1, y1, 0.0-x, 1.0));
			v_positions.push_back(glm::vec4(next_x2,next_y2, hl-x, 1.0));
			v_normals.push_back(glm::vec4(next_x2,next_y2, hl-x, 1.0));
			v_positions.push_back(glm::vec4(next_x2, next_y2, hl-x, 1.0));
			v_normals.push_back(glm::vec4(next_x2, next_y2, hl-x, 1.0));
			v_positions.push_back(glm::vec4(next_x1, next_y1, 0-x, 1.0));
			v_normals.push_back(glm::vec4(next_x1, next_y1, 0-x, 1.0));
			v_positions.push_back(glm::vec4(x1, y1, 0-x, 1.0));
			v_normals.push_back(glm::vec4(x1, y1, 0-x, 1.0));
	 		a += step;
		}
		
		v_colors.clear();
		for (int i = 0; i < v_positions.size(); ++i)
		{	
			v_colors.push_back(object_color);
			/* code */
		}
	}

void DrawCircle(float cx, float cy, float cz, float r1, float r2, float c1, float c2, float c3, int num_segments,std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors, std::vector<glm::vec4> &v_normals){
		//glBegin(GL_LINE_LOOP); 
		 	for (int ii = 0; ii < num_segments; ii++)
		 	{
		 		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
				float theta1 = 2.0f * 3.1415926f * float(ii+1) / float(num_segments);//get the current angle 


		 		float x1 = r1 * cosf(theta);//calculate the x component 
				float y1 = r1 * sinf(theta);//calculate the y component 
				float x2 = r2 * cosf(theta);//calculate the x component 
				float y2 = r2 * sinf(theta);//calculate the y component
				float next_x1 = r1 * cosf(theta1);
				float next_y1 = r1 * sinf(theta1);
				float next_x2 = r2 * cosf(theta1);
				float next_y2 = r2 * sinf(theta1);
				
				v_positions.push_back(glm::vec4(x1+cx, y1+cy, cz, 1.0));//output vertex 
		 		v_normals.push_back(glm::vec4(x1+cx, y1+cy, cz, 1.0));//output vertex 
		 		v_colors.push_back(glm::vec4(c1, c2, c3, 1.0));
		 		v_positions.push_back(glm::vec4(x2 + cx, y2 + cy, cz, 1.0));//output vertex 
		 		v_normals.push_back(glm::vec4(x2 + cx, y2 + cy, cz, 1.0));//output vertex 
		 		v_colors.push_back(glm::vec4(c1, c2, c3, 1.0));
				v_positions.push_back(glm::vec4(next_x2 + cx, next_y2 + cy, cz, 1.0));//output vertex 
				v_normals.push_back(glm::vec4(next_x2 + cx, next_y2 + cy, cz, 1.0));//output vertex 
				v_colors.push_back(glm::vec4(c1, c2, c3, 1.0));
				v_positions.push_back(glm::vec4(next_x2 + cx, next_y2 + cy, cz, 1.0));//output vertex 
				v_normals.push_back(glm::vec4(next_x2 + cx, next_y2 + cy, cz, 1.0));//output vertex 
				v_colors.push_back(glm::vec4(c1, c2, c3, 1.0));
				v_positions.push_back(glm::vec4(next_x1 + cx, next_y1 + cy, cz, 1.0));//output vertex 
				v_normals.push_back(glm::vec4(next_x1 + cx, next_y1 + cy, cz, 1.0));//output vertex 
				v_colors.push_back(glm::vec4(c1, c2, c3, 1.0));
				v_positions.push_back(glm::vec4(x1 + cx, y1 + cy, cz, 1.0));//output vertex 
				v_normals.push_back(glm::vec4(x1 + cx, y1 + cy, cz, 1.0));//output vertex 
				v_colors.push_back(glm::vec4(c1, c2, c3, 1.0));
		 	}
	 	//glEnd(); 
}


	void create_humanoid(){

		std::vector<glm::vec4> v_positions, v_colors, v_normals;
		csX75::HNode* curr;
		
		// hip
		curr = humanoid->create_elem(v_positions, v_colors, v_normals, 1);

		// torso
		make_pyramid(0.0f, 0.0f, 0.0f, 3, 1, v_positions, v_colors, v_normals, glm::vec4(1,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, v_normals, 15);
		curr->change_parameters(0.0,1.0,0.0,0.0,0.0,0.0);

		// hip joint
		make_pyramid(0.0f, 0.0f, 0.0f, 0.1, 0.1, v_positions, v_colors, v_normals, glm::vec4(1,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, v_normals, 24);
		curr->change_parameters(0.0,-1.75,0.0,0.0,0.0,0.0);		
		
		// upper left leg
		make_pyramid(0.0f, 0.0f, -30.0f, 2.5, 0.8, v_positions, v_colors,v_normals, glm::vec4(0,1,0,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 8);
		curr->change_parameters(-0.43,0,0.0,0.0,0.0,0);

		// left knee
		make_pyramid(0.0f, 0.0f ,0.0f ,0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, v_normals,KNEE_LEFT);
		curr->change_parameters(-1.25,-2,0,0,0,0);

		// lower left leg
		make_pyramid(0,0,180,2, 0.7, v_positions, v_colors,v_normals, glm::vec4(0,0,1,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 10);
		curr->change_parameters(0,-1.9,0.0,0.0,0.0,0);

		// left leg foot
		make_triangle(1, 1, 90, v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 12);
		curr->change_parameters(0,0,0.5,90,0,0);

		// upper right leg
		make_pyramid(0.0f, 0.0f, 30.0f, 2.5, 0.8, v_positions, v_colors,v_normals, glm::vec4(0,1,0,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 9);
		curr->change_parameters(0.43,0,0.0,0.0,0.0,0);

		// right knee
		make_pyramid(0.0f, 0.0f ,0.0f ,0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, v_normals,KNEE_RIGHT);
		curr->change_parameters(1.25,-2,0,0,0,0);

		// lower right leg
		make_pyramid(0,0,180,2, 0.7, v_positions, v_colors,v_normals, glm::vec4(0,0,1,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 11);
		curr->change_parameters(0,-1.9,0.0,0.0,0.0,0);

		// right leg foot
		make_triangle(1, 1,90, v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, v_normals,13);
		curr->change_parameters(0,0,0.5,270,0,180);		

		// shoulder
		make_pyramid(0,0,0,0, 0, v_positions, v_colors,v_normals, glm::vec4(1,1,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 14);

		// neck
		make_pyramid(0,0,0,0, 0, v_positions, v_colors, v_normals,glm::vec4(1,1,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 16);

		// head
		make_pyramid(0,0,0,1, 1, v_positions, v_colors,v_normals, glm::vec4(0.7,0.2,0.4,1));
		curr = humanoid->create_elem(v_positions, v_colors, v_normals,17);
		curr->change_parameters(0,1,0,0,0,0);

		// left upper arm
		make_pyramid(0,0,-50,1.8, 0.7, v_positions, v_colors,v_normals, glm::vec4(1,0.2,0.4,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 2);
		curr->change_parameters(-0.5,0,0,0,0,0);

		// left elbow
		make_pyramid(0,0,0,0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, ELBOW_LEFT);
		curr->change_parameters(-1.3,-1.1,0,0,0,-126);

		// left lower arm
		make_pyramid(0,0,180,1.8, 0.5, v_positions, v_colors, v_normals,glm::vec4(0.3,0.8,0.7,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 4);
		curr->change_parameters(0,-1.8,0,0,0,0);

		// left  wrist
		make_triangle(0, 0.5, 45, v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 6);
		curr->change_parameters(0,0,0,0,0,0);		

		// right upper arm
		make_pyramid(0,0,50,1.8, 0.7, v_positions, v_colors,v_normals, glm::vec4(1,0.2,0.4,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 3);
		curr->change_parameters(0.5,0,0,0,0,0);

		// right elbow
		make_pyramid(0,0,0,0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, ELBOW_RIGHT);
		curr->change_parameters(1.3,-1.1,0,0,0,126);

		// right lower arm
		make_pyramid(0,0,180,1.8, 0.5, v_positions, v_colors, v_normals,glm::vec4(0.3,0.8,0.7,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 5);
		curr->change_parameters(0,-1.8,0,0,0,0);

		// right  wrist
		make_triangle(0, 0.5, 45,v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 7);
		curr->change_parameters(0,0,0,0,0,0);

		//left lightsaber
		draw_cylinder(3.7,0.1,0.1,300,v_positions,v_colors,v_normals,glm::vec4(0.7,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 18);
		curr->change_parameters(0,0.1,0,0,-90,0);

		//RIGHT lightsaber
		draw_cylinder(3.7,0.1,0.1,300,v_positions,v_colors,v_normals,glm::vec4(0.7,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors,v_normals, 19);
		curr->change_parameters(0,0.1,0,0,90,0);

		curr_node = humanoid->get_root();
	}

	void create_droid(){

		std::vector<glm::vec4> v_positions, v_colors, v_normals;
		csX75::HNode* curr;

		// torso
		draw_cylinder(3, 1, 1, 1000,v_positions, v_colors, v_normals, glm::vec4(1,0,0,1));
		DrawCircle(0.0,0.0,3.0,1,0,1,0,0,1000, v_positions,v_colors,v_normals);
		curr = droid->create_elem(v_positions, v_colors, v_normals, 15);
		curr->change_parameters(7.0,1.0,0.0,90,0.0,0.0);
		
		// // upper left leg
		 make_pyramid(-90,0,0,2, 0.5, v_positions, v_colors,v_normals, glm::vec4(0,1,0,1));
		 curr = droid->create_elem(v_positions, v_colors,v_normals, 8);
		 curr->change_parameters(-1.3,0,1.0,0,0.0,0);

		// // left knee
		 make_pyramid(0,0,0,0,0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		 curr = droid->create_elem(v_positions, v_colors, v_normals,KNEE_LEFT);
		 curr->change_parameters(0,0,2,0,0,0);

		// // lower left leg
		 make_pyramid(90,0,0,2, 0.75, v_positions, v_colors,v_normals, glm::vec4(0,0,1,1));
		 curr = droid->create_elem(v_positions, v_colors,v_normals, 10);
		 curr->change_parameters(0,0,1.8,0,0.0,0);

		// // upper right leg
		 make_pyramid(-90,0,0,2, 0.5, v_positions, v_colors, v_normals,glm::vec4(0,1,0,1));
		 curr = droid->create_elem(v_positions, v_colors,v_normals, 9);
		 curr->change_parameters(1.3,0,1.0,0,0.0,0);

		// // right knee
		 make_pyramid(0,0,0,0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		 curr = droid->create_elem(v_positions, v_colors, v_normals,KNEE_RIGHT);
		 curr->change_parameters(0,0,2,0,0,0);

		// // lower right leg
		 make_pyramid(90,0,0,2, 0.75, v_positions, v_colors, v_normals,glm::vec4(0,0,1,1));
		 curr = droid->create_elem(v_positions, v_colors,v_normals, 11);
		 curr->change_parameters(0,0,1.8,0,0.0,0);


		// // wheel 1
		 draw_cylinder(0.2, 0.3, 0.3, 1000,v_positions, v_colors, v_normals, glm::vec4(1,1,1,1));
		 DrawCircle(0.0,0.0,0.0,0.3,0,1,0,0,1000, v_positions,v_colors,v_normals);
		 curr = droid->create_elem(v_positions, v_colors,v_normals, 25);
		 curr->change_parameters(0,0,0.1,90,90,0);


		// // wheel 2
		 draw_cylinder(0.2, 0.3, 0.3, 1000,v_positions, v_colors, v_normals, glm::vec4(1,1,1,1));
		 DrawCircle(0.0,0.0,0.0,0.3,0,1,0,0,1000, v_positions,v_colors,v_normals);
		 curr = droid->create_elem(v_positions, v_colors,v_normals, 26);
		 curr->change_parameters(0,0,0.1,90,90,0);

		// // right leg foot
		// make_triangle(1, 1,90, v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors, v_normals,13);
		// curr->change_parameters(0,0,0.5,270,0,180);		

		// // shoulder
		// make_pyramid(0, 0, v_positions, v_colors,v_normals, glm::vec4(1,1,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 14);

		// // neck
		// make_pyramid(0, 0, v_positions, v_colors, v_normals,glm::vec4(1,1,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 16);

		// // head
		 draw_cylinder(1, 0.5,1,1000, v_positions, v_colors,v_normals, glm::vec4(0.7,0.2,0.4,1));
		 curr = droid->create_elem(v_positions, v_colors, v_normals,17);
		 curr->change_parameters(0.0,0,-1.1,0,0,0);

		// // left upper arm
		// make_pyramid(1.8, 0.7, v_positions, v_colors,v_normals, glm::vec4(1,0.2,0.4,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 2);
		// curr->change_parameters(-0.5,0,0,0,0,-50);

		// // left elbow
		// make_pyramid(0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, ELBOW_LEFT);
		// curr->change_parameters(0,-1.8,0,0,0,0);

		// // left lower arm
		// make_pyramid(1.8, 0.5, v_positions, v_colors, v_normals,glm::vec4(0.3,0.8,0.7,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 4);
		// curr->change_parameters(-1.55,-0.9,0,0,0,120);

		// // left  wrist
		// make_triangle(0.7, 0.5, 45,v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 6);
		// curr->change_parameters(0,0,0,0,0,0);		

		// // right upper arm
		// make_pyramid(1.8, 0.7, v_positions, v_colors, v_normals,glm::vec4(1,0.2,0.4,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 3);
		// curr->change_parameters(0.5,0,0,0,0,50);

		// // right elbow
		// make_pyramid(0, 0, v_positions, v_colors,v_normals, glm::vec4(0,0,0,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, ELBOW_RIGHT);
		// curr->change_parameters(0,-1.8,0,0,0,0);

		// // right lower arm
		// make_pyramid(1.8, 0.5, v_positions, v_colors,v_normals, glm::vec4(0.3,0.8,0.7,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 5);
		// curr->change_parameters(1.55,-0.9,0,0,0,-120);

		// // right  wrist
		// make_triangle(0.7, 0.5, 135,v_positions, v_colors,v_normals, glm::vec4(0.5,0.3,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 7);
		// curr->change_parameters(0,0,0,0,0,0);		

		// //left lightsaber
		// draw_cylinder(3.7,0.1,0.1,300,v_positions,v_colors,v_normals,glm::vec4(0.7,0.3,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 18);
		// curr->change_parameters(0,0.1,0,0,90,0);

		// //RIGHT lightsaber
		// draw_cylinder(3.7,0.1,0.1,300,v_positions,v_colors,v_normals,glm::vec4(0.7,0.3,0.2,1));
		// curr = humanoid->create_elem(v_positions, v_colors,v_normals, 19);
		// curr->change_parameters(0,0.1,0,0,-90,0);

		curr_node = droid->get_root();
	}


	void create_static_object(GLfloat *a_vertices){

		GLuint vao, vbo;
		glGenVertexArrays (1, &vao);
		glGenBuffers (1, &vbo);
		
		num_vertices.push_back(36);
		vao_array.push_back(vao);
		vbo_array.push_back(vbo);
		
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glBufferData (GL_ARRAY_BUFFER, 36*4*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, 36*4*sizeof(GLfloat), a_vertices);

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition1 );
		glVertexAttribPointer( vPosition1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	}

	void initBuffersGL(void)
	{
		{
			std::string vertex_shader_file("vshader1.glsl");
			std::string fragment_shader_file("fshader1.glsl");

			std::vector<GLuint> shaderList;
			shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
			shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

			shaderProgram1 = csX75::CreateProgramGL(shaderList);
			glUseProgram( shaderProgram1 );

			// getting the attributes from the shader program
			vPosition1 = glGetAttribLocation( shaderProgram1, "vPosition" );
			uModelViewMatrix1 = glGetUniformLocation( shaderProgram1, "uModelViewMatrix");
			light1 = glGetAttribLocation( shaderProgram1, "light1_on_o" );
			light2 = glGetAttribLocation( shaderProgram1, "light2_on_o" );

			GLfloat skyboxVertices[] = {
			  -100.0f,  100.0f, -100.0f, 1.0f,
			  -100.0f, -100.0f, -100.0f, 1.0f,
			   100.0f, -100.0f, -100.0f, 1.0f,
			   100.0f, -100.0f, -100.0f, 1.0f,
			   100.0f,  100.0f, -100.0f, 1.0f,
			  -100.0f,  100.0f, -100.0f, 1.0f,
			  
			  -100.0f, -100.0f,  100.0f, 1.0f,
			  -100.0f, -100.0f, -100.0f, 1.0f,
			  -100.0f,  100.0f, -100.0f, 1.0f,
			  -100.0f,  100.0f, -100.0f, 1.0f,
			  -100.0f,  100.0f,  100.0f, 1.0f,
			  -100.0f, -100.0f,  100.0f, 1.0f,
			  
			   100.0f, -100.0f, -100.0f, 1.0f,
			   100.0f, -100.0f,  100.0f, 1.0f,
			   100.0f,  100.0f,  100.0f, 1.0f,
			   100.0f,  100.0f,  100.0f, 1.0f,
			   100.0f,  100.0f, -100.0f, 1.0f,
			   100.0f, -100.0f, -100.0f, 1.0f,
			   
			  -100.0f, -100.0f,  100.0f, 1.0f,
			  -100.0f,  100.0f,  100.0f, 1.0f,
			   100.0f,  100.0f,  100.0f, 1.0f,
			   100.0f,  100.0f,  100.0f, 1.0f,
			   100.0f, -100.0f,  100.0f, 1.0f,
			  -100.0f, -100.0f,  100.0f, 1.0f,
			  
			  -100.0f,  100.0f, -100.0f, 1.0f,
			   100.0f,  100.0f, -100.0f, 1.0f,
			   100.0f,  100.0f,  100.0f, 1.0f,
			   100.0f,  100.0f,  100.0f, 1.0f,
			  -100.0f,  100.0f,  100.0f, 1.0f,
			  -100.0f,  100.0f, -100.0f, 1.0f,
			  
			  -100.0f, -100.0f, -100.0f, 1.0f,
			  -100.0f, -100.0f,  100.0f, 1.0f,
			   100.0f, -100.0f, -100.0f, 1.0f,
			   100.0f, -100.0f, -100.0f, 1.0f,
			  -100.0f, -100.0f,  100.0f, 1.0f,
			   100.0f, -100.0f,  100.0f, 1.0f
			};			
			create_static_object(skyboxVertices);
			std::vector<const char*> faces;
			// faces.push_back("images/arrakisday_right.bmp");
			// faces.push_back("images/arrakisday_left.bmp");
			// faces.push_back("images/arrakisday_bottom.bmp");
			// faces.push_back("images/arrakisday_top.bmp");
			// faces.push_back("images/arrakisday_back.bmp");
			// faces.push_back("images/arrakisday_front.bmp");

			faces.push_back("images/cube/right_texture.bmp");
			faces.push_back("images/cube/left_texture.bmp");
			faces.push_back("images/cube/bottom_texture.bmp");
			faces.push_back("images/cube/top_texture.bmp");
			faces.push_back("images/cube/far_texture.bmp");
			faces.push_back("images/cube/near_texture.bmp");

			GLuint cubemapTexture = LoadTexture(faces, 150, 150);
	  		glDepthMask(GL_FALSE);

			glBindVertexArray(vao_array[0]);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
		}	

		{
			std::string vertex_shader_file("vshader2.glsl");
			std::string fragment_shader_file("fshader2.glsl");

			std::vector<GLuint> shaderList;
			shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
			shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

			shaderProgram2 = csX75::CreateProgramGL(shaderList);
			glUseProgram( shaderProgram2 );

			// getting the attributes from the shader program
			vPosition2 = glGetAttribLocation( shaderProgram2, "vPosition" );
			vColor2 = glGetAttribLocation( shaderProgram2, "vColor" );
			vNormal2 = glGetAttribLocation( shaderProgram2, "vNormal" );
//			texCoord2 = glGetAttribLocation( shaderProgram, "texCoord" );
			uModelViewMatrix2 = glGetUniformLocation( shaderProgram2, "uModelViewMatrix");
			normalMatrix =  glGetUniformLocation( shaderProgram2, "normalMatrix");
			viewMatrix = glGetUniformLocation( shaderProgram2, "viewMatrix");
			
			//create_humanoid();
			create_droid();
		}
	}

	void draw_buffer(int i){
		glBindVertexArray(vao_array[i]);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices[i]);
	}

	void renderGL(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matrixStack.clear();

		lookat_matrix = camera->get_lookat_matrix();

		//creating the projection matrix
		if(enable_perspective){
			//projection_matrix = glm::frustum(-20.0, 20.0, -20.0, 20.0, 1.0, 5.0);
			projection_matrix = glm::infinitePerspective(360.0f, 1000.0f/750.0f, 0.01f);
		}
		else{
			projection_matrix = glm::ortho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
		}

		view_matrix = projection_matrix*lookat_matrix;
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(uModelViewMatrix2, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniform1i(light1, light1_on);
		glUniform1i(light2, light2_on);

		glUseProgram(shaderProgram2);
		matrixStack.push_back(view_matrix);
		matrixStack.push_back(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-depth)));
		droid->get_root()->render_tree(depth);

		glm::mat4 skybox_view_matrix = glm::mat4(glm::mat3(lookat_matrix));
		glUniformMatrix4fv(uModelViewMatrix1, 1, GL_FALSE, glm::value_ptr(projection_matrix*skybox_view_matrix));
		glUseProgram(shaderProgram1);
		for(int i=0;i<vao_array.size();++i){
			draw_buffer(i);
		}		
	}
};

int main(int argc, char** argv)
{
	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	//We want OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//This is for MacOSX - can be omitted otherwise
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(1000, 750, "Star Wars", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	//Turn this on to get Shader based OpenGL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cerr<<"GLEW Init Failed : %s"<<std::endl;
	}

	//Print and see what context got enabled
	std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
	std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
	std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
	std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
	csX75::initGL();
	Starwars *starwars = new Starwars();
	starwars->initBuffersGL();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{

		// Render here
		starwars->renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}