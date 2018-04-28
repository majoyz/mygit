#!/bin/bash
#this is my first shell project
echo $(date)
a="hello"
echo a
read a
echo "$a"
echo "file test"
read dir
mkdir ${dir}
cp -rf /etc/*.conf ${dir}
ls -l /etc/*|grep ^d| wc -l > etcdir.txt
