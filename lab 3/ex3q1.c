/*Author: Samia Rahman
*Date: 29st September
*Purpose: 
*Persons discussed w/:
*References:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int live1 = 3;
    int live2 = 3;
    int player_1_point = 0;
    int player_2_point = 0;
    int dice_rolling[3];
    char answer;
    int turn1 = 1; // Took these 2 out of the loop nahole bar bar 0 dekhabe, also star from 1
    int turn2 = 1;

    while (live1 > 0 && live2 > 0)
    {

        printf("Turn %d player 1: ", turn1);
        scanf(" %c", &answer);

        if (answer == 'r' && turn1 < 4) /// added a couditon to stop the round after 3 turns
        {
            turn1++;

            int i;
            for (int i = 0; i < 3; i++)
            {
                dice_rolling[i] = rand() % 6 + 1; // dice value from 1 to 6
            }

            // Sort the dice in ascending order

            for (i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2 - i; j++)
                {
                    if (dice_rolling[j] > dice_rolling[j + 1])
                    {
                        int temp = dice_rolling[j];
                        dice_rolling[j] = dice_rolling[j + 1];
                        dice_rolling[j + 1] = temp;
                    }
                }
            }

            // Calculate points for Player 1
            if (dice_rolling[0] == 4 && dice_rolling[1] == 5 && dice_rolling[2] == 6)
            {
                player_1_point = 1000;
            }
            else if (dice_rolling[0] == 1 && dice_rolling[1] == 1 && dice_rolling[2] == 1)
            {
                player_1_point = 999;
            }
            else if (dice_rolling[0] == 2 && dice_rolling[1] == 2 && dice_rolling[2] == 2)
            {
                player_1_point = 998;
            }
            else if (dice_rolling[0] == 3 && dice_rolling[1] == 3 && dice_rolling[2] == 3)
            {
                player_1_point = 997;
            }
            else if (dice_rolling[0] == 4 && dice_rolling[1] == 4 && dice_rolling[2] == 4)
            {
                player_1_point = 996;
            }
            else if (dice_rolling[0] == 5 && dice_rolling[1] == 5 && dice_rolling[2] == 5)
            {
                player_1_point = 995;
            }
            else if (dice_rolling[0] == 6 && dice_rolling[1] == 6 && dice_rolling[2] == 6)
            {
                player_1_point = 994;
            }
            else if (dice_rolling[0] == 1 && dice_rolling[1] == 2 && dice_rolling[2] == 3)
            {
                player_1_point = 993;
            }
            else
            {
                player_1_point = 100 * dice_rolling[2] + 10 * dice_rolling[1] + dice_rolling[0];
            }

            printf("You rolled: %d %d %d = %d points\n", dice_rolling[0], dice_rolling[1], dice_rolling[2], player_1_point);
            live1--;
        }
        else if (answer == 's')
        {
            printf("Player 1 chose to stop rolling\n");
            player_1_point = 0;

            //  Player 2's turn
            printf("Turn %d player 2: ", turn2);
            scanf(" %c", &answer);

            if (answer == 'r' && turn2 < 4)
            {
                turn2++;
                int i;
                for (i = 0; i < 3; i++)
                {
                    dice_rolling[i] = rand() % 6 + 1; // Dice values from 1 to 6
                }

                // Sort the dice in ascending order
                for (i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2 - i; j++)
                    {
                        if (dice_rolling[j] > dice_rolling[j + 1])
                        {
                            int temp = dice_rolling[j];
                            dice_rolling[j] = dice_rolling[j + 1];
                            dice_rolling[j + 1] = temp;
                        }
                    }
                }

                // Calculate points for Player 2
                if (dice_rolling[0] == 4 && dice_rolling[1] == 5 && dice_rolling[2] == 6)
                {
                    player_2_point = 1000;
                }
                else if (dice_rolling[0] == 1 && dice_rolling[1] == 1 && dice_rolling[2] == 1)
                {
                    player_2_point = 999;
                }
                else if (dice_rolling[0] == 2 && dice_rolling[1] == 2 && dice_rolling[2] == 2)
                {
                    player_2_point = 998;
                }
                else if (dice_rolling[0] == 3 && dice_rolling[1] == 3 && dice_rolling[2] == 3)
                {
                    player_2_point = 997;
                }
                else if (dice_rolling[0] == 4 && dice_rolling[1] == 4 && dice_rolling[2] == 4)
                {
                    player_2_point = 996;
                }
                else if (dice_rolling[0] == 5 && dice_rolling[1] == 5 && dice_rolling[2] == 5)
                {
                    player_2_point = 995;
                }
                else if (dice_rolling[0] == 6 && dice_rolling[1] == 6 && dice_rolling[2] == 6)
                {
                    player_2_point = 994;
                }
                else if (dice_rolling[0] == 1 && dice_rolling[1] == 2 && dice_rolling[2] == 3)
                {
                    player_2_point = 993;
                }
                else
                {
                    player_2_point = 100 * dice_rolling[2] + 10 * dice_rolling[1] + dice_rolling[0];
                }

                printf("You rolled: %d %d %d = %d points\n", dice_rolling[0], dice_rolling[1], dice_rolling[2], player_2_point);
            }
            else if (answer == 's')
            {
                printf("Player 2 chose to stop rolling\n");
                player_2_point = 0;
            }
        }
        
    }

    return 0;
}
