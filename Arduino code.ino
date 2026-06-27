#define LED_PIN 7         // LED for Morse Code Output
#define BUZZER_PIN 8      // Active buzzer for Morse Code Sound
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 6); // LCD pins (RS, E, D4, D5, D6, D7)

String message = "HELLO"; // Default message — type a new one in the Serial Monitor
int dotDelay = 250;       // Duration of one Morse "unit" (a dot) in milliseconds

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
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("Morse Caster");
    delay(2000);
    lcd.clear();
}

void loop() {
    // Type a new message in the Serial Monitor (send with a newline) to change it.
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        if (input.length() > 0) message = input;
    }

    lcd.setCursor(0, 0);
    lcd.print("Message: " + message);
    lcd.setCursor(0, 1);
    lcd.print("Sending...      ");

    sendMorseCode(message);

    lcd.setCursor(0, 1);
    lcd.print("Completed       ");
    delay(3000);
    lcd.clear();
}

// Send text as Morse with standard timing (in dot "units"):
// dot = 1, dash = 3, gap between elements = 1, between letters = 3, between words = 7.
void sendMorseCode(String text) {
    text.toUpperCase(); // Convert text to uppercase
    bool prevWasLetter = false;  // tracks whether to insert an inter-letter/word gap
    for (unsigned int i = 0; i < text.length(); i++) {
        char c = text[i];

        if (c == ' ') {
            if (prevWasLetter) {        // one 7-unit word gap (collapses repeated spaces)
                delay(dotDelay * 7);
                prevWasLetter = false;
            }
            continue;
        }

        int index;
        if (c >= 'A' && c <= 'Z') {
            index = c - 'A'; // Index for A-Z
        } else if (c >= '0' && c <= '9') {
            index = c - '0' + 26; // Index for 0-9
        } else {
            continue; // Ignore unsupported characters
        }

        if (prevWasLetter) {
            delay(dotDelay * 3); // 3-unit gap between letters
        }

        const char* morse = morseCode[index];
        for (unsigned int j = 0; j < strlen(morse); j++) {
            blink(morse[j] == '-' ? dotDelay * 3 : dotDelay); // dash = 3 units, dot = 1
            if (j + 1 < strlen(morse)) {
                delay(dotDelay); // 1-unit gap between elements (not after the last one)
            }
        }
        prevWasLetter = true;
    }
}

// Pulse the LED + buzzer for one Morse element. No trailing gap — the caller adds it.
void blink(int duration) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
}
