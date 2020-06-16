#ifndef WET2_ARTIST_H
#define WET2_ARTIST_H

#include "AVL.hpp"

const int NO_SONGS = -1;

class Song{
public:
    int id;
    int streams;
   // bool operator<(const Song& s1,const Song& s2);
    //bool operator==(const Song& s1,const Song& s2);
};
inline bool operator==(const Song& s1,const Song& s2){
    return s1.id == s2.id && s1.streams == s2.streams;
}
inline bool operator<(const Song& s1,const Song& s2){
    //return true if s1<s2
    if(s1.streams>s2.streams) return true;
    if(s2.streams>s1.streams) return false;
    if(s1.streams == s2.streams) return s1.id<s2.id;
}

class Artist{
private:
    int id;
    int best_song_id;
    int best_song_streams;

    AVL<Song,int>* song_avl_id;
    AVL<Song,Song>* song_avl_streams;

    Artist *next;

    void UpdateBestSong();
public:
    Artist(int id);
    ~Artist();
    void AddSong(int song_id);
    void RemoveSong(int song_id);
    void AddToSongCount(int song_id, int count);
    int GetBestSong(){if(best_song_id == NO_SONGS) throw ArtistHasNoSongs();
        return best_song_id;}
    bool HasNoSongs(){return song_avl_id->avlIsEmpty();}

    Artist* GetNext(){return next;}
    void SetNext(Artist* a){next = a;}
    int GetId(){return id;}

    int GetSongStreams(int song_id);

    void PrintArtist();
    class SongAlreadyExists{};
    class SongDoesNotExist{};
    class ArtistHasNoSongs{};
};

#endif //WET2_ARTIST_H
