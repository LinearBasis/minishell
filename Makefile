#dir list
SRCS_DIR= srcs
OBJS_DIR= objs
HDRS_DIR= headers

# srcs, headers, objs, vpath
HDRS	= $(addprefix $(HDRS_DIR)/, minishell.h list.h)
SRCS 	= $(addprefix $(SRCS_DIR)/, main2.c \
				$(addprefix structs/,\
					$(addprefix list/, list.c list2.c)\
				)\
			)
OBJS 	= $(addprefix $(OBJS_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRCS))))
VPATH	= $(addprefix $(SRCS_DIR),\
		  		/ \
				/structs/list/ \
			)

# compile settings                                                 	
CC		= gcc
#CFLAGS	= -Wall -Werror -Wextra
NAME	= minishell	
 
$(OBJS_DIR)/%.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -I$(HDRS_DIR) -c $< -o $@

# main rules

.PHONY: clean fclean re all

all:	$(NAME)
	

$(NAME):		$(OBJS) 
	if [[ "$$USER" == "mgroot "]];
	then
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
	else
		$(CC) $(CFLAGs) $(OBJS) -o $(NAME) -lreadline\
			-L/Users/dnicki/.brew/Cellar/readline/8.1/lib\
			-L/Users/dnicki/.brew/Cellar/readline/8.1/include/readline
	fi

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean	$(NAME)
