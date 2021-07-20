NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra #-fsanitize=address #-Werror

HDRS_DIRS	= ./headers $(addprefix ./headers, /data_structs /readline)
OBJS_DIR	= ./objs
SRCS_DIRS	= ./srcs $(addprefix ./srcs, \
							/errors \
							/signals \
							$(addprefix /commands,\
								/ \
								/builtin \
								/exec\
								/parser\
							)\
							/envp \
							/utils \
							/parser\
							$(addprefix /data_structs, \
								/commlist\
							)\
						)

HDRS = $(wildcard $(addsuffix /*.h, $(HDRS_DIRS)))
SRCS = $(wildcard $(addsuffix /*.c, $(SRCS_DIRS)))
OBJS = $(addprefix objs/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
VPATH = $(SRCS_DIRS)

$(OBJS_DIR)/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $< -I./headers

all: $(NAME)

$(NAME): $(OBJS)
	@if [[ `uname -s` == "Darwin" ]]; \
	then \
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L./readline-8.1/lib; \
	else \
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline;\
	fi

	@echo "Build done"

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean	$(NAME)
