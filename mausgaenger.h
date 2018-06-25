
#ifndef _MOUSE_DOPP_H
#define _MOUSE_DOPP_H 
typedef struct {
  char out[256];
  char outb[256];
  char event_id[8];
  unsigned char dump;
  unsigned char gang;
  unsigned char help;
}cli_arg_t;
void arg_parser(cli_arg_t* cli_arg, int argc, char** argv);
void sigint_handler(int dummy);
int mouse_watch(char* _id, char* filename, char* fileb, unsigned char dump);
int mouse_gaenger(char* _id, char* file_r);
#endif
