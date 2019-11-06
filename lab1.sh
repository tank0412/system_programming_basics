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

if [ $choice -eq 1 ]
then
echo $PWD
fi

if [ $choice -eq 2 ]
then
FILE=lab1.txt
if test -f "$FILE"; then
    echo "$FILE exist so impossible to create it"
else
echo >> lab1.txt #create txt file with empty line
fi
fi

if [ $choice -eq 6 ]
then
exit 1
fi
menu
}

menu

