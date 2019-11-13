#pragma once

// internal
#include "common.hpp"
#include "char.hpp"

class Char;

// guard type 2 : spotter
class Spotter : public Entity
{
	// shared texture
	static Texture spotter_texture;

private:
	// config
	const float config_scale = 0.25;

	// animation
	int spotter_sprite_switch = 1;
	float spotter_sprite_countdown = 1500.f;

	// AI stuff
	float check_sgn(float value);
	float radius = 20.f;

public:
	bool init();
	void destroy();
	void update(float ms);
	void draw(const mat3& projection) override;
	bool collision_with(Char m_char);

	// movement
	void set_position(vec2 position);
	vec2 get_position() const;



	// collision
	vec2 get_bounding_box() const;

	bool alert_mode;

	vec2 direction = vec2({ 0, -1 });
	
	void reset_direction();
};