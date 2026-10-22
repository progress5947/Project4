#include <iostream>
#include <Windows.h>

int main()
{
    int rates[2][3][2] = {
        {{750, 1}, {1500, 4}, {2000, 7}},
        {{1000, 2}, {2000, 4}, {3000, 6}}
    };

    int capacity[2] = { 300, 1000 };
    int max_weight[2] = { 2000, 3000 };
    int drop_tank[2] = { 0, 100 };

    int num;
    double dist_ab, dist_bc, weight;

    std::cout << "Plane number (1 or 2): ";
    std::cin >> num;
    std::cout << "Distance A-B: ";
    std::cin >> dist_ab;
    std::cout << "Distance B-C: ";
    std::cin >> dist_bc;
    std::cout << "Cargo weight: ";
    std::cin >> weight;

    int plane = num - 1;

    int rate = 0;
    if (weight > max_weight[plane])
    {
        rate = -1;
    }
    else {
        for (int i = 0; i < 3; i++)
        {
            if (weight <= rates[plane][i][0])
            {
                rate = rates[plane][i][1];
                break;
            }
        }
    }

    if (rate == -1) 
    {
        std::cout << "Impossible: plane cannot lift this weight." ;
    }
    else 
    {
        double cap = capacity[plane];
        double drop = drop_tank[plane];

        double need_ab = dist_ab * rate;
        bool ok = true;
        double remaining = 0;

        if (num == 1)
        {
            if (need_ab > cap)
            {
                ok = false;
            }
            else
            {
                remaining = cap - need_ab;
            }
        }
        else
        {
            if (need_ab <= drop)
            {
                remaining = cap;
            }
            else
            {
                double need_main = need_ab - drop;
                if (need_main > cap)
                {
                    ok = false;
                }
                else 
                {
                    remaining = cap - need_main;
                }
            }
        }

        double need_bc = dist_bc * rate;

        if (ok == false)
        {
            std::cout << "Impossible to cover distance A-B.";
        }
        else if (need_bc > cap)
        {
            std::cout << "Impossible to cover distance B-C.";
        }
        else 
        {
            double refuel = need_bc - remaining;
            if (refuel < 0)
            {
                refuel = 0;
            }
            std::cout << "Fuel rate: " << rate << " l/km";
            std::cout << "Remaining at B: " << remaining << " l";
            std::cout << "Needed for B-C: " << need_bc << " l";
            std::cout << "Minimum refuel at B: " << refuel << " l";
        }
    }

    return 0;
}