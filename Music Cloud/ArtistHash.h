
#ifndef WET2_ARTISTHASH_H
#define WET2_ARTISTHASH_H
#include "Artist.h"

const int INITIAL_SIZE = 10;
const int MULTIPLIER_VAL = 10;
const double MINIMUM_LOAD_FACTOR = 0.05;

class ArtistHash {
private:
    Artist **artist_table;
    int size;
    int artist_count;

    int HashFunction(int key){return key % size;}
    void ExpandTable();
    void ShrinkTable();
public:
    ArtistHash();
    ~ArtistHash();
    void InsertArtist(int artist_id);
    void DeleteArtist(int artist_id);
    void AddSong(int artist_id, int song_id);
    void RemoveSong(int artist_id, int song_id);
    void AddToSongCount(int artist_id, int song_id, int count);
    int GetBestSongId(int artist_id);

    //find returns pointer to Artist or NULL if does not exist
    Artist* find(int artist_id);

    int GetSize(){return size;}

    class ArtistAlreadyExist{};
    class ArtistDoesNotExist{};
    class CanNotDeleteArtistWithSong{};

};


#endif //WET2_ARTISTHASH_H
