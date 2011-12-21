// Debugging Modus einschalten/auschalten
#ifndef DEBUG
// Gibt Text auf der Konsole aus, wenn DEBUG definiert ist. Benutzung siehe printf
#define debug_print(...) \
        do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define debug_print(...)
#endif


