#include <iostream>
#include <vector>
#include <cmath> 
#include <cassert>
#include <string>

using std::cout; 
using std::endl;
using std::cin;
using std::vector;
using std::abs;
using std::string;
typedef bool boolean;

class Address{
private:
  double x,y;
public:
  Address(double x,double y)
    : x(x),y(y) {};
  double distance(Address temp){
    double m=temp.x;
    double n=temp.y;
    return sqrt((m-x)*(m-x)+(n-y)*(n-y));
  };
  double the_x(){return x;};
  double the_y(){return y;};
};

class Route{
private:
  vector <Address> address_list;
public:
  Route()
    :address_list(2,Address(0,0)){};
  
  void add_address(Address a){
    address_list.insert(address_list.end()-1,a);
  }
  
  double length(){
    double len=0.;
    for(int i=0;i<address_list.size()-1;i++){
      Address p=address_list.at(i);
      Address q=address_list.at(i+1);
      double dist_temp=p.distance(q);
      len+=dist_temp;
    }
    return len;
  };
    
  int size(){
    return address_list.size();
  };
  
  Route greedy_route(){
    Route greedy;
    vector<Address> greedy_list=greedy.address_list;
    vector<Address> copy_list=address_list;
    copy_list.erase(copy_list.begin());
    copy_list.erase(copy_list.end());
    
    Address we_are_here=greedy_list.at(0);
    while(!copy_list.empty()){
      int target=0;
      double dist_temp=copy_list.at(0).distance(we_are_here);
      for(int i=1;i<copy_list.size();i++){
	if(copy_list.at(i).distance(we_are_here)<dist_temp){
	  target=i;
	}
      }
      we_are_here=copy_list.at(target);
      greedy_list.insert(greedy_list.end()-1,we_are_here);
      copy_list.erase(copy_list.begin()+target);
    }

    greedy.address_list=greedy_list;
    return greedy;
  };
  
  void as_string(){
    for(int i=0;i<address_list.size();i++){
      Address a = address_list.at(i);
      cout<<"("<<a.the_x()<<","<<a.the_y()<<") ";
    }
    cout<<endl;
  }
  
  Route reverse_route(){
    Route reverse;
    reverse.address_list=address_list;
    
    for(int i=1;i<address_list.size()-2;i++){
      for(int j=i+1;j<address_list.size()-1;j++){
      	vector<Address> temp_list=address_list;
	int left=i;
	int right=j;
	//cout<<i<<"   "<<j<<endl;
	while(left<=j){
	  temp_list.at(left)=address_list.at(right);
	  left++;
	  right--;
	}

	Route temp;
	temp.address_list=temp_list;
	//cout<<temp.length()<<endl;
	//temp.as_string();
	if(temp.length()<reverse.length()){
	  reverse.address_list=temp_list;
	}
      }
    }
    return reverse;
  };

  void switch_route(Route &path1, Route &path2){
    vector<Address> rem1=path1.address_list;
    vector<Address> rem2=path2.address_list;

    for(int i=1;i<path1.address_list.size()-2;i++){ 
      for(int j=i;j<path1.address_list.size()-1;j++){
        vector<Address> one=rem1;
        vector<Address> two=rem2;
        for(int k=i;k<=j;k++){
          one.at(k)=path2.address_list.at(k);
          two.at(k)=path1.address_list.at(k);  
        }

        Route temp_one;
        Route temp_two;
        temp_one.address_list=one;
        temp_two.address_list=two;
        //temp_one.as_string();
        //temp_two.as_string();
        if(temp_one.length()+temp_two.length()<path1.length()+path2.length()){
          path1.address_list=one;
          path2.address_list=two;
        }
      }
    }
  };


};


int main() {
  cout<<"Single Truck!"<<endl;
  Route deliveries;
  deliveries.add_address(Address(0,5));
  deliveries.add_address(Address(2,3));
  deliveries.add_address(Address(5,0));
  deliveries.add_address(Address(1,1));
  deliveries.add_address(Address(3,0));
  deliveries.add_address(Address(4,4));
  deliveries.add_address(Address(2,0));
  deliveries.add_address(Address(5,5));
  cout<<"Original!"<<endl;
  cout<<deliveries.length()<<"    ";
  //assert(deliveries.size()==5);
  deliveries.as_string();
  cout<<"Greedy!"<<endl;
  Route route=deliveries.greedy_route();
  //assert(route.size()==5);
  double len= route.length();
  cout<<len<<"    ";
  route.as_string();
  cout<<"Original Reverse!"<<endl;
  Route reverse=deliveries.reverse_route();
  //assert(reverse.size()==5);
  cout<<reverse.length()<<"    ";
  reverse.as_string();
  cout<<"Greedy Reverse!"<<endl;
  while(route.reverse_route().length()<route.length()){
    route=route.reverse_route();
    cout<<route.length()<<"   ";
    route.as_string();
  }

  cout<<"Multiple Truck!"<<endl;
  Route path1;
  Route path2;

  path1.add_address(Address(2,0));
  path1.add_address(Address(3,2));
  path1.add_address(Address(2,3));
  path1.add_address(Address(0,2));

  path2.add_address(Address(3,1));
  path2.add_address(Address(2,1));
  path2.add_address(Address(1,2));
  path2.add_address(Address(1,3));

  double len_original=path1.length()+path2.length();
  cout<<len_original<<"    ";
  path1.as_string();
  path2.as_string();

  path1.switch_route(path1,path2);
  double len_switch=path1.length()+path2.length();
  cout<<len_switch<<"    ";
  path1.as_string();
  path2.as_string();
}
