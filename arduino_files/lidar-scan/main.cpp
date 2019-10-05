
#include<iostream>  
#include "sync.h"
  
using namespace std; 
  
int main() 
{
    Sync s;
    
    s.set_angle_min(10);
    cout<<s.get_angle_min()<<'\n';
      
    return 0; 
} 
