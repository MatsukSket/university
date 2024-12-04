# Лабораторная работа 5
 
### Цель: 
 
Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows):
+ изучить основные встроенные команды,
+ научиться писать файлы сценариев,
+ научиться соотносить командные оболочки для разных OS.
+ Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Условия задания
Вариант 32: Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит числа (N и M) (как параметры пакетного файла). Каждые N секунд будет создаваться папка и файл в ней (файлы будут называться 1, 2, 3 и т.д.), в котором записано общее время работы скрипта на данный момент. Скрипт должен работать M секунд. Следующую папку создавать внутри уже созданной. При каждом создании файла писать в консоль «Новый файл был создан»
## Batch файл
- ### Код программы :computer:
```batch
@echo off
chcp 65001 > nul
set /p "N=Введите числовое значение для N (интервал в секундах): "
set /p "M=Введите числовое значение для M (максимальное время работы в секундах): "
set /a "total_time=0"
set /a "counter=1"
set "main_folder=%~dp0main_folder"
mkdir "%main_folder%"
set "current_path=%main_folder%"
   timeout /t %N% >nul
:loop
    if %total_time% geq %M% goto :end
    set "current_path=%current_path%\folder_%counter%"
    mkdir "%current_path%"
 set /a "total_time+=N"
    set "file_path=%current_path%\%counter%.txt"
    echo Общее время работы скрипта: %total_time% секунд > "%file_path%"
    echo Новый файл %counter% был создан
    set /a "counter+=1"
   
    timeout /t %N% >nul
goto :loop
:end
set /a "total_folders=counter-1"
echo Скрипт завершил работу. Общее количество созданных папок: %total_folders%
pause
```
### Пример работы кода
![](1.png)

### Пояснение кода



## Bash файл
- ### Код программы 
```bash
#!/bin/bash
export LANG=ru_RU.UTF-8
read -p "Введите числовое значение для N (интервал в секундах): " N
read -p "Введите числовое значение для M (максимальное время работы в секундах): " M

total_time=0
counter=1
current_path="$(pwd)/folder_$counter"
mkdir -p "$current_path"

while (( total_time < M )); do
    file_path="$current_path/$counter.txt"
sleep "$N"
 ((total_time += N))
    echo "Общее время работы скрипта: $total_time секунд" > "$file_path"
    echo "Новый файл $counter был создан"

    ((counter++))
    current_path="$current_path/folder_$counter"
    mkdir -p "$current_path"
    
   
    
done

total_folders=$((counter - 1))
echo "Скрипт завершил работу. Общее количество созданных папок: $total_folders"

```
### Пояснение кода

### Выводы: 
 В ходе выполнения лабораторной работы по освоению командных оболочек cmd (для операционных систем семейства MS Windows) и shell (для операционных систем семейства Unix) были получены практические навыки работы с консольными программами и командами в различных операционных системах. 
