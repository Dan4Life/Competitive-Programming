/*
2D Point Basic Structure
No complex
*/

template<class T>
struct Point2D{
    T x, y;

    Point2D(T x=T{}, T y=T{}) : x(x),y(y) {}

    bool operator<(const Point2D& other) const { return x<other.x||(x==other.x&&y<other.y); }
    bool operator==(const Point2D& other) const { return x==other.x and y==other.y; }

    Point2D& operator+=(const Point2D &P) { x+=P.x, y+=P.y; return *this; }
    Point2D& operator-=(const Point2D &P) { x-=P.x, y-=P.y; return *this; }
    Point2D& operator*=(const T &t) { x*=t, y*=t; return *this; }
    Point2D& operator/=(const T &t) { x/=t, y/=t; return *this; }

    Point2D operator+(const Point2D &P) const{ return Point2D(*this)+=P; }
    Point2D operator-(const Point2D &P) const{ return Point2D(*this)-=P; }
    Point2D operator*(const T &t) const{ return Point2D(*this)*=t; }
    Point2D operator/(const T &t) const{ return Point2D(*this)/=t; }

    T dotP(const Point2D &P={}) const{ return x*P.x+y*P.y; }
    T crossP(const Point2D &P={}) const{ return x*P.y-P.x*y; }
    T distSq(const Point2D &P = {}) const { return (P.x-x)*(P.x-x)+(P.y-y)*(P.y-y); }
    T dist(const Point2D &P={}) const{ return hypot(P.x-x,P.y-y); }

    friend istream& operator>>(istream& in, Point2D &P){ return in >> P.x >> P.y;  }
    friend ostream& operator<<(ostream& out, const Point2D &P){ return out << P.x << " " << P.y;  }
};

template<class T>
int sign(T x){ return (x>0)-(x<0); }

template<class T>
T area(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) {
    return a.crossP(b)+b.crossP(c)+c.crossP(a);
}

template<class T>
bool cw(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, bool colinear){
    if(colinear and !sign(area(a,b,c))) return 1;
    return sign(area(a,b,c))<0;
}

template<class T>
bool ccw(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, bool colinear){
    if(colinear and !sign(area(a,b,c))) return 1;
    return sign(area(a,b,c))>0;
}

template<class T>
double get_angle(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) {
    double angle1 = atan2(a.y-b.y,a.x-b.x);
    double angle2 = atan2(c.y-b.y,c.x-b.x);
    double result = angle2 - angle1;
    while (result <= -M_PI) result += 2 * M_PI;
    while (result > M_PI) result -= 2 * M_PI;
    return abs(result);
}
