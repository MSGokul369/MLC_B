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
void ui_homescreen(int *);
/*!
 * @brief Calls UI home screen and displays current configuration during slave mode operation.
 *
 */
void ui_homescreen_slave(int *ui_current_values);
/*!
 * @brief Configures RGB code scheme
 *
 */
void ui_rgb_code_scheme(int curent_rgb_scheme_index);
/*!
 * @brief Configures color pattern parameters
 *
 */
void ui_configure_color_pattern(int *);
/**
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
void start_color_read(int *);
/*!
 * @brief Read end color data
 *
 */
void end_color_read(int *);
/*!
 * @brief read resolution data
 *
 */
void resolution_read(int *);

int up_down_count_read(void);
/*!
 * @brief Call UI and subsequent functions in Master mode.
 *
 */
void master_ui(int *);

/*!
 * @brief Call UI and subsequent functions in Slave mode
 *
 */
void slave_ui(void *pvParameters);

/*!
 * @brief Send Start and Stop commands along with configuration during inter-task communication to generate pattern
 *
 */
void start_stop(int *);

/*!
 * @brief Send Play and Pause commands along with configuration during inter-task communication to generate pattern
 *
 */
void play_pause(int *);

/*!
 * @brief Verification of configuration and displays warning for invalid configurations.
 *
 */
int validation_warning(int *);

/*!
 * @brief Displays arrow key for selection of menu in UI.
 *
 */
int arrow_key_navigate(char prompt[][30], int num_of_ops, int x_cor, int y_cor);

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
