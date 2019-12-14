#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree3DNode{
public:
    int xLeft,xRight;
    int yLeft,yRight;
    int xMid,yMid;

};

template <typename T>
class SegmentTree3D{
public:
    int xLength;
    int yLength;
    T** data;
    SegmentTree3D(int xLength,int yLength,T** source){

    }
};


int main(){
    std::cout<<"Hello, World!"<<std::endl;
    return 0;
}