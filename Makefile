name = "bhola"
version = "1.0.0"
# Directory structure
# /
# |-- Makefile
# |-- main.c
# |-- collection/
# |   |-- linked_list.c
# |   |-- linked_list.h
# |--build/

cc = gcc
cflags = -I./collection -Wall -Wextra -Werror -g
src = main.c collection/linked_list.c
obj = $(src:%.c=build/%.o)
target = build/$(name)
.PHONY: all clean
all: $(target)
$(target): $(obj) | build
	@$(cc) $(cflags) -o $@ $^
build/%.o: %.c | build
	@$(cc) $(cflags) -c $< -o $@
build:
	@mkdir -p build/collection
run: $(target)
	@./$(target)
clean:
	@rm -rf build
