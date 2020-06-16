//
// Created by Administrator on 13/06/2020.
//

#include "SongSystem.h"


void SongSystem::AddArtist(int artist_id) {
    artist_hash.InsertArtist(artist_id);
}


void SongSystem::RemoveArtist(int artist_id) {
    artist_hash.DeleteArtist(artist_id);
}

void SongSystem::AddSong(int artist_id, int song_id) {
    artist_hash.AddSong(artist_id,song_id);

    SongData sd;
    sd.streams = 0;
    sd.artist_id = artist_id;
    sd.song_id = song_id;
    all_song_avl.insert(sd,sd);
}

void SongSystem::RemoveSong(int artist_id, int song_id) {
    Artist *a = artist_hash.find(artist_id);
    int streams = a->GetSongStreams(song_id);

    artist_hash.RemoveSong(artist_id,song_id);

    SongData sd;
    sd.streams = streams;
    sd.artist_id = artist_id;
    sd.song_id = song_id;

    all_song_avl.remove(sd);

}

void SongSystem::AddToSongCount(int artist_id, int song_id, int count) {
    Artist *a = artist_hash.find(artist_id);
    int streams = a->GetSongStreams(song_id);

    a->AddToSongCount(song_id,count);

    //take old song from avl:
    SongData sd;
    sd.streams = streams;
    sd.artist_id = artist_id;
    sd.song_id = song_id;

    all_song_avl.remove(sd);

    //put the song again inside avl with new amount of streams:
    SongData new_sd;
    new_sd.streams = streams + count;
    new_sd.artist_id = artist_id;
    new_sd.song_id = song_id;

    all_song_avl.insert(new_sd,new_sd);

}

void SongSystem::GetArtistBestSong(int artist_id, int *song_id) {
    *song_id = artist_hash.GetBestSongId(artist_id);
}

void
SongSystem::GetRecommendedSongInPlace(int rank, int *artist_id, int *song_id) {

    SongData sd = all_song_avl.getRank(rank);
    *artist_id = sd.artist_id;
    *song_id = sd.song_id;
}


