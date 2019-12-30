#include "base.h"
#include "SegmentTree.h"
#include "SegmentPersistenceTree.h"


/*
 *             注意左闭右开
 * */


void parse(const string& str){

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
