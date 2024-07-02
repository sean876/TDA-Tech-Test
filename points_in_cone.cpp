#include <iostream>
#include <vector>
#include <stdexcept>

enum Direction
{
    North,
    East,
    South,
    West
};

struct Point
{
    int number;
    int x;
    int y;
    Direction direction;

    Point(int number = 0, int x = 0, int y = 0, Direction direction = North ) : number(number), x(x), y(y), direction(direction) { }
};

std::vector<Point> VisiblePoints(const std::vector<Point>& points, const int number, const double cone, const double distance)
{
    //find point in vector
    Point activePoint;
    bool found = false;
    for (Point p : points)
    {
        if (p.number == number)
        {
            activePoint = p;
            found = true;
            break;
        }
    }

    if (not found) throw std::exception("Vector does not contain a point of the given number");

    const double pi = 3.14159;
    const double halfPi = pi / 2;
    const double radianMultiplier = pi / 180;
    
    double facingDirection = halfPi * activePoint.direction; //convert enum direction to radians
    double distanceSquared = pow(distance, 2);

    std::vector<Point> result;

    for (Point iterPoint : points)
    {
        if (iterPoint.number == activePoint.number) continue; //skip active point, assumes no duplicate id numbers

        double distanceBetweenPointsSquared = pow(activePoint.x - iterPoint.x, 2) + pow(activePoint.y - iterPoint.y, 2);

        if (distanceBetweenPointsSquared > distanceSquared) continue; //skip if point is too far

        double activeToIterDirection = atan2((iterPoint.x - activePoint.x), (iterPoint.y - activePoint.y));
        double radiansBetweenPoints = facingDirection - activeToIterDirection;

        if (abs(radiansBetweenPoints) > (cone * radianMultiplier)) continue; //skip if point is outside of cone

        result.push_back(iterPoint);
    }
    return result;    
}

int main()
{
    std::vector<Point> Points
    {
        Point( 1, 28, 42, North),
        Point( 2, 27, 46, East),
        Point( 3, 16, 22, South),
        Point( 4, 40, 50, West),
        Point( 5,  8,  6, North),
        Point( 6,  6, 19, East),
        Point( 7, 28,  5, South),
        Point( 8, 39, 36, West),
        Point( 9, 12, 34, North),
        Point(10, 36, 20, East),
        Point(11, 22, 47, South),
        Point(12, 33, 19, West),
        Point(13, 41, 18, North),
        Point(14, 41, 34, East),
        Point(15, 14, 29, South),
        Point(16,  6, 49, West),
        Point(17, 46, 50, North),
        Point(18, 17, 40, East),
        Point(19, 28, 26, South),
        Point(20,  2, 12, West)
    };

    int Number = 1;
    double Cone = 45;
    double Distance = 20;

    std::vector<Point> Results;
    try
    {
        Results = VisiblePoints(Points, Number, Cone, Distance);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }

    for (Point result : Results)
        std::cout << result.x << ", " << result.y << ", " << result.number << ", " << result.direction << std::endl;

    return 0;
}
