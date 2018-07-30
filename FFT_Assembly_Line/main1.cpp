//#include <thread>
//#include <atomic> 
//#include <chrono>
//#include <iostream>
//#include <condition_variable> 
//#include <string>
//#include <vector>
//#include <time.h>
//using namespace std;
//using std::string;
//using std::vector;
//using namespace std::chrono;
//using thread_id = std::thread::id;
//
//const int WORKERS_TOTAL = 3;
//
//typedef struct worker_type
//{
//    mutex mtx;
//    condition_variable cond_has_input;
//    condition_variable cond_has_finished;
//    int has_input;
//    int has_finished;
//    thread_id thread_Id;
//    void (*thread_worker)(void *);//工作线程
//    struct worker_type* next;
//    string name;
//    int input_data;
//
//} worker;
//
//typedef struct pipeline_type {
//    int count;
//    worker* head;
//    worker* tail;
//}pipeline;
//
//void send_input_to_worker(worker* my_worker, int input)
//{
//    //获得锁
//    my_worker->mtx.lock();
//    //等待工人完成工作
//    while (!my_worker->has_finished)
//    {
//        //等待pthread_cond_wait(&worker->cond_has_finished,&worker->mtx);
//    }
//    my_worker->has_input = 1;
//    my_worker->has_finished = 0;
//    my_worker->input_data = input;
//    //发送信号pthread_cond_signal(&worker->cond_has_input);
//
//    //解锁
//    my_worker->mtx.unlock();
//}
//
//void thread_worker(void* arg)
//{
//    //循环之前，初始化
//    worker* my_worker = (worker*)arg;
//    struct timespec t;
//    int status;
//    int input;
//    t.tv_nsec = 0;
//    while (true)
//    {
//        //访问my_worker前，锁住
//        my_worker->mtx.lock();
//
//        //等待输入
//        while (!my_worker->has_input)
//        {
//            cout << "给我工作:" << my_worker->name << endl;
//            status = 1;
//            //my_worker->cond_has_input.wait(my_worker->mtx);
//        }
//        //取到输入后，进行处理
//        input = my_worker->input_data;
//        cout << my_worker->name << "收到 " << input << "处理了: " << input << "秒" << endl;
//        //_sleep(input);
//        if (my_worker->next != nullptr)
//        {
//            send_input_to_worker(my_worker->next, input - 1);
//
//        }
//        else
//        {
//            cout << my_worker->name << "我的后面没有小伙伴了" << endl;
//        }
//        my_worker->has_input = 0;
//        my_worker->has_finished = 1;
//
//        //处理完成之后，发送信号，同时解锁
//        my_worker->cond_has_finished.notify_one();
//        my_worker->mtx.unlock();
//    }
//}
//
//void pipe_line_start(pipeline* my_pipline)
//{
//    worker  *worker_p, **worker_pp;
//    vector<string> names{"Lucy", "Lily", "Lilei"};
//    int i;
//    worker_pp = &my_pipline->head;
//    for (int i = 0; i < WORKERS_TOTAL; i++)
//    {
//        *worker_pp = (worker*)malloc(sizeof(worker));
//        worker_p = *worker_pp;
//        worker_p->name = names[i];
//        worker_p->thread_worker = thread_worker;
//        worker_p->has_input = 0;
//        worker_p->has_finished = 1;
//        //初始化锁
//        //pthread_mutex_init(&worker_p->mtx, NULL);
//        //pthread_cond_init(&worker_p->cond_has_input, NULL);
//        //pthread_create(&worker_p->thread_id, NULL, worker_p->thread_worker, worker_p);
//        worker_pp = &worker_p->next;
//    }
//    my_pipline->tail = *worker_pp;
//    worker_p->next = nullptr;
//}
//
//int main1()
//{
//    int i;
//    pipeline my_pipline;
//    pipe_line_start(&my_pipline);
//
//    while (1)
//    {
//        cin >> i;
//        send_input_to_worker(my_pipline.head, i);
//    }
//    system("pause");
//    return 0;
//}