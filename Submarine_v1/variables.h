/*
Classes
-------

Speed MaxDepth  Rudder  Torpedos  HullStrength  HasSonar  SonarAngle  ClassName   ClassType
33    950       10      24        2             1         75.0        LosAngeles  SSN
33    1300      10      24        2             1         75.0        Akula       SSN
60    3000      30      0         1             1         90.0        Torpedo
27    1200      10      20        2             1         75.0        Typhoon     SSBN

*/
#include <limits.h>
#include <Bounce2.h>
    #define DirectionAnalogPin 0
    #define BTNFASTER_PIN 13
    #define BTNSLOWER_PIN 14
    #define BTNUP_PIN     11
    #define BTNDOWN_PIN   12

    #define RADIANFACTOR  0.01745329
    #define MaxSpeed 33 /*Captin I've given her all she's got!*/
    #define MaxDepth 950 /*Why is my hull crushing!*/
    #define Rudder 10 /*bend me and she will turn*/
    #define TorpedosOnBoard 4 /* Because we're cheap */
    #define hull_strength 2
    #define has_sonar true
    #define sonar_angle 75.0
    #define MinSpeed -12 /*You want to go how fast in reverse!?*/
    #define Classname  "Los Angeles"
    #define speedIncrement 2
    #define diveIncrement 20
    #define PLANES_CHANGE 0.2
    #define RUDDER_CHANGE 0.025
    #define PERISCOPE_DEPTH 50

    int CavitationFlag=0;
    
    float Depth=0; /*How deep are we?*/
    float DesiredDepth = 0;
    
    float Speed=0.0; /* How fast am I going? Look out the window! */
    float DesiredSpeed=0.0; /*Scotty warp speed!*/

    double Heading = 0;
    double DesiredHeading = 0;
    
    int fuel_remaining = INT_MAX; 
    int mission_timer = 0;

    Metro SubHandelingTimer = Metro(1000);  // Instantiate an instance
    Metro PotHandelingTimer = Metro(100);
    Metro ScreenRefreshTimer = Metro(300);
    Bounce btnFaster = Bounce(); 
    Bounce btnSlower = Bounce();
    Bounce btnUp = Bounce();
    Bounce btnDown = Bounce();
