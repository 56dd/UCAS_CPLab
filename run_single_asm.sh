#!/bin/bash

# 运行单个RISC-V汇编文件并查看返回值的脚本
# 使用方法: ./run_single_asm.sh <汇编文件.s>

if [ $# -ne 1 ]; then
    echo "使用方法: $0 <汇编文件.s>"
    echo "示例: $0 ./Codegencases-main/functional/00.s"
    exit 1
fi

ASM_FILE=$1
BASE_NAME=$(basename "$ASM_FILE" .s)
DIR_NAME=$(dirname "$ASM_FILE")

echo "=== 运行RISC-V汇编文件: $ASM_FILE ==="

# 1. 显示汇编文件内容
echo "1. 汇编文件内容:"
cat "$ASM_FILE"
echo

# 2. 切换到汇编文件所在目录
cd "$DIR_NAME"

# 3. 编译汇编文件生成可执行文件
echo "2. 编译汇编文件..."
if riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -static -o "$BASE_NAME" "$BASE_NAME.s"; then
    echo "✓ 编译成功，生成可执行文件: $BASE_NAME"
else
    echo "✗ 编译失败"
    exit 1
fi

# 4. 运行程序
echo "3. 运行程序..."
echo "程序输出:"
if [ -f "${BASE_NAME}.in" ]; then
    echo "使用输入文件: ${BASE_NAME}.in"
    spike pk "./$BASE_NAME" < "${BASE_NAME}.in"
else
    spike pk "./$BASE_NAME"
fi

# 5. 获取退出码（返回值）
EXIT_CODE=$?
echo "退出码（返回值）: $EXIT_CODE"

# 6. 解释返回值
echo "4. 返回值说明:"
echo "   - 退出码 $EXIT_CODE 就是程序的返回值"
echo "   - 在RISC-V中，返回值通常存储在 a0 寄存器中"
echo "   - 对于简单的 return 语句，返回值就是退出码"

# 7. 查看期望输出（如果有）
if [ -f "${BASE_NAME}.out" ]; then
    echo "5. 期望输出:"
    cat "${BASE_NAME}.out"
fi

echo
echo "=== 完成 ==="

# 返回原目录
cd - > /dev/null 