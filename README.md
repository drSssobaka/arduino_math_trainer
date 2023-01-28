# arduino_math_trainer
Математический тренажер на базе arduino

Тренажер генерирует пару случайных чисел, а ученику необходимо посчитать в уме сумму чисел и ввести ее с клавиатуры.
Для создания тренажера нужны:
1) модуль Arduino UNO или один из клонов
2) LCD-дисплей 1602 (2 строки по 16 символов), подключенный через pcf8574-подобный i2c-переходник
3) клавиатура 4x4 (16 кнопок), подключенная через pcf8574-подобный i2c-переходник