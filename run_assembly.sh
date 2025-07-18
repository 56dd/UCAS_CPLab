#!/bin/bash

# 运行Codegencases-main中所有汇编代码的脚本

ASSEMBLY_DIR="./Codegencases-main/functional"

echo "=== 运行所有汇编代码 ==="

# 检查目录是否存在
if [ ! -d "$ASSEMBLY_DIR" ]; then
    echo "错误: 目录不存在 $ASSEMBLY_DIR"
    exit 1
fi

# 遍历所有.s文件
for asm_file in "$ASSEMBLY_DIR"/*.s; do
    if [ -f "$asm_file" ]; then
        base_name=$(basename "$asm_file" .s)
        echo "处理: $base_name.s"
        
        # 切换到汇编文件所在目录
        cd "$ASSEMBLY_DIR"
        
        # 编译汇编文件生成可执行文件
        if riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -static -o "$base_name" "$base_name.s"; then
            echo "✓ 编译成功"
            
            # 运行程序
            echo "运行结果:"
            if [ -f "${base_name}.in" ]; then
                # 如果有输入文件，使用输入文件
                spike pk "./$base_name" < "${base_name}.in"
            else
                # 否则直接运行
                spike pk "./$base_name"
            fi
            echo "退出码: $?"
        else
            echo "✗ 编译失败"
        fi
        
        echo "----------------------------------------"
        
        # 返回原目录
        cd - > /dev/null
    fi
done

echo "=== 完成 ===" 