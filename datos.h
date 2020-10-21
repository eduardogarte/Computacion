/* datos.h */

#define READY         0


/* Currently unused. 
 * The idea was to save the size of the panel in the PCB at
 * the time of initialization. That way, the task could be
 * placed at any point in the screen.
 * Instead, currently the tasks are fixed in some rectangle 
 * in the screen defined within the task
 */

/**
 * @brief Defines a process' information
 */

struct process_control_block_t {
  unsigned        id;       //Identificador
  char           *name;     //Nombre de la tarea
  int             state;    //Estado de la tarea
  unsigned        priority; //Prioridad de la tarea

//  struct panel_t  panel;    
//  int             where_x;
//  int             where_y;

  unsigned DirSeg;          //Semento de inicio de la tarea
  unsigned DirOff;          //Desplazamiento de inicio de la tarea
  unsigned status;          //Tiempo de espera en colo de retraso
  unsigned sp;              //Apuntador de Pila local
  unsigned ss;              //Apuntador de Pila Local

  char far stack[4096];     //Espacio de Pila Local
};

typedef struct process_control_block_t  process_control_block_t;

extern process_control_block_t PCB[8];
