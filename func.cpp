#include <iostream>
#include <cmath>
#include <vector>
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) {};
};

class Ellipse {
private:
    double x0, y0, a, b, c;
    Point f1, f2;
public:
    // Надо сюда бахнуть переход в другие координаты, там упростится штука, исчезнут x0 и y0
    Ellipse(double x0, double y0, double a, double b) {
        c = std::sqrt(std::abs(a * a - b * b));
        if (a > b) {
            f1 = Point(x0 - c, y0);
            f2 = Point(x0 + c, y0);
        }
        else {
            f1 = Point(x0, y0 - c);
            f2 = Point(x0, y0 + c);
        }
    }

    //Зай ты эти штуки ваще пока не используешь
    /*bool inEllipse(Point m) const {
        if (pow(m.x - x0, 2) / pow(a, 2) + pow(m.y - y0, 2) / pow(b, 2) < 1)return true;
        return false;
    }
    bool onEllipse(Point m) const {
        if (pow(m.x - x0, 2) / pow(a, 2) + pow(m.y - y0, 2) / pow(b, 2) == 1)return true;
        return false;
    }
    */


     /* Ax + By + C = 0 -- определенно до константы, приму А всегда равным 1
     *  B = -(x1 - x2)/(y1-y2)
     *  C = -Ax1 - By1 = -x1 - By1 */
    double distFromPointToLine(Point a, Point b1, Point b2) {
        double A = 1;
        double B = -(b1.x - b2.x)/(b1.y - b2.y);
        double C = -b1.x - B * b1.y;
        return (std::abs(A * a.x + B * a.y + C) / std::sqrt(A * A + B * B));
    }

    //Предлагаю функцию назвать по-другому, а еще надо как-то более понятно обозначить что такое k, вообще непонятно откуда оно
    Point sharedPoint(Point m, double k) {
        double A = 1 / (a * a) + (k * k) / (b * b);
        double B = 2 * (m.x - x0) / (a * a) + (k * m.y - k * y0) / (b * b); //переход в другие координаты упростит
        double C = (m.x - x0) * (m.x - x0) / (a * a) + (m.y - y0) * (m.y - y0) / (b * b) - 1; //переход в другие координаты упростит
        double dis = B * B - 4 * A * C;
        if (dis < 0)return Point(m.x + 1, m.y + k); //тут надо жесточайше сравнивать с машинным эпсилоном, это первая задача Марча в 1 семе
        double t1 = (-B + std::sqrt(dis)) / (2 * A);
        double t2 = (-B - std::sqrt(dis)) / (2 * A);
        double t = std::min(t1, t2);
        if (dis == 0)return Point(m.x + t1, m.y + k * t1);
        if (t1 < 0 && t2 < 0)return Point(m.x + 1, m.y + k);////
        if (t1 < 0 && t2 >= 0)return Point(m.x + t2, m.y + k * t2);
        if (t1 > 0 && t2 <= 0)return Point(m.x + t1, m.y + k * t1);
        return Point(m.x + t, m.y + k * t);
    }
    Point reflectedPoint(Point m, double k) {
        Point p = sharedPoint(m, k);
        double A = p.x / (a * a);
        double B = p.y / (b * b);
        double t = (A * (p.x - m.x) - B * (p.y - m.y)) / (B * B - A * A);
        Point l;
        l.x = 2 * A * t + 2 * p.x - m.x;
        l.y = m.y + A * (l.x - m.x) / B;
        return l;
    }
    void solution(Point m, double k, double& d1, double& d2, double& x, double& y) {
        Point p = sharedPoint(m, k);
        Point l = reflectedPoint(m, k);
        d1 = distFromPointToLine(f1, p, l);
        d2 = distFromPointToLine(f2, p, l);
        x = p.x;
        y = p.y;
    }
};

int main()
{
    double x0, y0, a, b, xi, eta;
    int m;
    std::cin >> x0 >> y0 >> a >> b;
    std::cin >> xi >> eta;
    std::cin >> m;
    Point M(xi, eta);
    Ellipse ellipse(x0, y0, a, b);
    for (int j = 0; j < m; ++j) {
        double k = atan(2 * asin(-1) * j / m);
        double d1 = 0, d2 = 0, x, y;
        ellipse.solution(M, k, d1, d2, x, y);
        std::cout << x << " " << y << " " << d1 << " " << d2 << std::endl;
    }

}
