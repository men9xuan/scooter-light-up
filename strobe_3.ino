// Strobe settings
#define STB_PIN_LIGHT 10 // Pin number for strobe light output
#define STB_BLINK_INTERVAL 2000000 // Blink interval for strobe light in microseconds

//  adesettings
#define FADE_PIN_LIGHT 5 // Pin number for fade light output
#define FADE_MIN 0 // Minimum fade level for beacon (0-255)
#define FADE_MAX 255 // Maximum fade level for beacon (0-255)
#define FADE_INTERVAL 4000 // Fade step interval, in microseconds (lower numbers = faster fade)

// Var declarations
unsigned long lastFadeTime = 0;
unsigned long lastStrobeTime = 0;
int currentFade = ACB_FADE_MIN;
int fadeDirection = 1;
void setup()
{
  // Declare output pins
//  pinMode(LL_PIN_LIGHT, OUTPUT);
  pinMode(STB_PIN_LIGHT, OUTPUT);
//  pinMode(STB_PIN_LIGHTB, OUTPUT);
  pinMode(FADE_PIN_LIGHT, OUTPUT);
//  pinMode(ACB2_PIN_LIGHT, OUTPUT);
  
}


// Called continuouly
void loop()
{
  unsigned long currentTime = micros();
 
  // Check if it's time to fade the anti-collision lights
  if ((currentTime - lastFadeTime) > FADE_INTERVAL) {
    doFade();
    lastFadeTime = currentTime;
  }

  // Check if it's time to blink the strobes
  if ((currentTime - lastStrobeTime) > STB_BLINK_INTERVAL) {
    doStrobe();
    lastStrobeTime = currentTime; 
  }
}


// Fade 
void doFade()
{
  currentFade += fadeDirection;
  if (currentFade == FADE_MAX || currentFade == FADE_MIN) {
    // If we hit the fade limit, flash the high beacon, and flip the fade direction
    if (fadeDirection == 1) {
      analogWrite(FADE_PIN_LIGHT, 255);
    }

//    } else {
//      analogWrite(ACB2_PIN_LIGHT, 255);
//    }
    delay(50); 
    fadeDirection *= -1; 
  }
  analogWrite(FADE_PIN_LIGHT, currentFade);
//  analogWrite(FADE_PIN_LIGHT, FADE_MAX - currentFade + FADE_MIN);
}

// Strobe
void doStrobe()
{
  digitalWrite(STB_PIN_LIGHT, HIGH);
//  digitalWrite(STB_PIN_LIGHTB, HIGH);
  delay(50);
  digitalWrite(STB_PIN_LIGHT, LOW);
//  digitalWrite(STB_PIN_LIGHTB, LOW);
  delay(50);
  digitalWrite(STB_PIN_LIGHT, HIGH);
//  digitalWrite(STB_PIN_LIGHTB, HIGH);
  delay(50);
  digitalWrite(STB_PIN_LIGHT, LOW);
//  digitalWrite(STB_PIN_LIGHTB, LOW);
}
