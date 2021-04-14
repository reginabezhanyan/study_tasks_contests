typedef int semaphore;

semaphore mutex = 1;
semaphore db = 1;
int rc = 0;

void Reader(void)
{
    while (1) {
        down(&mutex);
        rc += 1;
        if (rc == 1) {  
            down(&db);
        }
        up(&mutex);

        ReadDataBase();

        down(&mutex);
        rc -= 1;
        if (rc == 0) {
            up(&db);
        }
        up(&mutex);
        UseDataRead();
    }
}

void Writer(void)
{
    while(1) {
        ThinkUpData();
        down(&db);
        WriteDataBase();
        up(&db);
        
    }
}
