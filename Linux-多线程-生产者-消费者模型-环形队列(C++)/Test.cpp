//��һ�������� - �����ߵ������ǻ���queue��, ��ռ���Զ�̬����, ���ڻ��ڹ̶���С�Ļ��ζ�����д������� ��POSIX�ź����� :
//####���ڻ��ζ��е���������ģ��
//���ζ��в�������ģ�⣬��ģ������ģ�⻷״����
//���νṹ��ʼ״̬�ͽ���״̬����һ���ģ������ж�Ϊ�ջ���Ϊ�������Կ���ͨ���Ӽ��������߱��λ��
//�ж������߿ա�����Ҳ����Ԥ��һ���յ�λ�ã���Ϊ����״̬
//���������������ź���������������ͺܼ򵥵Ľ��ж��̼߳��ͬ������

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