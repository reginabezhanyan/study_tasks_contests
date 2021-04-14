#define N 5
#define LEFT (i - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef int semaphore;

int state[N];
semaphore mutex = 1;
semaphore s[N];

void Philosopher(int i)
{
    while (1) {
        Think();
        TakeForks(i);
        Eat();
        PutForks(i);
    }
}

void TakeForks(int i)
{
    down(&mutex);
    state[i] = HUNGRY;
    Test(i);
    up(&mutex);
    down(&s[i]);
}

void PutForks(int i)
{
    down(&mutex);
    state[i] = THINKING;
    Test(LEFT);
    Test(RIGHT);
    up(&mutex);
}

void Test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] !=  EATING) {
        state[i] = EATING;
        up(&s[i]);
    }
}
