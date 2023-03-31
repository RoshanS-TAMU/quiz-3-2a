#include <iostream>
#include <semaphore.h>
#include <thread>
using namespace std;
// include additional necessary headers

void query(int printNum,sem_t responseSem,sem_t querySem) {
    // Should print: the print number (starting from 0), "SYN", and the three dots "..."
    for (int i=0;i<printNum;++i){
        if (i>0){sem_wait(&querySem);}
    printf("[%d] SYN ...", i);
    sem_post(&responseSem);
    }
}

void response(int count,sem_t responseSem,sem_t querySem) {
    // Should print "ACK"
    for (int i=0;i<count;++i){
        if(i>0){sem_wait(&responseSem);}
    printf("ACK\n");
    sem_post(&querySem);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./handshake <count>\n");
        exit(1);
    }

    /**
     * Steps to follow:
     * 1. Get the "count" from cmd args
     
     * 2. Create necessary synchronization primitive(s)
     * 3. Create two threads, one for "SYN" and the other for "ACK"
     * 4. Provide the threads with necessary args
     * 5. Update the "query" and "response" functions to synchronize the output
    */
   
   int count = atoi(argv[1]);
    sem_t querySem, responseSem;
    thread t1(query,count,responseSem,querySem);
    thread t2(response,count,responseSem,querySem);
    t1.join();
    t2.join();
    return 0;
}
