#pragma once
#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;

void HumanStrategy::execute(Player* thisPlayer, Player* otherPlayer)
{
    Card c = thisPlayer->pickCard();
    thisPlayer->performgood(c.good);
    thisPlayer->performaction(c.action, otherPlayer);
    cout << "\n\n";
    thisPlayer->display();
}

void GreedyStrategy::execute(Player* thisPlayer, Player* otherPlayer)
{
    thisPlayer->hand->Show();

    vector <Card*> cards = thisPlayer->hand->getFaceUpCards();

    string action = "";
    int cost = 0;
    int destroyArmyIndex = -1;
    int buildCityIndex = -1;

    bool foundBuildCity = false;
    bool foundDestroyArmy = false;

    for (int i = 0; i < 6; i++)
    {
        action = cards[i]->action;
        
        cost = thisPlayer->hand->getCardCost(i);
        
        if (cost > thisPlayer->getmoney())
            continue;

        if (cards[i]->action.find(" Destroy army AND Build City") != string::npos)
        {
            if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
            {
                Card card = thisPlayer->hand->exchange(i);

                thisPlayer->handList->push_back(make_pair(card.toString(), i + 1));
                thisPlayer->setlastCard(card);
                //PHASE-OBSERVER
                thisPlayer->notify("cardpicked");

                thisPlayer->performgood(card.good);
                thisPlayer->performaction(action, otherPlayer);                


                cout << "\n\n";
                thisPlayer->display();
                return;
            }

        }
        else if (cards[i]->action.find("AND") != string::npos && (cards[i]->action.find("Destroy army") != string::npos || cards[i]->action.find("Build City") != string::npos) )
        {            
            if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
            {
                Card card = thisPlayer->hand->exchange(i);
                thisPlayer->handList->push_back(make_pair(card.toString(), i + 1));
                thisPlayer->setlastCard(card);

                //PHASE-OBSERVER
                thisPlayer->notify("cardpicked");

                thisPlayer->performgood(card.good);


                string actionone = action.substr(0, action.find("AND") - 1);
                string actiontwo = action.substr(action.find("AND") + 4);

                //only perform if it is destroy army or build city
                if (actionone.find("Destroy army") != string::npos || actionone.find("Build City") != string::npos)
                    thisPlayer->performaction(actionone, otherPlayer);

                if (actiontwo.find("Destroy army") != string::npos || actiontwo.find("Build City") != string::npos)
                    thisPlayer->performaction(actiontwo, otherPlayer);

                
                cout << "\n\n";
                thisPlayer->display();
                return;
            }

        }
            


        else if (cards[i]->action.find("OR") != string::npos)
        {
            if (cards[i]->action.find("Destroy army") != string::npos && !foundDestroyArmy) {
                destroyArmyIndex = i;
                foundDestroyArmy = true;
            }
            else if (cards[i]->action.find("Build City") != string::npos && !foundDestroyArmy) {
                buildCityIndex = i;
                foundBuildCity = true;
            }
        }
        else if (cards[i]->action.find("Destroy army") != string::npos && !foundDestroyArmy) {
            destroyArmyIndex = i;
            foundDestroyArmy = true;
        }
        else if (cards[i]->action.find("Build City") != string::npos && !foundDestroyArmy) {
            buildCityIndex = i;
            foundBuildCity = true;
        }

    }
    if (foundDestroyArmy) {
        cost = thisPlayer->hand->getCardCost(destroyArmyIndex);
        if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
        {
            Card card = thisPlayer->hand->exchange(destroyArmyIndex);
            thisPlayer->handList->push_back(make_pair(card.toString(), destroyArmyIndex + 1));

            thisPlayer->setlastCard(card);
            //PHASE-OBSERVER
            thisPlayer->notify("cardpicked");

            thisPlayer->performgood(card.good);
            thisPlayer->performaction("Destroy army", otherPlayer);

            cout << "\n\n";
            thisPlayer->display();
            return;
        }

    }
    if (foundBuildCity) {
        cost = thisPlayer->hand->getCardCost(buildCityIndex);
        if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
        {
            Card card = thisPlayer->hand->exchange(buildCityIndex);
            thisPlayer->handList->push_back(make_pair(card.toString(), buildCityIndex + 1));

            thisPlayer->setlastCard(card);
            //PHASE-OBSERVER
            thisPlayer->notify("cardpicked");

            thisPlayer->performgood(card.good);
            thisPlayer->performaction("Build City", otherPlayer);

            cout << "\n\n";
            thisPlayer->display();
            return;
        }

    }
    else 
    {
        Card card = thisPlayer->hand->exchange(0);
        thisPlayer->setlastCard(card);
        thisPlayer->handList->push_back(make_pair(card.toString(), 1));

        //PHASE-OBSERVER
        thisPlayer->notify("cardpicked");
        
        thisPlayer->performgood(card.good);

        //Left the below commented line delibrately
        //if we don't find any valid card with action which is build city or destroy army,
        //we will take the first card but wont play the action  
        //thisPlayer->performaction(cards[0]->action, otherPlayer);

        cout << "\n\n";
        thisPlayer->display();
        return;
    }
}

bool ModerateStrategy::tryMoveOverLand(int numOfArmies, Player* thisPlayer) {
    bool doneMovingbyLand = false;
    for (int j = 0; j < thisPlayer->graph->V; j++) // itrating over all teritory to find the region which is not owned by the current player
    {
        if (thisPlayer->graph->arr[j].t->getOwner() != thisPlayer->getname())
        {

            AdjlistNode* itr = thisPlayer->graph->arr[j].head;
            while (itr != NULL)
            {
                if (!itr->type) {

                    doneMovingbyLand = thisPlayer->MoveArmies(numOfArmies, itr->id, j);
                    if (doneMovingbyLand) {
                        cout << "\n\n---Armies successfully moved by Land from id: " << itr->id << " to " << j << ".---\n\n";
                        break;
                    }
                }
                itr = itr->next;
            }
        }
        if (doneMovingbyLand) break;
    }
    return doneMovingbyLand;
}

bool ModerateStrategy::tryPlaceNewArmies(int numOfArmies, Player* thisPlayer)
{
    bool donePlacingNewArmies = false;
    for (int j = 0; j < thisPlayer->graph->V; j++) // itrating over all teritory to find the region which is not owned by the current player
    {
        if (thisPlayer->graph->arr[j].t->getOwner() != thisPlayer->getname())
        {
            donePlacingNewArmies = thisPlayer->PLaceNewArmies(numOfArmies, j);
            if (donePlacingNewArmies) break;
        }
    }
    return donePlacingNewArmies;
}

bool ModerateStrategy::tryMoveOverWater(int numOfArmies, Player* thisPlayer)
{
    bool doneMovingbyWater = false;
    for (int j = 0; j < thisPlayer->graph->V; j++) // itrating over all teritory to find the region which is not owned by the current player
    {
        if (thisPlayer->graph->arr[j].t->getOwner() != thisPlayer->getname())
        {

            AdjlistNode* itr = thisPlayer->graph->arr[j].head;
            while (itr != NULL)
            {
                if (itr->type) {

                    doneMovingbyWater = thisPlayer->MoveArmies(numOfArmies / 3, itr->id, j); // trying moving by water
                    if (doneMovingbyWater) {
                        cout << "\n\n---Armies successfully moved over Water from id: " << itr->id << " to " << j << ".---\n\n";
                        break;
                    }
                }
                itr = itr->next;
            }
        }
        if (doneMovingbyWater) break;
    }
    return doneMovingbyWater;
}

void ModerateStrategy::execute(Player* thisPlayer, Player* otherPlayer) {

    string action = "";
    int cost = 0;
    bool doneAction1 = false;
    bool doneAction2 = false;
    bool doneMovingbyLand = false;
    bool doneMovingbyWater = false;
    bool donePlacingNewArmies = false;
    bool paid = false;
    thisPlayer->hand->Show();
    vector <Card*> cards = thisPlayer->hand->getFaceUpCards();

    for (int i = 0; i < 6; i++) {
        action = cards[i]->action;
        cost = thisPlayer->hand->getCardCost(i);

        if (cost > thisPlayer->getmoney())
            continue;

        if (action.find("AND") != string::npos)
        {
            string actionone = action.substr(0, action.find("AND") - 1);
            string actiontwo = action.substr(action.find("AND") + 4);
            if (actionone.find("Move over land/water") != string::npos && thisPlayer->armyList->size() > 0) // first trying moving by water , if not possible then trying moving by land
            {
                int numOfarmies = stoi(actionone.substr(0, 1));
                if (paid || thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    if (thisPlayer->armyList->size() > 2)
                        doneMovingbyWater = tryMoveOverWater(numOfarmies, thisPlayer);

                    if (!doneMovingbyWater) // if moving by water was not possible then trying moving by land
                    {
                        doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);
                    }

                }
                doneAction1 = true;
            }

            else if (actionone.find("Move armies over land") != string::npos && thisPlayer->armyList->size() > 0)
            {

                if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    int numOfarmies = stoi(actionone.substr(0, 1));
                    doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);

                }
                doneAction1 = true;
            }

            else if (actionone.find("Place new armies") != string::npos)
            {
                if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    int numOfarmies = stoi(actionone.substr(0, 1));
                    donePlacingNewArmies = tryPlaceNewArmies(numOfarmies, thisPlayer);

                }
                doneAction1 = true;
            }


            // executing action two
            if (actiontwo.find("Move over land/water") != string::npos && thisPlayer->armyList->size() > 0) // first trying moving by water , if not possible then trying moving by land
            {
                int numOfarmies = stoi(actiontwo.substr(0, 1));
                if (paid || thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;

                    if (thisPlayer->armyList->size() > 2) {

                        doneMovingbyWater = tryMoveOverWater(numOfarmies, thisPlayer);

                    }
                    if (!doneMovingbyWater) // if moving by water was not possible then trying moving by land
                    {

                        doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);
                    }

                }
                doneAction2 = true;
            }
            else if (actiontwo.find("Move armies over land") != string::npos && thisPlayer->armyList->size() > 0)
            {
                if (paid || thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    int numOfarmies = stoi(actiontwo.substr(0, 1));
                    doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);

                }
                doneAction2 = true;

            }

            else if (paid && actiontwo.find("Place new armies") != string::npos)
            {
                if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    int numOfarmies = stoi(actiontwo.substr(0, 1));
                    donePlacingNewArmies = tryPlaceNewArmies(numOfarmies, thisPlayer);
                }
                doneAction2 = true;
            }



            if (!doneAction1 && doneAction2) {
                thisPlayer->performaction(actionone, otherPlayer);
            }
            if (!doneAction2 && doneAction1) {
                thisPlayer->performaction(actiontwo, otherPlayer);
            }

        }

        if (action.find("OR") != string::npos && (!doneAction1 && !doneAction2))
        {
            doneAction1 = doneAction2 = doneMovingbyLand = doneMovingbyWater = donePlacingNewArmies = false;
            string actionone = action.substr(0, action.find("AND") - 1);
            string actiontwo = action.substr(action.find("AND") + 4);

            if (action.find("Move armies over land") != string::npos && thisPlayer->armyList->size() > 0)
            {
                if (actionone.find("Move armies over land") != string::npos)
                {
                    if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                    {
                        paid = true;
                        int numOfarmies = stoi(actionone.substr(0, 1));
                        doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);

                    }
                    doneAction1 = true;
                }
                else
                {
                    if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                    {
                        paid = true;
                        int numOfarmies = stoi(actiontwo.substr(0, 1));
                        doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);

                    }
                    doneAction2 = true;
                }
            }

            else if (action.find("Place new armies") != string::npos)
            {
                if (actionone.find("Place new armies") != string::npos)
                {
                    if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                    {
                        paid = true;
                        int numOfarmies = stoi(actionone.substr(0, 1));
                        donePlacingNewArmies = tryPlaceNewArmies(numOfarmies, thisPlayer);

                    }
                    doneAction1 = true;
                }
                else
                {
                    if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                    {
                        paid = true;
                        int numOfarmies = stoi(actiontwo.substr(0, 1));
                        donePlacingNewArmies = tryPlaceNewArmies(numOfarmies, thisPlayer);

                    }
                    doneAction2 = true;
                }
            }

            else if (action.find("Move over land/water") != string::npos && thisPlayer->armyList->size() > 0)
            {
                if (actionone.find("Move over land/water") != string::npos)
                {
                    int numOfarmies = stoi(actionone.substr(0, 1));
                    if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                    {
                        paid = true;
                        if (thisPlayer->armyList->size() > 2)
                            doneMovingbyWater = tryMoveOverWater(numOfarmies, thisPlayer);

                        if (!doneMovingbyWater) // if moving by water was not possible then trying moving by land
                        {
                            doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);
                        }

                    }
                    doneAction1 = true;
                }
                else
                {
                    int numOfarmies = stoi(actiontwo.substr(0, 1));
                    if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                    {
                        paid = true;

                        if (thisPlayer->armyList->size() > 2)
                            doneMovingbyWater = tryMoveOverWater(numOfarmies, thisPlayer);

                        if (!doneMovingbyWater) // if moving by water was not possible then trying moving by land
                        {
                            doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);
                        }

                    }
                    doneAction2 = true;
                }
            }


        }
        
        if (!doneAction1 && !doneAction2)
        {
            if (action.find("Move armies over land") != string::npos && thisPlayer->armyList->size() > 0)
            {
                if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    int numOfarmies = stoi(action.substr(0, 1));
                    doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);

                }
                doneAction1 = true;
            }
            if (action.find("Place new armies") != string::npos)
            {

                if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;
                    int numOfarmies = stoi(action.substr(0, 1));
                    donePlacingNewArmies = tryPlaceNewArmies(numOfarmies, thisPlayer);

                }
                doneAction1 = true;
            }
            if (action.find("Move over land/water") != string::npos && thisPlayer->armyList->size() > 0)
            {
                int numOfarmies = stoi(action.substr(0, 1));
                if (thisPlayer->PayCoin(cost)) // checking if the player has enough money to pay the amount 
                {
                    paid = true;

                    if (thisPlayer->armyList->size() > 2)
                        doneMovingbyWater = tryMoveOverWater(numOfarmies, thisPlayer);

                    if (!doneMovingbyWater) // if moving by water was not possible then trying moving by land
                    {
                        doneMovingbyLand = tryMoveOverLand(numOfarmies, thisPlayer);
                    }

                }
                doneAction1 = true;
            }

        }

        if (doneAction1 || doneAction2) {
            Card card = thisPlayer->hand->exchange(i);
            thisPlayer->handList->push_back(make_pair(card.toString(), i + 1));
            thisPlayer->setlastCard(card);

            //PHASE-OBSERVER
            thisPlayer->notify("cardpicked");

            thisPlayer->performgood(card.good);

            cout << "\n\n";
            thisPlayer->display();
            return;
        }
    }
    if (!doneAction1 && !doneAction2)
    {
        Card card = thisPlayer->hand->exchange(0);
        thisPlayer->handList->push_back(make_pair(card.toString(), 1));
        thisPlayer->setlastCard(card);

        //PHASE-OBSERVER
        thisPlayer->notify("cardpicked");

        thisPlayer->performgood(card.good);

        //Left the below commented line delibrately
        //if we don't find any valid card action
        //we will take the first card but wont play the action  
        //thisPlayer->performaction(action, otherPlayer);

        cout << "\n\n";
        thisPlayer->display();
        return;
    }
}