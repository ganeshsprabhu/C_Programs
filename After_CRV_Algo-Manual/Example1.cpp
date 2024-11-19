Example 1:

#include <stdio.h>
#include <stdbool.h>

// Function to simulate a room temperature control system
int control_temperature(float temperature, int fan_speed, int mode, int humidity_level) {
    bool alarm = false;

    // Temperature adjustment based on mode
    if (mode == 1) {  // Cooling mode
        temperature -= fan_speed;
    } else if (mode == 2) {  // Heating mode
        temperature += fan_speed;
    } else {  // Invalid mode
        alarm = true;
        printf("Invalid mode! Setting alarm...\n");
    }

    // Limit the effect of humidity_level: only add a small, bounded value
    if (humidity_level >= 20 && humidity_level <= 80) {
        temperature += humidity_level * 0.05;  // Small adjustment based on humidity
    }

    // Safety property: Temperature must not exceed 30 degrees
    if (temperature > 30) {
        alarm = true;
    }

    printf("Alarm: %s\n", alarm ? "ON" : "OFF");
    return temperature;
}

int main() {
    float temperature = 25;    // Initial room temperature
    int fan_speed = 5;       // Fan speed setting
    int mode = 1;            // Mode: 1 for cooling, 2 for heating
    int humidity_level = 60; // Humidity level (affects comfort but not safety directly)

    int final_temperature = control_temperature(temperature, fan_speed, mode, humidity_level);
    printf("Final temperature: %d\n", final_temperature);
    return 0;
}

CRV : temperature, fan_speed, mode
not a CRV : alarm
not always a CRV :  humidity_level

Details from above code:
 Line1 : if (humidity_level >= 20 && humidity_level <= 80) {
 Line2 :     temperature += humidity_level * 0.05;  // Small adjustment based on humidity
 Line 3: }
 
Observation1 : In this example
- Line 1 checks if humidity_level is between 20 and 80. If so, we adjust the temperature in Line 2.
- Because we have set bounds, humidity_level is not a CRV by itself.
- We do not have two different values of humidity_level that could satisfy and violate the safety condition (temperature ≤ 30 degrees).
 
Observation2 : In this example
Now, if a Single Event Upset (SEU) happens:
- At Line 1: Even if an SEU changes humidity_level during this check, there’s no problem because the temperature is not affected.
- At Line 2: If an SEU occurs and humidity_level becomes something extreme (e.g., 5000), 
  it could significantly affect the temperature and cause a violation. In this case, humidity_level becomes a CRV.
  
In summary, humidity_level only affects the safety condition at Line 2, not at Line 1.

