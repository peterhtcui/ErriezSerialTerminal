# ESP32 Serial Terminal 使用说明

## 项目配置

本项目已经配置为支持ESP32开发板，包含以下配置：

- **平台**: ESPressif 32
- **框架**: Arduino
- **串口监视器波特率**: 115200
- **LED引脚**: GPIO 2 (ESP32内置LED)

## 支持的ESP32开发板

项目配置了三种常见的ESP32开发板：

1. **ESP32 Dev Module** (`esp32dev`) - 最常用的ESP32开发板
2. **ESP32-S2 Saola-1** (`esp32-s2-saola-1`) - ESP32-S2系列
3. **ESP32-C3 DevKitM-1** (`esp32-c3-devkitm-1`) - ESP32-C3系列

## 编译和上传方法

### 方法一：使用VSCode PlatformIO扩展

1. **安装PlatformIO IDE扩展**
   - 在VSCode中搜索并安装 "PlatformIO IDE" 扩展

2. **编译项目**
   - 按 `Ctrl+Shift+P` (或 `Cmd+Shift+P` on Mac)
   - 输入 "PlatformIO: Build"
   - 或点击底部状态栏的 "✓" 按钮

3. **上传到开发板**
   - 按 `Ctrl+Shift+P` (或 `Cmd+Shift+P` on Mac)
   - 输入 "PlatformIO: Upload"
   - 或点击底部状态栏的 "→" 按钮

4. **打开串口监视器**
   - 按 `Ctrl+Shift+P` (或 `Cmd+Shift+P` on Mac)
   - 输入 "PlatformIO: Serial Monitor"
   - 或点击底部状态栏的 "🔌" 按钮

### 方法二：使用命令行

1. **快速编译上传**
   ```bash
   ./quick-build.sh
   ```

2. **选择开发板编译**
   ```bash
   ./build.sh
   ```

3. **手动编译**
   ```bash
   # 编译
   pio run -e esp32dev
   
   # 上传
   pio run -e esp32dev -t upload
   
   # 串口监视器
   pio device monitor -e esp32dev
   ```

### 方法三：使用其他ESP32开发板

如果你使用其他ESP32开发板，可以修改 `platformio.ini` 中的环境配置：

```ini
[env:your_board]
platform = espressif32
board = your_board_name
framework = arduino
monitor_speed = 115200
lib_deps = 
    https://github.com/Erriez/ErriezSerialTerminal.git
```

## 使用说明

### 连接硬件

1. 将ESP32开发板通过USB连接到电脑
2. 确保驱动程序已正确安装

### 串口设置

- **波特率**: 115200
- **数据位**: 8
- **停止位**: 1
- **校验位**: 无
- **流控制**: 无

### 可用命令

上传程序后，在串口监视器中输入以下命令：

```
help                    # 显示帮助信息
?                       # 显示帮助信息
on                      # 打开LED (GPIO 2)
off                     # 关闭LED (GPIO 2)
hello John 25           # 打印问候信息
i 123                   # 打印数字参数（十进制）
i 0x7B                  # 打印数字参数（十六进制）
s arg1 arg2 arg3        # 打印字符串参数
```

### 示例输出

```
Serial terminal example.
Type 'help' to display usage.
> help
Serial terminal usage:
  help or ?          Print this usage
  on                 Turn LED on
  off                Turn LED off
  hello [name] [age] Print your name and age
  s <arg 1>..<arg N> Print string arguments
  i <arg>            Print decimal or hex argument
> on
LED on
> hello Peter 30
Hello Peter!
You are 30 years old.
> i 0xFF
String: 0xFF; Hex: 0xFF; Dec: 255
> off
LED off
```

## 故障排除

### 常见问题

1. **编译失败**
   - 确保PlatformIO扩展已正确安装
   - 检查网络连接（需要下载依赖库）

2. **上传失败**
   - 检查USB连接
   - 确保选择了正确的串口
   - 尝试按住BOOT按钮再点击上传

3. **串口监视器无输出**
   - 检查波特率设置（115200）
   - 确保ESP32已正确连接
   - 尝试重启ESP32

4. **LED不工作**
   - ESP32内置LED通常在GPIO 2
   - 检查你的开发板LED引脚定义
   - 某些ESP32板可能没有内置LED

### 引脚说明

- **内置LED**: GPIO 2 (可配置)
- **串口**: UART0 (GPIO 1-TX, GPIO 3-RX)

## 项目结构

```
ErriezSerialTerminal/
├── src/
│   └── main.cpp              # 主程序文件
├── platformio.ini            # PlatformIO配置文件
├── build.sh                  # 完整编译脚本
├── quick-build.sh            # 快速编译脚本
└── ESP32_使用说明.md         # 本说明文件
```

## 技术支持

- 原始库文档: https://erriez.github.io/ErriezSerialTerminal
- GitHub仓库: https://github.com/Erriez/ErriezSerialTerminal
- PlatformIO文档: https://docs.platformio.org/
