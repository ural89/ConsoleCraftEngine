#include <iostream>

class Grid
{
public:
    void Render(int width, int height)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                std::cout << "+---";
            }
            std::cout << "+\n";

            for (int j = 0; j < width; ++j)
            {
                std::cout << "|   ";
            }
            std::cout << "|\n";
        }

        for (int j = 0; j < width; ++j)
        {
            std::cout << "+---";
        }
        std::cout << "+\n";
    }
};
