#include <Adafruit_NeoPixel.h>


int numPixels = 60;
int LEDstate = 0;

const int buttonInPin = 7;
const int motionInPin = 5;

int buttonState = 0;
int previousButtonState = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, 2, NEO_GRB + NEO_KHZ800);

long nightFadeOnTime = 0;
long nightFadeDuration = 30000;
int nightFadeState = 0;

void setup() {

  Serial.begin(9600);

  pinMode(buttonInPin, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //sweepOn();
  //delay(500);
  //sweepOff();
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState = digitalRead(buttonInPin);
  digitalWrite(13, buttonState);
  if (buttonState != previousButtonState)
  {

    Serial.println(buttonState);

    if (LEDstate)
    {
      sweepOff();
      //sweepOn();
//      digitalWrite(13, LOW);
      LEDstate = 0;

    } else
    {
      //sweepOff();
      sweepOn();
//      digitalWrite(13, HIGH);
      LEDstate = 1;
    }
    buttonState = digitalRead(buttonInPin);

    previousButtonState = buttonState;
  }

  if(digitalRead(motionInPin))
  {
    if(nightFadeState)
    {
      nightFadeOnTime = millis();
    }else
    {
      nightFadeState = 1;
      nightFadeOn();
      nightFadeOnTime = millis();
    }
      
  }

  if(nightFadeState)
  {
    if(millis() - nightFadeOnTime > nightFadeDuration)
    {
      nightFadeOff();
      nightFadeState = 0;
    }
  }

  delay(20);
}

void nightFadeOn()
{
  for(int i = 0; i>60; i = i + 5)
  {
    
    strip.setPixelColor(5, strip.Color(i,i,i));
    strip.setPixelColor(4, strip.Color(i*1.2,i*1.2,i*1.2));
    strip.setPixelColor(3, strip.Color(i*1.4,i*1.4,i*1.4));
    strip.setPixelColor(2, strip.Color(i*1.6,i*1.6,i*1.6));
    strip.setPixelColor(1, strip.Color(i*1.8,i*1.8,i*1.8));
    strip.show();
    delay(50);
    
  }
}

void nightFadeOff()
{
  for(int i = 60; i<0; i = i - 5)
  {
    
    strip.setPixelColor(5, strip.Color(i,i,i));
    strip.setPixelColor(4, strip.Color(i*1.2,i*1.2,i*1.2));
    strip.setPixelColor(3, strip.Color(i*1.4,i*1.4,i*1.4));
    strip.setPixelColor(2, strip.Color(i*1.6,i*1.6,i*1.6));
    strip.setPixelColor(1, strip.Color(i*1.8,i*1.8,i*1.8));
    strip.show();
    delay(50);
    
  }
}


void sweepOn()
{
  for (int i = 0; i <= numPixels + 20; i+=2)
  {
    if (i <= numPixels)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 110));
    }
    if (i >= 1)
    {
      strip.setPixelColor(i - 2, strip.Color(10, 10, 90));
    }
    if (i >= 4)
    {
      strip.setPixelColor(i - 4, strip.Color(10, 10, 90));
    }
    if (i >= 6)
    {
      strip.setPixelColor(i - 6, strip.Color(20, 20, 80));
    }
    if (i >= 8)
    {
      strip.setPixelColor(i - 8, strip.Color(40, 40, 80));
    }
    if (i >= 10)
    {
      strip.setPixelColor(i - 10, strip.Color(60, 60, 100));
    }
    if (i >= 12)
    {
      strip.setPixelColor(i - 12, strip.Color(90, 90, 100));
    }
    if (i >= 14)
    {
      strip.setPixelColor(i - 14, strip.Color(100, 100, 100));
    }
    if (i >= 16)
    {
      strip.setPixelColor(i - 16, strip.Color(120, 120, 120));
    }
//    if (i >= 18)
//    {
//      strip.setPixelColor(i - 18, strip.Color(150, 150, 150));
//    }
//    if (i >= 20)
//    {
//      strip.setPixelColor(i - 20, strip.Color(200, 200, 200));
//    }



    strip.show();

    delay(20);
  }


}

void sweepOnSmooth()
{

  int val1[3] = {0, 0, 110};
  int val2[3] = {10, 10, 110};
  int val3[3] = {10, 10, 90};
  int val4[3] = {20, 20, 80};
  int val5[3] = {40, 40, 80};
  int val6[3] = {60, 60, 100};
  int val7[3] = {90, 90, 100};
  int val8[3] = {100, 100, 100};
  int val9[3] = {120, 120, 120};
  int val10[3] = {150, 150, 150};
  int val11[3] = {200, 200, 200};

  int activePixel = 0;
  int fade = 0;


  for (int i = 0; i <= (numPixels + 20) * 10; i++)
  {

    if (activePixel <= numPixels)
    {
      strip.setPixelColor(activePixel, strip.Color(interp(0, val1[0], fade), interp(0, val1[1], fade), interp(0, val1[2], fade)));
    }
    if (activePixel >= 2)
    {
      strip.setPixelColor(activePixel - 2, strip.Color(interp(val1[0], val2[0], fade), interp(val1[1], val2[1], fade), interp(val1[2], val2[2], fade)));
    }
    if (activePixel >= 4)
    {
      strip.setPixelColor(activePixel - 4, strip.Color(interp(val2[0], val3[0], fade), interp(val2[1], val3[1], fade), interp(val2[2], val3[2], fade)));
    }
    if (activePixel >= 6)
    {
      strip.setPixelColor(activePixel - 6, strip.Color(interp(val3[0], val4[0], fade), interp(val3[1], val4[1], fade), interp(val3[2], val4[2], fade)));
    }
    if (activePixel >= 8)
    {
      strip.setPixelColor(activePixel - 8, strip.Color(interp(val4[0], val5[0], fade), interp(val4[1], val5[1], fade), interp(val4[2], val5[2], fade)));
    }
    if (activePixel >= 10)
    {
      strip.setPixelColor(activePixel - 10, strip.Color(interp(val5[0], val6[0], fade), interp(val5[1], val6[1], fade), interp(val5[2], val6[2], fade)));
    }
    if (activePixel >= 12)
    {
      strip.setPixelColor(activePixel - 12, strip.Color(interp(val6[0], val7[0], fade), interp(val6[1], val7[1], fade), interp(val6[2], val7[2], fade)));
    }
    if (activePixel >= 14)
    {
      strip.setPixelColor(activePixel - 14, strip.Color(interp(val7[0], val8[0], fade), interp(val7[1], val8[1], fade), interp(val7[2], val8[2], fade)));
    }
    if (activePixel >= 16)
    {
      strip.setPixelColor(activePixel - 16, strip.Color(interp(val8[0], val9[0], fade), interp(val8[1], val9[1], fade), interp(val8[2], val9[2], fade)));
    }
    if (activePixel >= 18)
    {
      strip.setPixelColor(activePixel - 18, strip.Color(interp(val9[0], val10[0], fade), interp(val9[1], val10[1], fade), interp(val9[2], val10[2], fade)));
    }
    if (activePixel >= 20)
    {
      strip.setPixelColor(activePixel - 20, strip.Color(interp(val10[0], val11[0], fade), interp(val10[1], val11[1], fade), interp(val10[2], val11[2], fade)));
    }





    strip.show();

    fade ++;
    if (fade == 10)
    {
      fade = 0;
      activePixel ++;
    }

    delay(2);
  }


}


void sweepOff()
{
  for (int i = 0; i <= numPixels + 20; i+=2)
  {
    if (i <= numPixels)
    {
      strip.setPixelColor(i, strip.Color(200, 200, 200));
    }
    if (i >= 1)
    {
      strip.setPixelColor(i - 2, strip.Color(200, 150, 150));
    }
    if (i >= 4)
    {
      strip.setPixelColor(i - 4, strip.Color(150, 100, 100));
    }
    if (i >= 6)
    {
      strip.setPixelColor(i - 6, strip.Color(150, 90, 90));
    }
    if (i >= 8)
    {
      strip.setPixelColor(i - 8, strip.Color(120, 80, 80));
    }
    if (i >= 10)
    {
      strip.setPixelColor(i - 10, strip.Color(100, 40, 40));
    }
    if (i >= 12)
    {
      strip.setPixelColor(i - 12, strip.Color(100, 20, 20));
    }
    if (i >= 14)
    {
      strip.setPixelColor(i - 14, strip.Color(90, 10, 10));
    }
    if (i >= 16)
    {
      strip.setPixelColor(i - 16, strip.Color(80, 0, 0));
    }
    if (i >= 18)
    {
      strip.setPixelColor(i - 18, strip.Color(60, 0, 0));
    }
    if (i >= 20)
    {
      strip.setPixelColor(i - 20, strip.Color(0, 0, 0));
    }



    strip.show();

    delay(20);
  }



  //    delay(200);
  //
  //    for(int i = 0; i<=numPixels; i++)
  //    {
  //      strip.setPixelColor(i, strip.Color(100, 100, 100));
  //    }
  //    strip.show();

}

uint8_t interp(int start, int finish, int fade)
{
  int difference = finish - start;
  uint8_t result;

  if (fade == 0)
  {
    result = start;
  } else if (fade == 10)
  {
    result = finish;
  } else
  {
    result = start + (difference / 10) * fade;
  }

  return (result);
}




