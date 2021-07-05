NAME = minishell.exe

MAIN = main2.c

CC = gcc

SRCS_DIRS = . ./signals ./do_command ./envp ./utils

CFLAGS = -fsanitize=address

OBJS_DIR = ./objs

LANGUAGE_END = .c

SRCS = $(wildcard $(addsuffix /*$(LANGUAGE_END), $(SRCS_DIRS)))

OBJS = $(addprefix objs/, $(notdir $(patsubst %$(LANGUAGE_END), %.o, $(SRCS))))

VPATH = $(SRCS_DIRS)

$(OBJS_DIR)/%.o: %$(LANGUAGE_END)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L/Users/dnicki/.brew/Cellar/readline/8.1/lib

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean	$(NAME)
