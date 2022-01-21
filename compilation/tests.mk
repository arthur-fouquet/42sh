##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Sources for parsing part
##

## ONLY Allowed to be edited by Edouard and Tom

TESTS_PARSERS_FILE=\
	tests_clean_string.c	\
	tests_lexer.c			\
	tests_cmd_ll.c			\
	tests_parser.c			\
	test_exec.c				\
	test_built_in.c			\
	test_header.c			\
	test_bonus.c			\
	test_common.c

TEST_PARSER_SRC=$(addprefix tests/unit_tests/, $(TESTS_PARSERS_FILE))