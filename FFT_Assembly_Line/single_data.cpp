//#include <thread>
//#include <atomic> 
//#include <chrono>
//#include <iostream>
//#include <condition_variable> 
//#include <string>
//#include <vector>
//#include <iomanip>
//using namespace std;
//using namespace std::chrono;
//using std::string;
//using std::vector;
//using std::mutex;
//using std::condition_variable;
//using std::thread;
//using std::ref;
//
//bool f1_input{true}, f1_out{ false },
//     f2_input{ true }, f2_out{ false },
//     f3_input{ true }, f3_out{ false };
//
//float x[8], y[8];
//const float p = 3.1416;
//
//decltype(high_resolution_clock::now()) time_begin, time_end, 
//        stage1_time_begin, stage1_time_end,
//        stage2_time_begin, stage2_time_end,
//        stage3_time_begin;
//
//void butterfly1()
//{
//    time_begin = high_resolution_clock::now();
//    while (true)
//    {
//        //有数据的时候，则进行处理
//        if (f1_input)
//        {
//            stage1_time_begin = high_resolution_clock::now();
//            f1_input = false;
//            f1_out = false;
//            //开始处理数据
//            float u, v;
//            int m1 = 1;//第一级中每个蝶群的运算碟总数——每个蝶群有1个运算蝶
//            int m2 = 2 * m1;//第一级中碟群长度——为2
//            int m3 = 4;//第一级中的蝶群个数——为4个
//
//                       //对于每个蝶群来说
//            for (int j = 0; j < m3; j++)
//            {
//                int m4 = j * m2;//蝶群址——每个碟群左上角编号
//
//
//                                //对于每个蝶群的每个运算蝶来说
//                for (int r = 0; r < m1; r++)
//                {
//                    int k1 = m4 + r;   //运算蝶上面括号内标
//                    int k2 = k1 + m1;  //运算蝶下面括号内标
//                    u = x[k2] * cos(2 * p * r / m2) + y[k2] * sin(2 * p * r / m2);
//                    v = y[k2] * sin(2 * p * r / m2) - x[k2] * cos(2 * p * r / m2);
//                    x[k2] = x[k1] - u;
//                    y[k2] = y[k1] - v;
//                    x[k1] = x[k1] + u;
//                    y[k1] = y[k1] + v;
//                }
//            }
//
//            //处理结束后，f1_out = true;
//            f1_out = true;
//            stage1_time_end = high_resolution_clock::now();
//            //不再有输入，则退出线程
//            return;
//        }
//        
//    }
//}
//void butterfly2()
//{
//    while (true)
//    {
//        //如果f1有输出，且f2可接受输入,则可以开始处理数据
//        if (f1_out && f2_input)
//        {
//            stage2_time_begin = high_resolution_clock::now();
//            f2_input = false;
//            f2_out = false;
//            float u, v;
//            int m1 = 2;//第二级中每个蝶群的运算碟总数——每个蝶群有2个运算蝶
//            int m2 = 2 * m1;//第二级中碟群长度——为4
//            int m3 = 2;//第二级中的蝶群个数——为2个
//
//                       //对于每个蝶群来说
//            for (int j = 0; j < m3; j++)
//            {
//                int m4 = j * m2;//蝶群址——每个碟群左上角编号
//
//
//                                //对于每个蝶群的每个运算蝶来说
//                for (int r = 0; r < m1; r++)
//                {
//                    int k1 = m4 + r;   //运算蝶上面括号内标
//                    int k2 = k1 + m1;  //运算蝶下面括号内标
//                    u = x[k2] * cos(2 * p * r / m2) + y[k2] * sin(2 * p * r / m2);
//                    v = y[k2] * sin(2 * p * r / m2) - x[k2] * cos(2 * p * r / m2);
//                    x[k2] = x[k1] - u;
//                    y[k2] = y[k1] - v;
//                    x[k1] = x[k1] + u;
//                    y[k1] = y[k1] + v;
//                }
//            }
//            //处理结束后，更新状态值
//            f2_input = true;
//            f2_out = true;
//            //不再有输入，则退出线程
//            if (!f1_input)
//            {
//                stage2_time_end = high_resolution_clock::now();
//                return;
//            }
//        }
//    }
//}
//void butterfly3()
//{
//    while (true)
//    {
//        //如果f2有输出，且f3可接受输入，则开始处理数据
//        if (f2_out && f3_input)
//        {
//            stage3_time_begin = high_resolution_clock::now();
//            f3_out = false;
//            f3_input = false;
//            float u, v;
//            int m1 = 4;//第三级中每个蝶群的运算碟总数——每个蝶群有4个运算蝶
//            int m2 = 2 * m1;//第三级中碟群长度——为8
//            int m3 = 1;//第二级中的蝶群个数——为1个
//
//                       //对于每个蝶群来说
//            for (int j = 0; j < m3; j++)
//            {
//                int m4 = j * m2;//蝶群址——每个碟群左上角编号
//
//
//                                //对于每个蝶群的每个运算蝶来说
//                for (int r = 0; r < m1; r++)
//                {
//                    int k1 = m4 + r;   //运算蝶上面括号内标
//                    int k2 = k1 + m1;  //运算蝶下面括号内标
//
//                    u = x[k2] * cos(2 * p * r / m2) + y[k2] * sin(2 * p * r / m2);
//                    v = y[k2] * sin(2 * p * r / m2) - x[k2] * cos(2 * p * r / m2);
//                    x[k2] = x[k1] - u;
//                    y[k2] = y[k1] - v;
//                    x[k1] = x[k1] + u;
//                    y[k1] = y[k1] + v;
//                }
//            }
//            //处理完数据，就开始更新数据
//            f3_input = true;
//            f3_out = true;
//            //this_thread::sleep_for(chrono::microseconds(100));
//            //不再有输入，则退出线程
//            if (!f1_input)
//            {
//                time_end = high_resolution_clock::now();
//                return;
//            }
//        }
//    }
//}
//void put_in()
//{
//    int i;
//    cout << " 输入序列为：" << endl;
//    for (i = 0; i < 8; i++)
//    {
//        x[i] = i;
//        y[i] = i;
//    }
//    for (i = 0; i < 8; i++)
//    {
//        cout << fixed << setprecision(6) << setw(10) << x[i] << " + " << setiosflags(ios::right) << setw(10) << y[i] << "j   ";
//        if (i % 4 == 3)
//        {
//            cout << endl;
//        }
//    }
//    cout << endl << endl;
//}
//void re_bit()
//{
//    float q11, q12, q21, q22;
//    cout << "比特逆序之后的数列为：" << endl;
//
//    q11 = x[1];
//    q12 = y[1];
//    x[1] = x[4];
//    y[1] = y[4];
//    x[4] = q11;
//    y[4] = q12;
//
//    q21 = x[3];
//    q22 = y[3];
//    x[3] = x[6];
//    y[3] = y[6];
//    x[6] = q21;
//    y[6] = q22;
//
//    cout.setf(ios::fixed);
//    for (int i = 0; i < 8; i++)
//    {
//        cout << fixed << setprecision(6) << setw(10) << x[i] << " + " << setiosflags(ios::right) << setw(10) << y[i] << "j   ";
//        if (i % 4 == 3)
//        {
//            cout << endl;
//        }
//    }
//    cout << endl << endl;
//}
//int main()
//{
//    put_in();
//    re_bit();
//    thread level_1(butterfly1), level_2(butterfly2), level_3(butterfly3);
//
//    level_1.join();
//    level_2.join();
//    level_3.join();
//
//    cout << " 输出序列为：" << endl;
//    for (int i = 0; i < 8; i++)
//    {
//        cout << fixed << setprecision(6) << setw(10) << x[i] << " + " << setiosflags(ios::right) << setw(10) << y[i] << "j   ";
//        if (i % 4 == 3)
//        {
//            cout << endl;
//        }
//    }
//    cout << endl << endl;
//    cout << "butterfly1运行时间: " << duration_cast<nanoseconds>(stage1_time_end - stage1_time_begin).count() << "纳秒" << endl;
//    cout << "butterfly2运行时间: " << duration_cast<nanoseconds>(stage2_time_end - stage2_time_begin).count() << "纳秒" << endl;
//    cout << "butterfly3运行时间: " << duration_cast<nanoseconds>(time_end - stage3_time_begin).count() << "纳秒" << endl;
//    cout << "运行时间: " << duration_cast<microseconds>(time_end - time_begin).count() << "微秒" << endl;
//    system("pause");
//    return 0;
//}