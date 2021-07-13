NAME = minishell

CC = gcc
CFLAGS = -fsanitize=address -Wall -Wextra # -Werror

HDRS_DIR	= ./headers
OBJS_DIR	= ./objs
SRCS_DIRS	= ./srcs $(addprefix ./srcs, \
							/signals \
							/builtin_command \
							/envp \
							/utils \
							/parser\
							$(addprefix /data_structs, \
								commlist\
								list\
								stack\
							)\
						)

HDRS = $(wildcard $(addsuffix /*.h, $(HDRS_DIRS)))
SRCS = $(wildcard $(addsuffix /*.c, $(SRCS_DIRS)))
OBJS = $(addprefix objs/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
VPATH = $(SRCS_DIRS)

$(OBJS_DIR)/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(HDRS_DIR)

# print_info:
# 	@echo $(SRCS_DIRS)
# 	@echo $(SRCS)
# 	@echo $(HDRS)
# 	@echo $(OBJS)

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
