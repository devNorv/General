#include <cstdlib>
#include <stdio.h>
#include <cfloat>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <chrono>
#include <iterator>
#include <stdlib.h>

using namespace std;

namespace ClosestPairOfPoints
{
    const int MAX_ITERATIONS = 10;

    class Point
    {
    public:
        Point()
        {
            x = 0;
            y = 0;
        }

        Point(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        ~Point()
        {
        }

        int x;
        int y;
    };

    float min(float x, float y)
    {
        return (x < y) ? x : y;
    }
    
    // float dist(Point *p1, Point *p2)
    // {
    //     return sqrt(pow((p1->x - p2->x), 2.0) + pow(p1->y - p2->y, 2.0));
    // }

    float dist(Point p1, Point p2)
    {
        return sqrt(pow((p1.x - p2.x), 2.0) + pow(p1.y - p2.y, 2.0));
    }
    
    int compareX(const void *a, const void *b)
    {
        Point *p1 = (Point *)a;
        Point *p2 = (Point *)b;
        return (p1->x - p2->x);
    }

    int compareY(const void *a, const void *b)
    {
        Point *p1 = (Point *)a;
        Point *p2 = (Point *)b;
        return (p1->y - p2->y);
    }

    void RandomPointGenerater(Point *p, const int n)
    {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < n; i++)
        {
            int x = rand() % RAND_MAX;
            int y = rand() % RAND_MAX;
            p[i] = Point(x, y);
        }
    }

    std::pair<Point, Point> BruteForceClosestPoints(Point *P, int n)
    {
        double d = DBL_MAX;
        Point p1;
        Point p2;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (dist(P[i], P[j]) < d)
                {
                    d = dist(P[i], P[j]);
                    p1.x = P[i].x;
                    p1.y = P[i].y;

                    p2.x = P[j].x;
                    p2.y = P[j].y;
                }
            }
        }

        return std::make_pair(p1, p2);
    }

    std::pair<Point, Point> ClosestPairRec(Point *Px, Point *Py, int n)
    {
        if (n <= 3)
        {
            // find closest pair by measuring all pairwise distances
            return BruteForceClosestPoints(Px, n);
        }
        else
        {
            int mid = n / 2;
            int lowerBound = mid;
            int upperBound = n - lowerBound;
            Point *Qx = new Point[lowerBound];
            Point *Qy = new Point[lowerBound];
            Point *Rx = new Point[upperBound];
            Point *Ry = new Point[upperBound];

            for (int i = 0; i < lowerBound; i++)
            {
                // Construct Qx, Qy, Rx, Ry (O(n) time)
                Qx[i] = Px[i];
                Qy[i] = Py[i];
            }

            for (int i = 0; i < upperBound; i++)
            {
                // Construct Qx, Qy, Rx, Ry (O(n) time)
                Rx[i] = Px[lowerBound + i];
                Ry[i] = Py[lowerBound + i];
            }

            // (q∗0,q∗1) = Closest-Pair-Rec(Qx, Qy)
            std::pair<Point, Point> q = ClosestPairRec(Qx, Qy, lowerBound);
            // (r∗0,r∗1 ) = Closest-Pair-Rec(Rx, Ry)
            std::pair<Point, Point> r = ClosestPairRec(Rx, Ry, upperBound);

            // δ = min(d(q∗0,q∗1), d(r∗0,r∗1 ))
            float d = min(dist(q.first, q.second), dist(r.first, r.second));

            /*
            Let x∗ denote the x-coordinate of the rightmost point in Q, and let L denote
            the vertical line described by the equation x = x∗. This line L “separates” Q
            from R. Here is a simple fact.
            */
            // x∗ = maximum x-coordinate of a point in set Q
            Point x = Qx[mid];
            // Let x∗ denote the x-coordinate of the rightmost point in Q
            int x_prime = x.x;
            // and let L denote the vertical line described by the equation x = x∗
            int L = x_prime;

            /*
            So if we want to find a close q and r, we can restrict our search to the
            narrow band consisting only of points in P within δ of L. Let S ⊆ P denote this
            set, and let Sy denote the list consisting of the points in S sorted by increasing
            y-coordinate. By a single pass through the list Py, we can construct Sy in O(n)
            time.
            */

            // S = points in P within distance δ of L.
            Point *S = new Point[n];
            bool *S_bool = new bool[n];
            int size = 0;
            for (int i = 0; i < n; i++)
            {
                S[i] = Px[i];
                if (abs(L - Px[i].x) < d)
                {
                    S_bool[i] = true;
                    size++;
                }
                else
                {
                    S_bool[i] = false;
                }
            }

            // Construct Sy (O(n) time)
            Point *Sy = new Point[size];
            for (int i = 0; i < n; i++)
            {
                if (S_bool[i] != false)
                {
                    Sy[i] = S[i];
                }
            }

            // let Sy denote the list consisting of the points in S sorted by increasing y-coordinate
            qsort(Py, size, sizeof(Point), compareY);


            // For each point s ∈ Sy, compute distance from s to each of next 15 points in Sy
            //      Let s, s' be pair achieving minimum of these distances
            //      (O(n) time)
            const int MAX = 15;
            Point s;
            Point s_prime;
            Point next;
            float d_prime;
            for (int i = 0; i < size; i++) {
                s = Sy[i];
                for (int j = 0; j < MAX; j++){
                    next = Sy[j];
                    d_prime = dist(s, next);
                    if (d_prime < d){
                        s_prime = next;
                        d = d_prime;
                    }
                }
            }

            std::pair<Point, Point> sp = std::make_pair(Point(s.x, s.y), Point(s_prime.x, s_prime.y));

            delete[] Sy;
            delete[] S_bool;
            delete[] S;
            delete[] Ry;
            delete[] Rx;
            delete[] Qy;
            delete[] Qx;

            // If d( s,s' ) < δ then
            // return (s, s')
            if (dist(sp.first, sp.second) < d)
            {
                return sp;
            }
            // Else if d( q∗0,q∗1 ) < d( r∗0,r∗1 ) then
            // Return (q∗0,q∗1)
            else if (dist(q.first, q.second) < dist(r.first, r.second))
            {
                return q;
            }
            // Else Return ( r∗0,r∗1 )
            else
            {
                return r;
            }
        }
    }

    std::pair<Point, Point> DivideAndConquerClosestPoints(Point *P, const int n)
    {
        Point *Px = new Point[n];
        Point *Py = new Point[n];
        for (int i = 0; i < n; i++)
        {
            Px[i] = P[i];
            Py[i] = P[i];
        }
        // Construct Px and Py (O(n log n) time)
        // First, before any of the recursion begins,
        // we sort all the points in P by xcoordinate and again by y-coordinate, producing lists Px and Py
        qsort(Px, n, sizeof(Point), compareX);
        qsort(Py, n, sizeof(Point), compareY);

        return ClosestPairRec(Px, Py, n);
    }
}
// namespace ClosestPairOfPoints

int main()
{
    using namespace ClosestPairOfPoints;
    using namespace std::chrono;

    std::map<int, milliseconds> BF_AvgTime;
    std::map<int, milliseconds> DC_AvgTime;
    
    milliseconds BruteForceAlgorithmAvg = milliseconds(0);
    milliseconds DivideAndConquerAlgorithmAvg = milliseconds(0);

    const int increment = 100;
    cout << "Closest Pair of Points RT Analysis"<< endl << endl;
    for (int n = increment; n <= 10*increment; n+=increment){
        cout << "Running Iteration where input size : " << n << endl;
        
        for (int m = 0; m < MAX_ITERATIONS; m++){
            
            Point *P = new Point[n];
            RandomPointGenerater(P, n);
            
            auto t1 = high_resolution_clock::now();
            {
                BruteForceClosestPoints(P, n);
            }
            auto t2 = high_resolution_clock::now();
            milliseconds duration_alg1 = duration_cast<milliseconds>(t2 - t1);
            BruteForceAlgorithmAvg += duration_alg1;
            
            auto t3 = high_resolution_clock::now();
            {
                DivideAndConquerClosestPoints(P, n);
            }
            auto t4 = high_resolution_clock::now();
            milliseconds duration_alg2 = duration_cast<milliseconds>(t4 - t3);
            DivideAndConquerAlgorithmAvg += duration_alg2;
            
            delete [] P;
        }
        
        BruteForceAlgorithmAvg /= MAX_ITERATIONS;
        DivideAndConquerAlgorithmAvg /= MAX_ITERATIONS;
        
        int k = n / increment;
        BF_AvgTime.insert(std::pair<int, milliseconds>(k, BruteForceAlgorithmAvg));
        DC_AvgTime.insert(std::pair<int, milliseconds>(k, DivideAndConquerAlgorithmAvg));
        
        BruteForceAlgorithmAvg = milliseconds(0);
        DivideAndConquerAlgorithmAvg = milliseconds(0);
    }

    cout << endl << "Computing RT Analysis Averages.." << endl << endl;
    
    cout << "********************************************" << endl;
    cout << " Brute Force Algorithm Average Empirical RT" << endl;
    cout << "********************************************" << endl;
    std::map<int, milliseconds>::iterator iterBF = BF_AvgTime.begin();
    while (iterBF != BF_AvgTime.end())
    {
        std::cout << "m: " << iterBF->first << ",\tTime (msec): " << iterBF->second.count() << std::endl;
        ++iterBF;
    }
    
    cout << endl;

    cout << "***************************************************" << endl;
    cout << " Divide and Conquer Algorithm Average Empirical RT" << endl;
    cout << "***************************************************" << endl;
    std::map<int, milliseconds>::iterator iterDC = DC_AvgTime.begin();
    while (iterDC != DC_AvgTime.end())
    {
        std::cout << "m: " << iterDC->first << ",\tTime (msec): " << iterDC->second.count() << std::endl;
        ++iterDC;
    }
    
    cout << "\nRT Analysis Complete" << endl;

    return 0;
}