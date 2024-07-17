#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "buffer.h"
#include "utils.h"
#ifndef WIN32
#include <unistd.h>
#include <execinfo.h>
#endif

const bool TRACE = true;


char *copy_name (char *name)
{
  size_t len = strlen(name) + 1;
  char *out = malloc(sizeof(char) * len);
  strncpy(out, name, len);
  return out;
}

void print_backtrace ()
{
#ifndef WIN32
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  backtrace_symbols_fd(array, size, STDERR_FILENO);
#endif /* WIN32 */
}

void print_trace(const char *format, ...) {
    char buf[1024];  // Assurez-vous que ce tampon est assez grand pour contenir le résultat
    va_list args;
    va_start(args, format);

    vsprintf(buf, format, args);
    va_end(args);

    // Affichage de la trace si c'est actif
    if (TRACE) {
        printf(COLOR_BLUE "TRACE %d:%d : ", buf_getline(), buf_getcol());
        printf("%s\n" COLOR_DEFAULT, buf);
    }
}

void print_error(const char *format, ...) {
    char buf[1024];  // Assurez-vous que ce tampon est assez grand pour contenir le résultat
    va_list args;
    va_start(args, format);

    vsprintf(buf, format, args);
    va_end(args);

    // Affichage de la trace si c'est actif
    printf(COLOR_RED "\n== ERROR %d:%d : ", buf_getline(), buf_getcol());
    printf("%s\n" COLOR_DEFAULT, buf);
}

void print_warn(const char *format, ...) {
    char buf[1024];  // Assurez-vous que ce tampon est assez grand pour contenir le résultat
    va_list args;
    va_start(args, format);

    vsprintf(buf, format, args);
    va_end(args);

    // Affichage de la trace si c'est actif
    printf(COLOR_YELLOW_ORANGE "WARN %d:%d : ", buf_getline(), buf_getcol());
    printf("%s\n" COLOR_DEFAULT, buf);
}