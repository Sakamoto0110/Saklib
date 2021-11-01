#pragma once


typedef struct INTPOINT2D
{
    int X;
    int Y;
    INTPOINT2D(int x, int y) :X(x), Y(y) {}
    INTPOINT2D(int u) :X(u), Y(u) {}
    INTPOINT2D() :X(0), Y(0) {}
   // INTPOINT2D(const INTPOINT2D& other) = default;

    bool operator ==(const INTPOINT2D& other) const { return other.X == X && other.Y == Y; }
    bool operator ==(const int v) const { return X == v && Y == v; }

    bool operator !=(const INTPOINT2D& other) const { return !(other == *this); }
    bool operator !=(const int v) const { return !((*this) == v); }

    INTPOINT2D operator+(const INTPOINT2D& other) const { return {X + other.X, Y + other.Y}; }
    INTPOINT2D operator+(const int v) const { return {X + v, Y + v}; }
    INTPOINT2D operator-(const int v) const { return {X - v, Y - v}; }
    INTPOINT2D operator-(const INTPOINT2D& other)const { return {X - other.X, Y - other.Y}; }

    INTPOINT2D& operator+=(const INTPOINT2D& other) { X += other.X; Y += other.Y; return *this; }
    INTPOINT2D& operator-=(const INTPOINT2D& other) { X -= other.X; Y -= other.Y; return *this; }
    INTPOINT2D& operator-=(const int v) { X -= v; Y -= v; return *this; }
    INTPOINT2D& operator+=(const int v) { X += v; Y += v; return *this; }

}Point2D,Point;


typedef struct DOUBLEPOINT2D
{
    double X;
    double Y;
    DOUBLEPOINT2D(double x, double y) :X(x), Y(y) {}
    DOUBLEPOINT2D(double u) :X(u), Y(u) {}
    DOUBLEPOINT2D() :X(0), Y(0) {}

    bool operator ==(const DOUBLEPOINT2D& other) const { return X-other.X <= 0.0000000000001 && Y - other.Y <= 0.0000000000001; }
    bool operator ==(const double v) const { return X - v <= 0.0000000000001 && Y - v <= 0.0000000000001; }

    bool operator !=(const DOUBLEPOINT2D& other) const { return !(other == *this); }
    bool operator !=(const double v) const { return !((*this) == v); }

    DOUBLEPOINT2D operator+(const DOUBLEPOINT2D& other) const { return {X + other.X, Y + other.Y}; }
    DOUBLEPOINT2D operator+(const double v) const { return {X + v, Y + v}; }
    DOUBLEPOINT2D operator-(const double v) const { return {X - v, Y - v}; }
    DOUBLEPOINT2D operator-(const DOUBLEPOINT2D& other)const { return {X - other.X, Y - other.Y}; }

    DOUBLEPOINT2D& operator+=(const DOUBLEPOINT2D& other) { X += other.X; Y += other.Y; return *this; }
    DOUBLEPOINT2D& operator-=(const DOUBLEPOINT2D& other) { X -= other.X; Y -= other.Y; return *this; }
    DOUBLEPOINT2D& operator-=(const double v) { X -= v; Y -= v; return *this; }
    DOUBLEPOINT2D& operator+=(const double v) { X += v; Y += v; return *this; }

}dPoint2D, dPoint;



struct DUMMYSTRUCT
{
    int DUMMYVAR = 1;
};