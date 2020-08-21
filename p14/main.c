#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * @fn int send_message(int argc, char** argv)
 * @brief sends a message to the specified queue (specified in the first command line argument)
 * @param argc number of command line arguments
 * @param argv list of the command line arguments
 * @return - 1 if some error occured, 0 otherwise
 */
int send_message(int argc, char** argv)
{
    mqd_t      queue = 0;
    struct mq_attr attrs;
    size_t msg_len   = 0;
    int     ret_flag = 0;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <queuename> <message>\n", argv[0]);
        ret_flag = 1;
    }

    queue = mq_open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, NULL);
    
    if (-1 == queue)
    {
        perror("mq_open");
        ret_flag = 1;
    }

    if (-1 == mq_getattr(queue, &attrs))
    {
        perror("mq_getattr");
        mq_close(queue);
        ret_flag = 1;
    }

    msg_len = strlen(argv[2]);
    if (msg_len > LONG_MAX || (long)msg_len > attrs.mq_msgsize)
    {
        fprintf(stderr, "Your message is too long for the queue.\n");
        mq_close(queue);
        ret_flag = 1;
    }

    if (-1 == mq_send(queue, argv[2], strlen(argv[2]), 0))
    {
        perror("mq_send");
        mq_close(queue);
        ret_flag = 1;
    }

    return ret_flag;
}

/**
 * @fn int receive_message(int argc, char **argv)
 * @brief prints the message from the specified queue, in any
 * @param argc number of command line arguments
 * @param argv list of the command line arguments
 * @return 1 if some error occured, 0 otherwise
 */
int receive_message(int argc, char **argv)
{
    mqd_t      queue = 0;
    struct mq_attr attrs;
    char *msg_ptr = NULL;
    ssize_t    recvd = 0;
    size_t         i = 0;
    int     ret_flag = 0;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <queuename>\n", argv[0]);
        ret_flag = 1;
    }

    queue = mq_open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR , NULL);


    if (-1 == queue)
    {
        perror("mq_open");
        ret_flag = 1;
    }

    if (-1 == mq_getattr(queue, &attrs))
    {
        perror("mq_getattr");
        mq_close(queue);
        ret_flag = 1;
    }

    msg_ptr = calloc(1, attrs.mq_msgsize);
    
    if (NULL == msg_ptr)
    {
        perror("calloc for msg_ptr");
        ret_flag = 1;
        return 1;
    }

    recvd = mq_receive(queue, msg_ptr, attrs.mq_msgsize, NULL);
    if (-1 == recvd)
    {
        perror("mq_receive");
        ret_flag = 1;
    }

    printf("Message: '");

    for (i = 0; i < (size_t)recvd; i++)
    {
        putchar(msg_ptr[i]);
    }
    printf("'\n");

    return ret_flag;
}


int main(int argc, char **argv)
{

    if (0 == send_message(argc, argv))
    {
        sleep(1);

        if (1 == receive_message(argc,argv))
        {
            fprintf(stderr,"Failed to receive message.\n");
        }

    }
    else
    {
        fprintf(stderr,"Failed to send message.\n");
    }
    
    return 0;
}