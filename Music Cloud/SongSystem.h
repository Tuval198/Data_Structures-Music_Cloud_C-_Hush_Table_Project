#ifndef WET2_SONGSYSTEM_H
#define WET2_SONGSYSTEM_H

#include "AVL.hpp"
#include "ArtistHash.h"
#include <iostream>

class SongData {
public:
    int song_id;
    int artist_id;
    int streams;

    friend std::ostream& operator<<(std::ostream& os, const SongData& sd);

};

inline std::ostream& operator<<(std::ostream& os,const SongData& sd)
{
    os <<"("<<sd.streams<<","<< sd.artist_id<<","<<sd.song_id<<")" ;
    return os;
}

inline bool operator==(const SongData& s1,const SongData& s2){
    return s1.song_id == s2.song_id && s1.artist_id == s2.artist_id &&
            s1.streams == s2.streams;
}
inline bool operator<(const SongData& s1,const SongData& s2){
    //return true if s1<s2
    if(s1.streams > s2.streams)  return true;
    else if (s1.streams < s2.streams) return false;
    else{
        if(s1.artist_id < s2.artist_id) return true;
        else if(s1.artist_id > s2.artist_id) return false;
        else{
            if(s1.song_id < s2.song_id)return true;
            else
                return false;
        }
    }
}



class SongSystem {
private:
    AVL<SongData,SongData> all_song_avl;
    ArtistHash artist_hash;

public:
    SongSystem() = default;
    ~SongSystem() = default;
    void AddArtist(int artist_id);
    void RemoveArtist(int artist_id);
    void AddSong(int artist_id, int song_id);
    void RemoveSong(int artist_id, int song_id);
    void AddToSongCount(int artist_id, int song_id,int count);
    void GetArtistBestSong(int artist_id, int *song_id);
    void GetRecommendedSongInPlace(int rank,int *artist_id, int *song_id);

    int GetHashSize(){return artist_hash.GetSize();}
    void PrintAllSongAvl(){all_song_avl.printInOrder();}


};


#endif //WET2_SONGSYSTEM_H
