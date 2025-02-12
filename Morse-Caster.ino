#define LED_PIN 7         // LED for Morse Code Output
#define BUZZER_PIN 8      // Buzzer for Morse Code Sound
#define BUTTON_PIN 2      // Button for input (optional)
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 6); // LCD pins

String message = "HELLO"; // Default message
int dotDelay = 250; // Duration of a dot in milliseconds

// Morse Code Dictionary (A-Z and 0-9)
const char* morseCode[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--..",  // A-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
    "---..", "----."  // 0-9
};

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    lcd.begin(16, 2);
    lcd.print("Morse Caster");
    delay(2000);
    lcd.clear();
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print("Message: " + message);
    lcd.setCursor(0, 1);
    lcd.print("Sending...");

    sendMorseCode(message);
    
    lcd.setCursor(0, 1);
    lcd.print("Completed   ");
    delay(3000);
    lcd.clear();
}

// Function to send Morse Code
void sendMorseCode(String text) {
    text.toUpperCase(); // Convert text to uppercase
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c == ' ') {
            delay(dotDelay * 7); // Space between words
            continue;
        }

        int index;
        if (c >= 'A' && c <= 'Z') {
            index = c - 'A'; // Get index for A-Z
        } else if (c >= '0' && c <= '9') {
            index = c - '0' + 26; // Get index for 0-9
        } else {
            continue; // Ignore unsupported characters
        }

        const char* morse = morseCode[index];

        for (int j = 0; j < strlen(morse); j++) {
            if (morse[j] == '.') {
                blink(dotDelay);
            } else if (morse[j] == '-') {
                blink(dotDelay * 3);
            }
            delay(dotDelay); // Space between dots and dashes
        }
        delay(dotDelay * 3); // Space between letters
    }
}

// Function to blink LED and buzz for Morse code
void blink(int duration) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    delay(dotDelay); // Short pause
}