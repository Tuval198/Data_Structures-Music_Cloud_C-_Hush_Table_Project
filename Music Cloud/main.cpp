#include <iostream>
#include <stdlib.h>     /* srand, rand */

#include "AVL.hpp"
#include "ArtistHash.h"
#include "Artist.h"
#include "SongSystem.h"

void AvlInsertTemp();

void ArtistTest();

void AvlInsertTest() {
    AVL<int> avl;

    for(int i =700; i>=500 ; i--){
        avl.insert(i,i);
    }

    for(int i =1; i<= 40; i++){
        avl.insert(i,i);
    }

    for(int i =100; i< 110; i++){
        avl.insert(i,i);
    }
    avl.printInOrder();
    for(int i =20; i<= 50; i++){
        std::cout << avl.getRank(i) << "is in " << i << " place" << std::endl;
    }
    for(int i =31; i<= 40; i++){
        avl.remove(i);
    }
    for(int i =601; i<= 700; i++){
        avl.remove(i);
    }
    avl.printInOrder();
    std::cout << "tree contains : [1,30] [100,110] [500,600] " << std::endl;
    std::cout << avl.getRank(1) << "is in " << 1 << " place" << std::endl;
    for(int i =20; i<= 50; i++){
        std::cout << avl.getRank(i) << "is in " << i << " place" << std::endl;
    }


    std::cout << "num of Nodes: " <<avl.getNodesCount()<< std::endl;
    std::cout << "height: " <<avl.getHeight()<< std::endl;
    avl.printInOrder();

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    //AvlTest();

    //AvlGetKTest();
    //AvlInsertZerosTest();

    AvlInsertTest();
    //AvlInsertTemp();

    //ArtistTest();
    return 0;
}

void ArtistTest() {
    Artist a(2);
    a.AddSong(2);
    a.AddSong(5);
    a.AddSong(1);
    a.AddToSongCount(2,6);
    a.AddToSongCount(5,9);
    a.RemoveSong(1);

    a.PrintArtist();
    a.RemoveSong(5);
    a.PrintArtist();
}

void AvlInsertTemp() {
    AVL<int> avl;

    avl.insert(24,24);
    avl.printInOrder();
    avl.insert(27,27);
    avl.printInOrder();
    avl.insert(23,23);
    avl.insert(28,28);
    avl.insert(26,26);
    avl.printInOrder();
    avl.insert(25,25);
    avl.printInOrder();
    for(int i =20; i>=6 ; i--){
        avl.insert(i,i);
        avl.printInOrder();
    }
    for(int i =1; i<=3 ; i++){
        avl.insert(i,i);
        avl.printInOrder();
    }
    for(int i =1; i<= 20; i++){
        std::cout << avl.getRank(i) << "is in " << i << " place" << std::endl;
    }

}

