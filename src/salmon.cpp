// Header
#include "salmon.hpp"

// internal
#include "turtle.hpp"
#include "fish.hpp"

// stlib
#include <string>
#include <algorithm>

bool Salmon::init()
{
	m_vertices.clear();
	m_indices.clear();

	// Reads the salmon mesh from a file, which contains a list of vertices and indices
	FILE *mesh_file = fopen(mesh_path("salmon.mesh"), "r");
	if (mesh_file == nullptr)
		return false;

	// Reading vertices and colors
	size_t num_vertices;
	fscanf(mesh_file, "%zu\n", &num_vertices);
	for (size_t i = 0; i < num_vertices; ++i)
	{
		float x, y, z;
		float _u[3]; // unused
		int r, g, b;
		fscanf(mesh_file, "%f %f %f %f %f %f %d %d %d\n", &x, &y, &z, _u, _u + 1, _u + 2, &r, &g, &b);
		Vertex vertex;
		vertex.position = {x, y, -z};
		vertex.color = {(float)r / 255, (float)g / 255, (float)b / 255};
		m_vertices.push_back(vertex);
	}

	// Reading associated indices
	size_t num_indices;
	fscanf(mesh_file, "%zu\n", &num_indices);
	for (size_t i = 0; i < num_indices; ++i)
	{
		int idx[3];
		fscanf(mesh_file, "%d %d %d\n", idx, idx + 1, idx + 2);
		m_indices.push_back((uint16_t)idx[0]);
		m_indices.push_back((uint16_t)idx[1]);
		m_indices.push_back((uint16_t)idx[2]);
	}

	// Done reading
	fclose(mesh_file);

	// Clearing errors
	gl_flush_errors();

	// Vertex Buffer creation
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	// Index Buffer creation
	glGenBuffers(1, &mesh.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Vertex Array (Container for Vertex + Index buffer)
	glGenVertexArrays(1, &mesh.vao);
	if (gl_has_errors())
		return false;

	// Loading shaders
	if (!effect.load_from_file(shader_path("salmon.vs.glsl"), shader_path("salmon.fs.glsl")))
		return false;

	// Setting initial values
	motion.position = {50.f, 100.f};
	motion.radians = 0.f;
	motion.speed = 200.f;

	physics.scale = {-35.f, 35.f};

	m_is_alive = true;
	m_light_up_countdown_ms = -1.f;

	m_color_change = 0.0;
	m_direction_change = 0.0;

	// Bound
	m_bound_up = false;
	m_bound_down = false;
	m_bound_left = false;
	m_bound_right = false;

	return true;
}

// Releases all graphics resources
void Salmon::destroy()
{
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ibo);
	glDeleteBuffers(1, &mesh.vao);

	glDeleteShader(effect.vertex);
	glDeleteShader(effect.fragment);
	glDeleteShader(effect.program);
}

// Called on each frame by World::update()
void Salmon::update(float ms)
{
	float step = motion.speed * (ms / 1000);
	if (m_is_alive)
	{
		if (m_moving_right && !m_bound_right) move({ step, 0.f });
		if (m_moving_left && !m_bound_left) move({ -step, 0.f });
		if (m_moving_up && !m_bound_up) move({ 0.f, -step });
		if (m_moving_down && !m_bound_down) move({ 0.f, step });
	}
	else
	{
		// If dead we make it face upwards and sink deep down
		//set_rotation(-1.5708f);
		move({600.0f, 650.0f});
	}

	if (m_light_up_countdown_ms > 0.f)
		m_light_up_countdown_ms -= ms;
}

void Salmon::draw(const mat3 &projection)
{
	transform.begin();

	// Initial salmon position and rotation
	//transform.translate({600.0f, 650.0f});
	//transform.rotate(-1.5708f);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// SALMON TRANSFORMATION CODE HERE

	// see Transformations and Rendering in the specification pdf
	// the following functions are available:
	// translate()
	// rotate()
	// scale()
	transform.translate(get_position());
	transform.rotate(motion.radians);
	transform.scale(physics.scale);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// REMOVE THE FOLLOWING LINES BEFORE ADDING ANY TRANSFORMATION CODE
	// transform.translate({ 100.0f, 100.0f });
	// transform.scale(physics.scale);
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	transform.end();

	// Setting shaders
	glUseProgram(effect.program);

	// Enabling alpha channel for textures
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	// depth is 0.00001

	// Getting uniform locations
	GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
	GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
	GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
	GLint light_up_uloc = glGetUniformLocation(effect.program, "light_up");
	GLint color_change_uloc = glGetUniformLocation(effect.program, "color_change");
	GLint direction_change_uloc = glGetUniformLocation(effect.program, "direction_change");

	// Setting vertices and indices
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	// Input data location as in the vertex buffer
	GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
	GLint in_color_loc = glGetAttribLocation(effect.program, "in_color");
	glEnableVertexAttribArray(in_position_loc);
	glEnableVertexAttribArray(in_color_loc);
	glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glVertexAttribPointer(in_color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));

	// Setting uniform values to the currently bound program
	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *)&transform.out);

	// !!! Salmon Color
	float color[] = {1.f, 1.f, 1.f};
	glUniform3fv(color_uloc, 1, color);
	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *)&projection);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// HERE TO SET THE CORRECTLY LIGHT UP THE SALMON IF HE HAS EATEN RECENTLY
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int light_up = 0;
	glUniform1iv(light_up_uloc, 1, &light_up);

	float color_change = get_color_change();
	glUniform1f(color_change_uloc, color_change);

	float direction_change = get_direction_change();
	glUniform1f(direction_change_uloc, direction_change);
	// Get number of infices from buffer,
	// we know our vbo contains both colour and position information, so...
	GLint size = 0;
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	GLsizei num_indices = size / sizeof(uint16_t);

	// Drawing!
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, nullptr);
}

// Simple bounding box collision check
// This is a SUPER APPROXIMATE check that puts a circle around the bounding boxes and sees
// if the center point of either object is inside the other's bounding-box-circle. You don't
// need to try to use this technique.
bool Salmon::collides_with(const Turtle &turtle)
{
	float dx = motion.position.x - turtle.get_position().x;
	float dy = motion.position.y - turtle.get_position().y;
	float d_sq = dx * dx + dy * dy;
	float other_r = std::max(turtle.get_bounding_box().x, turtle.get_bounding_box().y);
	float my_r = std::max(physics.scale.x, physics.scale.y);
	float r = std::max(other_r, my_r);
	r *= 0.6f;
	if (d_sq < r * r)
		return true;
	return false;
}

bool Salmon::collides_with(const Fish &fish)
{
	float dx = motion.position.x - fish.get_position().x;
	float dy = motion.position.y - fish.get_position().y;
	float d_sq = dx * dx + dy * dy;
	float other_r = std::max(fish.get_bounding_box().x, fish.get_bounding_box().y);
	float my_r = std::max(physics.scale.x, physics.scale.y);
	float r = std::max(other_r, my_r);
	r *= 0.6f;
	if (d_sq < r * r)
		return true;
	return false;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// HANDLE SALMON - WALL COLLISIONS HERE
// DON'T WORRY ABOUT THIS UNTIL ASSIGNMENT 2
// You will want to write new functions from scratch for checking/handling
// salmon - wall collisions.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

vec2 Salmon::get_position() const
{
	return motion.position;
}

void Salmon::move(vec2 off)
{
	motion.position.x += off.x;
	motion.position.y += off.y;
}

void Salmon::set_rotation(float radians)
{
	motion.radians = radians;
}

// Bound
void Salmon::set_bound(char direction, bool state)
{
	switch (direction) {
		case 'R':
			m_bound_right = state;
			break;
		case 'L':
		  m_bound_left = state;
			break;
		case 'U':
		  m_bound_up = state;
			break;
		case 'D':
		  m_bound_down = state;
			break;
		default:
			break;
	}
}

void Salmon::set_direction(char direction, bool value)
{
	if (direction == 'R')
	{
		m_moving_right = value;
	}
	else if (direction == 'L')
	{
		m_moving_left = value;
	}
	else if (direction == 'U')
	{
		m_moving_up = value;
	}
	else if (direction == 'D')
	{
		m_moving_down = value;
	}
}

float Salmon::get_direction_change()
{
	return m_direction_change;
}
void Salmon::change_direction(float c)
{
	m_direction_change = c;
}

bool Salmon::is_alive() const
{
	return m_is_alive;
}

// Called when the salmon collides with a turtle
void Salmon::kill()
{
	m_is_alive = false;
}

// Called when the salmon collides with a fish
void Salmon::light_up()
{
	m_light_up_countdown_ms = 1500.f;
}

void Salmon::change_color(float c)
{
	m_color_change = c;
}

float Salmon::get_color_change()
{
	return m_color_change;
}

void Salmon::set_mode(bool value)
{
	m_default_mode = value;
}

bool Salmon::get_mode()
{
	return m_default_mode;
}