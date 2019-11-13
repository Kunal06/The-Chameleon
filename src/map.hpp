#pragma once

// internal
#include "char.hpp"
#include "common.hpp"
class Char;

// TO REMOVE - placeholder for randomize path wall collision
#include "wanderer.hpp"
class Wanderer;

class Map : public Entity
{
	// shared texture
	static Texture wall_texture;
	static Texture corridor_texture;
	static Texture wall_light_texture;

	static Texture corridor_texture_red;
	static Texture corridor_texture_blue;
	static Texture corridor_texture_green;
	static Texture corridor_texture_yellow;

private:
	vec2 translation_tile;
	float m_dead_time;
	float m_flash_time;
	int flash_map;
	char current_level[40][61];

public:
	bool init();
	void destroy();

	// draw tiles
	void draw(const mat3 &projection) override;
	void draw_element(const mat3 &projection, const Texture &texture);
	void set_position(vec2 position);
	vec2 get_position() const;

	// color detection
	int get_tile(Char character);

	// wall collision
	void check_wall(Char &ch, const float ms);
	
	// TO REMOVE - placeholder for randomize path wall collision
	void is_wall_collision(Wanderer &wanderer);

	// char dead time getters and setters .. ported over from water
	void set_char_dead();

	void reset_char_dead_time();

	float get_char_dead_time() const;

	void set_flash(int value);
	int get_flash();

	void reset_flash_time();

	float get_flash_time() const;

	void set_current_map(int level);
};