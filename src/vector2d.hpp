#ifndef VECTOR2D_H
#define VECTOR2D_H

class vector2d
{
    private:
        double x,y;
    public:
        vector2d ();
        vector2d( double xN, double yN);
        double getX ();
        double getY ();
        void setX (double newX);
        void setY (double newY);
        double distance ();
        vector2d direction ();
        vector2d operator +(vector2d other) const;
        void operator +=(vector2d other);
        vector2d operator -(vector2d other) const;
        void operator -=(vector2d other);
        vector2d operator *(double num) const;
        double operator *(vector2d num) const;
        double operator %(vector2d num) const;
        void operator *=(double num);
        vector2d operator /(double num) const;
        void operator /=(double num);
};

vector2d operator*(double k, const vector2d& v);
#endif
