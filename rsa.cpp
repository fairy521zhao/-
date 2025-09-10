#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// 看一个数是不是素数
bool isPrime(int num) {
    if (num<=1) return false;
    if (num==2||num==3) return true;
    if (num%2==0) return false;
    for (int i=3;i<=sqrt(num);i+=2) {
        if (num%i==0) return false;
    }
    return true;
}

// 计算最大公约数（欧几里得算法）
int gcd(int a, int b) {
    while (b!=0) {
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

// // 扩展欧几里得算法计算模逆元，更可靠
// int modInverse(int a, int m) {
//     int m0 = m;
//     int y = 0, x = 1;
//     if (m == 1)
//         return 0;

//     while (a > 1) {
//         int q = a / m;
//         int t = m;

//         m = a % m;
//         a = t;
//         t = y;

//         y = x - q * y;
//         x = t;
//     }

//     // 确保x为正数
//     if (x < 0)
//         x += m0;

//     return x;
// }

// 计算模逆元
int modInverse(int e, int oula) {
    for (int d=1;d<oula;d++) {
        if ((e*d)%oula==1) {
            return d; 
        }
    }
    return -1;
}


// 生成指定范围内的随机数
int generateRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

// 生成 RSA 密钥对
void getKeys(int &e, int &d, int &n) {
    int p, q;
    srand(time(0)); 
    do {
        p=generateRandom(100,1000);  // 可更改
    } while (!isPrime(p));
    do {
        q=generateRandom(100,1000);
    } while (!isPrime(q)||q==p);
    n=p*q;
    int oula=(p-1)*(q-1);
    do {
        e=generateRandom(2, oula-1);
    } while (gcd(e,oula)!=1);
    d=modInverse(e,oula);
    cout<< "=== RSA 密钥对生成完成 ==="<<endl;
    cout<< "质数 p = " << p << ", q = " <<q<<endl;
    cout<< "公钥（加密用）：(e=" << e << ", n=" << n << ")"<<endl;
    cout<< "私钥（解密用）：(d=" << d << ", n=" << n << ")"<<endl;
}

// 快速幂模运算（改进版，处理更大的数）
int modPow(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            // 使用long long防止乘法溢出
            result = (int)(((long long)result * base) % mod);
        }
        exp/=2;
        base = (int)(((long long)base * base) % mod);
    }
    return result;
}

// 加密函数（公钥加密：c = m^e mod n）
int rsaJiami(int mingwen,int e,int n) {
    return modPow(mingwen,e,n);
}
// 解密函数（私钥解密：m = c^d mod n）
int rsaJiemi(int miwen,int d,int n) {
    return modPow(miwen,d,n);
}
// 演示 RSA 完整流程
int main() {
    int e,d,n;  
    int mingwen,miwen,mingwen2;
    getKeys(e,d,n);
    cout << "\n=== 请输入明文（需在0到 " << n-1 << " 之间）===" <<endl;
    cin>>mingwen;
    miwen=rsaJiami(mingwen,e,n);
    cout<< "=== 加密结果 ===" <<endl;
    cout<< "密文：" << miwen <<endl;
    mingwen2 = rsaJiemi(miwen,d,n);
    cout<< "=== 解密结果 ===" <<endl;
    cout<< "明文：" << mingwen2 <<endl;
    return 0;
}
