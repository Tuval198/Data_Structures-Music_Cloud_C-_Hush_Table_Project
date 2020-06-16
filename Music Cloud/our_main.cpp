#include <iostream>
#include <stdlib.h>     /* srand, rand */

#include "SongSystem.h"

void AvlInsertTemp();

void ArtistTest();

void TestSystem();

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
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    //AvlTest();

    //AvlGetKTest();
    //AvlInsertZerosTest();

    //AvlInsertTest();
    //AvlInsertTemp();

    //ArtistTest();

    TestSystem();
    return 0;
}

void TestSystem() {
    SongSystem s;
    for(int i = 1; i<1002; i++){
        s.AddArtist(i);
        std::cout << "artist" << i << "inserted"<< std::endl;
    }
    std::cout << "Hash size should be 10000, hash size : "<< s.GetHashSize() << std::endl;
    s.AddSong(970,1);
    s.AddSong(970,2);
    s.AddSong(970,4);
    s.AddSong(971,4);
    s.AddSong(972,1);

    s.AddToSongCount(970,1,50);
    s.AddToSongCount(970,4,50);
    s.AddToSongCount(971,4,30);

    int artist, song;
    s.GetRecommendedSongInPlace(1,&artist,&song);
    std::cout << "(should be 970,1)first rank: "<< artist << ","<<song << std::endl;
    s.GetRecommendedSongInPlace(2,&artist,&song);
    std::cout << "(should be 970,4)second rank: "<< artist << ","<<song << std::endl;
    s.GetRecommendedSongInPlace(3,&artist,&song);
    std::cout << "(should be 971,4)third rank: "<< artist << ","<<song << std::endl;
    s.GetRecommendedSongInPlace(4,&artist,&song);
    std::cout << "(should be 970,2)fourth rank: "<< artist << ","<<song << std::endl;

    s.PrintAllSongAvl();

    for(int i = 1; i<960; i++){
        try {
            s.RemoveArtist(i);
        }
        catch(ArtistHash::CanNotDeleteArtistWithSong){
            std::cout << "exeption thrown trying to remove: "<< i << std::endl;
        }
    }
    std::cout << "Hash size should be 100, hash size : "<< s.GetHashSize() << std::endl;

    s.RemoveSong(970,2);
    s.GetRecommendedSongInPlace(4,&artist,&song);
    std::cout << "(should be 972,1)fourth rank: "<< artist << ","<<song << std::endl;

//    for(int i = 1; i<960; i++){
//        try {
//            s.RemoveArtist(i);
//        }
//        catch(ArtistHash::CanNotDeleteArtistWithSong){
//            std::cout << "exeption thrown trying to remove: "<< i << std::endl;
//        }
//    }
}

