# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lduboulo && lzima				                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 18:29:51 by lduboulo          #+#    #+#              #
#    Updated: 2022/11/02 20:09:08 by ngda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS

GREEN	= \033[1;32m
RED 	= \033[1;31m
ORANGE	= \033[1;33m
BUILD	= \e[38;5;225m
SEP		= \e[38;5;120m
DUCK	= \e[38;5;227m
RESET	= \033[0m

# COLORS

##############################  FOLDER  ########################################
O_DIR			:= ./objs/
SRCS_DIR		:= ./srcs/
################################################################################


##############################   FILES  ########################################
SRCS_FILES		= main.c \
				  mlx_utils.c \
				  colors.c \
				  vector.c \
				  vector2.c \
				  vector3.c \
				  raytracing.c \
				  shadow.c \
				  camera.c \
				  intersection.c \
				  cylinder.c \
				  parsing.c \
				  parsing_utils.c \
				  check_args.c \
				  clean.c \
				  init.c \
				  fill_obj_1.c \
				  fill_obj_2.c \
				  get.c \
				  valid_char.c \
################################################################################

OBJS			:= $(addprefix $(O_DIR), $(SRCS_FILES:.c=.o))

HEADS_DIR		= ./includes/

NAME			= miniRT


LIB_MLX			= ./mlx/
LIBUTILS		= ./utils/


MAKELIB			= ${MAKE} -C
CC				= gcc
AR				= ar rcs
MKDIR			= mkdir -p
RM				= rm -rf


CFLAGS			= -Wall -Wextra -Werror -Ofast #-g3 -fsanitize=address
MLXFLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit


TSEP			= ${SEP}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=${RESET}



all:			${NAME}

${NAME}:		${OBJS}
				@printf "\n${GREEN}Compiling of ${NAME} ✅ done !${RESET}"
				@printf "\n\n"
				@printf "\e[4m\e[1mCompiling MiniLibX 🚧\n${RESET}"
				@${MAKELIB} ${LIB_MLX} 
				@printf "${GREEN}Compiling of MiniLibX ✅ done !\n\n${RESET}"
				@printf "\e[4m\e[1mCompiling Libft 🚧\n${RESET}"
				@${MAKELIB} ${LIBUTILS}
				@printf "\n${GREEN}Compiling of Libft ✅ done !\n\n${RESET}"
				@printf "${TSEP}\n"
				@printf "${GREEN} 💻 Successfully compiled ${NAME} .o's${RESET} ✅\n"
				@${CC} ${CFLAGS} ${MLXFLAGS} -o ${NAME} ${OBJS} ${LIBUTILS}/libutils.a
				@printf "${GREEN} 💻 Successfully created ${NAME} executable${RESET} ✅\n"
				@printf "${TSEP}\n"

$(O_DIR)%.o : $(SRCS_DIR)%.c includes/miniRT.h Makefile
				@${MKDIR} ${O_DIR}
				@${CC} ${CFLAGS} -Imlx -o $@ -c $<
				@printf "\e[1K\r${BUILD}$@ from $<${RESET}"

clean :
				@${RM} ${O_DIR}
				@${MAKELIB} ${LIBUTILS} clean
				@printf "${RED} 🧹 Deleted ${NAME} .o's${RESET} ❌\n"
				@printf "${RED}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-${RESET}\n"

fclean :
				@${RM} ${O_DIR}
				@printf "${RED}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-${RESET}\n"
				@printf "${RED} 🧹 Deleted ${NAME} .o's${RESET} ❌\n"
				@${RM} ${NAME} ${NAME}.dSYM
				@${MAKELIB} ${LIBUTILS} fclean
				@${MAKELIB} ${LIB_MLX} clean
				@printf "${RED} 💥 Deleted ${NAME} files${RESET} ❌\n"
				@printf "${RED}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-${RESET}\n"

re : 			fclean all

norm :
				@${MAKELIB} ${LIBUTILS} norm
				@printf "${DUCK} 🐥 Checking Norm for ${NAME}${RESET}\n"
				@norminette ${SRCS_DIR}
				@norminette ${HEADS_DIR}

.PHONY : all clean fclean re norm
