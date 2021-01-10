/*
 * author:  Alexander Grill
 * file:    Elves.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "Elves.h"

#include "rang.hpp"

#include <thread>
#include <random>
#include <iostream>

using namespace std;
using namespace rang;

void Elves::tinker(){
    while (sc->get_readytofly() == false){
        unique_lock<mutex> ulh{mxe};
        if(elves != 3){
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0.5, 1.2};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            elves += 1;
            cout << fg::cyan << elves << " Elves need help\n" << flush;
        }

        if (elfTex.wait_for(ulh, 1s, [&] { return sc->get_readytohelp() == true; })){
            cout << "quetsch" << endl;
            getHelp();
            return;
        }
        if(elves == 3 && !elves_ready){
            sc->set_doaction();
            cout << "hello elves " << endl;
            sc->santaSem.notify_one();
            elves_ready = true;
        }
    }
}

void Elves::getHelp(){
    while (elves >= 0){
        cout << "sasas" << endl;
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{0.1, 1.5};
        double time = dis(gen);
        int t = time * 1000;
        this_thread::sleep_for(chrono::milliseconds(t));
        cout << fg::cyan << (elves - 3) * -1 << " elves helped\n"<< flush;
        elves -= 1;
    }
}

int Elves::getElves(){
    return elves;
}

void Elves::setSanta(SantaClaus* s){
    sc = s;
}