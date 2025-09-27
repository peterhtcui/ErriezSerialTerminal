/*
 * MIT License
 *
 * Copyright (c) 2018-2021 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \brief Enhanced Serial Terminal Example
 * \details
 *      Source:         https://github.com/Erriez/ErriezSerialTerminal
 *      Documentation:  https://erriez.github.io/ErriezSerialTerminal
 *      
 *      This example demonstrates all the enhanced features of the SerialTerminal library:
 *      - Command history with arrow key navigation (↑/↓)
 *      - Tab completion for commands
 *      - Enhanced terminal editing with backspace support
 *      - Larger buffer size (256 bytes) for longer commands and more arguments
 *      - Increased command length support (12 characters)
 *      - History management commands
 *      - System information display
 *      
 *      Hardware: Any Arduino-compatible board with serial communication
 *      Serial: 115200 baud, 8N1
 */

#include <ErriezSerialTerminal.h>

// LED pin - ESP32 uses GPIO 2 as built-in LED
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif
#define LED_PIN     LED_BUILTIN

// Newline character '\r' or '\n' - using '\r' for better terminal compatibility
char newlineChar = '\r';
// Separator character between commands and arguments
char delimiterChar = ' ';

// Create serial terminal object
SerialTerminal term(newlineChar, delimiterChar);

// Function prototypes
void unknownCommand(const char *command);
void cmdHelp();
void cmdLedOn();
void cmdLedOff();
void cmdPrintHello();
void cmdPrintIntArgument();
void cmdPrintStringArguments();
void cmdShowHistory();
void cmdClearHistory();
void cmdSystemInfo();
void cmdLongCommand();
void cmdTestArgs();
void cmdTemperature();
void cmdPwmControl();
void cmdMemoryTest();
void printConsoleChar();

// Global variables for demo features
int pwmValue = 0;
float temperature = 25.5;

void setup()
{
    // Startup delay to initialize serial port
    delay(500);

    // Initialize serial port
    Serial.begin(115200);
    Serial.println(F("\n=== Enhanced Serial Terminal Example ==="));
    Serial.println(F("Features: History, Tab Completion, Larger Buffer"));
    Serial.println(F("Type 'help' to see all available commands."));
    Serial.println(F("Try using arrow keys for history and Tab for completion!"));
    printConsoleChar();

    // Initialize the built-in LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Set default handler for unknown commands
    term.setDefaultHandler(unknownCommand);

    // Add command callback handlers - demonstrating longer command names
    term.addCommand("?", cmdHelp);
    term.addCommand("help", cmdHelp);
    term.addCommand("on", cmdLedOn);
    term.addCommand("off", cmdLedOff);
    term.addCommand("hello", cmdPrintHello);
    term.addCommand("i", cmdPrintIntArgument);
    term.addCommand("s", cmdPrintStringArguments);
    term.addCommand("history", cmdShowHistory);
    term.addCommand("clear", cmdClearHistory);
    term.addCommand("info", cmdSystemInfo);
    term.addCommand("longcommand", cmdLongCommand);
    term.addCommand("testargs", cmdTestArgs);
    term.addCommand("temperature", cmdTemperature);
    term.addCommand("pwmcontrol", cmdPwmControl);
    term.addCommand("memorytest", cmdMemoryTest);

    // Enable character echoing for terminal emulators
    term.setSerialEcho(true);
    // Set post command handler for better UX
    term.setPostCommandHandler(printConsoleChar);
}

void loop()
{
    // Read from serial port and handle command callbacks
    term.readSerial();
}

void printConsoleChar()
{
    Serial.print(F("> "));
}

void unknownCommand(const char *command)
{
    // Print unknown command
    Serial.print(F("Unknown command: "));
    Serial.println(command);
    Serial.println(F("Type 'help' to see available commands."));
}

void cmdHelp()
{
    // Print comprehensive usage
    Serial.println(F("\n=== Enhanced Serial Terminal Commands ==="));
    Serial.println(F("Basic Commands:"));
    Serial.println(F("  help or ?          Print this usage"));
    Serial.println(F("  on                 Turn LED on"));
    Serial.println(F("  off                Turn LED off"));
    Serial.println(F("  hello [name] [age] Print greeting with name and age"));
    Serial.println(F("  i <number>         Print number in decimal and hex"));
    Serial.println(F("  s <args...>        Print multiple string arguments"));
    
    Serial.println(F("\nHistory Management:"));
    Serial.println(F("  history            Show command history"));
    Serial.println(F("  clear              Clear command history"));
    
    Serial.println(F("\nSystem Information:"));
    Serial.println(F("  info               Show system information"));
    Serial.println(F("  longcommand        Test longer command names"));
    Serial.println(F("  testargs           Test many arguments with large buffer"));
    
    Serial.println(F("\nDemo Commands:"));
    Serial.println(F("  temperature        Show temperature sensor demo"));
    Serial.println(F("  pwmcontrol         PWM control demo"));
    Serial.println(F("  memorytest         Memory usage test"));
    
    Serial.println(F("\nEnhanced Features:"));
    Serial.println(F("  ↑/↓ Arrow Keys     Navigate command history"));
    Serial.println(F("  Tab                Auto-complete commands"));
    Serial.println(F("  Backspace          Delete characters"));
    Serial.println(F("  Ctrl+C             Clear current line"));
    Serial.println(F(""));
    Serial.println(F("Try typing 't' and press Tab to see completion!"));
}

void cmdLedOn()
{
    Serial.println(F("LED turned ON"));
    digitalWrite(LED_PIN, HIGH);
}

void cmdLedOff()
{
    Serial.println(F("LED turned OFF"));
    digitalWrite(LED_PIN, LOW);
}

void cmdPrintHello()
{
    char *arg;
    char *name = NULL;
    int age = 0;

    // Get first argument
    arg = term.getNext();
    if (arg != NULL) {
        // Try to convert argument to int
        if (atoi(arg)) {
            // Name is not specified, only age
            age = atoi(arg);
        } else {
            // Store first name argument
            name = arg;

            // Get second age argument
            arg = term.getNext();
            if (arg != NULL) {
                age = atoi(arg);
            }
        }
    }

    // Print greeting
    if (name) {
        Serial.print(F("Hello "));
        Serial.print(name);
        Serial.println(F("!"));
    } else {
        Serial.println(F("Hello! You didn't specify your name."));
    }

    // Print age
    if (age > 0) {
        Serial.print(F("You are "));
        Serial.print(age, DEC);
        Serial.println(F(" years old."));
    } else {
        Serial.println(F("Age not specified."));
    }
}

void cmdPrintIntArgument()
{
    int val;
    char *arg;

    // Get argument
    arg = term.getNext();
    if (arg == NULL) {
        Serial.println(F("No number specified."));
        Serial.println(F("Usage: i <decimal_number> or i 0x<hex_number>"));
        return;
    }

    // Try to convert decimal or hex argument
    if (strncmp(arg, "0x", 2) == 0) {
        if (sscanf(arg, "0x%x", &val) != 1) {
            Serial.println(F("Invalid hex value."));
            return;
        }
    } else {
        if (sscanf(arg, "%d", &val) != 1) {
            Serial.println(F("Invalid decimal value."));
            return;
        }
    }

    // Print results
    Serial.print(F("Input: "));
    Serial.print(arg);
    Serial.print(F(" | Decimal: "));
    Serial.print(val, DEC);
    Serial.print(F(" | Hex: 0x"));
    if (val < 0x10) Serial.print(F("0"));
    Serial.print(val, HEX);
    Serial.print(F(" | Binary: "));
    Serial.println(val, BIN);
}

void cmdPrintStringArguments()
{
    char *arg;
    int argCount = 0;

    Serial.println(F("String Arguments:"));
    
    // Print all arguments
    while ((arg = term.getNext()) != NULL) {
        argCount++;
        Serial.print(F("  "));
        Serial.print(argCount);
        Serial.print(F(": \""));
        Serial.print(arg);
        Serial.println(F("\""));
    }

    if (argCount == 0) {
        Serial.println(F("  No arguments provided."));
        Serial.println(F("  Usage: s arg1 arg2 arg3 ..."));
    } else {
        Serial.print(F("Total arguments: "));
        Serial.println(argCount);
        
        // Show remaining string
        char *remaining = term.getRemaining();
        if (remaining && strlen(remaining) > 0) {
            Serial.print(F("Remaining: "));
            Serial.println(remaining);
        }
    }
}

void cmdShowHistory()
{
    Serial.println(F("=== Command History ==="));
    term.showHistory();
    Serial.println(F("Use ↑/↓ arrow keys to navigate history."));
}

void cmdClearHistory()
{
    term.clearHistory();
    Serial.println(F("Command history cleared."));
}

void cmdSystemInfo()
{
    Serial.println(F("=== System Information ==="));
    
    // Basic system info
    Serial.println(F("Hardware:"));
    Serial.print(F("  LED Pin: GPIO "));
    Serial.println(LED_PIN);
    
    Serial.println(F("\nLibrary Configuration:"));
    Serial.print(F("  Buffer Size: "));
    Serial.print(ST_RX_BUFFER_SIZE);
    Serial.println(F(" bytes"));
    Serial.print(F("  Max Command Length: "));
    Serial.print(ST_NUM_COMMAND_CHARS);
    Serial.println(F(" characters"));
    Serial.print(F("  Max History Entries: "));
    Serial.print(ST_MAX_HISTORY_ENTRIES);
    Serial.println(F(" entries"));
    Serial.print(F("  History Entry Size: "));
    Serial.print(ST_HISTORY_ENTRY_SIZE);
    Serial.println(F(" characters"));
    
    Serial.println(F("\nEnhanced Features:"));
    Serial.println(F("  ✓ Command History"));
    Serial.println(F("  ✓ Tab Completion"));
    Serial.println(F("  ✓ Arrow Key Navigation"));
    Serial.println(F("  ✓ Enhanced Editing"));
    Serial.println(F("  ✓ Larger Buffer Support"));
}

void cmdLongCommand()
{
    Serial.println(F("=== Long Command Demo ==="));
    Serial.println(F("This command demonstrates the increased command length support."));
    Serial.print(F("The library now supports commands up to "));
    Serial.print(ST_NUM_COMMAND_CHARS);
    Serial.println(F(" characters long!"));
    Serial.println(F("This allows for more descriptive and readable command names."));
    Serial.println(F("Try typing 'long' and press Tab to see completion in action!"));
}

void cmdTestArgs()
{
    Serial.println(F("=== Large Buffer Test ==="));
    
    char *arg;
    int argCount = 0;
    int totalChars = 0;
    
    Serial.println(F("Testing multiple arguments with larger buffer..."));
    
    // Count arguments and characters
    while ((arg = term.getNext()) != NULL) {
        argCount++;
        totalChars += strlen(arg);
        Serial.print(F("  Arg "));
        Serial.print(argCount);
        Serial.print(F(": \""));
        Serial.print(arg);
        Serial.print(F("\" ("));
        Serial.print(strlen(arg));
        Serial.println(F(" chars)"));
    }
    
    if (argCount == 0) {
        Serial.println(F("No arguments provided."));
        Serial.println(F("Try: testargs arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8"));
        Serial.print(F("The larger buffer ("));
        Serial.print(ST_RX_BUFFER_SIZE);
        Serial.println(F(" bytes) allows for many more arguments!"));
    } else {
        Serial.print(F("Total arguments: "));
        Serial.println(argCount);
        Serial.print(F("Total characters: "));
        Serial.println(totalChars);
        Serial.print(F("Buffer usage: "));
        Serial.print((totalChars * 100) / ST_RX_BUFFER_SIZE);
        Serial.println(F("%"));
    }
}

void cmdTemperature()
{
    Serial.println(F("=== Temperature Sensor Demo ==="));
    
    // Simulate temperature reading
    temperature += (random(-50, 51) / 10.0); // Random change ±5°C
    if (temperature < 0) temperature = 0;
    if (temperature > 100) temperature = 100;
    
    Serial.print(F("Current Temperature: "));
    Serial.print(temperature, 1);
    Serial.println(F("°C"));
    
    char *arg = term.getNext();
    if (arg != NULL) {
        float newTemp = atof(arg);
        if (newTemp >= 0 && newTemp <= 100) {
            temperature = newTemp;
            Serial.print(F("Temperature set to: "));
            Serial.print(temperature, 1);
            Serial.println(F("°C"));
        } else {
            Serial.println(F("Temperature must be between 0 and 100°C"));
        }
    }
}

void cmdPwmControl()
{
    Serial.println(F("=== PWM Control Demo ==="));
    
    char *arg = term.getNext();
    if (arg != NULL) {
        int newPwm = atoi(arg);
        if (newPwm >= 0 && newPwm <= 255) {
            pwmValue = newPwm;
            Serial.print(F("PWM value set to: "));
            Serial.println(pwmValue);
            
            // In a real application, you would set PWM here:
            // analogWrite(LED_PIN, pwmValue);
            
            Serial.println(F("(LED PWM simulation - use actual PWM pin for real control)"));
        } else {
            Serial.println(F("PWM value must be between 0 and 255"));
        }
    } else {
        Serial.print(F("Current PWM value: "));
        Serial.println(pwmValue);
        Serial.println(F("Usage: pwmcontrol <0-255>"));
    }
}

void cmdMemoryTest()
{
    Serial.println(F("=== Memory Usage Test ==="));
    
    // Test large string handling
    Serial.println(F("Testing large string handling..."));
    
    char *arg;
    int totalLength = 0;
    
    // Get all arguments and measure total length
    while ((arg = term.getNext()) != NULL) {
        totalLength += strlen(arg) + 1; // +1 for space
    }
    
    Serial.print(F("Total command length: "));
    Serial.print(totalLength);
    Serial.print(F(" / "));
    Serial.print(ST_RX_BUFFER_SIZE);
    Serial.print(F(" bytes ("));
    Serial.print((totalLength * 100) / ST_RX_BUFFER_SIZE);
    Serial.println(F("%)"));
    
    if (totalLength > ST_RX_BUFFER_SIZE * 0.8) {
        Serial.println(F("⚠️  Warning: Buffer usage > 80%"));
    } else {
        Serial.println(F("✓ Buffer usage within safe limits"));
    }
    
    // Show remaining buffer capacity
    Serial.print(F("Remaining buffer capacity: "));
    Serial.print(ST_RX_BUFFER_SIZE - totalLength);
    Serial.println(F(" bytes"));
}
