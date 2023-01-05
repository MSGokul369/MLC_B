void ui_homescreen(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]);
void ui_homescreen_slave();
void ui_rgb_code_scheme(int curent_rgb_scheme_index);
void ui_configure_colour_pattern(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]);
void ui_modes(int current_mode_index);
void ui_delay(int delay);

int colour_change_rate_read();
int refresh_rate_read();

int *start_colour_read();
int *end_colour_read();
int *resolution_read();

void master_ui(void);
void slave_ui(void);

void start_stop(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]);
void play_pause(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]);
int validation_warning(int led_refresh_rate, int start_colour[3], int end_colour[3],
		int colour_change_rate, int current_mode_index, int resolution[3]);

int arrow_key_navigate(char prompt[][30], int num_of_ops, int x_cor, int y_cor);

