/*Author: Samia Rahman
*Date: 21st September
*Purpose: discount and coupon total output
*Persons discussed w/:
*References:
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int hardcover, softcover, ebook;

    printf("How many hardcover books are you buying? ");
    if (scanf("%d", &hardcover) == 1 && (hardcover >= 0 && hardcover < 100000)) {
        printf("How many softcover books are you buying? ");
        if (scanf("%d", &softcover) == 1 && (softcover >= 0 && softcover < 100000)) {
            printf("How many ebooks are you buying? ");
            if (scanf("%d", &ebook) == 1 && (ebook >= 0 && ebook < 100000)) {
                float book_total = (hardcover * 15.00) + (softcover * 12.00) + (ebook * 7.00);


                // coupon discount
                if (hardcover>= 2) {
                    book_total -= 5.00;
                } 
                if (softcover >= 4) {
                    book_total -= 10.00;
                } 
                if ((hardcover+softcover)>= 6){
                    book_total -= 20.00;
                }


                //percentage discounts

                float total = book_total;

                // Apply percentage discounts
                if (hardcover >= 1 && softcover >= 1 && ebook >= 1) {
                    book_total -= (total*0.03);
                }

                if (ebook >= 3) {
                    book_total -= (total*0.04);
                }

                if (book_total > 75) {
                    book_total -= (total*0.10);
                }

                if (book_total >150) {
                    book_total -= (total*0.15);
                }

                printf("Order total: $%.2f\n", book_total);

                }
            }
        }

        return 0;

    }
