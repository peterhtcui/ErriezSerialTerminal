#!/bin/bash

# ESP32 Serial Terminal 编译和上传脚本

echo "ESP32 Serial Terminal 编译脚本"
echo "================================"

# 检查PlatformIO是否安装
if ! command -v pio &> /dev/null; then
    echo "错误: PlatformIO 未安装。请先安装 PlatformIO IDE 扩展。"
    exit 1
fi

# 选择开发板
echo "请选择你的ESP32开发板："
echo "1) ESP32 Dev Module (esp32dev)"
echo "2) ESP32-S2 Saola-1 (esp32-s2-saola-1)"
echo "3) ESP32-C3 DevKitM-1 (esp32-c3-devkitm-1)"
read -p "请输入选择 (1-3): " choice

case $choice in
    1)
        BOARD="esp32dev"
        ;;
    2)
        BOARD="esp32-s2-saola-1"
        ;;
    3)
        BOARD="esp32-c3-devkitm-1"
        ;;
    *)
        echo "无效选择，使用默认ESP32 Dev Module"
        BOARD="esp32dev"
        ;;
esac

echo "使用开发板: $BOARD"

# 编译项目
echo "正在编译项目..."
pio run -e $BOARD

if [ $? -eq 0 ]; then
    echo "编译成功！"
    
    # 询问是否上传
    read -p "是否上传到开发板？(y/n): " upload_choice
    if [[ $upload_choice == "y" || $upload_choice == "Y" ]]; then
        echo "正在上传到开发板..."
        pio run -e $BOARD -t upload
        
        if [ $? -eq 0 ]; then
            echo "上传成功！"
            echo "打开串口监视器..."
            pio device monitor -e $BOARD
        else
            echo "上传失败！"
        fi
    else
        echo "跳过上传。"
    fi
else
    echo "编译失败！"
    exit 1
fi
