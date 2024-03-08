// Example: clear, toggle a especific bit in a registrer from a configuration in a hardware;


#include <iostream>
#include <string>
#include <bit>
#include <cstdint>

using namespace std;

// Registrer
struct Reg_t {
    union{
    struct {
        u_int8_t A_0 : 1; 
        u_int8_t A_1 : 1; 
        u_int8_t A_2 : 1; 
        u_int8_t A_3 : 1; 
        u_int8_t A_4 : 1; 
        u_int8_t A_5 : 1; 
        u_int8_t A_6 : 1; 
        u_int8_t A_7 : 1; 
    };
    u_int8_t A;
    };
} PortA ;

void setBit(Reg_t& reg, int k) 
{ 
    reg.A |= (1 << (k )); 
} 
  
void clearBit(Reg_t& reg, int k) 
{ 
    reg.A &= ~(1 << (k )); 
} 
   
void toggleBit(Reg_t& reg, int k) 
{ 
    reg.A ^= (1 << (k )); 
} 


ostream& operator<<(ostream& cout_, Reg_t& reg){
    cout_ << "0: " << static_cast<int>(reg.A_0) << "\n"
            << "1: " << static_cast<int>(reg.A_1) << "\n"
            << "2: " << static_cast<int>(reg.A_2) << "\n"
            << "3: " << static_cast<int>(reg.A_3) << "\n"
            << "4: " << static_cast<int>(reg.A_4) << "\n"
            << "5: " << static_cast<int>(reg.A_5) << "\n"
            << "6: " << static_cast<int>(reg.A_6) << "\n"
            << "7: " << static_cast<int>(reg.A_7) << "\n";
    std::cout << '\n';
    return cout_;
}



int main() {

cout << "Initial registrer" << endl;
cout << PortA << endl;

cout << "Set bit 7 " << endl;
setBit(PortA,7);
cout << PortA << endl;
cout << "Set bit 6 " << endl;
setBit(PortA,6);
cout << PortA << endl;

cout << "Clear bit 7 " << endl;
clearBit(PortA,7);
cout << PortA << endl;

cout << "Toggle bit 2 " << endl;
toggleBit(PortA,2);
cout << PortA << endl;
cout << "Toggle bit 2 " << endl;
toggleBit(PortA,2);
cout << PortA << endl;


return 0;



}