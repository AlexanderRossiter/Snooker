#include "PhysicsEngine.h"

void PhysicsEngine::set_selected_ball(Ball& ball) {
	selected_ball = &ball;
}

void PhysicsEngine::deselect_ball() {
	selected_ball = nullptr;
}

void PhysicsEngine::update() {
	colliding_pairs.clear();
	calculate_wall_collisions();
	calculate_static_collisions();
	calculate_dynamic_collisions();

	integrate_accelerations();

}

void PhysicsEngine::set_extents(float _xmin, float _xmax, float _ymin, float _ymax) {
	xmin = _xmin;
	xmax = _xmax;
	ymin = _ymin;
	ymax = _ymax;
}

void PhysicsEngine::integrate_accelerations() {
	for (Ball& b : balls) {
		// Friction
		b.ax += -0.1f * b.vx;
		b.ay += -0.1f * b.vy;

		b.vx = b.vx + b.ax * delta_t;
		b.vy = b.vy + b.ay * delta_t;

		b.x = b.x + b.vx * delta_t;
		b.y = b.y + b.vy * delta_t;

		b.ax = 0;
		b.ay = 0;
	}
}

void PhysicsEngine::add_ball(float x, float y, float r) {
	balls.push_back(Ball(x, y, r));
	balls.back().id = balls.size()-1;
}

void PhysicsEngine::display(sf::RenderWindow &app) {
	for (Ball& b : balls) {
		b.draw(app);
	}
}

bool PhysicsEngine::ball_selected() {
	return selected_ball != nullptr;
}

Ball PhysicsEngine::get_selected_ball() {
	return *selected_ball;
}

void PhysicsEngine::calculate_static_collisions() {
	// Loop through all balls
	for (Ball& b1 : balls) {
		for (Ball& b2 : balls) {
			if (b1.id != b2.id) {
				if (balls_collided(b1, b2)) {
					// Store the coliding pairs
					colliding_pairs.push_back(std::vector<Ball*> {&b1, &b2});

					// Calculate the collision
					float dx = b1.x - b2.x;
					float dy = b1.y - b2.y;
					float dist = std::sqrt(dx * dx + dy * dy);

					float mv_dist = (dist - (b1.r + b2.r))/2.f;

					b1.x -= mv_dist * dx / dist;
					b1.y -= mv_dist * dy / dist;

					b2.x += mv_dist * dx / dist;
					b2.y += mv_dist * dy / dist;
				}
			}
		}
	}
}

void PhysicsEngine::calculate_dynamic_collisions() {
	for (std::vector<Ball*> pair : colliding_pairs) {
		Ball* b1 = pair[0];
		Ball* b2 = pair[1];

		float mag;

		// Normal vector
		float nx = b1->x - b2->x;
		float ny = b1->y - b2->y;
		mag = std::sqrt(nx * nx + ny * ny);
		nx = nx / mag;
		ny = ny / mag;

		// Tangent vector
		float tx = -ny;
		float ty = nx;
		mag = std::sqrt(tx * tx + ty * ty);
		tx = tx / mag;
		ty = ty / mag;

		// Velocity doesn't change in the tangential direction.
		float v_tang_1 = b1->vx * tx + b1->vy * ty;
		float v_tang_2 = b2->vx * tx + b2->vy * ty;

		// Normal velocity from 1D elastic collisions.
		float u1 = b1->vx * nx + b1->vy * ny;
		float u2 = b2->vx * nx + b2->vy * ny;
		float v_norm_1 = u1 * (b1->mass - b2->mass) / (b1->mass + b2->mass) + 2.f * b2->mass * u2 / (b1->mass + b2->mass);
		float v_norm_2 = u2 * (b2->mass - b1->mass) / (b1->mass + b2->mass) + 2.f * b1->mass * u1 / (b1->mass + b2->mass);

		// Update the cartesian velocities.
		b1->vx = v_tang_1 * tx +v_norm_1 * nx;
		b1->vy = v_tang_1 * ty +v_norm_1 * ny;
		b2->vx = v_tang_2 * tx +v_norm_2 * nx;
		b2->vy = v_tang_2 * ty +v_norm_2 * ny;


	}
}

void PhysicsEngine::apply_force_to_ball(Ball& b, float fx, float fy) {
	b.ax += fx / b.mass;
	b.ay += fy / b.mass;
}

void PhysicsEngine::calculate_wall_collisions() {
	for (Ball& b : balls) {
		if (x_value_in_ball(b, xmin)) { b.vx = -b.vx; }
		if (x_value_in_ball(b, xmax)) { b.vx = -b.vx; }
		if (y_value_in_ball(b, ymin)) { b.vy = -b.vy; }
		if (y_value_in_ball(b, ymax)) { b.vy = -b.vy; }
	}
}

bool PhysicsEngine::balls_collided(Ball& b1, Ball& b2) {
	return ((b1.x - b2.x) * (b1.x - b2.x) + (b1.y - b2.y) * (b1.y - b2.y)) <= (b1.r + b2.r) * (b1.r + b2.r);
}

bool PhysicsEngine::x_value_in_ball(Ball& b, float xv) {
	return xv >= b.x - b.r && xv <= b.x + b.r;
}

bool PhysicsEngine::y_value_in_ball(Ball& b, float yv) {
	return yv >= b.y - b.r && yv <= b.y + b.r;
}