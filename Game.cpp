#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <iomanip>

Game& Game::operator++(){
    incrementPlayerTurn();
    return *this;
}

Game::operator bool() const{
    return running;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os <<"Turns taken: "<<game.getPlayerTurns()
       <<"\nSuccessful hits: "<< game.getPlayerHits()
       <<"\nMisses: "<<game.getPlayerMisses()
       << "\nAccuracy: "<<std::fixed<<std::setprecision(2)<<game.getPlayerAccuracy()<<"%\n";
    return os;
}

Game::Game() : shipCount(0), playerBoard(nullptr), opponentBoard(nullptr), currentState(nullptr), running(true) {}

Game::~Game()
{
    delete playerBoard;
    delete opponentBoard;

    if (currentState)
    {
        currentState -> exit(*this);
        delete currentState;
    }
}

void Game::setShipCount(int count){
    shipCount = count;
}

int Game::getShipCount() const{
    return shipCount;
}

int Game::getBoardSize()
{
    return boardSize;
}

void Game::changeState(GameState* newState)
{
    if (currentState)
    {
        currentState -> exit(*this);
        delete currentState;
    }
    currentState = newState;
    currentState -> enter(*this);
}

void Game::run()
{
    while (*this && currentState)
    {
        currentState->update(*this);
    }
}

void Game::quit()
{
    running = false;
}

void Game::setDifficultyLevel(DifficultyLevel level)
{
    difficultyLevel = level;
}

void Game::setGameMode(GameMode mode)
{
    gameMode = mode;
}

void Game::setPlayerBoard(Board* board)
{
    if(playerBoard) { delete playerBoard; }
    playerBoard = board;
}

void Game::setOpponentBoard(Board* board)
{
    if(opponentBoard) { delete opponentBoard; }
    opponentBoard = board;
}

void Game::setBoardSize(int size)
{
    boardSize = size;
}

DifficultyLevel Game::getDifficultyLevel() const
{
    return difficultyLevel;
}

GameMode Game::getGameMode() const
{
    return gameMode;
}

Board* Game::getPlayerBoard()
{
    return playerBoard;
}

Board* Game::getOpponentBoard()
{
    return opponentBoard;
}

void Game::incrementPlayerTurn(){playerTurns++;}
void Game::incrementPlayerHit(){playerHits++;}
void Game::incrementPlayerMiss(){playerMisses++;}

int Game::getPlayerTurns() const{return playerTurns;}
int Game::getPlayerHits() const{return playerHits;}
int Game::getPlayerMisses() const{return playerMisses;}

double Game::getPlayerAccuracy() const{
    int totalShots = playerHits + playerMisses;

    if(totalShots==0) return 0.0;

    return (static_cast<double>(playerHits) / totalShots) * 100;
}

void Game::fullRestart()
{
    delete playerBoard;
    delete opponentBoard;
    playerTurns = 0;
    playerHits = 0;
    playerMisses = 0;
    shipCount = 0;
    boardSize = 0;
    difficultyLevel = Easy;
    gameMode = Standart;
}