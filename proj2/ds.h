/*
 *  Distributed system implementation using IPC.
 */

#ifndef DS_H
#define DS_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define N 7

#define QUEUE_KEY_PREFIX 256
#define DS_MESSAGE_TYPE 1
#define MONITOR_PID 0

typedef enum {ELECTION, OK, COORDINATOR, GENERIC} contentMsg;
typedef enum {IDLE, DEAD, CALL_ELECTION, WAITING_LEADER, LEADER} state;

typedef struct msgbuf {
  long mtype;      /* message type */
  contentMsg c;
  int receiver;
} Msgbuf;

/* Get N communication queues */
void get_queues();  

/* Send a message to Pj. */
void send_message(int j, const void* buffer, size_t msgsize);
/* Broadcast a message to all processes, including itself. */
void broadcast(const void* buffer, size_t msgsize);
  
/* Wait for a new message */ 
void receive_message(int pid, void* buffer, size_t msgsize);
/* Returns -1 immediately if no message is available in the queue. 
   Returns 0 and a new message in buffer otherwise. */
int nowait_receive_message(int pid, void* buffer, size_t msgsize);

#endif
