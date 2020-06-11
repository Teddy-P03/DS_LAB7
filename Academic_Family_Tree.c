#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "aftree.h"

int main(){
    char* advisor, * advisee;
    int scholars, relations, i, j, k;
    scanf("%d %d",&scholars, &relations);
    char scholar[64][100];    
    linkedlist_t * ancester = linkedlist_alloc(node_t);
    for(i=0;i<relations;i++){
        int pin = 0, cin = 0;
        node_t* parent, * child;
        scanf("%s %s",advisor, advisee);

        for(j=0;strlen(scholar[j]) == 0;j++){
            if(strcmp(scholar[j],advisor) == 0){            
                pin+=1;
            }
            if(strcmp(scholar[j],advisee) == 0){            
                cin+=1;
            }
        }

        if(pin == 0){
                strcpy(scholar[j],advisor);
                parent = tree_create_node(advisor) ;
        }
        else{
            for(k=0;k<linkedlist_length(ancester);k++){
                node_t * cmp;
                linkedlist_get (ancester, k, cmp) ;
                if(tree_search (cmp, advisor) != 0x0){
                    parent = tree_search (cmp, advisor) ;
                    break;
                }
            }
        }
        if(cin == 0){
            strcpy(scholar[j],advisee);
            child = tree_create_node(advisee) ;
        }
        else{
            for(k=0;k<linkedlist_length(ancester);k++){
                node_t * cmp;
                linkedlist_get (ancester, k, cmp) ;
                if(tree_search (cmp, advisee) != 0x0){
                    child = tree_search (cmp, advisee) ;
                    break;
                }
            }
        }
        tree_add_child (parent, child) ;
        
        if(linkedlist_length(ancester) > 0){
            int ck=0;
            for(k=0;k<linkedlist_length(ancester);k++){
                node_t * cmp;
                linkedlist_remove_first (ancester, cmp) ;
                if(tree_search (cmp, advisor) != 0x0){
                    linkedlist_insert_last (ancester, cmp) ;
                    ck = 0;
                    break;
                }
                else if(tree_search (parent, cmp->data) != 0x0){
                    linkedlist_insert_last (ancester, parent) ;
                    ck = 0;
                    break;
                }
                else ck+=1;
            }
            if(ck!=0){
                linkedlist_insert_last (ancester, parent) ;
            }
        }
        else{
            linkedlist_insert_last (ancester, parent) ;
        } 
    }

    for(k=0;k<linkedlist_length(ancester);k++){
        node_t * cmp;
        linkedlist_remove_first (ancester, cmp) ;
        tree_print (cmp) ;
    }

    linkedlist_free (ancester) ;
    return 0;
}
