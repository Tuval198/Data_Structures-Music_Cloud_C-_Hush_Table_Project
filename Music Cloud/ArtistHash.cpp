
#include "ArtistHash.h"

ArtistHash::ArtistHash(): artist_table(new Artist*[INITIAL_SIZE]),
                            size(INITIAL_SIZE),
                            artist_count(0){
    for(int i = 0; i<size; i++)
        artist_table[i] = NULL;
}

ArtistHash::~ArtistHash() {
    for(int i = 0; i<size; i++){
        Artist *a = artist_table[i];
        Artist *next = a;
        while(a != NULL) {
            next = a->GetNext();
            delete a;
            a = next;
        }
    }
    delete[] artist_table;
}


void ArtistHash::InsertArtist(int artist_id) {

    if(find(artist_id) != NULL) throw ArtistAlreadyExist();

    Artist *new_artist = new Artist(artist_id);
    int new_artist_place = HashFunction(artist_id);

    if(artist_table[new_artist_place] == NULL){
        artist_table[new_artist_place] = new_artist;
    }
    else{
        Artist *temp = artist_table[new_artist_place];
        new_artist->SetNext(temp);
        artist_table[new_artist_place] = new_artist;
    }

    artist_count ++;
    if(artist_count>=size) ExpandTable();
}

void ArtistHash::ExpandTable() {
    Artist **old_table = artist_table;
    artist_table = new Artist*[size*MULTIPLIER_VAL];
    int old_size = size;
    size = size*MULTIPLIER_VAL;

    for(int i = 0; i<size; i++)
        artist_table[i] = NULL;

    for(int i = 0; i<old_size; i++){
        Artist *artist_to_copy = old_table[i];
        while(artist_to_copy !=NULL){
            int new_artist_place = HashFunction(artist_to_copy->GetId());

            if(artist_table[new_artist_place] == NULL){
                artist_table[new_artist_place] = artist_to_copy;
            }
            else{
                Artist *temp = artist_table[new_artist_place];
                artist_to_copy->SetNext(temp);
                artist_table[new_artist_place] = artist_to_copy;
            }

            artist_to_copy=artist_to_copy->GetNext();
        }
    }
    delete[] old_table;
}

void ArtistHash::DeleteArtist(int artist_id) {
    Artist *to_delete = find(artist_id);
    if(to_delete == NULL) throw ArtistDoesNotExist();
    if(!to_delete->HasNoSongs()) throw CanNotDeleteArtistWithSong();

    int place = HashFunction(artist_id);
    Artist *a = artist_table[place];
    if(a == to_delete){
        artist_table[place] = a->GetNext();
    }
    else{
        while(a->GetNext() != to_delete){
            a = a->GetNext();
        }
        //a is prev to to_delete
        a->SetNext(to_delete->GetNext());
    }
    delete to_delete;

    artist_count--;
    if((double)artist_count <= (double)size * MINIMUM_LOAD_FACTOR)
        ShrinkTable();

}

Artist *ArtistHash::find(int artist_id) {
    int place = HashFunction(artist_id);
    Artist *a = artist_table[place];
    while(a!=NULL){
        if(a->GetId() == artist_id) return a;
        a = a->GetNext();
    }

    return NULL; //artist not found
}


void ArtistHash::ShrinkTable() {
    Artist **old_table = artist_table;
    artist_table = new Artist*[size/MULTIPLIER_VAL];
    int old_size = size;
    size = size/MULTIPLIER_VAL;

    for(int i = 0; i<size; i++)
        artist_table[i] = NULL;

    for(int i = 0; i<old_size; i++){
        Artist *artist_to_copy = old_table[i];
        while(artist_to_copy !=NULL){
            int new_artist_place = HashFunction(artist_to_copy->GetId());

            if(artist_table[new_artist_place] == NULL){
                artist_table[new_artist_place] = artist_to_copy;
            }
            else{
                Artist *temp = artist_table[new_artist_place];
                artist_to_copy->SetNext(temp);
                artist_table[new_artist_place] = artist_to_copy;
            }

            artist_to_copy=artist_to_copy->GetNext();
        }
    }
    delete[] old_table;
}


void ArtistHash::AddSong(int artist_id, int song_id) {
    Artist* a = find(artist_id);
    if(a == NULL) throw ArtistDoesNotExist();

    a->AddSong(song_id);
}


void ArtistHash::RemoveSong(int artist_id, int song_id) {
    Artist* a = find(artist_id);
    if(a == NULL) throw ArtistDoesNotExist();

    a->RemoveSong(song_id);
}


void ArtistHash::AddToSongCount(int artist_id, int song_id, int count) {
    Artist* a = find(artist_id);
    if(a == NULL) throw ArtistDoesNotExist();

    a->AddToSongCount(song_id,count);
}

int ArtistHash::GetBestSongId(int artist_id) {
    Artist* a = find(artist_id);
    if(a == NULL) throw ArtistDoesNotExist();

    return a->GetBestSong();
}
