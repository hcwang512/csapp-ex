/*************************************************************************
	> File Name: tiny.c
	> Author: hcwang
	> Mail: shexing.w@gmail.com 
	> Created Time: 2015年06月02日 星期二 17时18分37秒
 ************************************************************************/

#include "csapp.h"
#include "sbuf.h"

#define NTHREADS 4
#define SBUFSIZE 16
#define MAX_NTHREADS 1024
#define THREAD_DEBUG 0

/* shared buffer of connected despriptors */
sbuf_t sbuf;
enum BOOL {FALSE, TRUE};
typedef struct {
    pthread_t tid; // thread tid
    int b_exit; // the tag for exit this thread
    int b_running; //business in running not on wait
} thread_status;

sem_t strategy_mutex;
sem_t tids_status_nums_mutex;

int current_num_thrs = NTHREADS;
thread_status *tids_exit_tags = NULL;
void doit(int fd);
void *doit_thread(void *vargp);
void read_requestthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *srrnum, char *shortmsg, char *longmsg);
void *manager_thread(void *vargp);
void manager_threads(thread_status *tid_status, int buffer_counter, int *nums_thrs);
void debug_command();
void doit_thread_cleanup(void *arg);

int main(int argc, char **argv){
    int i, listenfd, confd, port;

    thread_status tids_tags[4] = {{0,0,0}};
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    pthread_t tid;
    fd_set read_set, ready_set;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    (void)signal(SIGPIPE, SIG_IGN);
    port = atoi(argv[1]);
    sbuf_init(&sbuf, SBUFSIZE);
    Sem_init(&strategy_mutex, 0, 1);
    Sem_init(&tids_status_nums_mutex, 0, 1);

    listenfd = Open_listenfd(port);
    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);
    Pthread_create(&tid, NULL, manager_thread, NULL);

    for(i = 0; i < NTHREADS; i++)
        Pthread_create(&tid, NULL, doit_thread, &tids_tags[1]);

    while(1){
        ready_set = read_set;
        Select(listenfd+1, &ready_set, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &ready_set)){
#ifdef THREAD_DEBUG
            printf("command enter:\n");
#endif
            debug_command();
        }
        if(FD_ISSET(listenfd, &ready_set)){
            clientlen = sizeof(clientaddr);
            confd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            sbuf_insert(&sbuf, confd);
            V(&strategy_mutex);
        }
    }
}

void *manager_thread(void *vargp){
    tids_exit_tags = (thread_status *)Malloc(sizeof(thread_status)*MAX_NTHREADS);
    memset(tids_exit_tags, 0, sizeof(thread_status)*MAX_NTHREADS);
    pthread_t self_tid = pthread_self();
    Pthread_detach(self_tid);
    int vCounter = 0;
    struct timespec ts;
    while(1){
        if(clock_gettime(CLOCK_REALTIME, &ts) == -1)
            printf("clock_gettime");
        ts.tv_sec += 10;
        sem_timedwait(&strategy_mutex, &ts);
        Sleep(1);
        if(++vCounter == SBUFSIZE){
            vCounter = 0;
            int item_counter = sbuf_item_counter(&sbuf);
            manager_threads(tids_exit_tags, item_counter, &current_num_thrs);
        }

    }
    free(tids_exit_tags);
}

void manager_threads(thread_status *tid_status, int buffer_counter, int *nums_thrs){
    int i = 0;
    int l_nums_thread = *nums_thrs;
    int num_threads_changed = 0;
    int num_threads_not_working = 0;
    printf("manager_threads buffer_counter &d, nums_thrs %d, tid_status %p \n", buffer_counter, (*nums_thrs), tid_status);
    P(&tids_status_nums_mutex);
    if(buffer_counter == 0 && *nums_thrs > NTHREADS){
        i = 0;
        while( i < MAX_NTHREADS){
            i++;
            if(tid_status[i].tid && !tid_status[i].b_exit){
                if(0 != pthread_cancel(tid_status[i].tid)){
                    printf("pthread_cancel error!");
                }
                tid_status[i].b_exit = TRUE;
                if(num_threads_changed++ > NTHREADS){
                    break;
                }
                    
            }
        }
    }else if(buffer_counter == SBUFSIZE){
        i = 0;
        while(i < MAX_NTHREADS){
            i++;
            if(tid_status[i].tid == 0 && sbuf_item_counter(&sbuf) == SBUFSIZE) {
                tid_status[i].b_exit = FALSE;
                tid_status[i].b_running = FALSE;
                Pthread_create(&(tid_status[i].tid), NULL, doit_thread, &tid_status[i]);
                printf("Create tid %08x \n", tid_status[i].tid);
                if(num_threads_changed++ > NTHREADS)
                    break;
                sleep(1);
            }else if(tid_status[i].tid && !tid_status[i].b_running){
                num_threads_not_working++;
            }
        }
        sleep(4);
        *nums_thrs += num_threads_changed;
    }
    V(&tids_status_nums_mutex);
}

void debug_command(){
    char buf[MAXLINE];
    if(!Fgets(buf, MAXLINE, stdin))
        eixt(0);
    int i = 0;
    printf("current_num_thrs %d\n", current_num_thrs);
    for(i = 0; i < MAX_NTHREADS; i++){
        if(tids_exit_tags[i].tid){
            printf("tid\n");
        }
    }
}

void doit_thread_cleanup(void *arg){
    P(&tids_status_nums_mutex);
    printf("doit_thread_cleanup: 0x%p\n", arg);
    thread_status* tid = (thread_status*)arg;
    tid->tid = 0;
    tid->b_exit = 0;
    tid->b_running = FALSE;
    current_num_thrs--;
    V(&tids_status_nums_mutex);
}

void *doit_thread(void *vargp){
    pthread_cleanup_push(doit_thread_cleanup, vargp);
    thread_status *tid = (thread_status*)vargp;
    pthread_t self_tid = pthread_self();
    Pthread_detach(self_tid);

    while(1) {
        tid->b_running = FALSE;
        int confd = sbuf_remove(&sbuf);
        tid->b_running = TRUE;
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        doit(confd);
        Close(confd);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        if(sbuf_item_counter(&sbuf) == 0 && tid->b_exit)
            break;


    }
    pthread_cleanup_pop(1);

}
void read_requesthdrs(rio_t *rp){
    char buf[MAXLINE];
    int head_nums = 0;
    Rio_readlineb(rp, buf, MAXLINE);
    while(strcmp(buf, "\r\n")){
        Rio_readlineb(rp, buf, MAXLINE);
        printf("%s", buf);
        if(head_nums++ > MAXLINE)
            break;
        
    }
    return;
}

void doit(int fd) {
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);
    if(strcasecmp(method, "GET")){
        clienterror(buf, method, "501", "NOT Implemented", "Tiny doesnot implement this method");
        return;
    }

    read_requesthdrs(&rio);
    is_static = parse_uri(uri, filename, cgiargs);
    if(stat(filename, &sbuf) < 0){
        clienterror(fd, filename, "404", "Not Found", "Tiny could not find this file");
        return;

    }

    if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)){
        clienterror(fd, filename, "403", "Forbidden", "Tiny could not read the file");
        return;
    }
    if(is_static) {
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden", "Tiny could not read the file");
            return;
        }
        serve_static(fd, filename, sbuf.st_size);
    }else{
        serve_dynamic(fd, filename, sbuf.st_size);
    }

}

int parse_uri(char *uri, char *filename, char *cgiargs){
    char *ptr;
    if(!strstr(uri, "cgi-bin")){
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if(uri[strlen(uri) -1 ] == '/')
            strcat(filename, "home.html");
        return 1;
    }
    else {
        ptr = index(uri, "?");
        if(ptr){
            strcpy(cgiargs, ptr+1);
            *ptr = '\0';
        }
        elsestrcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

void serve_static(int fd, char *filename, int filesize){
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");    //line:netp:servestatic:beginserve
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));       //line:netp:servestatic:endserve
    srcfd = Open(filename, O_RDONLY, 0);    //line:netp:servestatic:open
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);//line:netp:         servestatic:mmap
    Close(srcfd);                           //line:netp:servestatic:close
    Rio_writen(fd, srcp, filesize);         //line:netp:servestatic:write
    Munmap(srcp, filesize);                 //line:netp:servestatic:munmap
}


void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
    strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpeg");
    else
    strcpy(filetype, "text/plain");
}

void serve_dynamic(int fd, char *filename, char *cgiargs)
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

    if (Fork() == 0) { /* child */ //line:netp:servedynamic:fork
    /* Real server would set all CGI vars here */
    setenv("QUERY_STRING", cgiargs, 1); //line:netp:servedynamic:setenv
    Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */ //line:netp:   servedynamic:dup2
    Execve(filename, emptylist, environ); /* Run CGI program */ //line:netp:        servedynamic:execve
    }
    Wait(NULL); /* Parent waits for and reaps child */ //line:netp:servedynamic:wait
}

void clienterror(int fd, char *cause, char *errnum,
        char *shortmsg, char *longmsg)
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}



