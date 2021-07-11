NAME = minishell

CC = gcc
CFLAGS = -fsanitize=address -Wall -Wextra # -Werror

SRCS_DIRS = . ./signals ./do_command ./envp ./utils
OBJS_DIR = ./objs

HDRS = $(wildcard $(addsuffix /*.h, $(SRCS_DIRS)))
SRCS = $(wildcard $(addsuffix /*.c, $(SRCS_DIRS)))
OBJS = $(addprefix objs/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
VPATH = $(SRCS_DIRS)

$(OBJS_DIR)/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	@if [[ "$$LOGNAME" == "pp189" ]]; \
	then \
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline; \
	elif [[ "$$LOGNAME" == "dnicki" ]]; \
	then \
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L/Users/dnicki/.brew/Cellar/readline/8.1/lib; \
	else \
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L/Users/mgroot/.brew/Cellar/readline/8.1/lib; \
	fi

	@echo "Build done"

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean	$(NAME)
