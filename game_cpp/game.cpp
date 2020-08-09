#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player1_position_x = 80.f;
float player1_position_y = 0.f;
float player1_speed = 0.f;
float player1_acceleration = 0.f;
float player1_friction = 10.f;

float player2_position_x = 80.f;
float player2_position_y = 0.f;
float player2_speed = 0.f;
float player2_acceleration = 0.f;
float player2_friction = 10.f;

float player_halfsize_x = 2.5f;
float player_halfsize_y = 12.f;

float enemy_x = -80.0f;
float enemy_y = 0.f;
float enemy_speed = 50.f;

float ball_x = 0.f;
float ball_y = 0.f;
float ball_speed_x = 50.f;
float ball_speed_y = 20.f;

float ball_halfsize_x = 1.f;
float ball_halfsize_y = 1.f;

float arena_halfsize_x = 85.f;
float arena_halfsize_y = 45.f;

int player1_points = 0;
int player2_points = 0;

static void simulate_game(Input* input, float delta_time) {
	
	//clear previous frame
	clear_screen(0xff5500);

	//draw_arena
	draw_rect(0, 0, arena_halfsize_x, arena_halfsize_y, 0xffaa33);

	//control_player_acceleration
	player1_acceleration = 0.f;
	if (is_down(BUTTON_UP)) {
		player1_acceleration += 1000.f;
	}
	if (is_down(BUTTON_DOWN)) {
		player1_acceleration -= 1000.f;
	}
	//player_friction
	player1_acceleration -= player1_speed * player1_friction;

	//define player speed
	// s = so + vo * t + a * t2/2
	player1_position_y = player1_position_y + player1_speed * delta_time + player1_acceleration * delta_time * delta_time * .5f;
	// v = vo + a*t
	player1_speed = player1_speed + player1_acceleration * delta_time;

	//player_arena_collision
	if (player1_position_y + player_halfsize_y > arena_halfsize_y) {
		player1_position_y = arena_halfsize_y - player_halfsize_y;
		player1_speed *= -1;
	}
	if (player1_position_y - player_halfsize_y < -arena_halfsize_y) {
		player1_position_y = -arena_halfsize_y + player_halfsize_y;
		player1_speed *= -1;
	}


	//PLAYER_2
	player2_acceleration = 0.f;
	if (is_down(BUTTON_W)) {
		player2_acceleration += 1000.f;
	}
	if (is_down(BUTTON_S)) {
		player2_acceleration -= 1000.f;
	}
	//player_friction
	player2_acceleration -= player2_speed * player2_friction;

	//define player speed
	// s = so + vo * t + a * t2/2
	player2_position_y = player2_position_y + player2_speed * delta_time + player2_acceleration * delta_time * delta_time * .5f;
	// v = vo + a*t
	player2_speed = player2_speed + player2_acceleration * delta_time;
	//player_arena_collision
	if (player2_position_y + player_halfsize_y > arena_halfsize_y) {
		player2_position_y = arena_halfsize_y - player_halfsize_y;
		player2_speed *= -1;
	}
	if (player2_position_y - player_halfsize_y < -arena_halfsize_y) {
		player2_position_y = -arena_halfsize_y + player_halfsize_y;
		player2_speed *= -1;
	}

	//move_ball

	
	ball_x += ball_speed_x * delta_time;
	ball_y += ball_speed_y * delta_time;

	//collide_ball_wth_arena
	if (ball_y + ball_halfsize_y > arena_halfsize_y) {
		ball_y = arena_halfsize_y - ball_halfsize_y;
		ball_speed_y *= -1;
	}
	if (ball_y - ball_halfsize_y < -arena_halfsize_y) {
		ball_y = -arena_halfsize_y + ball_halfsize_y;
		ball_speed_y *= -1;
	}

	//collide_ball_with_players
	if (ball_x + ball_halfsize_x >= 80 - player_halfsize_x 
		&& ball_x - ball_halfsize_x <= 80 + player_halfsize_x) {
		if (ball_y + ball_halfsize_y <= player1_position_y + player_halfsize_y
			&& ball_y - ball_halfsize_y >= player1_position_y - player_halfsize_y) {
			ball_x = 80 - player_halfsize_x - ball_halfsize_x;
			ball_speed_x *= -1;
			ball_speed_y = (ball_y - player1_position_y)*2 + player1_speed * .75f;
		}
	}
	if (ball_x - ball_halfsize_x < -80 + player_halfsize_x
		&& ball_x - ball_halfsize_x <= 80 + player_halfsize_x) {
		if (ball_y + ball_halfsize_y <= player2_position_y + player_halfsize_y
			&& ball_y - ball_halfsize_y >= player2_position_y - player_halfsize_y) {
			ball_x = -80 + ball_halfsize_x + player_halfsize_x;
			ball_speed_x *= -1;
			ball_speed_y = (ball_y - player2_position_y)*2 + player2_speed * 0.75f;
		}
	}

	//collise_ball_with_back_wall
	if (ball_x + ball_halfsize_x >= arena_halfsize_x) {
		player2_points++;
		ball_x = 0;
		ball_y = 0;
	}
	if (ball_x - ball_halfsize_x <= -arena_halfsize_x) {
		player1_points++;
		ball_x = 0;
		ball_y = 0;
	}

	//render_ball
	draw_rect(ball_x, ball_y, ball_halfsize_x, ball_halfsize_y, 0xffffff);

	//render_player
	draw_rect(80, player1_position_y, player_halfsize_x, player_halfsize_y, 0xff0000);

	//render_enemy
	draw_rect(-80, player2_position_y, player_halfsize_x, player_halfsize_y, 0xff0000);

	for (int i = 0; i < player1_points; i++) {
		draw_rect(80 - (i*5), arena_halfsize_y + ball_halfsize_y, 1, 1, 0xffff44);
	}

	for (int i = 0; i < player2_points; i++) {
		draw_rect(-80 + (i*5), arena_halfsize_y + ball_halfsize_y, 1, 1, 0xffff44);
	}
}
