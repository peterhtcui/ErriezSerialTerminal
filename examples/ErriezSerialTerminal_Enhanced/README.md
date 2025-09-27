# Enhanced Serial Terminal Example

This example demonstrates all the enhanced features of the ErriezSerialTerminal library, including command history, tab completion, and improved terminal editing capabilities.

## Features Demonstrated

### Core Enhancements
- **Command History**: Navigate through previously entered commands using ↑/↓ arrow keys
- **Tab Completion**: Auto-complete commands by pressing the Tab key
- **Enhanced Editing**: Better backspace support and line editing
- **Larger Buffer**: 256-byte buffer for longer commands and more arguments
- **Extended Command Length**: Support for commands up to 12 characters

### Commands Available

#### Basic Commands
- `help` or `?` - Display comprehensive help information
- `on` / `off` - Control the built-in LED
- `hello [name] [age]` - Greeting with optional name and age
- `i <number>` - Display number in decimal, hex, and binary formats
- `s <args...>` - Display multiple string arguments

#### History Management
- `history` - Show command history
- `clear` - Clear command history

#### System Information
- `info` - Display system and library configuration information
- `longcommand` - Demonstrate longer command name support
- `testargs` - Test multiple arguments with large buffer

#### Demo Commands
- `temperature` - Temperature sensor simulation
- `pwmcontrol` - PWM control demonstration
- `memorytest` - Memory usage testing

## Enhanced Terminal Features

### Arrow Key Navigation
- **↑ (Up Arrow)**: Navigate backward through command history
- **↓ (Down Arrow)**: Navigate forward through command history

### Tab Completion
- **Tab Key**: Auto-complete commands
- If multiple matches exist, all possibilities are displayed
- If single match exists, command is auto-completed

### Editing Features
- **Backspace**: Delete characters
- **Ctrl+C**: Clear current line (terminal dependent)

## Usage Examples

### Basic Usage
```
> help
> on
> hello John 25
> i 255
> s arg1 arg2 arg3
```

### History Navigation
1. Enter several commands
2. Press ↑ to go back through history
3. Press ↓ to go forward through history
4. Press Enter to execute the selected command

### Tab Completion
1. Type `t` and press Tab
2. See all commands starting with 't'
3. Type more characters and press Tab again for auto-completion

### Large Buffer Testing
```
> testargs arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10
```

### System Information
```
> info
```

## Hardware Requirements

- Any Arduino-compatible board
- Built-in LED (for LED control commands)
- Serial communication capability

## Serial Settings

- **Baud Rate**: 115200
- **Data Bits**: 8
- **Stop Bits**: 1
- **Parity**: None
- **Flow Control**: None
- **Line Ending**: Carriage Return (CR) - `\r`

## Library Configuration

This example uses the enhanced configuration:

```cpp
// Buffer size increased from 32 to 256 bytes
#define ST_RX_BUFFER_SIZE       256

// Command length increased from 8 to 12 characters
#define ST_NUM_COMMAND_CHARS    12

// History support
#define ST_MAX_HISTORY_ENTRIES  20
#define ST_HISTORY_ENTRY_SIZE   128
```

## Compatibility

This enhanced example is compatible with:
- Arduino Uno, Nano, Micro, Pro Mini
- Arduino Mega, Leonardo
- ESP8266, ESP32
- STM32F1, SAMD21
- Other Arduino-compatible boards

## Terminal Emulator Compatibility

For best experience, use a terminal emulator that supports:
- ANSI escape sequences (for arrow keys)
- Tab character handling
- Character echoing

Recommended terminal emulators:
- **PuTTY** (Windows)
- **Terminal** (macOS)
- **GNOME Terminal** (Linux)
- **Arduino IDE Serial Monitor** (basic support)

## Troubleshooting

### Arrow Keys Not Working
- Ensure your terminal emulator supports ANSI escape sequences
- Try using PuTTY or another advanced terminal emulator
- The Arduino IDE Serial Monitor has limited support

### Tab Completion Not Working
- Make sure character echoing is enabled
- Verify the terminal supports Tab character input
- Try typing partial commands and pressing Tab

### History Not Saving
- Commands are saved automatically when you press Enter
- Empty commands are not saved to history
- History is cleared when you restart the Arduino

## Performance Notes

- History is stored in RAM, so it's cleared on power cycle
- Larger buffer uses more memory but allows longer commands
- Tab completion searches through all registered commands

## Future Enhancements

Potential improvements that could be added:
- Persistent history storage in EEPROM
- Command aliases and shortcuts
- Multi-line command support
- Command parameter validation
- Custom prompt configuration

## License

This example is part of the ErriezSerialTerminal library and is released under the MIT License.

## Contributing

If you have suggestions for improvements or find issues:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

For more information, visit the [ErriezSerialTerminal GitHub repository](https://github.com/Erriez/ErriezSerialTerminal).
