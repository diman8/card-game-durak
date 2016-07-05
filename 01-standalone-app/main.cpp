#include <iostream>
#include <Deck.h>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "");
    Deck my(13,4,0);
    my.Shuffle();
//    for(int i=0; i < 52; i++)
//    {
//        Card temp = my.Take();
//        std::wcout << temp.Print2() << std::endl;
//        for (int j=0; j < my.size; j++)
//        {
//            if (temp.Fight(my[j], 0) == 1)
//            {
//                std::wcout << L"    kill " << my[j].Print2() << std::endl;
//            }
//        }
//    }

    vector<Card> player1 = my.Take(6);
    vector<Card> player2 = my.Take(6);

    //GAEM

    wcout << L"Player1 has: ";
    for (int i=0; i<player1.size(); i++)
        wcout << player1[i].Print2() << ", ";
    wcout << L"\nPlayer2 has: ";
    for (int i=0; i<player2.size(); i++)
        wcout << player2[i].Print2() << ", ";
    //p1 turn





    return 0;
}
