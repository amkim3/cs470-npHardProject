#include "baseConversions.h"

int base10(long long int num) {
    int result = 0;
    int power = 0;
    while (num > 0) {
        int digit = num % 10;
        result += digit * pow(4, power);
        power++;
        num /= 10;
    }
    return result;
    
}
int base4(long long int num) {
    int base4 = 0;
    int power = 0;
    
    while (num > 0) {
        int remainder = num % 4;
        base4 += remainder * pow(10, power);
        num /= 4;
        power++;
    }
    
    return base4;

}