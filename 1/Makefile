# Компилятор и опции компиляции
CC=gcc
CFLAGS=-g -ggdb -std=c11 -pedantic -W -Wall -Wextra -D_POSIX_C_SOURCE=200809L

# Директории исходных файлов, объектных файлов и исполняемых файлов
SRC=src
BUILD=build
BIN=bin
DEBUG=$(BUILD)/debug
RELEASE=$(BUILD)/release

# Выбор режима сборки (debug или release)
ifeq ($(MODE), release)
    CFLAGS=-std=c11 -pedantic -W -Wall -Wextra -Werror
    OUT_DIR=$(BIN)/release
    BUILD_DIST=$(RELEASE)
else
    OUT_DIR=$(BIN)/debug
    BUILD_DIST=$(DEBUG)
endif

# Исходные файлы
SRCS=$(wildcard $(SRC)/*.c)

# Объектные файлы
OBJS=$(patsubst $(SRC)/%.c, $(BUILD_DIST)/%.o, $(SRCS))

# Правило сборки по умолчанию
.DEFAULT_GOAL := all

# Правила сборки
all: $(OUT_DIR)/lab1

# Создание директории для исполняемого файла
$(OUT_DIR)/lab1: $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^
# Создание объектных файлов
$(BUILD_DIST)/%.o : $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# Очистка сгенерированных файлов
clean:
	rm -rf $(BUILD) $(BIN)