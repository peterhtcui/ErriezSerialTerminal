# Serial Terminal library for Arduino

This is a universal Serial Terminal library for Arduino to parse ASCII commands and arguments with enhanced features including command history, tab completion, and improved terminal editing capabilities.

![Serial Terminal](https://raw.githubusercontent.com/peterhtcui/ErriezSerialTerminal/enhanced-features/extras/ScreenshotSerialTerminal.png)


## Hardware

Any Arduino hardware with a serial port, such as:

Arduino:
* UNO
* Nano
* Micro
* Pro or Pro Mini
* Mega or Mega2560
* Leonardo

Other targets:
* DUE
* ESP8266
* ESP32
* SAMD21
* STM32F1


## Examples

Arduino IDE | Examples | Erriez Serial Terminal |

* [ErriezSerialTerminal](https://github.com/Erriez/ErriezSerialTerminal/blob/master/examples/ErriezSerialTerminal/ErriezSerialTerminal.ino) - Basic example
* [ErriezSerialTerminal_EchoAndCallback](https://github.com/Erriez/ErriezSerialTerminal/blob/master/examples/ErriezSerialTerminal_EchoAndCallback/ErriezSerialTerminal_EchoAndCallback.ino) - Advanced example with character echoing
* [ErriezSerialTerminal_Enhanced](https://github.com/Erriez/ErriezSerialTerminal/blob/master/examples/ErriezSerialTerminal_Enhanced/ErriezSerialTerminal_Enhanced.ino) - **NEW**: Demonstrates all enhanced features including command history and tab completion


## Documentation

- [Online HTML](https://erriez.github.io/ErriezSerialTerminal)
- [Download PDF](https://github.com/Erriez/ErriezSerialTerminal/raw/master/ErriezSerialTerminal.pdf)


## Enhanced Features

**NEW in this version:**

* **Command History**: Navigate through previously entered commands using ↑/↓ arrow keys
* **Tab Completion**: Auto-complete commands by pressing the Tab key
* **Enhanced Terminal Editing**: Better backspace support and line editing capabilities
* **Larger Buffer**: Increased from 32 to 256 bytes for longer commands and more arguments
* **Extended Command Length**: Support for commands up to 12 characters (increased from 8)
* **History Management**: Built-in functions to view and clear command history

**Terminal Features:**
* Arrow key navigation (↑/↓) for command history
* Tab key for command auto-completion
* Enhanced backspace and delete key support
* Improved line editing and cursor control
* Character echoing for better terminal experience

## Usage

**Initialization**

Create a Serial Terminal object. This can be initialized with optional newline and delimiter characters.

Default newline character: ```'\n'```
Default delimiter character: ```Space```

```c++
#include <ErriezSerialTerminal.h>

// Newline character '\r' or '\n'
char newlineChar = '\n'; 
// Separator character between commands and arguments
char delimiterChar = ' ';

// Create serial terminal object
SerialTerminal term(newlineChar, delimiterChar);


void setup()
{
    // Initialize serial port
    Serial.begin(115200);
    
    // Initialize the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}
```
**Register new commands**

Commands must be registered at startup with a corresponding ```callback handler``` .  This registers the command only, excluding arguments.

The callback handler will be called when the command has been received including the newline character.

An example of registering multiple commands:

```c++
void setup()
{
    ...

    // Add command callback handlers
    term.addCommand("?", cmdHelp);
    term.addCommand("help", cmdHelp);
    term.addCommand("on", cmdLedOn);
    term.addCommand("off", cmdLedOff);
}

void cmdHelp()
{
    // Print usage
    Serial.println(F("Serial terminal usage:"));
    Serial.println(F("  help or ?          Print this usage"));
    Serial.println(F("  on                 Turn LED on"));
    Serial.println(F("  off                Turn LED off"));
}

void cmdLedOn()
{
    // Turn LED on
    Serial.println(F("LED on"));
    digitalWrite(LED_BUILTIN, HIGH);
}

void cmdLedOff()
{
    // Turn LED off
    Serial.println(F("LED off"));
    digitalWrite(LED_BUILTIN, LOW);
}
```

**Set default handler**

Optional: The default handler will be called when the command is not recognized.

```c++
void setup()
{   
    ...

    // Set default handler for unknown commands
    term.setDefaultHandler(unknownCommand);
}

void unknownCommand(const char *command)
{
    // Print unknown command
    Serial.print(F("Unknown command: "));
    Serial.println(command);
}
```

**Read from serial port**

Read from the serial port in the main loop:

```c++
void loop()
{
    // Read from serial port and handle command callbacks
    term.readSerial();
}
```

**Get next argument**

Get pointer to next argument in serial receive buffer:

```c++
char *arg;

// Get next argument
arg = term.getNext();
if (arg != NULL) {
    Serial.print(F("Argument: "));
    Serial.println(arg);
} else {
    Serial.println(F("No argument"));
}
```

**Get remaining characters**

Get pointer to remaining characters in serial receive buffer:

```c++
char *arg;

// Get remaining characters
arg = term.getRemaining();
if (arg != NULL) {
    Serial.print(F("Remaining: "));
    Serial.println(arg);
}
```

**Clear buffer**

Optional: The serial receive buffer can be cleared with the following call:

```c++
term.clearBuffer();
```


**Enable/Disable Character Echoing**

Optional: Allow for any entered charecters to be printed back to the Serial interface.
This is useful for terminal programs like PuTTY.
Supports both backspace characters, ^H and ^127.

```c++
term.setSerialEcho(true); //Enable Character Echoing
```


**Set Post Command Handler**

Optional: Add a function to be called AFTER a command has been handled.

```c++
void setup()
{   
    ...

    // Set handler to be run AFTER a command has been handled.
    term.setPostCommandHandler(postCommandHandler);
}

void setPostCommandHandler()
{
    // Print '> ' for a primitive user UI
    Serial.print(F("> "));
}
```

**Command History Management**

The library now includes built-in command history functionality:

```c++
void setup()
{   
    ...

    // Add commands that can be accessed via history
    term.addCommand("history", cmdShowHistory);
    term.addCommand("clear", cmdClearHistory);
}

void cmdShowHistory()
{
    // Display command history
    term.showHistory();
}

void cmdClearHistory()
{
    // Clear command history
    term.clearHistory();
    Serial.println(F("Command history cleared."));
}
```

**Enhanced Terminal Features**

The library automatically provides these enhanced features when character echoing is enabled:

```c++
void setup()
{
    ...
    
    // Enable character echoing for enhanced features
    term.setSerialEcho(true);
    
    // Features automatically available:
    // - Arrow key navigation (↑/↓) for command history
    // - Tab completion for commands
    // - Enhanced backspace and editing
}
```

## Library configuration

```SerialTerminal.h``` contains the following configuration macro's:

**Enhanced Configuration:**
* ```ST_RX_BUFFER_SIZE``` : The serial receive buffer size is now **256 Bytes** (increased from 32). This includes the command and arguments, excluding the ```'\0'``` character.
* ```ST_NUM_COMMAND_CHARS```: The number of command characters is now **12 Bytes** (increased from 8), excluding the ```'\0'``` character.

**New Configuration:**
* ```ST_MAX_HISTORY_ENTRIES```: Maximum number of history entries (default: 20)
* ```ST_HISTORY_ENTRY_SIZE```: Maximum length of each history entry (default: 128 characters)

**Legacy Configuration (backward compatible):**
* All original functionality is preserved
* Default behavior remains unchanged for existing code


## Library dependencies

* None.


## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Terminal Compatibility

For the best experience with enhanced features, use a terminal emulator that supports:

**Recommended Terminal Emulators:**
* **PuTTY** (Windows) - Full support for arrow keys and Tab completion
* **Terminal** (macOS) - Native support for all enhanced features
* **GNOME Terminal** (Linux) - Complete ANSI escape sequence support
* **Arduino IDE Serial Monitor** - Basic support (limited arrow key functionality)

**Enhanced Features Requirements:**
* ANSI escape sequence support (for arrow key navigation)
* Tab character handling (for command completion)
* Character echoing capability
* Proper line ending support (CR or LF)

**Note:** The Arduino IDE Serial Monitor has limited support for arrow keys. For full enhanced functionality, use a dedicated terminal emulator like PuTTY.

## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)
