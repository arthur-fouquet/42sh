##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for input part 
##

## ONLY Allowed to be edited by Killian


INPUT_NAME	=	input				\
				print				\
				queue				\
				terminal			\
				get_data			\
				init_exec			\
				special_key			\
				linked_list			\
				write_dir			\
				dyna_rebind			\
				flag_history		\
				delete_node			\
				control_tower		\
				builtin_input		\
				auto_compression	\
				exit_term			\
				prompt	\

INPUT_SRC = $(addprefix src/input/, $(addsuffix .c, $(INPUT_NAME)))
