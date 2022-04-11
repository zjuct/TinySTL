#include<iostream>
#include"list.h"
#include"vector.h"
#include"algorithm.h"
using namespace TinySTL;
using std::cout;
using std::endl;


class Person{
	public:
	Person()=default;
	Person(int age,std::string name):_age(age),_name(name){

	}
	public:
	int _age;
	std::string _name;
};

int main(){
	std::initializer_list<int>il={5,3,4,2,1,7};
	vector<int>vec(il);
	//for_each(il.begin(),il.end(),[](const Person& person){
		//std::cout<<person._name<<"  "<<person._age<<std::endl;
	//});
	for_each(vec.begin(),vec.end(),[](const int& num){
		cout<<num<<endl;
	});

	cout<<"---------------------------------------------"<<endl;
	

	
	
}