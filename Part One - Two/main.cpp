#include "part1_2.h"

int main(){
    PartOne_Two function;
    //Segments hotel pricing data into different months under the divide-and-conquer principle.
    function.readData("marketData_1Jan.csv");
    function.readData("marketData_2Feb.csv");
    function.readData("marketData_3Mar.csv");
    function.readData("marketData_4Apr.csv");
    function.readData("marketData_5May.csv");
    function.readData("marketData_6Jun.csv");
    function.readData("marketData_7Jul.csv");
    function.readData("marketData_8Aug.csv");
    function.readData("marketData_9Sep.csv");
    function.readData("marketData_10Oct.csv");
    function.readData("marketData_11Nov.csv");
    function.readData("marketData_12Dec.csv");
    function.dynamicPricing(4); // Current function set to (4). It finds the best prices for each month for the suites type.

}