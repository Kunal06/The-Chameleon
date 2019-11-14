// header
#include "wanderer.hpp"

// stlib
#include <cmath>
#include <string> 
#include <iostream>

// CONSTANTS
const int CHASE_REFRESH_MS = 5000;

// texture
Texture Wanderer::wanderer_texture;
using namespace std;

bool Wanderer::init(vector<vec2> path, Map& map, Char& player)
{
	// Pathing AI init
	m_map = &map;
	m_player = &player;
	m_path = path;
	set_position(m_map->get_tile_center_coords(m_path[0]));
	current_goal_index = 1;
	current_immediate_goal_index = 1;
	calculate_immediate_path(m_path[current_goal_index], 0);

	// load shared texture
	if (!wanderer_texture.is_valid())
	{

		if (!wanderer_texture.load_from_file(textures_path("wanderers/1.png")))
		{
			fprintf(stderr, "Failed to load wanderer texture!\n");
			return false;
		}
	}

	// the position corresponds to the center of the texture
	float wr = wanderer_texture.width * 0.5f;
	float hr = wanderer_texture.height * 0.5f;

	TexturedVertex vertices[4];
	vertices[0].position = { -wr, +hr, -0.00f };
	vertices[0].texcoord = { 0.f, 1.f};
	vertices[1].position = { +wr, +hr, -0.00f };
	vertices[1].texcoord = { 1.f, 1.f };
	vertices[2].position = { +wr, -hr, -0.00f };
	vertices[2].texcoord = { 1.f, 0.f };
	vertices[3].position = { -wr, -hr, -0.00f };
	vertices[3].texcoord = { 0.f, 0.f };

	// counterclockwise as it's the default opengl front winding direction
	uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };

	// clear errors
	gl_flush_errors();

	// vertex buffer creation
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_DYNAMIC_DRAW);

	// index buffer creation
	glGenBuffers(1, &mesh.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_DYNAMIC_DRAW);

	// vertex array (container for vertex + index buffer)
	glGenVertexArrays(1, &mesh.vao);
	if (gl_has_errors())
		return false;

	// load shaders
	if (!effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl")))
		return false;

	//motion.radians = 0.f;
	motion.speed = config_speed;
	physics.scale = { config_scale, config_scale };

	// TO REMOVE - placeholder for randomize path wall collision
	m_wall_up = false;
	m_wall_down = false;
	m_wall_left = false;
	m_wall_right = false;

	return true;
}

// release all graphics resources
void Wanderer::destroy()
{
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ibo);
	glDeleteVertexArrays(1, &mesh.vao);

	effect.release();
}

void Wanderer::update(float ms)
{
	if (!m_player->is_alive())
	{
		return;
	}
	if (alert_mode) {
		chase_refresh_timer -= ms;
		if (check_goal_arrival(m_map->get_tile_center_coords(immediate_path[current_immediate_goal_index]))
		&& !check_goal_arrival(m_map->get_grid_coords(m_player->get_position())))
		{
			current_immediate_goal_index++;
		}
		if (chase_refresh_timer < 0 || current_immediate_goal_index == immediate_path.size())
		{
			chase_refresh_timer = CHASE_REFRESH_MS;
			calculate_immediate_path(m_map->get_grid_coords(m_player->get_position()), 10);
			current_immediate_goal_index = 0;
		}
	}
	else {
		if (check_goal_arrival(m_map->get_tile_center_coords(m_path[current_goal_index])))
		{
			current_goal_index = (current_goal_index + 1) % m_path.size();
			calculate_immediate_path(m_path[current_goal_index], 0);
			current_immediate_goal_index = 1;
		}
		else if (check_goal_arrival(m_map->get_tile_center_coords(immediate_path[current_immediate_goal_index])))
		{
			current_immediate_goal_index++;
		}
	}
	if (current_immediate_goal_index < immediate_path.size())
	{
		move_towards_goal(m_map->get_tile_center_coords(immediate_path[current_immediate_goal_index]), ms);
	}
	
	// sprite change
	if (sprite_countdown > 0.f)
		sprite_countdown -= ms;

	sprite_switch >= 5 ? sprite_switch = 1 : sprite_switch++;
}

void Wanderer::draw(const mat3& projection)
{
	// transformation
	transform.begin();
	transform.translate(motion.position);
	transform.scale(physics.scale);
	transform.end();

	// set shaders
	glUseProgram(effect.program);

	// enable alpha channel for textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // depth
	glDisable(GL_DEPTH_TEST);

	// get uniform locations for glUniform* calls
	GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
	GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
	GLint projection_uloc = glGetUniformLocation(effect.program, "projection");

	// set vertices and indices
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	// input data location as in the vertex buffer
	GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
	GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
	glEnableVertexAttribArray(in_position_loc);
	glEnableVertexAttribArray(in_texcoord_loc);
	glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
	glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));

	// enable and binding texture to slot 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wanderer_texture.id);

	// set uniform values to the currently bound program
	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)& transform.out);
	float color[] = { 1.f, 1.f, 1.f };
	glUniform3fv(color_uloc, 1, color);
	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)& projection);

	if (sprite_countdown < 0) {
		string temp_str = "data/textures/wanderers/" + to_string(sprite_switch) + ".png";
		string s(PROJECT_SOURCE_DIR);
		s += temp_str;
		const char* path = s.c_str();

		wanderer_texture.~Texture();
		wanderer_texture.load_from_file(path);
		sprite_countdown = 200.f;
	}

	// draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

// movement
void Wanderer::set_position(vec2 position)
{
	motion.position = position;
}

vec2 Wanderer::get_position() const
{
	return motion.position;
}

// collision
void Wanderer::set_wall_collision(char direction, bool value)
{
	if (direction == 'R') m_wall_right = value;
	else if (direction == 'L') m_wall_left = value;
	else if (direction == 'U') m_wall_up = value;
	else if (direction == 'D') m_wall_down = value;
}

vec2 Wanderer::get_bounding_box() const
{
	return { std::fabs(physics.scale.x) * wanderer_texture.width * 0.5f, std::fabs(physics.scale.y) * wanderer_texture.height * 0.5f };
}

void Wanderer::alert_wanderer_status(bool alert) 
{
	if (alert_mode == false && alert == true)
	{
		alert_mode = true;
		calculate_immediate_path(m_map->get_grid_coords(m_player->get_position()), 10);
		current_immediate_goal_index = 1;
		chase_refresh_timer = CHASE_REFRESH_MS;
	}
	else if (alert_mode == true && alert == false)
	{
		alert_mode = false;
		set_position(m_map->get_tile_center_coords(m_path[0]));
		current_goal_index = 1;
		current_immediate_goal_index = 0;
		calculate_immediate_path(m_path[current_goal_index], 0);
	}
}


void Wanderer::calculate_immediate_path(vec2 goal, int limit_search)
{
	bool limit_set = limit_search != 0;
	if (!limit_set)
	{
		limit_search = 1;
	}

	immediate_path.clear();

	vec2 grid_position = m_map->get_grid_coords(motion.position);

	vector<path_construction> paths_in_progress;
	path_construction beginning;
	beginning.path = { {grid_position} };
	beginning.heuristic = abs(grid_position.x - goal.x) + abs(grid_position.y - goal.y);
	beginning.expected_total = beginning.heuristic;

	paths_in_progress.push_back(beginning);

	
	while (paths_in_progress[0].heuristic != 0 && limit_search > 0)
	{
		vector<path_construction> new_paths = find_paths_from(paths_in_progress[0], goal);
		paths_in_progress.erase(paths_in_progress.begin());
		paths_in_progress = merge_in_order(paths_in_progress, new_paths);

		if (limit_set)
		{
			limit_search--;
		}
	}

	immediate_path = paths_in_progress[0].path;
}

bool Wanderer::check_goal_arrival(vec2 goal)
{
	return fabs(goal.x - motion.position.x) < 5 && fabs(goal.y - motion.position.y) < 5;
}

void Wanderer::move_towards_goal(vec2 goal, float ms)
{
	float step = -1.0 * motion.speed * (ms / 1000);
	vec2 motionVector = { motion.position.x - goal.x, motion.position.y - goal.y };
	float magnitude = std::sqrt((motionVector.x * motionVector.x) + (motionVector.y * motionVector.y));
	motion.position.y += step * (motionVector.y / magnitude);
	motion.position.x += step * (motionVector.x / magnitude);
}

vector<path_construction> Wanderer::find_paths_from(path_construction origin, vec2 goal)
{
	vec2 point_of_origin = origin.path[origin.path.size() - 1];
	vector<path_construction> return_list;
	for (int x = 1; x > -2; x--)
	{
		for (int y = 1; y > -2; y--)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}

			if (x != 0 && y != 0) // is diagonal from origin
			{
				if (!tile_is_accessible(point_of_origin, x, y))
				{
					continue;
				}
			}

			path_construction new_path;
			new_path.path = origin.path;
			vec2 new_point = { point_of_origin.x + x, point_of_origin.y + y };
			if (m_map->is_wall(new_point))
			{
				continue;
			}

			new_path.path.push_back(new_point);
			new_path.heuristic = abs(new_point.x - goal.x) + abs(new_point.y - goal.y);
			new_path.expected_total = new_path.heuristic + origin.path.size();
			
			if (return_list.empty())
			{
				return_list.insert(return_list.begin(), new_path);
			}
			else
			{
				int insertion_index = 0;
				for (path_construction construction : return_list)
				{
					if (construction.expected_total > new_path.expected_total)
					{
						break;
					}
					else
					{
						insertion_index++;
					}
				}
				return_list.insert(return_list.begin() + insertion_index, new_path);
			}
		}
	}
	return return_list;
}

vector<path_construction> Wanderer::merge_in_order(vector<path_construction> p1, vector<path_construction> p2)
{
	if (p1.empty())
	{
		return p2;
	}
	else if (p2.empty())
	{
		return p1;
	}
	int p1_index = 0;
	int p2_index = 0;
	vector<path_construction> return_list;

	for (int i = 0; i < p1.size() + p2.size(); i++)
	{
		if (p1_index == p1.size())
		{
			return_list.push_back(p2[p2_index++]);
		}
		else if (p2_index == p2.size())
		{
			return_list.push_back(p1[p1_index++]);
		}
		else if (p1[p1_index].expected_total < p2[p2_index].expected_total)
		{
			return_list.push_back(p1[p1_index++]);
		}
		else
		{
			return_list.push_back(p2[p2_index++]);
		}
	}
	return return_list;
}

bool Wanderer::tile_is_accessible(vec2 origin, int x_delta, int y_delta)
{
	return !m_map->is_wall({ origin.x, origin.y + y_delta }) && !m_map->is_wall({ origin.x + x_delta, origin.y });
}
