#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;


 int ranks[13] = {  2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
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


class Shoe{
  private:
    vector<CardStruct> shoeOfCards;
  public:
    Shoe(int x = 1){
      for (int i = 0; i < x; i++){
        for (auto& rank : ranks){
          for (auto& suit : suits){
            shoeOfCards.push_back(CardStruct(suit, rank));
          }
        }
      }
    }

    CardStruct dealCard(){
      int randInt = rand() % cardsInShoe();
      CardStruct chosenCard = shoeOfCards.at(randInt);
      shoeOfCards.erase(shoeOfCards.begin() + randInt);
      return chosenCard;
    }

    void shuffleRack(){
      random_device rd;
      mt19937 g(rd());
      shuffle(shoeOfCards.begin(), shoeOfCards.end(), g);
    }

    void presentShoe(){
      for (auto& pair : shoeOfCards){
        cout << pair.rank <<" of " << pair.suit << endl;
      }
    }

    int cardsInShoe(){
      return shoeOfCards.size();
    }
};




class Player{
  private:
    string name;
    int wins = 0;
    int bal;
  public:
    Player(string x = "John", int y = 100){
      this->name = x;
      this->bal = y;
    }

    void addBalance(){
      int topUp;
      do {
        cout << "How much would you like to topup? " << endl;
        cout << "+>: ";
        cin >> topUp;
      } while (topUp < 1 || topUp > 99999);

      this->bal += topUp;
    }

    int getBalance(){
      return this->bal;
    }

    void presentPlayer(){
      cout << endl;
      cout << "Player: " << this->name << endl;
      cout << "Wins: " << this->wins << endl;
      cout << "Balance: " << this->bal << endl;
      cout << endl;
    }
};



// GAME CLASS 
class Game{
  private:
    Player currentPlayer; //could be vector for "accounts"
    int playedGames;
  public:
    Game(string name, int bal){
      this->currentPlayer = Player(name, bal);
    }

    Game(){
      this->currentPlayer = Player(); 
    }

    Player& getCurrentPlayer(){
      return this->currentPlayer;
    }

    void startGame();
};

class Table{
  private:
    int betAmount;
    int incurance = 0;
    vector<CardStruct> playerCards;
    vector<CardStruct> houseCards;
  public:
      Table(int x){
        this->betAmount = x;
      }

      string firstSetup(Shoe& shoe){
        playerCards.push_back(shoe.dealCard());
        playerCards.push_back(shoe.dealCard());
        houseCards.push_back(shoe.dealCard());
        houseCards.push_back(shoe.dealCard());
        cout << "House card: " << this->houseCards[0].rank << endl;
        cout << "Player total: " << this->playerTotal() << endl;
        if (this->houseCards[0].rank == 11){
          int pinc;
          do {
            cout << "Incurance?" << endl;
            cout << "1. yes | 2. no" << endl;
            cout << "+>: ";
            cin >> pinc;
          } while(pinc < 1 || pinc > 2);
          if (pinc == 1){
            this->incurance = betAmount / 2;
          }
        }
        if (this->playerTotal() == 21 && this->playerTotal() > this->houseTotal()){
          return "player";
        } else if (this->houseTotal() == 21 && this->houseTotal() > this->playerTotal()){
          return "house"; 
        } 
        return "none";
      }

      string playerTurn(Shoe& shoe){
        cout << "Player turn" << endl;
        int playerChoice;
        string avalibility = (this->playerCards[0].rank == this->playerCards[1].rank) ? "" : "not avalibile";
        while (true){
          cout << "(1). Hit" << endl;
          cout << "(2). Stand" << endl;
          cout << "(3). Split " << avalibility << endl;
          cout << "+>: ";
          cin >> playerChoice;
          if (playerChoice == 1){
            CardStruct dealtCard = shoe.dealCard();
            if (dealtCard.rank == 11 && playerTotal() >= 11){
              dealtCard.rank = 1;
            }
            this->playerCards.push_back(dealtCard);
            cout << "Player total: "<< this->playerTotal() << endl;
            if (this->playerTotal() > 21){
              cout << "Hitting..." << endl;
              return "house";
            }
          } else if (playerChoice == 2){
            cout << "Standing..." << endl;
            return "none";
          } else if (playerChoice == 3 && avalibility == ""){
            cout << "Splitting..." << endl;
            return "none";
          }
        }
      }
      string houseTurn(Shoe& shoe){
        cout << "House turn" << endl;
        cout << "House total: " << this->houseTotal() << endl;
        while (true){
          this->houseCards.push_back(shoe.dealCard());
          cout << "House total: " << this->houseTotal() << endl;
          if (this->houseTotal() < 17){
            continue;
          }
          if (this->houseTotal() > 21 || this->houseTotal() < playerTotal()){
            return "player";
          } else if (this->houseTotal() == playerTotal()){
            return "none";
          }
        }

        return "none";
      }

      int playerTotal(){
        int total = 0;
        for (auto& card : playerCards){
          total += card.rank;
        }
        return total;
      }

      int houseTotal(){
        int total = 0;
        for (auto& card : houseCards){
          total += card.rank;
        }
        return total;
      }
 

      // Winning logic

};

void Game::startGame(){
  int playerChoice;
  do{
    cout << "Choose deck amount (1-8)" << endl;
    cout << "+>: ";
    cin >> playerChoice;
  } while(playerChoice < 1 || playerChoice > 8);

  Shoe shoe(playerChoice); // shoe init when game starts

  // WHILE LOOP SHOULD BE HERE

  int playerOption;
  while (true){
    cout << "\n(1) Choose bet" << endl;
    cout << "(2) Leave table" << endl;
    cout << "+>: ";
    cin >> playerOption;
    if (playerOption == 1){
      break;
    } else if (playerOption == 2) {
      return;
    } else {
      continue;
    }
  }

  int playerBet;
  do{
    cout << "\nBet amount (1-100)" << endl;
    cout << "+>: ";
    cin >> playerBet;
  } while (playerBet < 1 || playerBet > 100 || playerBet > currentPlayer.getBalance());
  // GAME STARTS

  Table cutb(playerBet);
  string winner = cutb.firstSetup(shoe);
  if (winner == "none"){
    string winner = cutb.playerTurn(shoe);
    if (winner == "none"){
      string winner = cutb.houseTurn(shoe);
    }
  }
  cout << winner << " has won" << endl;
}

struct InitPlayer{
  string name;
  int bal;

  InitPlayer(string x, int y){
    this->name = x;
    this->bal = y;
  }
};

InitPlayer initGame(){
  string name;
  int bal;
  do {
    cout << "Enter playername: ";
    getline(cin, name);
  } while (name.empty());

  do {
    cout << "Enter balance: ";
    cin >> bal;
  } while (bal < 1 || bal > 99999);
  return InitPlayer(name, bal);
}



int main(){
  cout << "--------- --" << endl;
  cout << "BLACKJACK 21" << endl;
  cout << "--------- --" << endl;

  srand(time(0)); 

  InitPlayer player = initGame();
  Game myGame(player.name, player.bal);
  
  int playerChoice;

  while (true){
    cout << "Options: " << "\n\n";
    cout << "(1) Join Table " << endl;
    cout << "(2) Top Up" << endl;
    cout << "(3) View Stats" << endl;
    cout << "(4) Exit" << endl;
    cout << "+>: ";
    cin >> playerChoice;
    if (playerChoice == 1){
      myGame.startGame();
    } else if (playerChoice == 2){
      myGame.getCurrentPlayer().addBalance();
    } else if (playerChoice == 3){
      myGame.getCurrentPlayer().presentPlayer();
    } else if (playerChoice == 4) {
      cout << "\n" << "GAME HAS ENDED" << "\n";
      break;
    } else {
      continue;
    }

  }
  return 0;
}
