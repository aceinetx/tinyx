/*
tinyx
=====
binary executable format, designed to be very economical in size
made by aceinet (2022-present)
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#endif

typedef int (*entry_f)(int, char **);

void die(const char *s) {
  puts(s);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    die("e: no program specified");
  }

  FILE *p;
  size_t bin_size;

  // open specified program
  p = fopen(argv[1], "r");

  if (p == NULL) {
    die("e: couldn't find specified program\n");
  }

  // get executable size in bytes
  fseek(p, 0, SEEK_END);
  bin_size = ftell(p);
  rewind(p);

  // read executable
  char bin[bin_size];
  fread(bin, bin_size, 1, p);

  fclose(p);

  if (bin_size <= 4) {
    die("e: program may be corrupt: too few bytes at least for signature\n");
  }

  char valid_signature[] = "tiny";

  if (bin[0] == '#' && bin[1] == '!') {
    // if starts with a shebang
    // which makes the executable able to run as ./test, not with ./tinyx test
    size_t inc_size = 0;
    char c = bin[inc_size];
    while (c != '\0') {
      inc_size++;
      c = bin[inc_size];
    }

    memset(bin, '\x90',
           inc_size + sizeof(valid_signature)); // set other bytes to nop
    memcpy(bin, valid_signature, sizeof(valid_signature));
  }

  // checking signature
  char signature[sizeof(valid_signature)];
  memcpy(signature, bin, sizeof(valid_signature));
  if (strcmp(valid_signature, signature) != 0) {
    die("e: invalid signature, put valid string in assembly of your program\n");
  }

  // make space for executable code
  uint8_t *allocated_code = mmap(NULL, bin_size - sizeof(valid_signature),
                                 PROT_EXEC | PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  memcpy(allocated_code, bin, bin_size);

  // funny trick
  union {
    entry_f entry;
    void *entry_voidp;
  } exec;

  exec.entry_voidp = allocated_code + sizeof(signature);

  // finally, run the executable
  return exec.entry(argc, argv);
}
