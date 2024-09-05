#include <stdio.h>
#include <stdint.h>

// Structure to hold individual LED settings
typedef struct {
    uint8_t state;        // ON/OFF state (1 for ON, 0 for OFF)
    uint8_t brightness;   // Brightness level (0-255)
    uint32_t color;       // RGB color value encoded in a 32-bit integer
} LEDSettings;

// Structure to represent a group of LEDs
typedef struct {
    LEDSettings *singleLED;   // Pointer to individual LED settings
    uint8_t groupState;       // Group ON/OFF state (1 for ON, 0 for OFF)
    uint8_t groupBrightness;  // Group brightness level (0-255)
} LEDGroup;

// Function to initialize the LED group with default values using pointers
void initLEDGroup(LEDGroup *group, LEDSettings *singleLED) {
    if (group == NULL || singleLED == NULL) {
        return; // Safeguard in case a NULL pointer is passed
    }

    // Initialize individual LED settings
    singleLED->state = 0;           // All LEDs OFF
    singleLED->brightness = 0;      // Minimum brightness
    singleLED->color = 0x000000;    // No color (black/off)

    // Initialize group settings
    group->singleLED = singleLED;   // Set the pointer to the single LED settings
    group->groupState = 0;          // Group OFF
    group->groupBrightness = 0;     // Minimum group brightness
}

// Function to update the LED group settings using deep pointers
void updateLEDGroupSettings(LEDGroup *group, uint8_t *groupState, uint8_t *groupBrightness, 
                            uint8_t *state, uint8_t *brightness, uint32_t *color) {
    if (group == NULL || group->singleLED == NULL || groupState == NULL || 
        groupBrightness == NULL || state == NULL || brightness == NULL || color == NULL) {
        return; // Safeguard in case any NULL pointer is passed
    }

    // Update group-wide settings using deep pointers
    group->groupState = *groupState;              // Update group ON/OFF state
    group->groupBrightness = *groupBrightness;    // Update group brightness

    // Update individual LED settings using deep pointers
    group->singleLED->state = *state;             // Update individual LED state
    group->singleLED->brightness = *brightness;   // Update individual LED brightness
    group->singleLED->color = *color;             // Update individual LED color
}

// Function to display the LED group status with pointer dereferencing
void displayLEDGroupStatus(const LEDGroup *group) {
    if (group == NULL || group->singleLED == NULL) {
        return; // Safeguard in case a NULL pointer is passed
    }

    // Print group-wide settings
    printf("Group State: %s\n", group->groupState ? "ON" : "OFF");
    printf("Group Brightness: %d\n", group->groupBrightness);

    // Print individual LED settings (nested structure)
    printf("Single LED State: %s\n", group->singleLED->state ? "ON" : "OFF");
    printf("Single LED Brightness: %d\n", group->singleLED->brightness);
    printf("Single LED Color: 0x%06X\n", group->singleLED->color);  // Print color in hexadecimal format
}

int main() {
    // Create instances of structures
    LEDSettings ledSettings;
    LEDGroup group;

    // Initialize the LED group with default values
    initLEDGroup(&group, &ledSettings);

    // Display the initial status of the LED group
    printf("Initial LED Group Status:\n");
    displayLEDGroupStatus(&group);

    // New settings to update
    uint8_t newGroupState = 1;
    uint8_t newGroupBrightness = 180;
    uint8_t newState = 1;
    uint8_t newBrightness = 150;
    uint32_t newColor = 0x00FF00; // Green color

    // Update the LED group settings using deep pointers
    updateLEDGroupSettings(&group, &newGroupState, &newGroupBrightness, 
                           &newState, &newBrightness, &newColor);

    // Display the updated status of the LED group
    printf("\nUpdated LED Group Status:\n");
    displayLEDGroupStatus(&group);

    return 0;
}



  
