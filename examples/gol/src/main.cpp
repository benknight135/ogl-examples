// Include standard headers
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <functional>

// Include OpenGL headers
#ifdef WITH_GLAD2
    // Glad v2 beta uses different header name
	#include <glad/gl.h>
#else
	#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

// Include GOL headers
#include "window.h"
#include "camera.h"
#include "game.h"

typedef std::vector< std::vector<bool>> Matb;
typedef std::vector<bool> Rowb;

class RandomBool{
public:
	RandomBool(int seed = 0):
		generator(std::bind(std::uniform_int_distribution<>(0,6),std::default_random_engine(seed)))
	{
	}

	static int randomSeed(){
		return std::random_device{}();
	}

	bool gen(){
		return generator() == 0;
	}
private:
	std::_Binder<std::remove_cv<std::_Unforced>::type, std::uniform_int_distribution<>, std::default_random_engine> generator;
};

int main(void)
{
	int seed = abs(RandomBool::randomSeed());
	std::cout << "Seed: " << seed << std::endl;
	RandomBool rndBool(seed);

	// Create window 
	// also initalises OpenGL so must be at start of program
    Window* window = new Window(true);

	// Create camera
    Camera* camera = new Camera(0, 0, 10, 45.0f, window->getAspectRatio());

    // Setup Game of Life entities
    // Create grid of bool to signify alive/dead
	float e_size = 0.04f;
	bool display = true;
	int disp_grid_width = (int)(window->getWidth() * 0.2f);
	int disp_grid_height = (int)((1.0f/window->getAspectRatio())*disp_grid_width);

	int sim_grid_size;
	if (disp_grid_height > disp_grid_width){
		sim_grid_size = (int)(disp_grid_height * 1.2f);
	} else {
		sim_grid_size = (int)(disp_grid_width * 1.2f);
	}
	std::cout << "Simulation grid size: " << sim_grid_size << ", " << sim_grid_size << std::endl;
	std::cout << "Visible size: " << disp_grid_width << ", " << disp_grid_height << std::endl;

	int disp_grid_min_x = (int)((sim_grid_size - disp_grid_width) / 2.0f);
	int disp_grid_max_x = disp_grid_min_x + disp_grid_width;
	int disp_grid_min_y = (int)((sim_grid_size - disp_grid_height) / 2.0f);
	int disp_grid_max_y = disp_grid_min_y + disp_grid_height;
	Matb alive_mat;
	for(int i = 0; i < sim_grid_size; ++i)
	{
		Rowb row(sim_grid_size);
		for(int j = 0; j < sim_grid_size; ++j)
		{
			row[j] = rndBool.gen();
		}
		alive_mat.push_back(row); // push each row after being filled
	}
	// Create GL Triangle vector to display alive entities
	// Must be initalised after Window as entities require OpenGL to be ready
	std::vector<GLTriangle*> glEntities = std::vector<GLTriangle*>();
	if (display){
		for (int i = disp_grid_min_x; i < disp_grid_max_x; i++)
		{
			for (int j = disp_grid_min_y; j < disp_grid_max_y; j++)
			{
				if(alive_mat[i][j]){
					glEntities.push_back(new GLTriangle(
						e_size, (i-sim_grid_size/2.0f)*e_size, (j-sim_grid_size/2.0f)*e_size, 0.0f,
						1.0f, 0.0f, 1.0f, 1.0f
					));
				}
			}
		}
	}

	bool sw = true;
	float r = 0.0f;
	float b = 1.0f;
	do{
		if (sw){
			r = 0.0f;
			b = 1.0f;
		} else{
			r = 1.0f;
			b = 0.0f;
		}
		// for (std::vector<GLTriangle*>::iterator it = glEntities.begin() ; it != glEntities.end(); ++it){
		// 	GLTriangle* golEntity = *it;
		// 	golEntity->updateColor(r, 1.0f, b, 1.0f);
		// }
		// Clear window for new frame
		window->clear();
		
		// Update camera perpective
        camera->update();

		int golEntity_index = -1;
		// create copy of alive matrix to save over-written entities
		Matb tmp_alive_mat(alive_mat);
		for (int i = 0; i < sim_grid_size; i++)
		{
			for (int j = 0; j < sim_grid_size; j++)
			{
				if (tmp_alive_mat[i][j]){
					if ((i > disp_grid_min_x && j > disp_grid_min_y) && (i < disp_grid_max_x && j < disp_grid_max_y)){
						golEntity_index++;
					}
				}
				// Count alive neighbours
				int count_alive_neighbours = 0;
				int o_i = 0;
				int o_j = 0;
				for (int k = -1; k < 2; k++){
					for (int l = -1; l < 2; l++){
						// Ignore 0,0 offset (center)
						if (k != 0 || l != 0){
							// Check within grid
							o_i = i+k;
							o_j = j+l;
							if ((o_i > 0 && o_j > 0) && (o_i < sim_grid_size && o_j < sim_grid_size)){
								// Check state of neighbour
								if (tmp_alive_mat[o_i][o_j]){
									// Add 1 to count if neighbour alive
									count_alive_neighbours++;
								}
							}
						}
					}
				}
				if (tmp_alive_mat[i][j] && count_alive_neighbours == 2 || tmp_alive_mat[i][j] && count_alive_neighbours == 3){
					// Rule 1: Any live cell with two or three live neighbours survives.
					alive_mat[i][j] = true;
				} else if (!tmp_alive_mat[i][j] && count_alive_neighbours == 3){
					// Rule 2: Any dead cell with three live neighbours becomes a live cell.
					alive_mat[i][j] = true;
				} else {
					// Rule 3: All other live cells die in the next generation. Similarly, all other dead cells stay dead.
					alive_mat[i][j] = false;
				}
				if (tmp_alive_mat[i][j] != alive_mat[i][j]){
					if ((i > disp_grid_min_x && j > disp_grid_min_y) && (i < disp_grid_max_x && j < disp_grid_max_y)){
						//std::cout << "updating changed element..." << std::endl;
						if (alive_mat[i][j]){ // was dead, now alive so add
							// glEntities.push_back(new GLTriangle(
							// 	e_size, (i-grid_size/2.0f)*e_size, (j-grid_size/2.0f)*e_size
							// ));
						} else { // was alive, now dead so remove
							if (display){
								delete(glEntities.at(golEntity_index));
								glEntities.erase(glEntities.begin() + golEntity_index);
								golEntity_index--;
							}
						}
					}
				}
			}
		}

		// add alive
		if (display){
			for (int i = disp_grid_min_x; i < disp_grid_max_x; i++)
			{
				for (int j = disp_grid_min_y; j < disp_grid_max_y; j++)
				{
					if (tmp_alive_mat[i][j] != alive_mat[i][j]){
						if (alive_mat[i][j]){ // was dead, now alive so add
							glEntities.push_back(new GLTriangle(
								e_size, (i-sim_grid_size/2.0f)*e_size, (j-sim_grid_size/2.0f)*e_size, 0.0f,
								1.0f, 0.0f, 1.0f, 1.0f
							));
						}
					}
				}
			}
		}

		// Draw GOL entities
		for (std::vector<GLTriangle*>::iterator it = glEntities.begin() ; it != glEntities.end(); ++it){
			GLTriangle* golEntity = *it;
			golEntity->draw();
		}

		// Update window frame
		window->update();
		std::cout << "FPS: " << window->getFPS() << std::endl;
		//std::cout << "Size: " << glEntities.size() << std::endl;

		sw = !sw;
	} // Check if the ESC key was pressed or the window was closed
	while(window->isOpen());

    // Cleanup
	// (required to clean OpenGL objects in correct order)
	for (std::vector<GLTriangle*>::iterator it = glEntities.begin() ; it != glEntities.end(); ++it){
		GLTriangle* golEntity = *it;
		delete(golEntity);
	}
	delete(camera);
	// Calls 'glfwTerminate' so all OpenGL object should be cleaned
	// before removing the window
	delete(window);

    exit(EXIT_SUCCESS);
}