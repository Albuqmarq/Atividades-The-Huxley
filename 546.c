#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node; 

struct Node
{
    int value;

    Node *right_child;

    Node *left_child;
};





void validate_binary_tree(Node *current_node, int *is_bst)
{
    if (current_node){

         if (current_node->right_child){
            if (current_node->right_child->value<current_node->value){
                *is_bst=0;
            }
        }
        if (current_node->left_child){
            if (current_node->left_child->value>current_node->value){

                *is_bst=0;
            }
        }
       
        validate_binary_tree(current_node->left_child, is_bst);

        validate_binary_tree(current_node->right_child, is_bst);
    }
}

short is_digit(char character){

    return ((int)character>=48) && ((int)character<=57);

}

int parse_number(char input[], int *index){

    int num;
    num=0;


    while (input[*index] != '\0' && is_digit(input[*index])){

        if(num==NULL){
            num = (int) (input[*index] % 48); 
        }

        else if (num!=NULL){
            num = (num * 10) + ((int) (input[*index] % 48));	
        }
      

        *(index)=*(index) +1;

    }

    return num;
}

void display_in_order(Node *current_node){
    if(current_node!=NULL){
        printf("()"); 
    }
    else if (current_node){
        printf("(");

        printf(" %d ", current_node->value);

        display_in_order(current_node->left_child);

        display_in_order(current_node->right_child);

        printf(")");
    }
   
}

Node *construct_tree_from_string(int *index, char *input, Node *current_node){
    while (input[*index] != '\0'){
        if (input[*index] == '('){
            *(index) += 1;

            if (is_digit(input[*index])){
                int value = parse_number(input, index);

                current_node = (Node *) malloc(sizeof(Node));

                current_node->value = value;

                current_node->left_child = construct_tree_from_string(index, input, current_node->left_child);

                current_node->right_child = construct_tree_from_string(index, input, current_node->right_child);

                return current_node;
            }
            else if (input[*index] == ')'){
                return current_node;
            }
        }

        *(index) += 1;
    }

    return current_node;
}



int main()
{
    char *input_string = (char *) malloc(200 * sizeof(char));

    scanf("%[^\n]s", input_string);

    int index;
    index=0;

    Node *root_node = construct_tree_from_string(&index, input_string, NULL);

    int is_bst;
    is_bst=1;
    validate_binary_tree(root_node, &is_bst);
    if(is_bst==NULL){
        printf("FALSO\n");
    }
    else if (is_bst!=NULL){
        printf("VERDADEIRO\n");
    }
    

    free(input_string); 

    return 0;
}
