/*
*/
#define False  0
#define True  1

int button = 7;                                 // The pin # to the play button.
int LEDLight = 6;                               // The pin # to the LED light.
int speakerPin = 8 ;                            // The pin to the signal.


// device status enum
typedef enum enum_deviceStatus { 
  IDLEING = 10,
  RUN = 11,
  CANCEL = 12,
  DONE = 13
}deviceStatus;

deviceStatus state = IDLEING;                      // Default State



int CANCEL_WAIT_DURATION = 2000;

/*
 Function to run setup and initializations.
*/
void setup() {
  Serial.begin(9600);               // Initialize Serial.
  pinMode(button, INPUT_PULLUP);    // Initialize Button  
  pinMode(LEDLight, OUTPUT);        // default Button
  pinMode(speakerPin, OUTPUT);      // Initialize Speaker
  digitalWrite(LEDLight, LOW);      // default LED
}


/*
 Function that gets called continuously.
*/
void loop() {
  // PRECONDITION: idle mode (not started).
  // State Machine Transition
  switch(state){
    case IDLEING:    if ButtonShort(): state = RUN; break;
    case RUN:     if ButtonLong(): state = CANCEL; 
                  else if checktime(): state = DONE; break;  // if time >= time_set
    case CANCEL:  if ButtonShort() || ButtonLong(): state = IDLEING; break;
    case DONE:    if ButtonShort() || ButtonLong(): state = IDLEING; break;
    default:      state = IDLE;
  }

  if (state == IDLE){
    // TODO: set everything to not work
  }

  if (state == RUN){
    // TODO: set everything running
  }

  if (state == CANCEL){
    // TODO: set cancel mode
  }

  if (state == DONE){
    // TODO: set done mode
  }

  /*
  // EFFECT: Don't do anything.
  if (!isDeviceRunning && !isButtonPressed()) {
    delay(100);
    return;
  }
  
  // PRECONDITION: turning on from idle mode.
  // EFFECT: Turns on the device.
  if (!isDeviceRunning && isButtonPressed()) {
    isDeviceRunning = True;
    notifyOn();
    startUV();
    Serial.print("Device is started...\n");
    waitUntilButtonIsReleased();
    return;
  }

  // PRECONDITION: running mode (button not pressed).
  // EFFECT: Decrement Timer;
  if (isDeviceRunning && !isButtonPressed()) {
    delay(100);
    return;
  }
  
  // Case for turning off from running.
  if (isDeviceRunning && isButtonPressed()) {
    int timeElapsed = 0;
    while(isButtonPressed() && timeElapsed < CANCEL_WAIT_DURATION) {
      timeElapsed += 100;
      delay(100);
    }
    
    if (timeElapsed >= CANCEL_WAIT_DURATION) {
      stopUV();
      notifyOff();
      isDeviceRunning = False;
      Serial.print("Device deactivation: SUCCESS...\n");
      waitUntilButtonIsReleased();
      return;
    }
    
    Serial.print("Device deactivation: CANCELLED...\n");
    return;
  }
  */
 
  
  return;
}


// ** HELPER FUNCTIONS ** //
// ---------------------- //

/*
Checks if the button is pressed.
*/
void checktime(){
  // TODO
}

void ButtonShort(){
  // TODO
}

void ButtonLong(){
  //  TODO
}

bool isButtonPressed() {
  return digitalRead(button) == LOW;
}


/**
 * Notify the user that the device is on using speaker.
 **/
void notifyOn() {
    for(int i = 100; i < 1600; i+= 600) {
      tone(speakerPin, 500 + i, 100);
      delay(50);
    }
    Serial.print("Speaker beeps ON tone...\n");
}

/**
 * Notify the user that the device is off using speaker.
 **/
void notifyOff() {
    for(int i = 1600; i > 100; i-= 300) {
      tone(speakerPin, 500 + i, 100);
      delay(100);
    }
    Serial.print("Speaker beeps ON tone...\n");
}

/**
 * Starts UV module.
 **/
void startUV() {
    for(int i = 0; i < 250; i+=2) {
      analogWrite(LEDLight, i);
      delay(75);
    }
    Serial.print("UV is on and in full power...\n");
}


/**
 * Stops UV module.
 **/
void stopUV() {
  analogWrite(LEDLight, 0);
  Serial.print("UV is on and in full power...\n");
}


/**
 * Hang the program until button is released.
 **/
void waitUntilButtonIsReleased() {
  while(isButtonPressed()) {
    delay(100);
  }
  
  return;
}