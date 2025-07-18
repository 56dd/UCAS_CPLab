#!/bin/bash
#set -x

root_folder="."
regex_folder="\./functional"
regex_file="\./.*\.cact"

CXX="clang++"
#CLANGFLAGS="-x c++ -S" 
CLANGFLAGS="-x c++ -Xclang -disable-O0-optnone -O0 -emit-llvm -S" 

find "$root_folder" -maxdepth 1 -type d -regex "$regex_folder"| while read -r folder; do
    echo "$folder"  # 在这里可以执行你想要的操作
    cd "$folder"

    rm -r ll s
    mkdir ll s
    find "$root_folder" -type f -regex "$regex_file"| while read -r file; do
        echo "Processing file: $folder/$file"  # 输出当前处理的文件
        filebasename=$(basename "$file" .cact)
        $CXX $CLANGFLAGS -emit-llvm -o ll/"$filebasename.ll"  "$file"
        $CXX $CLANGFLAGS -o s/"$filebasename.s" "$file"
    done
    rm ll/*.ll.tmp s/*.s.tmp

    cd ..
done