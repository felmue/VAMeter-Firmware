/*
* SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
*
* SPDX-License-Identifier: MIT
*/
#include "../hal_vameter.h"
#include "../hal_config.h"
#include <mooncake.h>
#include <driver/gpio.h>

void HAL_VAMeter::_gamepad_init()
{
    spdlog::info("gamepad init");

    // Side button
    gpio_reset_pin((gpio_num_t)HAL_PIN_SIDE_BTN);
    gpio_set_direction((gpio_num_t)HAL_PIN_SIDE_BTN, GPIO_MODE_INPUT);

    // Encoder button
    gpio_reset_pin((gpio_num_t)HAL_PIN_ENCODER_S);
    gpio_set_direction((gpio_num_t)HAL_PIN_ENCODER_S, GPIO_MODE_INPUT);
}

static bool _side_button_state = false;
static bool _encoder_button_state = false;

bool HAL_VAMeter::getButton(GAMEPAD::GamePadButton_t button)
{
    // Side button
    if (button == GAMEPAD::BTN_B)
    {
        if (!gpio_get_level((gpio_num_t)HAL_PIN_SIDE_BTN))
        {
            // If just pressed
            if (!_side_button_state)
            {
                _side_button_state = true;
                beep(600, 20);
            }
            return true;
        }
        // If just released
        if (_side_button_state)
        {
            _side_button_state = false;
            beep(800, 20);
        }
    }

    // Encoder button
    if (button == GAMEPAD::BTN_A)
    {
        if (!gpio_get_level((gpio_num_t)HAL_PIN_ENCODER_S))
        {
            // If just pressed
            if (!_encoder_button_state)
            {
                _encoder_button_state = true;
                beep(600, 20);
            }
            return true;
        }
        // If just released
        if (_encoder_button_state)
        {
            _encoder_button_state = false;
            beep(800, 20);
        }
    }

    return false;
}
