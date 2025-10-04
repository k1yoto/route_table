CC       := gcc
CFLAGS   := -Wall -Wextra -O2 -g
VALGRIND := valgrind
VFLAGS   := -s --leak-check=full --show-leak-kinds=all --track-origins=yes

# 共通ソース
COMMON_SRCS := radix.c test.c
COMMON_OBJS := $(COMMON_SRCS:.c=.o)

# プログラム main
PROGS     := main
SRCS_main := main.c $(COMMON_SRCS)
OBJS_main := $(SRCS_main:.c=.o)

all: $(PROGS)

# main のリンク
# inet_net_pton のために -lresolv を追加
main: $(OBJS_main)
	$(CC) $(CFLAGS) -o $@ $^ -lresolv

# valgrind 実行
main-valgrind: main
	$(VALGRIND) $(VFLAGS) ./main

# .c → .o のルール
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 依存関係
main.o:   radix.h test.h
radix.o:  radix.h
test.o:   test.h

clean:
	rm -f $(PROGS) *.o

.PHONY: all clean main-valgrind