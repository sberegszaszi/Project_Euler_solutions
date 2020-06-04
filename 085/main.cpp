// Problem 85 - Counting rectangles
// By counting carefully it can be seen that a rectangular grid measuring 3 by 2 contains 18 rectangles:
// 6 x						4 x						2 x
//  -----  . . . . . .		 ----- -----  . . .		 ----- ----- -----
// |     |     .     .		|           |     .		|                 |
// |     |     .     .		|           |     .		|                 |
//  -----  . . . . . .		 ----- -----  . . .		 ----- ----- -----
// .     .     .     .		.     .     .     .		.     .     .     .
// .     .     .     .		.     .     .     .		.     .     .     .
// . . . . . . . . . .		. . . . . . . . . .		. . . . . . . . . .
// 3 x						2 x						1 x
//  -----  . . . . . .		 ----- -----  . . .		 ----- ----- -----
// |     |     .     .		|           |     .		|                 |
// |     |     .     .		|           |     .		|                 |
// |     | . . . . . .		|           | . . .		|                 |
// |     |     .     .		|           |     .		|                 |
// |     |     .     .		|           |     .		|                 |
//  -----  . . . . . .		 ----- -----  . . .		 ----- ----- -----
// Although there exists no rectangular grid that contains exactly two million rectangles, find the area of the grid with the nearest solution.

#include <iostream>

struct RectanglesInGrid
{
    int x;
    int y;
    int rectangles;
};

int CalculateRectsInGrid(int x, int y);
RectanglesInGrid SearchForGrid(const int numOfRectangles, const int epsilon);

int main()
{
    const int numOfRectangles = 2'000'000;
    int epsilon = 100;
    auto result = SearchForGrid(numOfRectangles, epsilon);
    std::cout << "Area: " << result.x << " * " << result.y << " = " << result.x * result.y << std::endl;
    return 0;
}

// number of rectangles in a x*y grid = ( SUM[i=0..(x-1)](x - i) ) * ( SUM[j=0..(y-1)](y - j) )
int CalculateRectsInGrid(int x, int y)
{
    int result = 0;
    for(auto i = 0; i < x; ++i){
        for(auto j = 0; j < y; ++j){
            result += ((x - i) * (y - j));
        }
    }
    return result;
}

// searching for result closest to given number of rectangles in epsilon radius
RectanglesInGrid SearchForGrid(const int numOfRectangles, const int epsilon)
{
    RectanglesInGrid current{0,0,0};
    RectanglesInGrid result{0,0,0};
    int diff = 1000;
    for(int x = 1; diff > epsilon; ++x){
        for(int y = 1; y <= x; ++y){
            current = {x, y, CalculateRectsInGrid(x, y)};
            if(current.rectangles > (numOfRectangles + diff)){
                break;
            } else if(current.rectangles > (numOfRectangles - diff)){
                if(result.rectangles == 0 || current.rectangles > result.rectangles){
                    result = current;
                    diff = abs(current.rectangles - numOfRectangles);
                }
            }
        }
        if(x > 1000) break;
    }
    std::cout << "Closest result is a " << result.x << " x " << result.y << " grid.\n";
    std::cout << "Number of rectangles in the grid: " << result.rectangles << "\n";
    return result;
}