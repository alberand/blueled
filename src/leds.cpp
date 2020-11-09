#include "leds.hpp"
#include "common.hpp"

static struct animation_state animation_t;

void animation_state_reset()
{
    animation_t.iteration = 0;
}

void animation_state_update(CRGB* leds, uint16_t num_leds,
                            const struct animation_config* config)
{
    if(config != NULL) {
        config->leds_update(leds, num_leds, config);
    }

    animation_t.iteration++;
}

void fadeall(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    for(uint16_t i = 0; i < num_leds; i++) {
        leds[i].nscale8(250);
    }
}

void fadeinout(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    const CRGB color = config->params[0];

    animation_t.iteration++;
    if(animation_t.iteration < 128) {
        fadeall(leds, num_leds, config);
    } else if(animation_t.iteration < 256) {
        for(uint16_t i = 0; i < num_leds; i++) {
            leds[i].red = color.red * (animation_t.iteration - 127)/127;
            leds[i].green = color.green * (animation_t.iteration - 127)/127;
            leds[i].blue = color.blue * (animation_t.iteration - 127)/127;
        }
    } else {
        animation_t.iteration = 0;
    }
}

void solid(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    const CRGB color = config->params[0];
    uint16_t offset = 0;
    if(config->params[1] != 0){
        offset = config->params[1];
    }

    uint16_t num = num_leds;
    if(config->params[2] != 0){
        num = config->params[2];
    }

    for( int i = 0; i < num; ++i) {
        leds[offset + i] = color;
    }
}

void gradient(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    uint16_t start = 0;
    uint16_t len = int(num_leds/(config->params[0] - 1));

    for(int i = 1; i < config->params[0]; i++) {
        fill_gradient_RGB(leds, start, config->params[i], \
                          start + len, config->params[i + 1]);
        start = start + len;
    }
}

void rainbow(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
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

    for( uint16_t i = 0 ; i < num_leds; i++) {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;

        brightnesstheta16  += brightnessthetainc16;
        uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        CRGB newcolor = CHSV( hue8, sat8, bri8);

        uint16_t pixelnumber = i;
        pixelnumber = (num_leds-1) - pixelnumber;

        nblend( leds[pixelnumber], newcolor, 64);
    }
}

void cylon(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    static uint8_t hue = 0;

    fadeall(leds, num_leds, config);

    if (animation_t.iteration == (num_leds*2))
        animation_t.iteration = 0;
    if(animation_t.iteration < num_leds)
        leds[animation_t.iteration] = CHSV(hue++, 255, 255);
    if(num_leds < animation_t.iteration && animation_t.iteration < (2*num_leds))
        leds[2*num_leds - animation_t.iteration] = CHSV(hue++, 255, 255);
}

static void drawRainbowDashes(CRGB* leds, uint16_t num_leds,
                              uint8_t startpos, uint16_t lastpos,
                              uint8_t period, uint8_t width,
                              uint8_t huestart, uint8_t huedelta,
                              uint8_t saturation, uint8_t value)
{
    uint8_t hue = huestart;
    for( uint16_t i = startpos; i <= lastpos; i += period) {
        CRGB color = CHSV( hue, saturation, value);

        // draw one dash
        uint16_t pos = i;
        for( uint8_t w = 0; w < width; w++) {
            leds[ pos ] = color;
            pos++;
            if( pos >= num_leds) {
                break;
            }
        }

        hue += huedelta;
    }
}

void stroboscopeWorker(CRGB* leds, uint16_t num_leds,
                       uint8_t dashperiod,
                       uint8_t dashwidth,
                       int8_t  dashmotionspeed,
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
    drawRainbowDashes( leds, num_leds, sStartPosition, num_leds-1,
                       dashperiod, dashwidth,
                       sStartHue, huedelta,
                       kSaturation, kValue);
}

void stroboscope(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    // First, we black out all the LEDs
    fill_solid( leds, num_leds, CRGB::Black);

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
        uint8_t zoomBPM = 122;
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
        stroboscopeWorker(leds, num_leds, dashperiod, dashwidth,
                          dashmotionspeed, strobesPerPosition, hueShift);
    }
}

void confetti(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    static uint16_t hue = 0;
    fadeToBlackBy( leds, num_leds, 10);
    int pos = random16(num_leds);
    leds[pos] += CHSV( hue++ + random8(64), 200, 255);
}

void sinelon(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    static uint16_t hue = 0;
    fadeToBlackBy( leds, num_leds, 20);
    int pos = beatsin16( 13, 0, num_leds-1 );
    leds[pos] += CHSV( hue++, 255, 192);
}

void bpm(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    static uint16_t hue = 0;
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    for(uint16_t i = 0; i < num_leds; i++) {
        hue++;
        leds[i] = ColorFromPalette(palette, hue +(i*2), beat-hue +(i*10));
    }
}

void juggle(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    fadeToBlackBy( leds, num_leds, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
        leds[beatsin16( i+7, 0, num_leds-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void twinkle(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    if(animation_t.iteration == 400) {
        animation_t.iteration = 0;
    }

    if(animation_t.iteration == 100) {
        animation_t.iteration = 0;
        leds[random(num_leds)] = config->params[0];
    } else {
        fadeall(leds, num_leds, config);
    }
}

void snowsparkle(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    static const CRGB base_color = config->params[0];
    static const CRGB sparkle_color = config->params[1];

    if(animation_t.iteration == 130) {
        animation_t.iteration = 0;
    }

    if(animation_t.iteration == 100) {
        leds[random(num_leds)] = base_color;
    }

    if(animation_t.iteration == 115) {
        for(uint16_t i = 0; i < num_leds; i++) {
            leds[i] = sparkle_color;
        }
    }
}

void train(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    const CRGB color = config->params[0];

    if(animation_t.iteration >= (num_leds*2)) {
        animation_t.iteration  = 0;
    }

    uint16_t position = animation_t.iteration;

    for(uint16_t i = 0; i < num_leds; i++) {
        const uint8_t R = ((sin(i + position) * 127 + 128)/255)*color.red;
        const uint8_t G = ((sin(i + position) * 127 + 128)/255)*color.green;
        const uint8_t B = ((sin(i + position) * 127 + 128)/255)*color.blue;
        leds[i] = CRGB(R, G, B);
    }
}

void color_wipe(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    const CRGB color = config->params[0];

    uint32_t led_idx = 0;
    uint32_t period = num_leds*4;

    if(animation_t.iteration%4 == 0) {
        led_idx = (animation_t.iteration/4)%num_leds;
    } else {
        return;
    }

    if(POSITION_IN_FIRST_HALF((animation_t.iteration/4)%period, period)) {
        leds[led_idx] = color;
    }

    if(POSITION_IN_SECOND_HALF((animation_t.iteration/4)%period, period)) {
        leds[led_idx] = 0;
    }
}

void rainbow_classic(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    uint16_t i;
    static byte c[3];

    if(animation_t.iteration >= (256*5)) {
        animation_t.iteration  = 0;
    }

    for(i=0; i< num_leds; i++) {
        byte pos = ((i * 256 / num_leds) + animation_t.iteration) & 255;

        if(pos < 85) {
            c[0]=pos * 3;
            c[1]=255 - pos * 3;
            c[2]=0;
        } else if(pos < 170) {
            pos -= 85;
            c[0]=255 - pos * 3;
            c[1]=0;
            c[2]=pos * 3;
        } else {
            pos -= 170;
            c[0]=0;
            c[1]=pos * 3;
            c[2]=255 - pos * 3;
        }

        leds[i] = CRGB(c[0], c[1], c[2]);
    }
}

void theater_chase(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    const uint8_t step = (uint8_t)config->params[0];
    const CRGB color_on = config->params[1];
    const CRGB color_off = config->params[2];

    if(animation_t.iteration == step) {
        animation_t.iteration = 0;
    }

    for (uint32_t i = 0; i < num_leds; i++) {
        if(i%step == animation_t.iteration) {
            leds[i] = color_on;
        } else {
            leds[i] = color_off;
        }
    }
}

void fire(CRGB* leds, uint16_t num_leds, const struct animation_config* config)
{
    const uint32_t cooling = 55;
    const uint32_t sparking = 120;
    static byte heat[10];
    uint32_t cooldown = 0;

    if(num_leds > 10)
        num_leds = 10;

    // Step 1.  Cool down every cell a little
    for( uint32_t i = 0; i < num_leds; i++) {
        cooldown = random(0, ((cooling * 10) / num_leds) + 2);

        if(cooldown > heat[i]) {
            heat[i] = 0;
        } else {
            heat[i] = heat[i] - cooldown;
        }
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k = num_leds - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if( (uint32_t)random(255) < sparking ) {
        int y = random(7);
        heat[y] = heat[y] + random(160,255);
        //heat[y] = random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for( uint32_t j = 0; j < num_leds; j++) {

        byte temperature = heat[j];
        // Scale 'heat' down from 0-255 to 0-191
        byte t192 = round((temperature/255.0)*191);

        // calculate ramp up from
        byte heatramp = t192 & 0x3F; // 0..63
        heatramp <<= 2; // scale up to 0..252

        // figure out which third of the spectrum we're in:
        if( t192 > 0x80) {                     // hottest
            leds[j] = CRGB(255, 255, heatramp);
        } else if( t192 > 0x40 ) {             // middle
            leds[j] = CRGB(255, heatramp, 0);
        } else {                               // coolest
            leds[j] = CRGB(0, heatramp, 0);
        }
    }

}
