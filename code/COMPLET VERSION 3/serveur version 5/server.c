#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include "../API/json.h"
#include "time.h"
#include <jansson.h>

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

static _Atomic unsigned int cli_count = 0;
static int id = 10;
 
pthread_t pwaiting;
struct get_json get[10];

/* Raspberry structure */
typedef struct{
    int raspfd;
    int index;
    int current_time;
}Rasp;


/* Client structure */
typedef struct {
    struct sockaddr_in addr; /* Client remote address */
    int connfd;              /* Connection file descriptor */
    int id;                  /* Client unique identifier */
    char name[32];           /* Client name */
} client_t;


typedef struct{
	int hour;
	int index;
	char* type;
}next;

Rasp rasp;

next next_coffee;

client_t *clients[MAX_CLIENTS];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t api_mutex = PTHREAD_MUTEX_INITIALIZER;


/* Add client to queue */
void queue_add(client_t *cl){
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (!clients[i]) {
            clients[i] = cl;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

/* Delete client from queue */
void queue_delete(int id){
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i]) {
            if (clients[i]->id == id) {
                clients[i] = NULL;
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *waiting(void* arg)
{
    Rasp *prasp = (Rasp *)arg;
    printf("coffee is waiting coffee %d : %d\n",next_coffee.index, prasp->current_time);
    sleep(prasp->current_time);

    char index = next_coffee.index + '0';

    put_json_file(index, "activate", "0");

    printf("%d\n",(int)prasp->current_time);
    printf("coffee is starting\n");
    write(prasp->raspfd,next_coffee.type,sizeof(next_coffee));
    return NULL;
}

void SendRasp()
{
    Rasp *raspberry = (Rasp *)malloc(sizeof(Rasp));
    

    pthread_cancel(pwaiting);
    rasp.current_time = next_coffee.hour;
    rasp.index = next_coffee.index;
    raspberry->raspfd = rasp.raspfd;
    raspberry->current_time = rasp.current_time;
    pthread_create(&pwaiting, NULL, &waiting, (void*)raspberry);
}

/* Do the GET to the API */
void Get_Api(void *arg)
{
    client_t *cli = (client_t *)arg;
    

    int min_i = -1;
    int min = 999999;

    get_json_file(get);

    char json_file[BUFFER_SZ];
    memset(json_file, 0, BUFFER_SZ);
    for(size_t i = 0; i < 10; i++)
    {
        char tmp[BUFFER_SZ];
        memset(tmp, 0, BUFFER_SZ);

        sprintf(tmp, "%s\n%d\n%d\n", get[i].type, get[i].heure, get[i].activate);
        strcat(json_file, tmp);
        
        if(get[i].activate == 1)
        {
            //write(cli->connfd,get,sizeof(get));
            int hour = get[i].heure;
            int to_wait = coffee(hour / 100, hour % 100);

            if(to_wait < min)
            {
                
                min = to_wait;
                min_i = i;

                next_coffee.index = i;
                next_coffee.type = get[i].type;
                next_coffee.hour = min;
                printf("%d\n",min);

            }
            
        }
    }
    
    write(cli->connfd, json_file, BUFFER_SZ);
    printf("get_api : %d\n", min_i);
    SendRasp();
    
}

/* Print ip address */
void print_client_addr(struct sockaddr_in addr){
    printf("%d.%d.%d.%d",
        addr.sin_addr.s_addr & 0xff,
        (addr.sin_addr.s_addr & 0xff00) >> 8,
        (addr.sin_addr.s_addr & 0xff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/* Handle all communication with the client */
void *handle_client(void *arg)
{
    cli_count++;
    client_t *cli = (client_t *)arg;

    /* displays that the connection with the client is successful */
    printf("<< receved ");
    print_client_addr(cli->addr);
    printf(" referenced by %d\n", cli->id);
    

    char buff[2];
	bzero(buff, sizeof(buff));
	ssize_t r = -1;

    /* checks if the connection with the client has not been interrupted */
    r = read(cli->connfd, buff, sizeof(buff));
    if(r != 0)
    {
        /* call the Get_Api() function */
        pthread_mutex_lock(&api_mutex);
        printf("buff = %s\n",buff);
        Get_Api(cli);
        pthread_mutex_unlock(&api_mutex);
    }
	
    

    /* Delete client from queue and yield thread */
    queue_delete(cli->id);
    
    cli_count--;
    pthread_detach(pthread_self());

    /* Close connection */
    close(cli->connfd);
    free(cli);
    return NULL;
}

void *handle_rasp()
{
    cli_count++;
    pthread_detach(pthread_self());
    return NULL;
}

int main(){
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;
    int value = 1;
    rasp.current_time = 9999999;
    rasp.index = 0;

    /* Socket settings */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.29");
    serv_addr.sin_port = htons(8080);

    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&value,sizeof(int)) < 0)
        perror("Fail reusing the same address");
    /* Bind */
    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Socket binding failed");
        return EXIT_FAILURE;
    }

    /* Listen */
    if (listen(listenfd, 10) < 0) {
        perror("Socket listening failed");
        return EXIT_FAILURE;
    }

    printf("<[ SERVER STARTED ]>\n");

    /* Accept clients */
    while (1) {

        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);

        /* Check if max clients is reached */
        if ((cli_count + 1) == MAX_CLIENTS) {
            printf("<< max clients reached\n");
            printf("<< reject ");
            print_client_addr(cli_addr);
            printf("\n");
            close(connfd);
            continue;
        }

        /* Client settings */
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->addr = cli_addr;
        cli->connfd = connfd;
        cli->id = id++;
        sprintf(cli->name, "%d", cli->id);
        
        if((cli_count) == 0)
        {
            rasp.raspfd = connfd;
            sprintf(cli->name, "%s", "===Raspberry===");
            pthread_create(&tid, NULL, &handle_rasp, NULL);
        }
        else
        {
        	
            /* Add client to the queue and fork thread */
            queue_add(cli);
            pthread_create(&tid, NULL, &handle_client, (void*)cli);
        }
        
        /* Reduce CPU usage */
        sleep(1);
        
    }

    return EXIT_SUCCESS;
}
