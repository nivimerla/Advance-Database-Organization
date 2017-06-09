# Advance-Database-Organization
--------Storage Manager CS - 525 -----------------------


Kavya Goli          - A20378676 -----------
Nivedita Merla      - A20391011 -----------
Sohan Manohar Patil - A20388048 -----------


--------------------------------------------------------

Function Description :

1. Fucntions to manipulate page file(Create,Open,Close,Destroy)

a) createPageFile():
      - Creates a new page file of 1 page(PAGE_SIZE) and fills it with '\0' bytes.
      - In this function we are using fopen() function to create the file.
      - The file is opened in the write mode so that we can fill it with '\0' bytes.

b) openPageFile():
      - Checks if the input file is present.
      - If file is present then opens the existing file or else throws an error RC_FILE_NOT_FOUND.
      - We are calculating the total number of pages by pointing the file pointer to end and then dividing it by the page size. 
      - After that we are updating the file handle with file name, total number of pages and current page position.
      
c) closePageFile():
      - Closes the already opened page file.
      - Returns RC_OK if file closes successfully else returns RC_FILE_NOT_FOUND.

d) destroyPageFile():
      - Destroys already created page file.
      - We are using remove function to destroy the file.
      - Returns RC_OK if file destroyed successfully else returns RC_FILE_NOT_FOUND. 

------------------------------------------------------------------------------------
2. Read functions :

a) readBlock():
      - Checks if the total number of pages are not greater than the page number(pageNum) from where to read.
      - If it is greater then throws an error.
      - Else we will set the pointer position to the page which we have to read.
      - then we read the block.
      - And then we set the current page position to the page number that we read.

b) getBlockPos():
      - Returning the current page position in the page file by using the data structure object fHandle.

c) readFirstBlock():
      - Checks if the data structure fHandle contains the values or not.
      - If it does then checks if the total number of pages are greater than 0.
      - If, then read the first block of the file.
      - And set the current page position to first block i.e. 0.

d) readPreviousBlock():
      - Checks if the data structure fHandle contains the values or not.
      - If it does then setting the pointer position to the previous page position.
      - If previous page position is out of boundry then throws an error.
      - Else reading the previous block of the file.
      - And setting the current page position to the previous block.

e) readCurrentBlock():
      - Checks if the data structure fHandle contains the values or not.
      - If it does then getting the current page position by calling the getBlockPos() function.
      - And then reading the current page of the file.
      - After that setting the current page position the the current block.

f) readNextBlock():
      - Checks if the data structure fHandle contains the values or not.
      - If it does then setting the pointer position to the next page position.
      - If the next block is not out of boundry.
      - then, reading the next block of the file.
      - And setting the current page position to the next block.

g) readLastBlock():
      - Checks if the data structure fHandle contains the values or not.
      - If it does then setting the pointer position to the last page position.
      - Reading the last block of the file.
      - And setting the current page position to the last block.

-------------------------------------------------------------------------------------------------------------

3. Write Functions

a) writeBlock():
      - Checks if the page number where to write is not less than 0 or not greater than total number of pages.
      - If not, then checks the data structure fHandle contains the values or not.
      - If it is Null then throws an error.
      - Else we will set the pointer position to the page where we have to write.
      - then we write the block at page number(pageNum).
      - And then we set the current page position to the page number that we just write.
      - Then we update the total number of pages.

b)writeCurrentBlock():      
      - First we get the current page position by calling the getBlockPos().
      - then we call the writeBlock() function by passing the current position in its arguments.
      - If current block is successfully written then we return RC_OK.
      - Else we return RC_WRITE_FAILED.

c)appendEmptyBlock():
      - Checks if the data structure fHandle contains the values or not.
      - if it does, then we create a buffer of PAGE_SIZE.
      - then we point the position of the file pointer to the end and we write an empty block there.
      - then we are updating the total number of pages and current page position.
    
d)ensureCapacity():
      - First we check if the total number of pages are less than the number of pages(numberOfPages) passed in the function argument.
      - If it is less, then we find how many pages we have to add.
      - we then create the remaining number of pages by running a loop and calling the appendEmptyBlock() function in the loop.
