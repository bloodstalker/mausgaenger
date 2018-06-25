
#include "./mausgaenger.h"
#include <fcntl.h>
#include <inttypes.h>
#include <linux/input.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MOUSEFILE "/dev/input/event"

void sigint_handler(int dummy) {
  printf("caught sigint.\n");
}

int mouse_watch(char* _id, char* filename, char* fileb, unsigned char dump) {
  char path[100] = {0};
  strcat(path, MOUSEFILE);
  strcat(path, _id);
  int fd;
  struct input_event ie;
  if ((fd = open(path, O_RDONLY)) == -1) {
  //if ((fd = open(path, O_RDWR)) == -1) {
    perror("opening device failed.");
    exit(EXIT_FAILURE);
  }
  FILE *out = fopen(filename, "w");
  FILE *outb = fopen(fileb, "wb");

  while (read(fd, &ie, sizeof(struct input_event))) {
    if (dump) printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
    fprintf(out, "time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
    fwrite(&ie, sizeof(struct input_event), 1, outb);
  }
  return 0;
}

int mouse_gaenger(char* _id, char* file_r) {
  char path[100] = {0};
  strcat(path, MOUSEFILE);
  strcat(path, _id);
  struct input_event ie;
  int fd = open(file_r, O_RDONLY);
  FILE *out_w = fopen(path, "wb");
  while (read(fd, &ie, sizeof(struct input_event))) {
    fwrite(&ie, sizeof(struct input_event), 1, out_w);
  }
  return 0;
}

void arg_parser(cli_arg_t* cli_arg, int argc, char** argv) {
  unsigned char dual = 0;
  cli_arg->help = 0;
  cli_arg->gang = 0;
  cli_arg->dump = 0;
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "--out") == 0) {strcpy(cli_arg->out, argv[i+1]);dual = 1;}
    else if (strcmp(argv[i], "--outb") == 0) {strcpy(cli_arg->outb, argv[i+1]);dual = 1;}
    else if (strcmp(argv[i], "--event-id") == 0) {strcpy(cli_arg->event_id, argv[i+1]);dual = 1;}
    else if (strcmp(argv[i], "--dump") == 0) {cli_arg->dump = 1; dual = 0;}
    else if (strcmp(argv[i], "--gang") == 0) {cli_arg->gang = 1; dual = 0;}
    else if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0)) {printf("fuck\n");cli_arg->help = 1; dual = 0;}
    else {printf("unknown cli arg passed:%s.\n", argv[i]);}
    if (dual) {i++;dual = 0;}
  }
}

#pragma weak main
int main (int argc, char** argv) {
  cli_arg_t cli_arg; 
  arg_parser(&cli_arg, argc, argv);
  //signal(SIGINT, sigint_handler);
  if (cli_arg.help) {
    printf("--out | text output file name.\n");
    printf("--outb | binary output file name.\n");
    printf("--event-id | mouse event file's id, e.g. 6 in event6\n");
    printf("--dump | dump text output to stdout.\n");
    printf("--gang | impersonate the mouse by writing to the corresponding event file.\n");
    printf("--help | -h | display help.\n");
    return 0;
  }
  if (cli_arg.gang) return mouse_gaenger(cli_arg.event_id, cli_arg.outb);
  else return mouse_watch(cli_arg.event_id, cli_arg.out, cli_arg.outb, cli_arg.dump);
}
