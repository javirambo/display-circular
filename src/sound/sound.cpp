#include <Arduino.h>
#include "risa.h"
#include "pwm_audio.h"

const int LEFT_CHANNEL_GPIO = GPIO_NUM_47;  // Pin de salida del altavoz

void PlaySound()
{
    static bool iniciado = false;

    pwm_audio_config_t pac;
    pac.duty_resolution    = LEDC_TIMER_10_BIT;
    pac.gpio_num_left      = LEFT_CHANNEL_GPIO;
    pac.ledc_channel_left  = LEDC_CHANNEL_0;
    pac.gpio_num_right     = -1;
    pac.ledc_channel_right = LEDC_CHANNEL_1;
    pac.ledc_timer_sel     = LEDC_TIMER_0;
    pac.tg_num             = TIMER_GROUP_0;
    pac.timer_num          = TIMER_0;
    pac.ringbuf_len        = 1024 * 8;

    if (!iniciado)
    {
        pwm_audio_init(&pac);
        pwm_audio_set_param(44100, 16, 1);
        pwm_audio_set_volume(16);
        iniciado = true;
    }
    pwm_audio_start();
    Serial.println("play");

    uint32_t index = 0;
    size_t cnt;
    uint32_t block_w = 2048;
    size_t wave_size = sizeof(RISA);

    while (1)
    {
        if (index < wave_size)
        {
            if ((wave_size - index) < block_w)
            {
                block_w = wave_size - index;
            }

            pwm_audio_write((uint8_t *)RISA + index, block_w, &cnt, 5000 / portTICK_PERIOD_MS);
            Serial.println("write");
            index += cnt;
        }
        else
        {
            pwm_audio_stop();
            Serial.println("stop");
            return;
        }

        vTaskDelay(6 / portTICK_PERIOD_MS);
    }
}
