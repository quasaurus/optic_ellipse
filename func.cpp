#include <iostream>
#include <cmath>
#include <vector>
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) {};
};
// мяу мяу
class Ellipce {
private:
    double x0, y0, a, b, c;
    Point f1, f2;
public:
    Ellipce(double x0, double y0, double a, double b) {
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
    bool inEllipce(Point m) const {
        if (pow(m.x - x0, 2) / pow(a, 2) + pow(m.y - y0, 2) / pow(b, 2) < 1)return true;
        return false;
    }
    bool onEllipce(Point m) const {
        if (pow(m.x - x0, 2) / pow(a, 2) + pow(m.y - y0, 2) / pow(b, 2) == 1)return true;
        return false;
    }
    double fromPointToLine(Point c, Point l, Point n) {
        double A = l.y - n.y;
        double B = n.x - l.x;
        double C = n.y * l.x - n.x * l.y;
        return (std::abs(A * c.x + B * c.y + C) / std::sqrt(A * A + B * B));
    }
    Point pointPer(Point m, double k) {
        double A = 1 / (a * a) + (k * k) / (b * b);
        double B = 2 * (m.x - x0) / (a * a) + (k * m.y - k * y0) / (b * b);
        double C = (m.x - x0) * (m.x - x0) / (a * a) + (m.y - y0) * (m.y - y0) / (b * b) - 1;
        double dis = B * B - 4 * A * C;
        if (dis < 0)return Point(m.x + 1, m.y + k); /////
        double t1 = (- B + std::sqrt(dis)) / (2 * A);
        double t2 = (- B - std::sqrt(dis)) / (2 * A);
        double t = std::min(t1, t2);
        if (dis == 0)return Point(m.x + t1, m.y + k * t1);
        if (t1 < 0 && t2 < 0)return Point(m.x + 1, m.y + k);////
        if (t1 < 0 && t2 >= 0)return Point(m.x + t2, m.y + k * t2);
        if (t1 > 0 && t2 <= 0)return Point(m.x + t1, m.y + k * t1);
        return Point(m.x + t, m.y + k * t);
    }
    Point reflect(Point m, double k) {
        Point p = pointPer(m, k);
        double A = p.x / (a * a);
        double B = p.y / (b * b);
        double t = (A * (p.x - m.x) - B * (p.y - m.y)) / (B * B - A * A);
        Point l;
        l.x = 2 * A * t + 2 * p.x - m.x;
        l.y = m.y + A * (l.x - m.x) / B;
        return l;
    }
    void resh(Point m, double k, double& d1, double& d2, double& x, double& y) {
        Point p = pointPer(m, k);
		Point l = reflect(m, k);
		d1 = fromPointToLine(f1, p, l);
		d2 = fromPointToLine(f2, p, l);
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
    Ellipce ellipce(x0, y0, a, b);
    for (int j = 0; j < m; ++j) {
        double k = atan(2 * asin(-1) * j / m);
        double d1 = 0, d2 = 0, x, y;
        ellipce.resh(M, k, d1,d2, x, y);
        std::cout << x << " " << y << " " << d1 << " " << d2 << std::endl;
    }
    
}
