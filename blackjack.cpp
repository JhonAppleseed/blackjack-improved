#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;


  // BLACK JACK LOGIC
  //
  // 52 cards
  // multiple decks?
  //
  // face cards = 10
  // ace = 1/11
  // number cards = pip value
  // 0. bets
  // 1. player recieve 2 face up cards
  // 2. host recieve 1 face up 1 face down (check wheter if face card is ace to incurance )
  // 3. player actions (hit/stand/double/split) (if over 21 bust)
  // 4. host hits until equal or higher than 17 (if over 21 bust)
  // 5. payout player or host


 // 1. CARD CLASS
 // 2. DECK CLASS
 // 3. RACK CLASS
 // 4. GAME CLASS
 // 5. PLAYER CLASS

 int ranks[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, };
 string suits[4] = {"spades", "hearts", "diamonds", "clubs"};

struct CardStruct{
  string suit;
  int rank;

  CardStruct(string x, int y)
    : suit(x), rank(y) {}
};

class Card{
  private:
    string suit;
    int rank;
  public:
    Card(){
      this->suit = "unknown";
      this->rank = 0;
    }

    Card(string x, int y){
      this->suit = x;
      this->rank = y;
    }

    CardStruct getValues(){
      return {this->suit, this->rank};
    }
};

class Deck {
  private:
     vector<CardStruct> deckOfCards;
  public:
    Deck(){
      for (auto& suit : suits){
        for (auto& rank : ranks){
          deckOfCards.push_back(CardStruct(suit, rank));
        }
      }
      
    }
    vector<CardStruct> getDeckVector(){
      return this->deckOfCards;
    }

    void shuffleDeck(){
      random_device rd;
      mt19937 g(rd());
      shuffle(deckOfCards.begin(), deckOfCards.end(), g);
    }
};

class Shoe {
  private:
    vector<Deck> shoeRack;
  public:
    Shoe(){
      this->shoeRack.push_back(Deck());
    }
    Shoe(int x){
      for (int i = 0; i < x; i++){
        this->shoeRack.push_back(Deck());
      }
    }
    //CardStruct dealCard(){}
    void shuffleShoe(){
      for (auto& deck : shoeRack){
        deck.shuffleDeck();
      }
    }

    void presentShoe(){
      for (auto& deck : shoeRack){
        for (auto& pair : deck.getDeckVector()){
           cout << pair.rank <<" of " << pair.suit << endl;
        }
        cout << "END OF DECK" << endl;
      }
    }
};


int main(){
  srand(time(0));
  //Deck myDeck;
  //myDeck.shuffleDeck();
  //for (auto& pair : myDeck.getDeckVector()){
  //  cout << pair.rank <<" of " << pair.suit << endl;
  //} // DEBUG LOOP TO CHECK ONE DECK
  //Shoe myShoe(4);
  //myShoe.shuffleShoe();
  //myShoe.presentShoe();

  return 0;
}
