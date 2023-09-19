CC = cc
ODIR = obj
BDIR = bin
SDIR = src
IDIR = include
NAME = philo
NOTLIBFT = $(IDIR)/libft/notlibft.a
RM = rm -f
CFLAGS = -Wall -Wextra -I$(IDIR) 
LFLAGS = -L$(IDIR)/notlibft -lnft
FILES =  main utils philo_init philo_life philo_forks philo_states
OBJS = $(patsubst %,$(ODIR)/%,$(FILES:=.o))
DEPS = $(patsubst %,$(SDIR)/%,$(FILES:=.d))

all: lib | $(NAME)

lib : $(NOTLIBFT)

$(ODIR):
	mkdir -p $(ODIR)

$(BDIR):
	mkdir -p $(BDIR)

$(NOTLIBFT):
	$(MAKE) -C $(IDIR)/notlibft

$(ODIR)/%.o : src/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) | $(BDIR)
	$(CC) $(CFLAGS)  -o  $@ $(OBJS) $(LFLAGS)

clean:
	$(RM) -R $(ODIR)
	$(MAKE) -C $(IDIR)/notlibft $@

fclean: clean
	$(MAKE) -C $(IDIR)/notlibft $@
	$(RM) -R $(BDIR)

re: fclean all

.PHONY: all clean fclean re
