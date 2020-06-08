#include "tree_serializer.h"
#include <iostream>
#include "tree.pb.h"

using namespace std;


const string TreeSerializer::FILE_NAME = "tree.bin";


bool TreeSerializer::Deserialize(){
    ifstream in(FILE_NAME,std::ios::binary);
    Serialize::NodeList nodeList;

    if (!in){
        return false;
    }else{
        if (nodeList.ParseFromIstream(&in)){
             for(const auto& value : nodeList.nodes()){
                switch(value.type()){
                    case Serialize::Node_TYPE::Node_TYPE_INT :
                        cout<<"value: "<<value.valueint()<<" level: "<<value.level()<<endl;
                    break;

                    case Serialize::Node_TYPE::Node_TYPE_DOUBLE :
                        cout<<"value: "<<value.valuedouble()<<" level: "<<value.level()<<endl;
                    break;

                    case Serialize::Node_TYPE::Node_TYPE_STRING :
                        cout<<"value: "<<value.valuestring()<<" level: "<<value.level()<<endl;
                    break;
                }
             }
        }
    }
    return true;
}
