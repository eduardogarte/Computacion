
typedef void (*task_x) (void);

/*
extern void init_task(void (*task)(void), unsigned task_id, const char *task_name, 
               unsigned int x, unsigned int y, unsigned int width, unsigned int height);
*/

extern void init_task(void (*task)(void), unsigned task_id, const char *task_name);