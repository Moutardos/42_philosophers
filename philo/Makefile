CC = cc
ODIR = obj
BDIR = bin
SDIR = src
IDIR = include
NAME = philo
RM = rm -f
CFLAGS = -Wall -Wextra -I$(IDIR) 
FILES =  main utils philo_init philo_life philo_forks philo_states utils_parsing
OBJS = $(patsubst %,$(ODIR)/%,$(FILES:=.o))
DEPS = $(patsubst %,$(SDIR)/%,$(FILES:=.d))

all: $(NAME)

$(ODIR):
	mkdir -p $(ODIR)

$(BDIR):
	mkdir -p $(BDIR)

$(ODIR)/%.o : src/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) | $(BDIR)
	$(CC) $(CFLAGS)  -o  $@ $(OBJS)

clean:
	$(RM) -R $(ODIR)

fclean: clean
	$(RM) -R $(BDIR)

re: fclean all

.PHONY: all clean fclean re
