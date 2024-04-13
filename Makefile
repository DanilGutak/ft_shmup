CXX			= c++

NAME		= ft_shmup

RM			= rm -rf

SRCS_DIR	= src


OBJS_DIR	= obj

CXXFLAGS	= -Wall -Wextra -Werror -MP -MD -std=c++98 -g -Iinc 



SRCS   	= \
		$(SRCS_DIR)/main.cpp \
		$(SRCS_DIR)/Player.cpp \
		$(SRCS_DIR)/Enemy.cpp \
		$(SRCS_DIR)/Background.cpp \

OBJS		= $(SRCS:${SRCS_DIR}/%.cpp=${OBJS_DIR}/%.o)

DEPS	= $(OBJS:%.o=%.d)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -lncursesw -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


all		: $(NAME)

fclean	: clean
		$(RM) $(NAME)
		$(RM) $(TEST_OBJS_DIR)
		$(RM) $(OBJS_DIR)

clean:
	$(RM) $(OBJS)

re		: fclean all

run		: all
	./$(NAME)

-include $(DEPS)

.PHONY	: all clean fclean re run
