#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int MAX7219_CS = 10;
const int NUM_MAX7219 = 8;
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

MD_Parola P = MD_Parola(HARDWARE_TYPE, MAX7219_CS, NUM_MAX7219);

const uint8_t scrollSpeed = 25;
const uint16_t scrollPause = 2000;

#define BUF_SIZE 75
char curMessage[BUF_SIZE] = "";
char newMessage[BUF_SIZE] = "";
bool newMessageAvailable = true;

const int startTime[] = {1000, 1100, 1145, 1230, 1315, 1400, 1445, 1530};
const int endTime[] = {1059, 1144, 1229, 1314, 1359, 1444, 1529, 1614};
const int numSessions = sizeof(startTime) / sizeof(startTime[0]);
const char* classNames[] = {"English", "Science", "Computer", "Social", "Lunch Break", "Nepali", "C Maths", "A Math"};
const int displayDuration = 6000;
unsigned long previousMillis = 0;
bool showClass = false;
bool classDisplayed[numSessions] = {false};
int currentSession = -1;

const int buzzerPin = A0; // Define the pin for the buzzer (using A0)
bool buzzerRang = false;

// Function declarations
int timeToMinutes(int time);
int calculateTimeDifference(int timeA, int timeB);
int combineTime(int hour, int minute);
int getCurrentSession(int cTime);
void playRickrollTune();

int timeToMinutes(int time) {
    int hh = time / 100;
    int mm = time % 100;
    return hh * 60 + mm;
}

int calculateTimeDifference(int timeA, int timeB) {
    int minutesA = timeToMinutes(timeA);
    int minutesB = timeToMinutes(timeB);
    int difference = abs(minutesA - minutesB);

    if (difference > 720) {
        difference = 1440 - difference;
    }

    return difference;
}

int combineTime(int hour, int minute) {
    return hour * 100 + minute;
}

int getCurrentSession(int cTime) {
    for (int i = 0; i < numSessions; i++) {
        if (cTime >= startTime[i] && cTime <= endTime[i]) {
            return i;
        }
        // Check if we're in the transition period to the next class
        if (i < numSessions - 1 && cTime > endTime[i] && cTime < startTime[i + 1]) {
            return i + 1;  // Return the upcoming session
        }
    }
    return -1; // no session active or upcoming
}

void displayTimeAndTemperatureAndCount() {
    DateTime now = rtc.now();
    int hour = now.hour();
    int minute = now.minute();
    int hours = (hour % 12 == 0) ? 12 : hour % 12;
    int temp = int(rtc.getTemperature());
    int cTime = combineTime(hour, minute);

    currentSession = getCurrentSession(cTime);

    unsigned long currentMillis = millis();
    if (currentSession != -1 && !classDisplayed[currentSession] &&
        cTime == startTime[currentSession]) {
        classDisplayed[currentSession] = true;
        previousMillis = currentMillis;
        showClass = true;
        buzzerRang = false; // Reset buzzer flag for the new session
        snprintf(newMessage, BUF_SIZE, "%s", classNames[currentSession]);
        newMessageAvailable = true;
    }

    if (currentSession != -1 && !showClass) {
        int remainingMinutes;
        if (cTime < startTime[currentSession]) {
            // We're in the transition period, count down to the start of the next class
            remainingMinutes = calculateTimeDifference(startTime[currentSession], cTime);
        } else {
            // We're in a class session, count down to the end of the current class
            remainingMinutes = calculateTimeDifference(endTime[currentSession], cTime) + 1;

            // Check if there are 5 minutes left
            if (remainingMinutes == 5 && !buzzerRang) {
                // Buzz normally for 3 seconds
                digitalWrite(buzzerPin, HIGH);
                delay(3000);
                digitalWrite(buzzerPin, LOW);

                // Play the Rickroll tune
                playRickrollTune();
                buzzerRang = true;
            }
        }
        snprintf(newMessage, BUF_SIZE, "%2d:%02d %2dm %dC", hours, minute, remainingMinutes, temp);
        newMessageAvailable = true;
    } else if (!showClass) {
        snprintf(newMessage, BUF_SIZE, "%2d:%02d %dC", hours, minute, temp);
        newMessageAvailable = true;
    }

    if (showClass && currentMillis - previousMillis >= displayDuration) {
        showClass = false;
        newMessageAvailable = true;
    }
}

void playRickrollTune() {
    int noteDurations[] = {
        200,100,100,200,200,200,100,100,200,200,200,100,100,400,
        200,100,100,200,200,200,100,100,200,200,200,100,100,400
    };
    
    for (int i = 0; i < sizeof(noteDurations) / sizeof(noteDurations[0]); i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(noteDurations[i]);
        digitalWrite(buzzerPin, LOW);
        delay(50); // Short pause between notes
    }
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    rtc.begin();
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
    P.begin(1);
    P.setInvert(false);
    P.setZone(0, 0, NUM_MAX7219 - 1);
    P.displayZoneText(0, curMessage, PA_CENTER, scrollSpeed, scrollPause, PA_PRINT, PA_NO_EFFECT);
    DateTime now = rtc.now();
    int hour = now.hour();
    int minute = now.minute();
    snprintf(newMessage, BUF_SIZE, "%s", classNames[getCurrentSession(combineTime(hour, minute))]);
    newMessageAvailable = true;
    showClass = true;
}

void loop() {
    if (P.displayAnimate()) {
        if (newMessageAvailable) {
            strcpy(curMessage, newMessage);
            newMessageAvailable = false;
        }
        P.displayReset();
    }
    displayTimeAndTemperatureAndCount();
}