#include "base.h"
#include "SegmentTree.h"
#include "SegmentPersistenceTree.h"


/******************************************
 *             注意左闭右开                *
 ******************************************/


Segment3DPersistenceTree* tree=nullptr;


bool startWith(const string& a,const string& pattern){
    return pattern==a.substr(0,pattern.length());
}


void parse(const string& str){
    istringstream iss(str);
    string temp;

    // create tree 3 4 5
    if(startWith(str,"create tree ")){
        iss>>temp>>temp;
        int x,y,z;
        iss>>x>>y>>z;
        tree=new Segment3DPersistenceTree(x,y,z);
        return;
    }else{
        if(tree==nullptr){
            cout<<"Tree hasn't been initialized!"<<endl;
            return;
        }
    }

    // modify seg 1 2 1 2 1 2 5
    if(startWith(str,"modify seg ")){
        int xl,xr,yl,yr,zl,zr,diff;
        iss>>temp>>temp;
        iss>>xl>>xr>>yl>>yr>>zl>>zr>>diff;
        tree->modifySegment({xl,xr,yl,yr,zl,zr},diff);
        return;
    }

    // modify point 1 2 3 5
    if(startWith(str,"modify point ")){
        int x,y,z,diff;
        iss>>temp>>temp;
        iss>>x>>y>>z>>diff;
        tree->modifyPoint(x,y,z,diff);
        return;
    }

    // set seg 1 2 1 2 1 2 5
    if(startWith(str,"set seg ")){
        int xl,xr,yl,yr,zl,zr,set;
        iss>>temp>>temp;
        iss>>xl>>xr>>yl>>yr>>zl>>zr>>set;
        tree->setSegment({xl,xr,yl,yr,zl,zr},set);
        return;
    }

    // set point 1 2 3 5
    if(startWith(str,"set point ")){
        int x,y,z,set;
        iss>>temp>>temp;
        iss>>x>>y>>z>>set;
        tree->setPoint(x,y,z,set);
        return;
    }

    // query seg sum 1 2 1 2 1 2 5
    if(startWith(str,"query seg sum ")){
        int xl,xr,yl,yr,zl,zr,t;
        iss>>temp>>temp>>temp;
        iss>>xl>>xr>>yl>>yr>>zl>>zr>>t;
        cout<<tree->querySegmentSum({xl,xr,yl,yr,zl,zr},t)<<endl;
        return;
    }

    // query seg min 1 2 1 2 1 2 5
    if(startWith(str,"query seg min ")){
        int xl,xr,yl,yr,zl,zr,t;
        iss>>temp>>temp>>temp;
        iss>>xl>>xr>>yl>>yr>>zl>>zr>>t;
        cout<<tree->querySegmentMin({xl,xr,yl,yr,zl,zr},t).val<<endl;
        return;
    }

    // query seg max 1 2 1 2 1 2 5
    if(startWith(str,"query seg max ")){
        int xl,xr,yl,yr,zl,zr,t;
        iss>>temp>>temp>>temp;
        iss>>xl>>xr>>yl>>yr>>zl>>zr>>t;
        cout<<tree->querySegmentMax({xl,xr,yl,yr,zl,zr},t).val<<endl;
        return;
    }

    // query point 1 2 3 8
    if(startWith(str,"query point ")){
        int x,y,z,t;
        iss>>temp>>temp;
        iss>>x>>y>>z>>t;
        tree->queryPoint(x,y,z,t);
        return;
    }

    // show seg sum progress 1 2 1 2 1 2
    if(startWith(str,"show seg sum progress ")){
        int xl,xr,yl,yr,zl,zr;
        iss>>temp>>temp>>temp>>temp;
        iss>>xl>>xr>>yl>>yr>>zl>>zr;
        tree->debug_output_sum_process({xl,xr,yl,yr,zl,zr});
        return;
    }

}


int main(){
    while(true){
        cout<<"SegmentTree-> ";
        string input;
        getline(cin,input);
        if(input=="exit"){
            return 0;
        }
        try{
            parse(input);
        }catch(...){
            cout<<endl<<"Caught ERROR"<<endl<<endl;
        }
    }
}
