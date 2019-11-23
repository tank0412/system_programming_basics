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
if test -f "$FILE"; then
    echo "$FILE exist so impossible to create it" >> lab1_err.txt
else
echo >> lab*1.txt #create txt file with empty line
fi
menu
;;

"3")
if ! test -f "lab*1.txt"; then
    echo "lab1.txt does not exists so impossible to change it permissions" >> lab1_err.txt
else
chmod 760 lab*1.txt
fi
menu
;;

"4")
if ! test -f "lab*1.txt"; then
    echo "lab*1.txt does not exists so impossible to change it permissions" >> lab1_err.txt
else
chmod u-w lab*1.txt
fi
menu
;;

"5")
if test -f "lab1_mv.txt"; then
    echo "lab1_mv.txt exists so impossible to rename lab1.txt to it" >> lab1_err.txt
elif
test -f "lab*1.txt"; then
    mv "lab*1.txt" "lab1_mv.txt"
else
echo "lab*1.txt does not exists so impossible to rename it" >> lab1_err.txt
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

menu
