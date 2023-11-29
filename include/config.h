#ifndef CONFIG_H
#define CONFIG_H

#define PRINTDBG(f_, ...) \
  fprintf(stderr, "%s" f_ "%s", "\e[38;5;87m", ##__VA_ARGS__, "\e[0m\n")

#define PRINTERR(f_, ...) \
  fprintf(stderr, "%s" f_ "%s", "\e[38;5;9m", ##__VA_ARGS__, "\e[0m\n")

#define PRINTALRT(f_, ...) \
  fprintf(stderr, "%s" f_ "%s", "\e[38;5;226m", ##__VA_ARGS__, "\e[0m\n")

#define PRINTSUCCES(f_, ...) \
  fprintf(stderr, "%s" f_ "%s", "\e[38;5;82m", ##__VA_ARGS__, "\e[0m\n")

#endif
