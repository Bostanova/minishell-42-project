Задачи:
bigSmile> kjdfg dmfjgkj dfg > jdhfb | jdh djhfg
kjdfg dmfjgkj dfg > jdhfb | jdh djhfg
args[0] = kjdfg			- сама команда
args[1] = dmfjgkj		- аргументы
args[2] = dfg			- аргументы
cmd->count_args:3
cmd->redir[0]:  0		- сама команда								(входной файл  0, 1, 3)
cmd->redir[1]:  1		- далее все идет аргументы для команды		(выходной файл 0, 2, 4)
cmd->pipe:      1		- наличие пайпа
cmd->infile:    (null)	- имя файла записи (входной)
cmd->outfile:   jdhfb	- имя файла записи (выходной)

bigSmile> exit

Порядое действий:
Чекаешь структуру, при наличии пайпа форкаешь професс и загоняешь в процесс, иначе просто обрабатываешь комнаду.

Для Ахмеда:

1. cmd заканчивается на null
2. env и cmd.args заканчиваются на null
3. все переменные типа char*  - нуль-терминированные строки
4.
