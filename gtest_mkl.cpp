/*
void DSYEV(char* jobz, char* uplo, int* n, double* a, int* lda, double* w, double* work, int* lwork, int* info);
参数说明：

jobz：字符，指定计算特征值及特征向量的选项。
'N' 或 'n'：仅计算特征值，不计算特征向量；
'V' 或 'v'：计算特征值和特征向量。

uplo：字符，指定矩阵的存储方式。
'U' 或 'u'：上三角存储；
'L' 或 'l'：下三角存储。

n：整型，表示矩阵的阶数。

a：双精度浮点型数组，输入和输出参数，表示存储对称矩阵的数组。在输入时，应该传入待计算特征值和特征向量的对称矩阵；在输出时，a数组将包含归一化的特征向量。

lda：整型，表示矩阵的第一个维度大小。通常是大于等于n的整数。

w：双精度浮点型数组，输出参数，用于存储特征值。

work：双精度浮点型数组，工作空间数组。在调用函数之前，需要分配足够的内存空间。

lwork：整型，表示工作空间数组的大小。需要保证lwork >= max(1, 3*n - 1)。如果lwork = -1，则函数会自动计算所需的最小工作空间大小，并将结果存储在work[0]中。

info：整型，输出参数，表示函数的返回状态。
info = 0：函数执行成功；
info < 0：出现错误，具体错误代码可以参考MKL文档。
*/
#include <iostream>
#include <mkl.h>
#include <ctime>
#include <cstdlib>
using namespace std;
#define MAX 256

int main()
{
    char jobz = 'N';     // 仅计算特征值，不计算特征向量
    char uplo = 'L';     // 对称矩阵的下三角部分
    int n = 0;           // 矩阵的阶数
    int nn = 0;          // 输入矩阵的元素个数
    double *x = nullptr; // 输入矩阵
    double *w = nullptr; // 特征值
    double *z = nullptr; // 左特征向量
    int info = 0;        // 错误信息
  int lwork=0;
    double *work=nullptr; 
    while (true)
    {
        cout << "请输入矩阵的阶数: ";
        cin >> n;
        if (n <= 0)
        {
            cout << "请输入大于0的数字." << endl;
            continue;
        }
        if (n > MAX)
        {
            cout << "请输入小于256的数字." << endl;
            continue;
        }
        nn = n * n;
     lwork = max(1, 3 * n - 1);
        // 分配内存空间
        x = (double *)malloc(sizeof(double) * nn);
        w = (double *)malloc(sizeof(double) * n);
        z = (double *)malloc(sizeof(double) * n * n); // 修改为n * n
       work = (double *)malloc(sizeof(double) * lwork);
        // 生成随机矩阵
        srand(time(NULL));
        for (int i = 0; i < nn; ++i)
        {
            x[i] = (double)rand() / RAND_MAX + 1.0; // 修改为大于1的随机值
        }

        // 打印随机生成的矩阵
        cout << "随机生成的矩阵：" << endl;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << x[i * n + j] << " ";
            }
            cout << endl;
        }

        // 计算特征值
        dsyev_(&jobz, &uplo, &n, x, &n, w, work, &lwork, &info);

        // 输出结果
        cout << "特征值：" << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << w[i] << " ";
        }
        cout << endl;
        cout << "请输入'quit'退出程序." << endl;

        string quit = "quit";
        cin >> quit;
        if (quit == "quit")
        {
            break;
        }
    }

    // 释放内存空间
    free(x);
    free(w);
    free(z);
    free(work);
    return 0;
}
/*
总结：
1、空间问题：首先是对于矩阵空间的开辟，要在计算之前开辟，且要足够大
2、对函数（计算特征值）:函数的第7个数据和第八个数据总出问题，要严格按照手册上的函数的各个参数的空间大小分配空间
3、对于参数：参数一定要先赋初值，否则释放空间容易出现不再一个作用域的情况
4、对于max：暂时的最大值是256，255阶的计算还可以
*/