#include "leds.hpp"

void solid_handler(uint8_t* payload, uint8_t len){
    // parse parameters
	solid_params_t.color = get_u32(payload);
}

void gradient_handler(uint8_t* payload, uint8_t len){
    // parse parameters
    gradient_params_t.num = get_u8(payload);
    // for(; gradient_params_t.index < gradient_params_t.num; gradient_params_t.index++){
        // gradient_params_t.colors[gradient_params_t.index] = get_u32(payload + gradient_params_t.index + 1);
    // }

}

void fadeall(CRGB* leds) { 
    for(int i = 0; i < NUM_LEDS; i++) { 
        leds[i].nscale8(250);
    } 
}

void solid(CRGB* leds){
    for(int i = 0; i < NUM_LEDS; i++) { 
        leds[i] = solid_params_t.color;
    } 
}

void gradient(CRGB* leds){
	// uint16_t start = 0;
	// uint16_t len = int(NUM_LEDS/(state_t.c_index - 2));

	// for(int i = 0; i < state_t.c_index - 2; i++){
		// fill_gradient_RGB(leds, start, state_t.colors[i], \
			// start + len, state_t.colors[i+1]);
		// start = start + len;
	// }
}

void pride(CRGB* leds) 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;

  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV( hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;

    nblend( leds[pixelnumber], newcolor, 64);
  }
}

void cylon(CRGB* leds){
    static uint8_t hue = 0;
    static uint16_t iteration = 0;

	fadeall(leds);

	if(iteration < NUM_LEDS)
		leds[iteration] = CHSV(hue++, 255, 255);
	if(NUM_LEDS < iteration && iteration < (2*NUM_LEDS))
		leds[2*NUM_LEDS - iteration] = CHSV(hue++, 255, 255);

	if (iteration++ == (NUM_LEDS*2)){
		iteration = 0;
	}
}

