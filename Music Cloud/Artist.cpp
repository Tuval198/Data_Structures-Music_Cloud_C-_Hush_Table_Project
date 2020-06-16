#include "Artist.h"
#include <iostream>

Artist::Artist(int id):id(id),
                        best_song_id(NO_SONGS),
                        best_song_streams(NO_SONGS),
                        song_avl_id(new AVL<Song,int>()),
                        song_avl_streams(new AVL<Song,Song>()),
                        next(NULL) {}

Artist::~Artist() {
    delete song_avl_id;
    delete song_avl_streams;
}


void Artist::AddSong(int song_id) {
    if(song_avl_id->exists(song_id)) throw SongAlreadyExists();

    Song s;
    s.id = song_id;
    s.streams = 0;

    song_avl_id->insert(s,song_id);
    song_avl_streams->insert(s,s);

    UpdateBestSong();
}

void Artist::UpdateBestSong() {
    if(song_avl_id->avlIsEmpty()) {
        best_song_id = NO_SONGS;
        best_song_streams = NO_SONGS;
        return;
    };
    Song s = song_avl_streams->getRank(1);
    best_song_id = s.id;
    best_song_streams = s.streams;
}

void Artist::RemoveSong(int song_id) {
    if(!song_avl_id->exists(song_id)) throw SongDoesNotExist();

    Song s = song_avl_id->find(song_id);

    song_avl_streams->remove(s);
    song_avl_id->remove(song_id);

    UpdateBestSong();
}

void Artist::AddToSongCount(int song_id, int count) {
    if(!song_avl_id->exists(song_id)) throw SongDoesNotExist();

    Song s = song_avl_id->find(song_id);
    int old_streams = s.streams;

    song_avl_streams->remove(s);
    song_avl_id->remove(song_id);

    Song new_s;
    new_s.id = song_id;
    new_s.streams = old_streams + count;

    song_avl_id->insert(new_s,song_id);
    song_avl_streams->insert(new_s,new_s);

    UpdateBestSong();
}

void Artist::PrintArtist() {
    std::cout << "artist id:"<< id<< std::endl;
    std::cout << "(best songs, streams): ("<< best_song_id << ","<< best_song_streams<< ")" << std::endl;

    std::cout << "avl by id:"<< std::endl;
    song_avl_id->printInOrder();

    //std::cout << "avl by streams:"<< std::endl;

}

int Artist::GetSongStreams(int song_id) {
    if(!song_avl_id->exists(song_id)) throw SongDoesNotExist();
        //added by yuval
    Song s = song_avl_id->find(song_id);
    return s.streams;
}
