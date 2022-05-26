#include "buzzer.h"
#include "main.h"

#include "tim.h"

void Buzzer_Init (void) {
	HAL_TIM_OC_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Init(&htim2);
}

void Buzzer_Set_Freq (uint16_t freq) {
	TIM2->PSC = ((2 * HAL_RCC_GetPCLK1Freq()) / (2 * BUZZER_VOLUME_MAX * freq)) - 1;
}

void Buzzer_Set_Volume (uint16_t volume) {
	if (volume > BUZZER_VOLUME_MAX)
		volume = BUZZER_VOLUME_MAX;
	TIM2->CCR1 = volume;
}

void Buzzer_Play_Sound (uint32_t* sound, uint32_t* delays, uint16_t len) {
	for(int i = 0; i < len; i++) {
	  	if (sound[i] != 0) {
	  		Buzzer_Set_Freq(sound[i]);
	  		Buzzer_Set_Volume(BUZZER_VOLUME_MAX);
	  		HAL_Delay(1920/delays[i]/2);
	  		Buzzer_Set_Volume(BUZZER_VOLUME_MUTE);
	  	} else HAL_Delay(1920/delays[i]/2);
	  	HAL_Delay(10);
	}
}
