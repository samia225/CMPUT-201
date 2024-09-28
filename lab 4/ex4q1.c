/*Author: Samia Rahman
*Date: 8th October
*Purpose: Expression interpreter
*Persons discussed w/:
*References:
*/

#include <stdio.h>

int main(int argc, char **argv) {
    char crop;
    double sale_price, purchase_price;
    double total_profit = 0.0, total_loss = 0.0;

    while ((crop = getchar()) != '\n' && crop != EOF) {
        if (crop == '/') {
            crop = getchar();
            if (crop == 'C') {
                sale_price = 0.50;
                purchase_price = 0.05;
                total_profit += sale_price - purchase_price;
            } else if (crop == 'T') {
                sale_price = 1.25;
                purchase_price = 0.25;
                total_profit += sale_price - purchase_price;
            } else if (crop == 'P') {
                sale_price = 3.00;
                purchase_price = 0.70;
                total_profit += sale_price - purchase_price;
            } else if (crop == 'L') {
                sale_price = 1.00;
                purchase_price = 0.30;
                total_profit += sale_price - purchase_price;
            }
        } else if (crop == '#') {
            crop = getchar();
            if (crop == 'C') {
                purchase_price = 0.05;
                total_loss += purchase_price;
            } else if (crop == 'T') {
                purchase_price = 0.25;
                total_loss += purchase_price;
            } else if (crop == 'P') {
                purchase_price = 0.70;
                total_loss += purchase_price;
            } else if (crop == 'L') {
                purchase_price = 0.30;
                total_loss += purchase_price;
            }
        }
    }

    double net_profit = total_profit - total_loss;

    if (net_profit>0){
        printf("Net profit: $%.2lf\n", net_profit);
    }
    else if (net_profit<0){
        net_profit = net_profit*(-1);
        printf("Net profit: -$%.2lf\n", net_profit);
    }
    
    
    return 0;
}
