#!/bin/bash

# 快速编译和上传ESP32项目

echo "ESP32 快速编译上传"
echo "==================="

# 使用默认的esp32dev配置
pio run -e esp32dev -t upload

if [ $? -eq 0 ]; then
    echo "上传成功！正在打开串口监视器..."
    pio device monitor -e esp32dev
else
    echo "编译或上传失败！"
fi

