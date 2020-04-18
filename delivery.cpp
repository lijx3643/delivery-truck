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
  Address(double x,double y)                // constructor, passing in value of x and y
    : x(x),y(y) {};
  double distance(Address temp){            // calculating distance between two Address points
    double m=temp.x;                       
    double n=temp.y;
    return sqrt((m-x)*(m-x)+(n-y)*(n-y));
  };
  double the_x(){return x;};                // return the value of x
  double the_y(){return y;};                // return the value of y
};

class Route{
private:
  vector <Address> address_list;                  // the list of addresses
public:
  Route()                                         // constructor of an address list
    :address_list(2,Address(0,0)){};              
  
  void add_address(Address a){                    // insert new address into the list
    address_list.insert(address_list.end()-1,a);
  }
  
  double length(){                                // calculate the length to travel the list in order
    double len=0.;
    for(int i=0;i<address_list.size()-1;i++){
      Address p=address_list.at(i);
      Address q=address_list.at(i+1);
      double dist_temp=p.distance(q);
      len+=dist_temp;
    }
    return len;
  };
    
  int size(){                                     // return the size of the list
    return address_list.size();
  };
  
  void as_string(){                               // print the list as string
    for(int i=0;i<address_list.size();i++){
      Address a = address_list.at(i);
      cout<<"("<<a.the_x()<<","<<a.the_y()<<") ";
    }
    cout<<endl;
  };

  Route greedy_route(){
    Route greedy;                                             // create a new Route, greedy
    vector<Address> greedy_list=greedy.address_list;          // the greedy_list, used to construct new list
    vector<Address> copy_list=address_list;                   // copy the original list
    copy_list.erase(copy_list.begin());                       // erase the begin and end point
    copy_list.erase(copy_list.end());
    
    Address we_are_here=greedy_list.at(0);                    // the current point
    while(!copy_list.empty()){                                // loop until the copy_list is empty
      int target=0;                                 
      double dist_temp=copy_list.at(0).distance(we_are_here); 
      for(int i=1;i<copy_list.size();i++){
        if(copy_list.at(i).distance(we_are_here)<dist_temp){  // find the point closest to current point
          target=i;                                           // keep its index
        }
      }
      we_are_here=copy_list.at(target);                       // update current point
      greedy_list.insert(greedy_list.end()-1,we_are_here);    // insert the point into the new list
      copy_list.erase(copy_list.begin()+target);              // erase the point from copy list
    }
    greedy.address_list=greedy_list;                          // update the list in Route greedy
    return greedy;                                            // return the new Route
  };
  
  Route reverse_route(){
    Route reverse;                                            // create a new Route, reverse
    reverse.address_list=address_list;                        // initialize the reverse route
    for(int i=1;i<address_list.size()-2;i++){                 // for each sublist 
      for(int j=i+1;j<address_list.size()-1;j++){
      	vector<Address> temp_list=address_list;               // create a temp_list to store reverse list
        int left=i;
        int right=j;
        while(left<=j){                                       // reverse the sublist
          temp_list.at(left)=address_list.at(right);
          left++;
          right--;
        }
        Route temp;                                           // create a new Route, temp
        temp.address_list=temp_list;
        if(temp.length()<reverse.length()){                   // if the temp_list is shorter, update reverse
          reverse.address_list=temp_list;
        }
      }
    }
    return reverse;                                           // return the Route reverse
  };
};


int main() {
  Route deliveries;
  deliveries.add_address(Address(0,5));                   // test addresses
  deliveries.add_address(Address(2,3));
  deliveries.add_address(Address(5,0));
  deliveries.add_address(Address(1,1));
  deliveries.add_address(Address(3,0));
  deliveries.add_address(Address(4,4));
  deliveries.add_address(Address(2,0));
  deliveries.add_address(Address(5,5));
  cout<<deliveries.length()<<endl;                      
  //assert(deliveries.size()==5);
  deliveries.as_string();
  Route route=deliveries.greedy_route();
  //assert(route.size()==5);
  double len= route.length();
  cout<<len<<endl;
  route.as_string();
  Route reverse=deliveries.reverse_route();
  //assert(reverse.size()==5);
  cout<<reverse.length()<<endl;
  reverse.as_string();
  
  while(route.reverse_route().length()<route.length()){
    route=route.reverse_route();
    cout<<route.length();
    route.as_string();
  }

}
