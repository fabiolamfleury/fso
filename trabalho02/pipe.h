void writing_pipe(int pipe[], long int times[], int i, char *message);
void reader (FILE* stream, long int times[], struct timeval initial_time);
void reading_messages(int sleepy_pipe[], int active_pipe[]);
void writer(const char* message, long int* times, int i, FILE* stream);
