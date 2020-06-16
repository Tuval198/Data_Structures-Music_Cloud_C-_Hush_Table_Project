//
// Created by Administrator on 14/06/2020.
//
#include "library2.h"
#include "SongSystem.h"


void *Init() {
    try{
        SongSystem *DS = new SongSystem();
        return (void*)DS;
    }
    catch(std::bad_alloc& ba){
        return NULL;
    }
}

StatusType AddArtist(void *DS, int artistID) {
    if(artistID <=0 || DS ==NULL) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->AddArtist(artistID);

    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (ArtistHash::ArtistAlreadyExist){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveArtist(void *DS, int artistID) {
    if(artistID <=0 || DS ==NULL) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->RemoveArtist(artistID);

    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (ArtistHash::ArtistDoesNotExist){
        return FAILURE;
    }
    catch (ArtistHash::CanNotDeleteArtistWithSong){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddSong(void *DS, int artistID, int songID) {
    if(artistID <=0 || songID<=0 || DS ==NULL) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->AddSong(artistID,songID);

    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (ArtistHash::ArtistDoesNotExist){
        return FAILURE;
    }
    catch (Artist::SongAlreadyExists){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveSong(void *DS, int artistID, int songID) {
    if(artistID <=0 || songID<=0 || DS ==NULL) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->RemoveSong(artistID,songID);
    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (ArtistHash::ArtistDoesNotExist){
        return FAILURE;
    }
    catch (Artist::SongDoesNotExist){
        return FAILURE;
    }
    return SUCCESS;
}


StatusType AddToSongCount(void *DS, int artistID, int songID, int count) {
    if(artistID <=0 || songID<=0 || DS ==NULL || count<=0) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->AddToSongCount(artistID,songID,count);

    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (ArtistHash::ArtistDoesNotExist){
        return FAILURE;
    }
    catch (Artist::SongDoesNotExist){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetArtistBestSong(void *DS, int artistID, int *songId) {
    if(artistID <=0 || songId==NULL || DS ==NULL) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->GetArtistBestSong(artistID,songId);
    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (ArtistHash::ArtistDoesNotExist){
        return FAILURE;
    }
    catch (Artist::ArtistHasNoSongs){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType
GetRecommendedSongInPlace(void *DS, int rank, int *artistId, int *songId) {
    if(artistId == NULL|| songId==NULL || DS ==NULL || rank<=0) return INVALID_INPUT;
    try{
        SongSystem *temp = (SongSystem*)DS;
        temp->GetRecommendedSongInPlace(rank,artistId,songId);
    }
    catch(std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    catch (AVL<SongData,SongData>::TreeIsTooSmall){
        return FAILURE;
    }

    return SUCCESS;
}

void Quit(void **DS) {
    SongSystem* temp = (SongSystem*)(*DS);
    delete temp;
    *DS = NULL;
}
