void writing_pipe(int pipe[], long int times[], int i, char *message);
void reader (FILE* stream);
void reading_messages(int pipe[]);
void writer(const char* message, long int* times, int i, FILE* stream);
