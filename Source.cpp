#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

double used_f(double x) {
    return ((1 - x) * (1 - x) + exp(x));
}

int main() {
    //x=[-2; 4]
    const float eps = 0.1;
    double b = 4.0;
    double a = -2.0;
    unsigned int N = 1;
    double Xi;
    double s; //погрешность
    double min;
    std::map<double, double> values;
    std::cout << "passive search\n";
    do {
        for (auto k = 1; k < N + 1; ++k) {
            Xi = ((b - a) * k / (N + 1)) + a;
            values.insert(std::make_pair(used_f(Xi), Xi));
        }
        s = (b - a) / (N + 1);
        std::map<double, double> ::iterator it = values.begin();
        std::cout << "N = " << N << " = " << it->second << " +- " << s << "\n";
        values.clear();
        ++N;
    } while (s > eps);


    const float delta = 0.01;
    double Xleft, Xright;
    std::cout << "\ndihotomiya\n";
    std::cout << "a=" << a << " b=" << b << " b-a=" << (b - a) << used_f(a) << " "<<  used_f(b) << "\n";
    double a1, b1;
    do {
        Xleft = 0.5 * (b + a) - delta;
        Xright = 0.5 * (b + a) + delta;
        values.insert(std::make_pair(used_f(Xleft), Xleft));
        values.insert(std::make_pair(used_f(Xright), Xright));
        std::map<double, double> ::iterator it = values.begin();
        a1 = it->second;
        ++it;
        b1 = it->second;
        if (a1 > b1) {
            a = a1;
        }
        else {
             b = b1;
        }
        --it;
        std::cout << "a=" << a << " b=" << b << " b-a=" << (b - a)
            << "\nf(Xleft)=" << it->first;
        ++it;
        s = 0.5 * (b - a);
        std::cout << " f(Xright)=" << it->first << "\nmin:"
            << (a + b) / 2 << " +- " << s << "\n";
        values.clear();
    } while ((b - a) > eps);
    system("pause");
    return 0;
}