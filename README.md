
*******************Assignment-1:Storage Manager*******************


*Kavya Goli            - A20392402
*Nivedita Merla     - A20391011
*Sohan Manohar Patil - A20389075

**************Function Description***************

createPageFile
1. Create a new page file using fopen function by name pointed by fileName pointer.
2. Check if the file pointer fp is properly initialized.
3. Fill this single page with ’\0’ bytes.
4. Close the file.

openPageFile 
1. Opens an existing page file and if the file does not exist return RC_FILE_NOT_FOUND.
2. If opening this file is successful, then initialise all fields of file handle with information about the opened file.
3. After successful initialization, return RC_OK. 

closePageFile
1. Close a page file opened in openPageFile function.
2. After successful closing of file return RC_OK.

destroyPageFile
1. Deletes a page file pointed to by fileName.
2. After successful deletion of file return RC_OK. 

readBlock
1. Check if the pageNum passed as parameter to this function is greater than totalNumPages stored in file handle. If it’s greater then return error RC_READ_NON_EXISTING_PAGE.
2. If pageNum is smaller or equal to totalNumPage then move the file pointer to desire position to read pageNumth block.
3.Read the pageNumth block and store its content in the memory pointed to by the memPage page handle.
4. Update the curPagePos field.
5. After successful reading return RC_OK.

getBlockPos
1. Return current page position in file.

readFirstBlock
1. Move the file pointer to the beginning of the file using fseek.
2. Read the first block of size PAGE_SIZE.
3. Update the curPagePos field. 
4. After successful reading of first block return RC_OK.

readPreviousBlock
1. Check if the curPagePos is greater than 0. If its not then return error RC_READ_NON_EXISTING_PAGE.
2. If curPagePos is valid, then move the file pointer to desire position.
3. Read the previous block and update the curPagePos.
4. After successful reading of block return RC_OK.

readCurrentBlock
1. Move the file pointer to current block.
2. Read the current block and update the curPagePos field.
3. After successful reading of current block return RC_OK.

readNextBlock
1. Check if the curPagePos is not pointing to last page. If it is, then return error RC_READ_NON_EXISTING_PAGE.
2. If curPagePos is valid, then move the file pointer to desire position to read next block.
3. Read the next block and update the curPagePos field.
4. After successful reading of block return RC_OK.

readLastBlock
1. Move the file pointer to last block using fseek.
2. Read the last block and update the curPagePos field.
3. After successful reading of first block return RC_OK. 

writeBlock
1. Check if the pageNum passed as parameter to this function is greater than totalNumPages stored in file handle. If it’s greater then return error RC_WRITE_FAILED.
2. If pageNum is smaller or equal to totalNumPage then move the file pointer to desire position to write a block.
3. Write a block of size PAGE_SIZE stored in the memory pointed to by the memPage page handle.
4. Update the curPagePos field.
5. After successful writing return RC_OK.

writeCurrentBlock
1. Move the file pointer to current page position.
2. Write a block and update the curPagePos field.
3. After successful writing of current block return RC_OK.

appendEmptyBlock
1. Append a new page file at the end of already opened page file.
2. Fill this new page with zero bytes.
3. Update the file handle fields.
4. Return RC_OK.

ensureCapacity
1. Check if the numberOfPages passed as parameter to this method is greater than totalNumPages of opened file.
2. If it is greater, then increase the totalNumPages of opened file to numberOfPages by appending empty block to file.
3. After increasing the capacity return RC_OK.

