#include <stdio.h>
#include <stdlib.h>
#include "storage_mgr.h"
#include "dberror.h"



void initStorageManager(void){
    printf("***Initialising Storage Manager***");
}

//Creating a Page file
RC createPageFile(char *fileName){
    FILE *fp;
    fp=fopen(fileName, "wb");
    if(fp==NULL){
        printf("unable to open file");
        return RC_FILE_NOT_FOUND;
    }
    int i;
    for(i=0;i<PAGE_SIZE;i++){
        fwrite("\0",sizeof(char),1,fp);
        
    }
    fclose(fp);
    return RC_OK; 
}

//Opening a Page file
RC openPageFile(char *fileName, SM_FileHandle *fHandle){
    FILE *fp;
    int size;
    fp=fopen(fileName,"rb+");
    if(fp==NULL){
        printf("unable to open file");
        return RC_FILE_NOT_FOUND;
    }
    fHandle->fileName =fileName;
    fHandle->curPagePos=0;
    fseek(fp, 0L, SEEK_END);
    size=ftell(fp);
   
    fHandle->totalNumPages=size/PAGE_SIZE;
    fseek(fp, 0, SEEK_SET);
    fHandle->mgmtInfo=fp;
    return RC_OK;
}

//Closing a Page file
RC closePageFile(SM_FileHandle *fHandle){
    
    fclose(fHandle->mgmtInfo);
    return RC_OK;
    
}

//Destroying a Page file
RC destroyPageFile(char *fileName){
    remove(fileName);
    return RC_OK;
}

//Reading a Block
RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage){
    if(pageNum> fHandle->totalNumPages){
      return RC_READ_NON_EXISTING_PAGE;  
    }
    fseek(fHandle->mgmtInfo, pageNum*PAGE_SIZE, SEEK_SET);
    fread((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fHandle->curPagePos=pageNum+1; 
    return RC_OK;

}


//Getting the current block position
int getBlockPos(SM_FileHandle *fHandle){
    return fHandle->curPagePos; 
}

//Reading the first block from the file
RC readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage){
    fseek(fHandle->mgmtInfo, 0, SEEK_SET);
    fread((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fHandle->curPagePos=1; 
    return RC_OK;

}

//Reading the previous block in file
RC readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage){
    if(fHandle->curPagePos<0 )
       return RC_READ_NON_EXISTING_PAGE;
    fseek(fHandle->mgmtInfo, (fHandle->curPagePos-1)*PAGE_SIZE, SEEK_SET);
    fread((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fseek(fHandle->mgmtInfo, -1*PAGE_SIZE, SEEK_CUR);
    fHandle->curPagePos=fHandle->curPagePos-1; 
    return RC_OK;

}

//Reading the current block
RC readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage){
   
    fseek(fHandle->mgmtInfo, 0, SEEK_CUR);
    fread((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fHandle->curPagePos=fHandle->curPagePos+1; 
    return RC_OK;

}

//Reading the next block in file
RC readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage){
    if(fHandle->curPagePos>fHandle->totalNumPages)
        return RC_READ_NON_EXISTING_PAGE;
    fseek(fHandle->mgmtInfo, (fHandle->curPagePos+1)*PAGE_SIZE, SEEK_SET);
    fread((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fseek(fHandle->mgmtInfo, PAGE_SIZE, SEEK_CUR);
    fHandle->curPagePos=fHandle->curPagePos+1; 
    return RC_OK;

}

//Reading the last block of the file
RC readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage){
  
    fseek(fHandle->mgmtInfo, -1*PAGE_SIZE, SEEK_END);
    fread((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fHandle->curPagePos=fHandle->totalNumPages; 
    return RC_OK;

}

//Writing block to pageNum
RC writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage){
    if(pageNum>fHandle->totalNumPages){
       return RC_WRITE_FAILED;  
    }
    fseek(fHandle->mgmtInfo, pageNum*PAGE_SIZE, SEEK_SET);
    fwrite((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fHandle->curPagePos=pageNum+1; 
    return RC_OK;
}

//Writing current block
RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage){
  
    fseek(fHandle->mgmtInfo, 0, SEEK_CUR);
    fwrite((void*)memPage, PAGE_SIZE, 1,fHandle->mgmtInfo);
    fHandle->curPagePos=fHandle->curPagePos+1; 
    return RC_OK;

}

//Appending an empty block to the file
RC appendEmptyBlock(SM_FileHandle *fHandle){
 
    if(fHandle->mgmtInfo==NULL){
        printf("unable to open file");
        return RC_FILE_NOT_FOUND;
    }
    char *newPage;
    newPage = (char *) calloc(PAGE_SIZE, sizeof(char));
    int i;
    fseek(fHandle->mgmtInfo,0L,2);
    for(i=0;i<PAGE_SIZE;i++){
        fwrite(newPage,sizeof(char),1,fHandle->mgmtInfo);
        fseek(fHandle->mgmtInfo,0L,2);
    }
    int size;
    size=ftell(fHandle->mgmtInfo);
   
    fHandle->totalNumPages=size/PAGE_SIZE;
    //fseek(fHandle->mgmtInfo, 0, SEEK_SET);
    fHandle->curPagePos = fHandle->totalNumPages - 1;
    //printf("Cur pages:%d", fHandle->curPagePos);
    free(newPage);
    return RC_OK;

}

//Ensuring capacity of the file is not less than numberOfPages
RC ensureCapacity(int numberOfPages, SM_FileHandle *fHandle){
   if(fHandle->totalNumPages< numberOfPages){
      int appendPage,i;
      appendPage=numberOfPages-fHandle->totalNumPages;
      for(i=0;i<appendPage;i++){
         appendEmptyBlock(fHandle);
        // printf("No of pages:%d", fHandle->totalNumPages);
      }
      fHandle->totalNumPages=numberOfPages;
      fHandle->curPagePos = fHandle->totalNumPages - 1;
      return RC_OK;
    }
    return RC_WRITE_FAILED;
}
