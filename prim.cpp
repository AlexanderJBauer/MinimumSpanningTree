// Alexander Bauer
// CS 130B Programming Assignment 2
// Last Edited: May 5th, 2017
// Implementation of Prim's Algroithm for finding the
//  minimum spanning tree of a connected graph

#include <string>       /* std::string */
#include <cmath>        /* std::abs */
#include <limits>       /* std::numeric_limits */
#include <math.h>       /* sqrt */
#include <vector>       /* std::vector */
#include <cstdlib>      /* qsort */
#include <algorithm>    /* std::sort */
#include <iostream>     /* std::cout, std::cin */
#include <iomanip>      /* std::setw */

// Global variables
int numPoints = 0;
int numEdges = 0;

// Point struct to make things easier
struct Point
{
    double x;
    double y;
    
    //CONSTRUCTOR
    Point( double xVal = 0, double yVal = 0 ): x( xVal ), y( yVal ) { }
    
};

// DISTANCE FUNCTION
double distanceBetween( Point p1, Point p2 )
{
    return sqrt( ( p1.x - p2.x ) * ( p1.x - p2.x )
                +( p1.y - p2.y ) * ( p1.y - p2.y ) );
}

// A utility function to find the vertex with
// minimum distance from node in tree
int closestVertex( double distances[], bool inTree[] )
{
    // Initialize variable for holding min
    double min      = std::numeric_limits<double>::max();
    int    minIndex = -1;

    for ( int i = 0; i < numPoints; i++ ){
        if( inTree[i] == false && distances[i] < min ){
            min = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// A utility function to print the constructed MST
// by taking in an array parent where parent[i]
// describes the node i is connected to where
// parent[treeRoot] = -1
void printMST( int parent[numPoints], double** Graph )
{
    // Prints unsorted output of my implementation
/*    for( int i = 1; i < numPoints; i++ )
    {
        std::cout << std::setw(6) << i << std::setw(6) << parent[i] << std::endl;
    }
*/
    
    // Prints the data in the desired format by making
    // an array for each vertex and sorting any others
    // associated with it in the tree that have not yet
    // been printed
    bool isPrinted[numPoints - 1];
    for( int i = 0; i < numPoints-1; i++ )
        isPrinted[i] = false;
    std::vector<int> pairs;
    for( int i = 0; i < numPoints; i++ )
    {
        for( int j = i; j < numPoints; j++ )
        {

            if( parent[j] == i && isPrinted[j] == false )
            {
                pairs.push_back(j);
                isPrinted[j] = true;
            }
        }
        if( parent[i] != -1 && isPrinted[i] == false)
        {
            pairs.push_back(parent[i]);

            isPrinted[i] = true;
        }
        std::sort (pairs.begin(), pairs.end());
        if( pairs.size() > 0 )
        {
            for( int r = 0; r < pairs.size(); r++ )
            {
                std::cout << std::setw(6) << i << std::setw(6) << pairs[r] << std::endl;
            }
            pairs.clear();
        }
    }
}

void printPrimMST( double** Graph )
{
    int    parent[numPoints];
    double distances[numPoints];
    bool   inTree[numPoints];
    
    // Initialize all distances as infinite
    // and all points as not in tree
    for ( int i = 0; i < numPoints; i++ )
    {
        distances[i] = std::numeric_limits<double>::max();
        inTree[i]    = false;
    }
    
    // Start tree at first vertex
    distances[0] = 0;
    
    // Signifies first vertex as root of MST
    parent[0] = -1;
    
    // The MST must have V vertices
    for( int i = 0; i < numPoints - 1; i++ )
    {
        // From the set of verticies not yet in the tree
        // pick the closest adjacent vertex to the current
        // MST
        int closest = closestVertex( distances, inTree );
        
        // Add that vertex to the tree
        inTree[closest] = true;
        
        // Update distances array to add vertices that have
        // now become adjacent to the MST
        for( int j = 0; j < numPoints; j++ )
        {
            // Graph[u][j] is only non-zero for vertices
            // u and j such that u and j are connected by
            // an edge of the Euclidian distance between
            // Points u and j
            
            // inTree[j] is false for vertex j not yet in MST
            
            // Update distances[j] only if Graph[u][j] is smaller
            // than its current distance from the tree
            // Remember they all start at infinite distances
            if ( Graph[closest][j] > 0 && inTree[j] == false  && Graph[closest][j] < distances[j] )
            {
                parent[j]    = closest;
                distances[j] = Graph[closest][j];
            }
        }
    }
    // Print the constructed MST
    printMST( parent, Graph );
}

int main()
{
    //Get the number of Points/vertices
    std::cin >> numPoints;

    std::vector<Point> Vertex;
    double x      = 0;
    double y      = 0;
    // Create an array of Points from intputs
    for( int i = 0; i < numPoints; i++){
        std::cin >> x;
        std::cin >> y;
        Vertex.push_back( Point( x, y ) );
    }
    
    // Initialize Graph to all zeroes
    double** Graph = new double* [numPoints];
    for ( int i = 0; i < numPoints; i++)
    {
        Graph[i] = new double[numPoints];
    }
    
    for( int i = 0; i < numPoints; i++ ){
        for( int j = 0; j < numPoints; j++ ){
            Graph[i][j] = 0;
        }
    }
    
    // Construct Graph based of vertices
    int vertex1     = 0;
    int vertex2     = 0;
    double distance = 0;
    std::cin >> numEdges;
    for( int i = 0; i < numEdges; i++ ){
        std::cin >> vertex1;
        std::cin >> vertex2;
        distance = distanceBetween( Vertex[vertex1], Vertex[vertex2] );
        Graph[vertex1][vertex2] = distance;
        Graph[vertex2][vertex1] = distance;
    }
    
    // Special case where m = 0;
    if( numEdges == 0 ){
        for( int i = 0; i < numPoints; i++ ){
            for( int j = 0; j < numPoints; j++){
                if ( i != j ){
                    distance = distanceBetween( Vertex[i], Vertex[j] );
                    Graph[i][j] = distance;
                }
            }
        }
    }
    
    //Print graph
    for( int i = 0; i < numPoints; i++ ){
        for( int j = 0; j < numPoints; j++ ){
            std::cout << std::setw(12) << Graph[i][j];
        }
        std::cout << std::endl;
    }
    
    printPrimMST( Graph );
    
    return 0;
}
