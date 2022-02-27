    #include<stdio.h>  
    #include<stdbool.h>  
    #include<stdlib.h>
    #include<unistd.h>
    typedef struct __s_block{  
        struct __s_block *next;  
        bool isfree;  
        size_t size;  
        void *memoryAddress;  
    }_SBLOCK;   
    #define BLOCK_SIZE sizeof(_SBLOCK)  

    _SBLOCK *allocateMemBlock(size_t size)  
    {  
        _SBLOCK *block = (_SBLOCK*)sbrk(0);  
        void *memadr = (void*)sbrk(0);  
        void *allocate_mem = (void*)sbrk(BLOCK_SIZE + size);  
      
        if(allocate_mem == (void*)-1){  
            return NULL;  
        }else{  
            block->next = NULL;  
            block->isfree = false;  
            block->size = size;  
            block->memoryAddress = memadr+BLOCK_SIZE;  
            return block;  
        }  
    }  
      
    //allocate next memory block  
    void allocateNextMemBlock(size_t size, _SBLOCK **head)  
    {  
        _SBLOCK *current = *head;  
        void *allocate_mem = NULL;  
        void *memadr = (void*)sbrk(0);  
      
        if(current==NULL){  
            *head = allocateMemBlock(size);  
        }else{  
            while(current->next != NULL){  
                current = current->next;  
            }  
            _SBLOCK *newblock = sbrk(0);  
      
            allocate_mem = (void*)sbrk(BLOCK_SIZE + size);        
            if(allocate_mem == (void*) - 1){ }  
            else{  
                newblock->next = NULL;  
                newblock->isfree = false;  
                newblock->size = size;  
                newblock->memoryAddress = memadr+BLOCK_SIZE;  
                current->next = newblock;  
          }  
        }  
    }  
      
      
    void freeMemBlock(_SBLOCK **head)  
    {  
        if(*head == NULL){}  
        else{  
            (*head)->isfree = true;  
        }  
    }  
     void freeNode(_SBLOCK *heada)
     { int a;
     _SBLOCK *head=heada;
            int n;
            printf("enter the block you want to free\n");
            scanf("%d",&n);
           while(n--)
           {
               head=head->next;
           } 
          freeMemBlock(&head); 
     }
      
    void printMemBlocks(_SBLOCK *current)  
    {  
        while(current != NULL){  
            printf("isfree = %d, size = %ld, memoryAddress = %p, current = %p, next-node = %p\n",  
                    current->isfree, current->size, current->memoryAddress, current, current->next);  
            current = current->next;  
        }  
    }  
    _SBLOCK *checkfree(_SBLOCK *curr,int size)
    {
        _SBLOCK *cur=curr;
        while(cur!=NULL)
        {
          if(cur->size>=size &&cur->isfree==1)
          {
              return cur;
          }
          cur=cur->next;
        }
        return NULL;
    } 
    int main()  
    {  
           char  ch;
        _SBLOCK *sMemBlock = NULL; 
        int size;
        int n;
        int a;
        
        while(1)
        {
           printf("1) WANT to enter a process\n");
        printf("2) want to display memory blocks\n");
        printf("3) want to free memory blocks\n");
         scanf("%d",&a);

            switch(a)
            {
              case 1:
         printf("enter the size of the process\n");
         scanf("%d",&size);
         if(checkfree(sMemBlock,size)!=NULL)
         {
             _SBLOCK *mem=checkfree(sMemBlock,size);
               mem->isfree=0;
         }
         else
         {
         allocateNextMemBlock(size,&sMemBlock);
         }
         break;
          case 2:
             printMemBlocks(sMemBlock); 
         break;
         case 3:
         freeNode(sMemBlock);
         break;
            }
        }   
      
        return 0;  
    }   
