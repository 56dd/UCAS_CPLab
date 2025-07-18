#!/bin/bash

# RISC-V汇编运行演示

echo "=== RISC-V汇编运行演示 ==="

# 示例：运行00.s
EXAMPLE_ASM="./Codegencases-main/functional/00.s"

if [ ! -f "$EXAMPLE_ASM" ]; then
    echo "错误: 找不到示例文件 $EXAMPLE_ASM"
    exit 1
fi

echo "1. 查看汇编文件内容:"
cat "$EXAMPLE_ASM"
echo

echo "2. 编译汇编文件:"
cd "./Codegencases-main/functional"
riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -static -o "00" "00.s"
echo "编译完成"
echo

echo "3. 运行程序:"
spike pk "./00"
EXIT_CODE=$?
echo

echo "4. 查看返回值:"
echo "退出码（返回值）: $EXIT_CODE"
echo

echo "5. 解释:"
echo "   - 汇编代码中的 'li a0, 3' 将值3加载到a0寄存器"
echo "   - a0寄存器是RISC-V中用于返回值的寄存器"
echo "   - 程序退出时，a0寄存器的值成为退出码"
echo "   - 所以返回值是 3"

cd - > /dev/null 