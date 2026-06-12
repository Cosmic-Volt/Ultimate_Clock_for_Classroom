# Ultimate_Clock_for_Classroom(The_Classinator)

## Features:

-Time | Countdown Time | Temperature --on Dot Matrix Display(MAX7219)

-Countdown Timer for when class will end     

-Buzzer to buzz 5min before Class ends

-Subject displays for few seconds when that class starts

## Demo Video:


https://github.com/user-attachments/assets/744bfbe7-7ddf-4959-8aff-afa398dfe1c7


## Original Hardware:
-Arduino Nano 
-MAX7219 Dot Matrix
-DS3231 RTC Module
-Buzzer


Feel Free to update code and change class times and Sujects to your desire. 

## WokWi Simulation: https://wokwi.com/projects/402586282048113665

## Instructables : https://www.instructables.com/The-Classinator-Ultimate-Clock-for-Classroom/

## Libraries to install: 

-MD_Parola
    by MajicDesigns — scrolling text on MAX7219 panels
    
-MD_MAX72xx
    by MajicDesigns — low-level MAX7219 driver (dependency of Parola)
    
-RTClib
    by Adafruit — DS3231 real-time clock interface


## How I made this Project✨

In my class (grade 8 'Uranus') we desperately needed a clock for our classroom to denote time and how much time is left for the class, and my classmates came up to me asking me to build a clock, but I wanted to step up the game abit and make 'The Ultimate Clock' customed designed to our class schedule for optimal time keeping.
I wanted to have firstly regular clock, then also have a countdown timer to when the class will end, also a buzzer to ring 5 minute before the class will end so that teachers could wrap up the class and be students be done with their presentations (we had a presentation on a topic every class according to our roll no.), and also a temperature display because why not? (i thought of this later when I found out DS3231 RTC module has a temperature sensor)

## Building code

At the time, I was completely new to Arduino programming.

I couldn't find a Arduino course that covered coding, so I started experimenting with ChatGPT (and later Claude), But My god did i Get so many errorsss!
(This was long before AI became particularly good at coding, and the generated code was full of bugs.)

I spent countless hours:

- Reading documentation
- Asking Help in countless Discord channels
- Debugging compiler errors
- Asking questions in Discord communities
- Testing ideas in Wokwi

Eventually, after many late nights of troubleshooting, I got a fully working simulation.
Although it was frustrating at times, I learned more from fixing those errors than I would have from simply following a tutorial. Building projects remains the fastest way I learn new things.


## Hardware 

I wanted the clock to be visible far from the class, so small lcd display and 0.96 inch oled display rulled out. 
I initially tried to build this clock with P10 Display but trying the hardware and using scrolling text example code, the Display got fired and messed up 2 leds in the middle that made everything not work, I tried reparing it but it had this layer of apoxy and things that made it impossible, i gave to techincian and he told me the IC got fried and he couldn't fix it.

Ultimately I went with MAX7219 Dot matrix Display and I think that was the best decision, But that was the best decision (then I started Building code) and figured everything out as i had a successful wokwi simulation, but as I upladed the code with wiring of respected components. It displayed: 

<img width="1904" height="857" alt="error" src="https://github.com/user-attachments/assets/3aeb9159-233f-4abe-8a20-8e09e9d6c901" />

After debugging i found that changing "PAROLA_HW" TO "FC16_HW" fixed the error.

But then after sometime it stopped working and I spend DAYS trying to figure it out but by replacing the jumper wires it worked, so I guess it was fault of poor quality copper, DAMN you Ea Nasir!

But then guess what My arduino UNO died on me:
<img width="452" height="1005" alt="arduinouno" src="https://github.com/user-attachments/assets/d1aa0d9a-844f-4240-93e1-7824d783626b" />

After chaniging to Arduino Nano It finally worked!!!! 
Clock in class room:


https://github.com/user-attachments/assets/21ef53cc-fdcb-4e02-a8e2-9c667d332db9



https://github.com/user-attachments/assets/6a762a8f-2e52-4eed-b631-6691f23e824f


