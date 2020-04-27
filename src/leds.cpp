#include "leds.hpp"

static struct animation_state {
	uint16_t iteration;
	uint16_t period;
} animation_state_t;

static struct solid_params {
    uint32_t color;
} solid_params_t;

static struct gradient_params {
    uint32_t colors[20];
    uint8_t index;
    uint8_t num;
} gradient_params_t;

void solid_handler(uint8_t* payload, uint8_t len) {
    // parse parameters
    solid_params_t.color = get_u32(payload);
}

void gradient_handler(uint8_t* payload, uint8_t len) {
    // parse parameters
    gradient_params_t.num = get_u8(payload);
    for(int i = 0; i < gradient_params_t.num; i++) {
        gradient_params_t.colors[i] = get_u32((payload + i*4 + 1));
        gradient_params_t.index = i;
    }

}

void fadeall(CRGB* leds) {
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i].nscale8(250);
    }
}

void fadeInOut(CRGB* leds){
    CRGB color = 0xe37d09;

	animation_state_t.iteration++;
	if(animation_state_t.iteration < 128){
		fadeall(leds);
	} else if(animation_state_t.iteration < 256) {
        for(int i = 0; i < NUM_LEDS; i++) {
 	    	leds[i].red = color.red * (animation_state_t.iteration - 127)/127;
 	    	leds[i].green = color.green * (animation_state_t.iteration - 127)/127;
 	    	leds[i].blue = color.blue * (animation_state_t.iteration - 127)/127;
        }
	} else {
		animation_state_t.iteration = 0;
	}
}

void solid(CRGB* leds) {
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = solid_params_t.color;
    }
}

void gradient(CRGB* leds) {
    uint16_t start = 0;
    uint16_t len = int(NUM_LEDS/(gradient_params_t.num - 1));

    for(int i = 0; i < gradient_params_t.num - 1; i++) {
        fill_gradient_RGB(leds, start, gradient_params_t.colors[i], \
                          start + len, gradient_params_t.colors[i+1]);
        start = start + len;
    }
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

void cylon(CRGB* leds) {
    static uint8_t hue = 0;

    fadeall(leds);

    if(animation_state_t.iteration < NUM_LEDS)
        leds[animation_state_t.iteration] = CHSV(hue++, 255, 255);
    if(NUM_LEDS < animation_state_t.iteration && animation_state_t.iteration < (2*NUM_LEDS))
        leds[2*NUM_LEDS - animation_state_t.iteration] = CHSV(hue++, 255, 255);

    if (animation_state_t.iteration++ == (NUM_LEDS*2)) {
        animation_state_t.iteration = 0;
    }
}





// drawRainbowDashes - draw rainbow-colored 'dashes' of light along the led strip:
//   starting from 'startpos', up to and including 'lastpos'
//   with a given 'period' and 'width'
//   starting from a given hue, which changes for each successive dash by a 'huedelta'
//   at a given saturation and value.
//
//   period = 5, width = 2 would be  _ _ _ X X _ _ _ Y Y _ _ _ Z Z _ _ _ A A _ _ _
//                                   \-------/       \-/
//                                   period 5      width 2
//
static void drawRainbowDashes(CRGB* leds,
                              uint8_t startpos, uint16_t lastpos, uint8_t period, uint8_t width,
                              uint8_t huestart, uint8_t huedelta, uint8_t saturation, uint8_t value)
{
    uint8_t hue = huestart;
    for( uint16_t i = startpos; i <= lastpos; i += period) {
        CRGB color = CHSV( hue, saturation, value);

        // draw one dash
        uint16_t pos = i;
        for( uint8_t w = 0; w < width; w++) {
            leds[ pos ] = color;
            pos++;
            if( pos >= NUM_LEDS) {
                break;
            }
        }

        hue += huedelta;
    }
}

// stroboscopeWorker updates the positions of the dashes, and calls the draw function
//
void stroboscopeWorker(CRGB* leds,
                       uint8_t dashperiod, uint8_t dashwidth, int8_t  dashmotionspeed,
                       uint8_t stroberepeats,
                       uint8_t huedelta)
{
    static uint8_t sRepeatCounter = 0;
    static int8_t sStartPosition = 0;
    static uint8_t sStartHue = 0;

    // Always keep the hue shifting a little
    sStartHue += 1;

    // Increment the strobe repeat counter, and
    // move the dash starting position when needed.
    sRepeatCounter = sRepeatCounter + 1;
    if( sRepeatCounter>= stroberepeats) {
        sRepeatCounter = 0;

        sStartPosition = sStartPosition + dashmotionspeed;

        // These adjustments take care of making sure that the
        // starting hue is adjusted to keep the apparent color of
        // each dash the same, even when the state position wraps around.
        if( sStartPosition >= dashperiod ) {
            while( sStartPosition >= dashperiod) {
                sStartPosition -= dashperiod;
            }
            sStartHue  -= huedelta;
        } else if( sStartPosition < 0) {
            while( sStartPosition < 0) {
                sStartPosition += dashperiod;
            }
            sStartHue  += huedelta;
        }
    }

    // draw dashes with full brightness (value), and somewhat
    // desaturated (whitened) so that the LEDs actually throw more light.
    const uint8_t kSaturation = 208;
    const uint8_t kValue = 255;

    // call the function that actually just draws the dashes now
    drawRainbowDashes( leds, sStartPosition, NUM_LEDS-1,
                       dashperiod, dashwidth,
                       sStartHue, huedelta,
                       kSaturation, kValue);
}

void stroboscope(CRGB* leds)
{
    // First, we black out all the LEDs
    fill_solid( leds, NUM_LEDS, CRGB::Black);

    // To achive the strobe effect, we actually only draw lit pixels
    // every Nth frame (e.g. every 4th frame).
    // sStrobePhase is a counter that runs from zero to kStrobeCycleLength-1,
    // and then resets to zero.
    const uint8_t kStrobeCycleLength = 4; // light every Nth frame
    static uint8_t sStrobePhase = 0;
    sStrobePhase = sStrobePhase + 1;
    if( sStrobePhase >= kStrobeCycleLength ) {
        sStrobePhase = 0;
    }

    // We only draw lit pixels when we're in strobe phase zero;
    // in all the other phases we leave the LEDs all black.
    if( sStrobePhase == 0 ) {

        // The dash spacing cycles from 4 to 9 and back, 8x/min (about every 7.5 sec)
        uint8_t dashperiod= beatsin8( 8/*cycles per minute*/, 4,10);
        // The width of the dashes is a fraction of the dashperiod, with a minimum of one pixel
        uint8_t dashwidth = (dashperiod / 4) + 1;

        // The distance that the dashes move each cycles varies
        // between 1 pixel/cycle and half-the-dashperiod/cycle.
        // At the maximum speed, it's impossible to visually distinguish
        // whether the dashes are moving left or right, and the code takes
        // advantage of that moment to reverse the direction of the dashes.
        // So it looks like they're speeding up faster and faster to the
        // right, and then they start slowing down, but as they do it becomes
        // visible that they're no longer moving right; they've been
        // moving left.  Easier to see than t o explain.
        //
        // The dashes zoom back and forth at a speed that 'goes well' with
        // most dance music, a little faster than 120 Beats Per Minute.  You
        // can adjust this for faster or slower 'zooming' back and forth.
        uint8_t zoomBPM = ZOOMING_BEATS_PER_MINUTE;
        int8_t  dashmotionspeed = beatsin8( (zoomBPM /2), 1,dashperiod);
        // This is where we reverse the direction under cover of high speed
        // visual aliasing.
        if( dashmotionspeed >= (dashperiod/2)) {
            dashmotionspeed = 0 - (dashperiod - dashmotionspeed );
        }


        // The hueShift controls how much the hue of each dash varies from
        // the adjacent dash.  If hueShift is zero, all the dashes are the
        // same color. If hueShift is 128, alterating dashes will be two
        // different colors.  And if hueShift is range of 10..40, the
        // dashes will make rainbows.
        // Initially, I just had hueShift cycle from 0..130 using beatsin8.
        // It looked great with very low values, and with high values, but
        // a bit 'busy' in the middle, which I didnt like.
        //   uint8_t hueShift = beatsin8(2,0,130);
        //
        // So instead I layered in a bunch of 'cubic easings'
        // (see http://easings.net/#easeInOutCubic )
        // so that the resultant wave cycle spends a great deal of time
        // "at the bottom" (solid color dashes), and at the top ("two
        // color stripes"), and makes quick transitions between them.
        uint8_t cycle = beat8(2); // two cycles per minute
        uint8_t easedcycle = ease8InOutCubic( ease8InOutCubic( cycle));
        uint8_t wavecycle = cubicwave8( easedcycle);
        uint8_t hueShift = scale8( wavecycle,130);


        // Each frame of the animation can be repeated multiple times.
        // This slows down the apparent motion, and gives a more static
        // strobe effect.  After experimentation, I set the default to 1.
        uint8_t strobesPerPosition = 1; // try 1..4


        // Now that all the parameters for this frame are calculated,
        // we call the 'worker' function that does the next part of the work.
        stroboscopeWorker(leds,  dashperiod, dashwidth, dashmotionspeed, strobesPerPosition, hueShift);
    }
}

void confetti(CRGB* leds)
{
// random colored speckles that blink in and fade smoothly
    static uint16_t hue = 0;
    fadeToBlackBy( leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV( hue++ + random8(64), 200, 255);
}

void sinelon(CRGB* leds)
{
// a colored dot sweeping back and forth, with fading trails
    static uint16_t hue = 0;
    fadeToBlackBy( leds, NUM_LEDS, 20);
    int pos = beatsin16( 13, 0, NUM_LEDS-1 );
    leds[pos] += CHSV( hue++, 255, 192);
}

void bpm(CRGB* leds)
{
// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    static uint16_t hue = 0;
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    for( int i = 0; i < NUM_LEDS; i++) { //9948
        hue++;
        leds[i] = ColorFromPalette(palette, hue +(i*2), beat-hue +(i*10));
    }
}

void juggle(CRGB* leds) {
// eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
        leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void twinkle(CRGB* leds, uint16_t step) {
	animation_state_t.iteration++;
	if(animation_state_t.iteration*step == 500){
		animation_state_t.iteration = 0;
    	leds[random(NUM_LEDS)] = solid_params_t.color;
	} else {
		fadeall(leds);
	}

	if(animation_state_t.iteration*25 == 2000){
		animation_state_t.iteration = 0;
	}
}

void snowSparkle(CRGB* leds) {
	animation_state_t.iteration++;

	if(animation_state_t.iteration*25 == 1500){
  		leds[random(NUM_LEDS)] = CRGB(0xff, 0xff, 0xff);
	}

	if(animation_state_t.iteration*25 == 1900){
    	for(int i = 0; i < NUM_LEDS; i++) {
        	leds[i] = 0x101010;
    	}
	}

	if(animation_state_t.iteration*25 == 2000){
		animation_state_t.iteration = 0;
	}
}
