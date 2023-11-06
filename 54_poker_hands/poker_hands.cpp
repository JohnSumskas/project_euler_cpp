
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

typedef std::pair<int, char> Card;
typedef std::vector<Card> Hand;

int getHighestCardValueExcluding(Hand hand, int excludedValue);
bool isStraight(Hand hand);
bool isFlush(Hand hand);
bool isFullHouse(Hand hand);
int getRepeatsOfValue(Hand hand, int value);


bool isStraight(Hand hand, std::vector<int> valueVector)
{
    std::vector<int> cardValues;
    for (auto& card : hand)
    {
        cardValues.push_back(card.first);
    }
    
    std::sort(cardValues.begin(), cardValues.end());

    if 
    (
        cardValues[1] == cardValues[0] + 1 &&
        cardValues[2] == cardValues[1] + 1 &&
        cardValues[3] == cardValues[2] + 1
    )
    {
        if (cardValues[4] == cardValues[3] + 1)
        {
            valueVector.push_back(cardValues[4]);
            return true;
        }
        else if(cardValues[0] == 2 && cardValues[4] == 14)
        {
            valueVector.push_back(5);
            return true;
        }
    }
    return false;
}

bool isFlush(Hand hand, std::vector<int>& valueVector)
{
    char suit = hand[0].second;

    std::vector<int> values;

    for (auto& card : hand)
    {
        if (card.second != suit)
        {
            return false;
        }
        values.push_back(card.first);
    }

    std::sort(values.begin(), values.end());

    valueVector.insert(valueVector.end(), values.begin(), values.end());
    return true;
}

bool isFullHouse(Hand hand, std::vector<int>& valueVector)
{
    int threeOfKindValue = 0;
    int pairValue = 0;

    for (auto& card : hand)
    {
        int repeats = getRepeatsOfValue(hand, card.first);
        if (repeats == 2)
        {
            pairValue = card.first;
        }
        else if (repeats == 3)
        {
            threeOfKindValue = card.first;
        }
        else
        {
            return false;
        }
    }
    if (threeOfKindValue == 0 || pairValue == 0)
    {
        return false;
    }
    valueVector.push_back(threeOfKindValue);
    valueVector.push_back(pairValue);
    return true;
}

int getRepeatsOfValue(Hand hand, int value)
{
    int count = 0;
    for (auto& card : hand)
    {
        if (card.first == value)
        {
            count++;
        }
    }
    return count;
}

int maxRepeats(Hand hand, int& repeatsValue)
{
    int maxRepeats = 0;
    int cardValue = 0;
    for (auto& card : hand)
    {
        int count = 0;
        int value = card.first;
        int repeats = getRepeatsOfValue(hand, value);
        if (repeats > maxRepeats)
        {
            maxRepeats = repeats;
            cardValue = value;
        }
    }

    repeatsValue = cardValue;
    return maxRepeats;
}

bool isFourOfAKind(Hand hand, std::vector<int>& valueVector)
{
    int value = 0;
    if (maxRepeats(hand, value) == 4)
    {
        valueVector.push_back(value);
        valueVector.push_back(getHighestCardValueExcluding(hand, value));

        return true;
    }
    return false;
}

int getHighestCardValue(Hand hand)
{
    int maxHand = 0;
    for (auto& card : hand)
    {
        if (card.first > maxHand)
        {
            maxHand = card.first;
        }
    }
    return maxHand;
}

int getHighestCardValueExcluding(Hand hand, int excludedValue)
{
    int maxHand = 0;
    for (auto& card : hand)
    {
        if (card.first == excludedValue)
        {
            continue;
        }
        if (card.first > maxHand)
        {
            maxHand = card.first;
        }
    }
    return maxHand;
}

int getHighestCardValueExcluding(Hand hand, int excludedValue1, int excludedValue2)
{
    int maxHand = 0;
    for (auto& card : hand)
    {
        if (card.first == excludedValue1 || card.first == excludedValue2)
        {
            continue;
        }
        if (card.first > maxHand)
        {
            maxHand = card.first;
        }
    }
    return maxHand;
}


int getHighestCardValueExcluding(Hand hand, int excludedValue1, int excludedValue2, int excludedValue3)
{
    int maxHand = 0;
    for (auto& card : hand)
    {
        if (card.first == excludedValue1 || card.first == excludedValue2 || card.first == excludedValue3)
        {
            continue;
        }
        if (card.first > maxHand)
        {
            maxHand = card.first;
        }
    }
    return maxHand;
}



bool containsCardValue(Hand hand, int value)
{
    for (auto& card : hand)
    {
        if (card.first == value)
        {
            return true;
        }
    }
    return false;
}

bool isThreeOfAKind(Hand hand, std::vector<int>& valueVector)
{
    int value = 0;
    if (maxRepeats(hand, value) == 3)
    {
        valueVector.push_back(value);
        int highest = getHighestCardValueExcluding(hand, value);
        valueVector.push_back(highest);
        valueVector.push_back(getHighestCardValueExcluding(hand, value, highest));
        return true;
    }
    return false;
}

bool isTwoPair(Hand hand, std::vector<int>& valueVector)
{
    int pairOneValue = 0;
    int pairTwoValue = 0;
    int lastValue = 0;

    for (auto& card : hand)
    {
        int repeats = getRepeatsOfValue(hand, card.first);
        if (repeats == 2)
        {
            if (pairOneValue == 0)
            {
                pairOneValue = card.first;
            }
            else if (pairOneValue != card.first)
            {
                pairTwoValue = card.first;
            }
        }
        else if (repeats == 3)
        {
            return false;
        }
        else
        {
            lastValue = card.first;
        }

    }
    if (pairOneValue == 0 || pairTwoValue == 0)
    {
        return false;
    }

    if (pairOneValue > pairTwoValue)
    {
        valueVector.push_back(pairOneValue);
        valueVector.push_back(pairTwoValue);
    }
    else
    {
        valueVector.push_back(pairTwoValue);
        valueVector.push_back(pairOneValue);
    }
    valueVector.push_back(lastValue);
    return true;
}


bool isPair(Hand hand, std::vector<int>& valueVector)
{
    int value = 0;
    if (maxRepeats(hand, value) == 2)
    {
        valueVector.push_back(value);
        int highest = getHighestCardValueExcluding(hand, value);
        valueVector.push_back(highest);

        int highest2 = getHighestCardValueExcluding(hand, value, highest);
        valueVector.push_back(highest2);
        valueVector.push_back(getHighestCardValueExcluding(hand, value, highest, highest2));

        return true;
    }
    return false;
}


void getHandScore(Hand hand, std::vector<int>& scoreVector)
{
    // 0 high card: 1, 2, 3, 4, 5
    // 1 pair: 1000 * suit + high card score   1, 2, 3
    // 2 two pair; pair 1, pair 2, high card
    // 3 three of a kind, card value, high card 1, high card 2
    // 4 Straight, high card
    // 5 flush, high card, 1, 2, 3, 4, 5
    // 6 full house, high card 1, high card 2
    // 7 four of a kind, value, high card
    // 8 straight flush, value
    // 9 royal flush

    std::vector<int> dummyValueVector = {};

    std::vector<int> valueVector = {};
    // Royal Flush
    if (isStraight(hand, dummyValueVector) && isFlush(hand, valueVector) && containsCardValue(hand, 14) && containsCardValue(hand, 13))
    {
        scoreVector.push_back(9);
        return;
    }
    // Straight Flush
    else if (isStraight(hand, valueVector) && isFlush(hand, dummyValueVector))
    {
        scoreVector.push_back(8);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else if (isFourOfAKind(hand, valueVector))
    {
        scoreVector.push_back(7);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else if (isFullHouse(hand, valueVector))
    {
        scoreVector.push_back(6);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else if (isFlush(hand, valueVector))
    {
        scoreVector.push_back(5);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else if (isStraight(hand, valueVector))
    {
        scoreVector.push_back(4);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else if (isThreeOfAKind(hand, valueVector))
    {
        scoreVector.push_back(3);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }

    else if (isTwoPair(hand, valueVector))
    {
        scoreVector.push_back(2);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else if (isPair(hand, valueVector))
    {
        scoreVector.push_back(1);
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }
    else
    {
        scoreVector.push_back(0);
        for (auto& card: hand)
        {
            valueVector.push_back(card.first);
        }

        std::sort(valueVector.begin(), valueVector.end());
        std::reverse(valueVector.begin(), valueVector.end());
        scoreVector.insert(scoreVector.end(), valueVector.begin(), valueVector.end());
        return;
    }

    return;
}

bool doesPlayerOneWinScoreVector(std::vector<int> playerOneScoreVector, std::vector<int> playerTwoScoreVector)
{
    if (playerOneScoreVector[0] > playerTwoScoreVector[0])
    {
        return true;
    }
    else if (playerOneScoreVector[0] < playerTwoScoreVector[0])
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < playerOneScoreVector.size(); i++)
        {
            int p1 = playerOneScoreVector[i];
            int p2 = playerTwoScoreVector[i];

            if (p1 > p2)
            {
                return true;
            }
            else if (p2 > p1)
            {
                return false;
            }
        }
    }
    return false;
}

void stringToHand(std::string stringHand, Hand& hand)
{
    std::istringstream handStream(stringHand);

    while (!handStream.eof())
    {
        std::string cardString;
        std::getline(handStream, cardString, ' ');

        int cardValue = 0;

        char cardValueChar = cardString[0];

        if (cardValueChar > '0' && cardValueChar <= '9')
        {
            cardValue = (int) (cardValueChar - '0');
        }
        else
        {
            switch (cardValueChar)
            {
            case 'T':
                cardValue = 10;
                break;
            case 'J':
                cardValue = 11;
                break;
            case 'Q':
                cardValue = 12;
                break;
            case 'K':
                cardValue = 13;
                break;
            case 'A':
                cardValue = 14;
                break;
            
            default:
                std::cout << "UNKNOWN CARD: " << cardValueChar << std::endl;
                break;
            }
        }

        Card card(cardValue, cardString[1]);
        hand.push_back(card);
    }
}

bool doesPlayerOneWin(Hand playerOneHand, Hand playerTwoHand)
{
    std::vector<int> p1Score = {};
    std::vector<int> p2Score = {};

    getHandScore(playerOneHand, p1Score);
    getHandScore(playerTwoHand, p2Score);

    return doesPlayerOneWinScoreVector(p1Score, p2Score);

}

int handsPlayerOneWins(std::string pokerHandsFileName)
{
    std::ifstream myfile; 
    myfile.open(pokerHandsFileName);

    int playerOneWinCount = 0;

    while ( !myfile.eof()) 
    {
        std::string myline;
        std::getline (myfile, myline);
        std::cout << myline << '\n';


        std::string playerOneHandString = myline.substr(0, 14);
        std::string playerTwoHandString = myline.substr(15);

        std::cout << playerOneHandString << " : " << playerTwoHandString << std::endl;

        Hand playerOneHand;
        Hand playerTwoHand;

        stringToHand(playerOneHandString, playerOneHand);
        stringToHand(playerTwoHandString, playerTwoHand);

        bool playerOneWins = doesPlayerOneWin(playerOneHand, playerTwoHand);

        if (playerOneWins)
        {
            std::cout << "Player 1 Won with " << playerOneHandString << " against " << playerTwoHandString << std::endl;
            playerOneWinCount++;
        }
        else
        {
            std::cout << "Player 2 Won with " << playerTwoHandString << " against " << playerOneHandString << std::endl;
        }
        }

    return playerOneWinCount;
}

int main()
{
    // std::string playerOneHandString = "2C 3S TH 9D JC";
    // std::string playerTwoHandString = "7D 2S 5D 3S AC";

    // Hand playerOneHand;
    // Hand playerTwoHand;

    // stringToHand(playerOneHandString, playerOneHand);
    // stringToHand(playerTwoHandString, playerTwoHand);

    // std::vector<int> scoreVector = {};

    // getHandScore(playerOneHand, scoreVector);

    // std::vector<int> valueVector = {};


    // std::cout << "Player 1 Score: " << p1scoreVector[0] << std::endl;

    // for (auto& score: p1scoreVector)
    // {
    //     std::cout << score << ", ";
    // }
    // std::cout << std::endl;




    // bool playerOneWins = doesPlayerOneWin(playerOneHand, playerTwoHand);

    // if (playerOneWins)
    // {
    //     std::cout << "Player 1 Won with " << playerOneHandString << " against " << playerTwoHandString << std::endl;
    // }
    // else
    // {
    //     std::cout << "Player 2 Won with " << playerTwoHandString << " against " << playerOneHandString << std::endl;
    // }
    int winCount = handsPlayerOneWins("poker_hands.txt");
    std::cout << "Hands Player 1 Wins: " << winCount << std::endl;
    return 0;
}