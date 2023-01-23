/**
 * @file
 * @brief
 *
 *
 *
 * @note
 *
 * Revision History:
 * 	-060123 MSG : Creation Date
 */

/*******************************************************************************
 * Functions
 ******************************************************************************/

void boot_screen(void);
/*!
 * @brief Calls UI home screen and displays current configuration during master mode operation.
 *
 */
void ui_homescreen(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3], int up_down_count, int process_status);
/*!
 * @brief Calls UI home screen and displays current configuration during slave mode operation.
 *
 */
void ui_homescreen_slave(int *configuration_array);
/*!
 * @brief Configures RGB code scheme
 *
 */

int slave_current_colour(int *configuration_array);

void ui_rgb_code_scheme(int curent_rgb_scheme_index);
/*!
 * @brief Configures color pattern parameters
 *
 */
void ui_configure_color_pattern(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3], int up_down_count);
/*!
 * @brief Calls mode selection home screen
 *
 */
void ui_modes(int current_mode_index, int up_down_count);
/*!
 * @brief Set delay
 *
 */
void ui_delay(int delay);
/*!
 * @brief Read color change read data
 *
 */
int color_change_rate_read();
/*!
 * @brief Read refresh rate data
 *
 */
int refresh_rate_read();
/*!
 * @brief Read start color data
 *
 */
int *start_color_read();
/*!
 * @brief Read end color data
 *
 */
int *end_color_read();
/*!
 * @brief read resolution data
 *
 */
int *resolution_read();

int up_down_count_read(void);
/*!
 * @brief Call UI and subsequent functions in Master mode.
 *
 */
void master_ui(int *configuration_array);

/*!
 * @brief Call UI and subsequent functions in Slave mode
 *
 */
void slave_ui(void *pvParameters);

/*!
 * @brief Send Start and Stop commands along with configuration during inter-task communication to generate pattern
 *
 */
int start_stop(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3],
		int up_down_count, int process_status);

/*!
 * @brief Send Play and Pause commands along with configuration during inter-task communication to generate pattern
 *
 */
int play_pause(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3],
		int up_down_count, int process_status);

/*!
 * @brief Verification of configuration and displays warning for invalid configurations.
 *
 */
int validation_warning(int led_refresh_rate, int start_color[3], int end_color[3],
		int color_change_rate, int current_mode_index, int resolution[3]);

/*!
 * @brief Displays arrow key for selection of menu in UI.
 *
 */
int arrow_key_navigate(char prompt[][30], int num_of_ops, int x_cor, int y_cor);

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
