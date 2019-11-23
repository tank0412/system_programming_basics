#!/bin/bash
menu () {
echo "Лаб 1 Бухтиаров Роман P3418 var 3"
echo "1.Напечатать имя текущего каталога"
echo "2.Создать файл"
echo "3.Отменить доступ к файлу для всех остальных пользователей"
echo "4.Отменить право на запись для владельца файла"
echo "5.Переименовать файл"
echo "6.Выйти из программы"
proceedCHoice 
}
proceedCHoice () {
read choice 

case $choice in 
"1") 
echo  ${PWD##*/}
menu
;;

"2") 
FILE=lab*1.txt
getFileName FILE
echo $FILE
if test -f "$FILE"; then
    echo "$FILE exist so impossible to create it" >> lab1_err.txt
else
echo >> $FILE #create txt file with empty line
fi
menu
;;

"3")
FILE=lab*1.txt
getFileName FILE
if ! test -f $FILE; then
    echo "file does not exists so impossible to change it permissions" >> lab1_err.txt
else
chmod 760 -- $FILE
fi
menu
;;

"4")
FILE=lab*1.txt
getFileName FILE
if ! test -f $FILE; then
    echo "file does not exists so impossible to change it permissions" >> lab1_err.txt
else
chmod u-w -- $FILE
fi
menu
;;

"5")
echo "Старое имя файла"
FILE=lab*1.txt
getFileName FILE

echo "Новое имя файла"
FILE2=lab1_mv.txt
getFileName FILE2

if test -f $FILE2; then
    echo "file exists so impossible to rename file1.txt to it" >> lab1_err.txt
elif
test -f $FILE; then
    mv -- $FILE $FILE2
else
echo "file does not exists so impossible to rename it" >> lab1_err.txt
fi
menu
;;

"6")
exit 1
;;
esac

echo "Некорректный ввод"
menu
}

getFileName() {
local  __resultvar=$1
echo "Введите имя файла"
read fileName 
eval $__resultvar=$fileName
}

menu
