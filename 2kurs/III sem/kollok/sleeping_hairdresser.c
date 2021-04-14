#define CHAIRS 5

typedef int semaphore

semaphore customers = 0;
semaphore barbers = 0;
semaphore mutex = 1;
int waiting = 0;

void Barber(void)
{
    while (1) {
        down(&customers);
        down(&mutex);
        waiting -= 1;
        up(&barbers);
        up(&mutex);
        CutHair();
    }
}

void Customer(void)
{
    down(&mutex);
    if (waiting < CHAIRS) {
        waiting += 1;
        up(&customers);
        up(&mutex);
        down(&barbers);
        GetHaircut();
    } else {
        up(&mutex);
    }
}
