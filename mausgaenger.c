
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

#pragma weak main
int main (int argc, char** argv) {
  //signal(SIGINT, sigint_handler);
  return mouse_watch(argv[1], argv[2], argv[3], 0);
  //return mouse_gaenger(argv[1], argv[2]);
}
