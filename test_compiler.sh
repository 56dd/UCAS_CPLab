#!/bin/bash

# 对每个cact文件执行 ./build/compiler 命令

COMPILER="./build/compiler"

echo "编译 functional 目录..."
for file in ./testcases-main/functional/*.cact; do
    if [ -f "$file" ]; then
        echo "编译: $file"
        $COMPILER "$file"
    fi
done

echo "编译 performance 目录..."
for file in ./testcases-main/performance/*.cact; do
    if [ -f "$file" ]; then
        echo "编译: $file"
        $COMPILER "$file"
    fi
done

echo "完成"