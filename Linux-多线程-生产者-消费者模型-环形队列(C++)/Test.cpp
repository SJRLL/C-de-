//上一节生产者 - 消费者的例子是基于queue的, 其空间可以动态分配, 现在基于固定大小的环形队列重写这个程序 （POSIX信号量） :
//####基于环形队列的生产消费模型
//环形队列采用数组模拟，用模运算来模拟环状特性
//环形结构起始状态和结束状态都是一样的，不好判断为空或者为满，所以可以通过加计数器或者标记位来
//判断满或者空。另外也可以预留一个空的位置，作为满的状态
//但是我们现在有信号量这个计数器，就很简单的进行多线程间的同步过程

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

#define MUM 16

class RingQueue{
private:
	std::vector<int> q;
	int cap;
	sem_t data_sem;
	sem_t space_sem;
	int consume_step;
	int product_step;

public:
	RingQueue(int _cap = MUM) :q(_cap), cap(_cap)
	{
		sem_init(&data_sem, 0, 0);
		sem_init(&space_sem, 0, cap);
		consume_step = 0;
		product_step = 0;
	}

	void PutData(const int &data)
	{
		sem_wait(&space_sem);
		q[consume_step] = data;
		consume_step++;
		consume_step %= cap;
		sem_post(&data_sem);
	}
	
	void GetData(int &data)
	{
		sem_wait(&data_sem);
		data = q[product_step];
		product_step++;
		product_step %= cap;
		sem_post(&space_sem);
	}

	~RingQueue()
	{
		sem_destory(&data_sem);
		sem_destory(&space_sem);
	}
};

void *consumer(void *arg)
{
	RingQueue *rap = (RingQueue*)arg;
	int data;
	for (;;)
	{
		rqp->GetData(data);
		std::cout << "Consume data done:" << data << std::endl;
		sleep(1);
	}
}

void *productor(void *arg)
{
	RingQueue *rqp = (RingQueue)arg;
	srand((unsigned long)time(NULL));
	for (;;)
	{
		int data = rand() % 1024;
		rqp->GetData(data);
		std::cout << "Prodoct data done:" << data << std::endl;
	}
}

int main()
{
	RingQueue rp;
	pthread_t c, p;
	pthread_create(&c, NULL, consumer, (void*)&rp);
	pthread_create(&p, NULL, producter, (void*)&rp);
	pthread_join(c, NULL);
	pthread_join(p, NULL);
}