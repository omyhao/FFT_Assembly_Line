//#include <math.h>
//#include <time.h>
//#include <windows.h>
//#include <conio.h>
//#include"omp.h" 
//#include <stdio.h>
//#define p 3.1416
//
//float x[8];
//float y[8];
//
//void put_in();
//void re_bit();
//void butterfly1();
//void butterfly2();
//void butterfly3();
//
//int main()
//{
//
//
//    double run_time;
//    _LARGE_INTEGER time_start;  //开始时间  
//    _LARGE_INTEGER time_over;   //结束时间  
//    double dqFreq;      //计时器频率  
//    LARGE_INTEGER f;    //计时器频率  
//    QueryPerformanceFrequency(&f);
//    dqFreq = (double)f.QuadPart;
//    QueryPerformanceCounter(&time_start);   //计时开始！！！
//
//    put_in();
//    re_bit();
//    butterfly1();
//    butterfly2();
//    butterfly3();
//
//
//    QueryPerformanceCounter(&time_over);    //计时结束！！！  
//    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
//
//
//    printf(" 输出序列为：\n");
//    for (int i = 0; i < 8; i++)
//        printf(" %f+j%f ", x[i], y[i]);
//    printf("\n\n");
//    //getchar();
//
//    printf("\nrun_time：%fus\n", run_time);
//    system("pause");
//    return 0;
//}
//void put_in()
//{
//    int i;
//    printf(" 输入序列为：\n");
//    for (i = 0; i < 8; i++)
//    {
//        x[i] = i;
//        y[i] = i;
//    }
//    for (i = 0; i < 8; i++)
//    {
//        printf(" %f+j%f ", x[i], y[i]);
//    }
//    printf("\n\n");
//}
//void re_bit()
//{
//    float q11, q12, q21, q22;
//    printf("比特逆序之后的数列为：\n");
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
//    for (int i = 0; i < 8; i++)
//    {
//        printf(" %f+j%f ", x[i], y[i]);
//    }
//    printf("\n\n");
//}
//void butterfly1()
//{
//    float u, v;
//    int m1 = 1;//第一级中每个蝶群的运算碟总数——每个蝶群有1个运算蝶
//    int m2 = 2 * m1;//第一级中碟群长度——为2
//    int m3 = 4;//第一级中的蝶群个数——为4个
//
//               //对于每个蝶群来说
//    for (int j = 0; j < m3; j++)
//    {
//        int m4 = j * m2;//蝶群址——每个碟群左上角编号
//
//
//                        //对于每个蝶群的每个运算蝶来说
//        for (int r = 0; r < m1; r++)
//        {
//            int k1 = m4 + r;   //运算蝶上面括号内标
//            int k2 = k1 + m1;  //运算蝶下面括号内标
//            u = x[k2] * cos(2 * p * r / m2) + y[k2] * sin(2 * p * r / m2);
//            v = y[k2] * sin(2 * p * r / m2) - x[k2] * cos(2 * p * r / m2);
//            x[k2] = x[k1] - u;
//            y[k2] = y[k1] - v;
//            x[k1] = x[k1] + u;
//            y[k1] = y[k1] + v;
//        }
//    }
//}
//void butterfly2()
//{
//    float u, v;
//    int m1 = 2;//第二级中每个蝶群的运算碟总数——每个蝶群有2个运算蝶
//    int m2 = 2 * m1;//第二级中碟群长度——为4
//    int m3 = 2;//第二级中的蝶群个数——为2个
//
//               //对于每个蝶群来说
//    for (int j = 0; j < m3; j++)
//    {
//        int m4 = j * m2;//蝶群址——每个碟群左上角编号
//
//
//                        //对于每个蝶群的每个运算蝶来说
//        for (int r = 0; r < m1; r++)
//        {
//            int k1 = m4 + r;   //运算蝶上面括号内标
//            int k2 = k1 + m1;  //运算蝶下面括号内标
//            u = x[k2] * cos(2 * p * r / m2) + y[k2] * sin(2 * p * r / m2);
//            v = y[k2] * sin(2 * p * r / m2) - x[k2] * cos(2 * p * r / m2);
//            x[k2] = x[k1] - u;
//            y[k2] = y[k1] - v;
//            x[k1] = x[k1] + u;
//            y[k1] = y[k1] + v;
//        }
//    }
//}
//void butterfly3()
//{
//    float u, v;
//    int m1 = 4;//第三级中每个蝶群的运算碟总数——每个蝶群有4个运算蝶
//    int m2 = 2 * m1;//第三级中碟群长度——为8
//    int m3 = 1;//第二级中的蝶群个数——为1个
//
//               //对于每个蝶群来说
//    for (int j = 0; j < m3; j++)
//    {
//        int m4 = j * m2;//蝶群址——每个碟群左上角编号
//
//
//                        //对于每个蝶群的每个运算蝶来说
//        for (int r = 0; r < m1; r++)
//        {
//            int k1 = m4 + r;   //运算蝶上面括号内标
//            int k2 = k1 + m1;  //运算蝶下面括号内标
//
//            u = x[k2] * cos(2 * p * r / m2) + y[k2] * sin(2 * p * r / m2);
//            v = y[k2] * sin(2 * p * r / m2) - x[k2] * cos(2 * p * r / m2);
//            x[k2] = x[k1] - u;
//            y[k2] = y[k1] - v;
//            x[k1] = x[k1] + u;
//            y[k1] = y[k1] + v;
//        }
//    }
//}